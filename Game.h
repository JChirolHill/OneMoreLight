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
    
        bool GetWin() { return mWin; }
        void SetWin() { mWin = true; }
        SDL_Texture* GetTexture(std::string);
        Mix_Chunk* GetSound(const std::string& filename);
        class Vector2 GetScreenDimen();
        class Player* GetPlayer();
        int GetMusicChannel() { return mMusicChannel; }
    
        const int SCREEN_WIDTH = 1020;
        const int SCREEN_HEIGHT = 760;
        const float STAR_LEVEL = 150.f;
        const float GRASS_LEVEL = 660.f;
        const float GRAVITY = 1000.0f;
        const float STAR_SPRITE_RATE = 1.f;
    private:
        SDL_Window* window;
        SDL_Renderer *renderer;
    
        bool mIsRunning;
//        bool mIncreaseSpeed;
        int mPreviousTime;
        int mMusicChannel;
        bool mWin;
        float starSpriteTimer = 0.0f;
    
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
    
        void LoadData();
        void UnloadData();
    
        class Player* mPlayer;
        std::vector<class Actor*> actors;
        std::vector<class Star*> mStars;
        std::unordered_map<std::string, SDL_Texture*> textures;
        std::unordered_map<std::string, Mix_Chunk*> sounds;
        std::vector<class SpriteComponent*> mSprites;
};

