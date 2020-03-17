//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <fstream>
#include <algorithm>
#include <SDL/SDL_image.h>
#include "Random.h"
#include "Math.h"
#include "Game.h"
#include "Actor.h"
#include "Player.h"
#include "Loser.h"
#include "Star.h"
#include "SpriteComponent.h"
#include "ProgressBar.h"
#include "PlayerMove.h"

Game::Game() {
    // set variables
    mIsRunning = true;
    mPreviousTime = SDL_GetTicks();
    renderer = NULL;
    window = NULL;
    mPlayer = NULL;
    mMusicChannel = -1;
}

// initializes game, returns true if successful
bool Game::Initialize() {
    // initialize random
    Random::Init();
    
    // initialize
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    
    // create the window
    window = SDL_CreateWindow("SDLWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    
    if(window == NULL) {
        SDL_Log("Window not successfully initialized");
        return false;
    }
    
    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // initialize SDL_Images
    IMG_Init(IMG_INIT_PNG);
    
    // initialize music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
    LoadData();
    
    return true;
}

void Game::Shutdown() {
    UnloadData();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RunLoop() {
    while(mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    // get input events
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case(SDL_QUIT):
                mIsRunning = false;
                break;
            default:
                break;
        }
    }
    
    // read keyboard inputs separately
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    
    // if showing menu to play again, handle yes (Y) and no (N)
    if(mGameOver) {
        if(state[SDL_SCANCODE_Y]) {
            // reset game
            mWin = true;
            mSunUp = false;
            mStarsDone = false;
            mGameOver = false;
            starSpriteTimer = 0.0f;
            mDayOpacity = 0.0f;
            mWarmUpTimer = 0.0f;
            
            UnloadData();
            LoadData();
        }
        else if(state[SDL_SCANCODE_N]) {
            mIsRunning = false;
        }
    }
    
    // copy actors and call process input on all
    std::vector<Actor*> copyActors = actors;
    for(Actor* a : copyActors) {
        a->ProcessInput(state);
    }
}

void Game::UpdateGame() {
    // calculate delta time
    int currentTime = SDL_GetTicks(); // in milliseconds
    float deltaTime = 0;
    while(currentTime - mPreviousTime < 16) {
        currentTime = SDL_GetTicks();
    }
    deltaTime  = std::min(33, (currentTime - mPreviousTime)) / 1000.0f; // in seconds
    mPreviousTime = currentTime;
    
    // update background to day, game stop condition
    mWarmUpTimer += deltaTime;
    if(mWarmUpTimer > TIME_WARM_UP) {
        mDayOpacity += deltaTime * 255.0f / TIME_TO_DAY;
        if(mDayOpacity > 255.0f) {
            mDayOpacity = 255.0f;
            mSunUp = true;
        }
        else {
            SDL_SetTextureAlphaMod(mBackgroundTextureDay, (int)mDayOpacity);
        }
    }
    
    // spawn new stars
    if(!mSunUp) {
        starSpriteTimer += deltaTime;
        if(starSpriteTimer > STAR_SPRITE_RATE) {
            starSpriteTimer = 0.0f;
            AddStar(new Star(this, true));
        }
    }
    
    // stop player moving if all stars completely gone
    if(mSunUp && mStars.size() == 0) {
        mStarsDone = true;
        if(mPlayer->DidWin(STARS_TO_WIN)) {
            mWin = true;
        }
        else {
            mWin = false;
        }
    }
    
    // make a copy of actors vector and update
    std::vector<Actor*> copyActors = actors;
    for(Actor* a : copyActors) {
        a->Update(deltaTime);
    }
    
    // find actors to destroy
    std::vector<Actor*> actorsToDestroy;
    for(Actor* a : copyActors) {
        if(a->GetState() == ActorState::Destroy) {
            actorsToDestroy.push_back(a);
        }
    }
    
    // destroy actors to destroy
    for(Actor* a : actorsToDestroy) {
        delete a;
    }
}

void Game::GenerateOutput() {
    // clear the entire screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    
    // draw game objects
    for(SpriteComponent* s : mSprites) {
        if(s->IsVisible()) {
            s->Draw(renderer);
        }
    }
    
    // present to user/screen
    SDL_RenderPresent(renderer);
}

void Game::AddActor(Actor* a) {
    actors.push_back(a);
}

void Game::RemoveActor(Actor* a) {
    std::vector<Actor*>::iterator it = std::find(actors.begin(), actors.end(), a);
    if(it != actors.end()) {
        actors.erase(it);
    }
}

void Game::AddStar(Star* s) {
    mStars.push_back(s);
}

void Game::RemoveStar(Star* s) {
    std::vector<Star*>::iterator it = std::find(mStars.begin(), mStars.end(), s);
    if(it != mStars.end()) {
        mStars.erase(it);
    }
}

void Game::AddSprite(SpriteComponent* sprite) {
    mSprites.push_back(sprite);
    std::sort(mSprites.begin(), mSprites.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                  return a->GetDrawOrder() < b->GetDrawOrder();
              });
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    std::vector<SpriteComponent*>::iterator it = std::find(mSprites.begin(), mSprites.end(), sprite);
    if(it != mSprites.end()) {
        mSprites.erase(it);
    }
}

