#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <vector>
#include <unordered_map>
#include <string>

class Game {
    public:
        Game();
        bool Initialize();
        void Shutdown();
        void RunLoop();
        void AddActor(class Actor*);
        void RemoveActor(class Actor*);
        void AddSprite(class SpriteComponent*);
        void RemoveSprite(class SpriteComponent*);
        void AddStar(class Star*);
        void RemoveStar(class Star*);
    
        SDL_Renderer* GetRenderer() { return renderer; }
        SDL_Texture* GetTexture(std::string);
        Mix_Chunk* GetSound(const std::string& filename);
        class Vector2 GetScreenDimen();
        class Player* GetPlayer();
        class Loser* GetLoser() { return mLoser; }
        int GetMusicChannel() { return mMusicChannel; }
        class ProgressBar* GetProgressBar() { return mProgressBar; }
        bool mWin = true;
        bool mSunUp = false;
        bool mStarsDone = false;
        bool mGameOver = false;
    
        const int SCREEN_WIDTH = 1020;
        const int SCREEN_HEIGHT = 760;
        const float STAR_LEVEL = 150.f;
        const float GRASS_LEVEL = 575.f;
        const float GRAVITY = 1000.0f;
        const float STAR_SPRITE_RATE = 1.f;
        const float TIME_WARM_UP = 5.0f;
        const float TIME_TO_DAY = 5.0f;
        const int STARS_TO_WIN = (int)((TIME_WARM_UP + TIME_TO_DAY) * (3.f/4.f));
    
        std::vector<class Star*> mStars;
    private:
        SDL_Window* window;
        SDL_Renderer *renderer;
    
        bool mIsRunning;
        int mPreviousTime;
        int mMusicChannel;
        bool mPrompted = false;
    
        float starSpriteTimer = 0.0f;
        float mDayOpacity = 0.0f;
        float mWarmUpTimer = 0.0f;
    
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
    
        void LoadData();
        void UnloadData();
    
        class Player* mPlayer;
        class Loser* mLoser;
        class ProgressBar* mProgressBar;
        std::vector<class Actor*> actors;
        std::unordered_map<std::string, SDL_Texture*> textures;
        std::unordered_map<std::string, Mix_Chunk*> sounds;
        std::vector<class SpriteComponent*> mSprites;
        class SDL_Texture* mBackgroundTextureDay;
};