void Game::LoadData() {
    // background
    Actor* background = new Actor(this);
    background->SetPosition(Vector2(510.f, 380.f));
    SpriteComponent* scBack = new SpriteComponent(background, 90);
    scBack->SetTexture(GetTexture("Assets/NightBackground.png"));
    
    Actor* backgroundDay = new Actor(this);
    backgroundDay->SetPosition(Vector2(510.f, 380.f));
    SpriteComponent* scBackDay = new SpriteComponent(backgroundDay, 92);
    mBackgroundTextureDay = GetTexture("Assets/DayBackground.png");
    scBackDay->SetTexture(mBackgroundTextureDay);
    SDL_SetTextureAlphaMod(mBackgroundTextureDay, (int)mDayOpacity);
    
    // load player and loser
    mLoser = new Loser(this);
    mLoser->SetPosition(Vector2(90.0f, GRASS_LEVEL - 40.0f));
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector2(SCREEN_WIDTH - 200.f, GRASS_LEVEL));
    
    // show progress bar
    mProgressBar = new ProgressBar(this);
    
    // play music
//    mMusicChannel = Mix_PlayChannel(-1, GetSound("Assets/Sounds/star_gazing.wav"), -1);
}

void Game::UnloadData() {
    // remove all actors
    while(!actors.empty()) {
        delete actors.back();
    }
    actors.clear();
    
    // unload all textures
    while(!textures.empty()) {
        SDL_DestroyTexture(textures.begin()->second);
        textures.erase(textures.begin());
    }
    textures.clear();
    
    // unload all sounds
    while(!sounds.empty()) {
        Mix_FreeChunk(sounds.begin()->second);
        sounds.erase(sounds.begin());
    }
}

SDL_Texture* Game::GetTexture(std::string filename) {
    std::unordered_map<std::string, SDL_Texture*>::iterator inMap = textures.find(filename);
    if(inMap == textures.end()) {
        SDL_Surface* image = IMG_Load(filename.c_str());
        if(image) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
            textures.insert(make_pair(filename, texture));
        }
        else {
            SDL_Log("Failed to load image %s", filename.c_str());
        }
        inMap = textures.find(filename);
    }
    return inMap->second;
}

Mix_Chunk* Game::GetSound(const std::string& filename) {
    std::unordered_map<std::string, Mix_Chunk*>::iterator inMap = sounds.find(filename);
    if(inMap == sounds.end()) {
        Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
        if(sound) {
            sounds.insert(make_pair(filename, sound));
        }
        else {
            SDL_Log("Failed to load sound file %s", filename.c_str());
        }
        inMap = sounds.find(filename);
    }
    return inMap->second;
}

Vector2 Game::GetScreenDimen() {
    return Vector2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
}

Player* Game::GetPlayer() {
    return mPlayer;
}
