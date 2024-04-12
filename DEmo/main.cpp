#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Animation.h"
#include "player.h"
#include "platform.h"

const double pi = 3.1415926535897;
const int gravity = 1;
Platform platforms[10] = { {0}, {1}, {2}, {3}, {4}, {5},{6},{7},{8},{9} };
Player player(platforms[0].getX() + platforms[0].getWidth() / 2 + 32 / 2, platforms[0].getY() - player.getHeight(), 32, 32);

int LoadHighScore() {
    return 32;
}

void SaveHighScore(int val) {
   
}

int scoreInt = 0;
int highscoreInt = LoadHighScore();
char score[32];
char highscore[32] ;

bool titleScreen = true;
bool playCoinFX = false;


void addScore(int amount) {
    scoreInt += amount;

    if (scoreInt < 10) {
        score[0] = '0';
        score[1] = '0';
        score[2] = scoreInt + 48;
    }
    else if (scoreInt < 100)
    {
        score[0] = '0';
        score[1] = std::to_string(scoreInt)[0];
        score[2] = std::to_string(scoreInt)[1];
    }
    else
    {
        std::string str = std::to_string(scoreInt);
        size_t sz = str.size();
        for (int i = 0; i < sz; i++)
        {
            score[i] = std::to_string(scoreInt)[i];
        }
    }

    if (scoreInt > highscoreInt) {
        highscoreInt = scoreInt;
        highscore[0] = 'B';
        highscore[1] = 'E';
        highscore[2] = 'S';
        highscore[3] = 'T';
        highscore[4] = ':';
        highscore[5] = ' ';
        std::string str = std::to_string(highscoreInt);
        size_t sz = str.size();
        for (int i = 6; i < sz + 6; i++)
        {
            highscore[i] = std::to_string(highscoreInt)[i];
        }
    }
}

void resetScore() {
    scoreInt = 0;
    score[0] = '0';
    score[1] = '0';
    score[2] = scoreInt + 48;
    SaveHighScore(highscoreInt);
}

void resetGame() {
    resetScore();

    for (int i = 0; i < 10; i++)
        platforms[i] = Platform(i);

    player.setVelocity(0, 0);
    player.setX((int)platforms[0].getX() + (int)platforms[0].getWidth() / 2 - 26 / 2);
    player.setY((int)platforms[0].getY() - (int)player.getHeight());
}


void checkPlayerCollision() {
    bool onPlatform = false;

    for (int i = 0; i < 10; i++) {
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
            addScore(1);
            platforms[i].setHasCoin(false);
            playCoinFX = true;
        }

        if (player.getX() + 1 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) {
            if (player.getY() > platforms[i].getY() + platforms[i].getHeight() / 2) {
                player.setVelocity(player.getVelocity().x, 5);
            }
            else if (player.getY() + player.getHeight() < platforms[i].getY() + platforms[i].getHeight()) {
                onPlatform = true;
                player.setY((int)platforms[i].getY() - (int)player.getHeight());
                player.setY((int)player.getY() + 1);
            }
        }
    }
    player.setOnPlatform(onPlatform);
}

void Draw_Font(SDL_Renderer* renderer, const char* str, int x, int y, int width, int height, int size, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("resources/font.otf", size);

    SDL_Surface* message_surf = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, message_surf);
    SDL_Rect Message_rect = { x, y, width, height };
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_DestroyTexture(Message);
    SDL_FreeSurface(message_surf);
    TTF_CloseFont(font);
}

int main(int argc, char** argv) {
    

    resetScore();
    

    const int screenWidth = 1400;
    const int screenHeight = 800;

    const int FPS = 144;
    const int frameDelay = 1000 / FPS;

   

    int mouseDownX = 0;
    int mouseDownY = 0;

    double lavaY = screenHeight - 32;
    double timer = 0;
    int timer1 = 0;
    double splashTimer = 0;

    bool firstTime = true;
    bool playedSplash = false;
    bool playedSelect = false;

    SDL_Window* window;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow(
        "SunnyLand",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_OPENGL
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* icon = IMG_Load("resources/icon.png");
    SDL_SetWindowIcon(window, icon);

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);    
    // SetMasterVolume(0.3f);
    Animation idle, running,fall,ready;

    SDL_Surface* playerSprite_surf = IMG_Load("resources/egg1.png");
    SDL_Surface* lavaSprite_surf = IMG_Load("resources/lava.png");
    SDL_Surface* platformSprite_surf = IMG_Load("resources/platform.png");
    SDL_Surface* coinSprite_surf = IMG_Load("resources/coin.png");
    SDL_Surface* scoreBoxSprite_surf = IMG_Load("resources/scorebox.png");
    SDL_Surface* logo_surf = IMG_Load("resources/title.png");
    SDL_Surface* splashEggSprite_surf = IMG_Load("resources/splash_egg.png");

    SDL_Texture* charactertex = IMG_LoadTexture(renderer, "resources/player.png");
    SDL_Texture* playerSprite = SDL_CreateTextureFromSurface(renderer, playerSprite_surf);
    SDL_Texture* lavaSprite = SDL_CreateTextureFromSurface(renderer, lavaSprite_surf);
    SDL_Texture* platformSprite = SDL_CreateTextureFromSurface(renderer, platformSprite_surf);
    SDL_Texture* coinSprite = SDL_CreateTextureFromSurface(renderer, coinSprite_surf);
    SDL_Texture* scoreBoxSprite = SDL_CreateTextureFromSurface(renderer, scoreBoxSprite_surf);
    SDL_Texture* logo = SDL_CreateTextureFromSurface(renderer, logo_surf);
    SDL_Texture* splashEggSprite = SDL_CreateTextureFromSurface(renderer, splashEggSprite_surf);

    Mix_Chunk* fxLaunch = Mix_LoadWAV("resources/launch.wav");
    Mix_Chunk* fxClick = Mix_LoadWAV("resources/click.wav");
    Mix_Chunk* fxDeath = Mix_LoadWAV("resources/die.wav");
    Mix_Chunk* fxCoin = Mix_LoadWAV("resources/coin.wav");
    Mix_Chunk* fxSplash = Mix_LoadWAV("resources/splash.wav");
    Mix_Chunk* fxSelect = Mix_LoadWAV("resources/select.wav");

    idle.init(charactertex, IDLE_FRAMES, IDLE_CLIPS);
    running.init(charactertex, RUNNING_FRAMES, RUNNING_CLIPS);
    fall.init(charactertex, FALL_FRAMES, FALL_CLIPS);
    ready.init(charactertex, READY_FRAMES, READY_CLIPS);

    bool quit = false;

    bool mouse_down = false;

    bool a_pressed = false, d_pressed = false;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    int mouse_x, mouse_y;
   
    while (!quit) {
        SDL_Event e;
        bool mouse_released = false;
        bool mouse_pressed = false;
        
        if (timer1 % 5 == 0){
            idle.tick();
            running.tick();
            fall.tick();
            ready.tick();
        }
        
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym) {
                case SDLK_a:
                    player.setVelocity(-3, 0);
                    a_pressed = true;
                    flip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    player.setVelocity(3, 0);
                    d_pressed = true;
                    break;
                }
            }
            else  if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_a:
                    player.setVelocity(0, 0);
                    a_pressed = false;
                    flip = SDL_FLIP_NONE;
                    break;
                case SDLK_d:
                    player.setVelocity(0, 0);
                    d_pressed = false;
                    break;
                }
            }
            else {
                switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;

                case SDL_MOUSEBUTTONDOWN: {
                    mouse_down = true;
                    mouse_pressed = true;
                    
                } break;
                case SDL_MOUSEBUTTONUP: {
                    mouse_down = false;
                    mouse_released = true;
                   
                } break;
                }
            }
        }

        SDL_PumpEvents();
        SDL_GetMouseState(&mouse_x, &mouse_y);

        // TODO: Vsync instead
        SDL_Delay(16);
       

        if (titleScreen) {
            if (splashTimer > 120) {
                if (!playedSelect) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    playedSelect = true;
                }

                SDL_SetRenderDrawColor(renderer, 238, 228, 225, 255);
                SDL_RenderClear(renderer);

                SDL_Rect logo_rect = { screenWidth / 2 - 200, screenHeight / 2 - 45 - 30, 400, 90 };
                SDL_RenderCopy(renderer, logo, NULL, &logo_rect);

                Draw_Font(renderer, highscore, screenWidth / 2 - 37, screenHeight / 2 + 10, 74, 32, 32, { 0, 0, 0 });
                Draw_Font(renderer, "CLICK ANYWHERE TO BEGIN", screenWidth / 2 - 134, screenHeight / 2 + 50, 268, 32, 32, { 178, 150, 125 });

                SDL_RenderPresent(renderer);

                if (mouse_pressed) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    mouseDownX = mouse_x;
                    mouseDownY = mouse_y;
                }
            }
            else {
                if (!playedSplash) {
                    Mix_PlayChannel(-1, fxSplash, 0);
                    playedSplash = true;
                }

                SDL_SetRenderDrawColor(renderer, 238, 228, 225, 255);
                SDL_RenderClear(renderer);

                Draw_Font(renderer, "LE ProcG", screenWidth / 2 - 54, screenHeight / 2 + 3, 108, 32, 32, { 213, 128, 90 });

                SDL_Rect splashEggSprite_rect = { screenWidth / 2 - 16, screenHeight / 2 - 16 - 23, 32, 32 };
                SDL_RenderCopy(renderer, splashEggSprite, NULL, &splashEggSprite_rect);

                SDL_RenderPresent(renderer);

                splashTimer += 1;
            }
        }
        else {
            if (playCoinFX) {
                Mix_PlayChannel(-1, fxCoin, 0);
                playCoinFX = false;
            }

            if (mouse_pressed && player.isOnGround()) {
                Mix_PlayChannel(-1, fxClick, 0);
                mouseDownX = mouse_x;
                mouseDownY = mouse_y;
            }

            if (mouse_released && player.isOnGround()) {
                if (firstTime) {
                    firstTime = false;
                }
                else {
                    Mix_PlayChannel(-1, fxLaunch, 0);

                    if (player.isOnPlatform())
                        player.setY((int)player.getY() - 1);

                    int velocityX = mouse_x - mouseDownX;
                    int velocityY = mouse_y - mouseDownY;

                    player.setVelocity((double)velocityX * .08, (double)velocityY * .08);
                }
            }

            checkPlayerCollision();
            player.updatePosition();

            if (player.getY() > screenHeight) {
                Mix_PlayChannel(-1, fxDeath, 0);
                resetGame();
            }
            for (int i = 0; i < 10; i++) {
                platforms[i].updatePosition();
            }

            lavaY = screenHeight - 43 - sin(timer) * 5;
            timer += 0.05;
            timer1 += 1;

            SDL_SetRenderDrawColor(renderer, 238, 228, 225, 255);
            SDL_RenderClear(renderer);

            if (mouse_down && player.isOnGround()) {
                SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
                SDL_RenderDrawLine(
                    renderer,
                    mouseDownX + (int)(player.getX() - mouseDownX) + (int)(player.getWidth() / 2),
                    mouseDownY + (int)(player.getY() - mouseDownY) + (int)(player.getHeight() / 2),
                    mouse_x + (int)(player.getX() - mouseDownX) + (int)(player.getWidth() / 2),
                    mouse_y + (int)(player.getY() - mouseDownY) + (int)(player.getHeight() / 2)
                );
            }

            //DrawRectangle(player.getX(), player.getY(), player.getWidth(), player.getHeight(), WHITE);
            double distance = (double)mouse_x - player.getX();
            for (int i = 0; i < 10; i++) {
                SDL_Rect platformSprite_rect = { (int)platforms[i].getX(),(int)platforms[i].getY(), 100, 32 };
                SDL_RenderCopy(renderer, platformSprite, NULL, &platformSprite_rect);

                if (platforms[i].getHasCoin()) {
                    SDL_Rect coinSprite_rect = { platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24 };
                    SDL_RenderCopy(renderer, coinSprite, NULL, &coinSprite_rect);
                }
            }
            if (!a_pressed && !d_pressed && player.getVelocity().y == 0 && !mouse_down)
            {
                const SDL_Rect* clip = idle.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() - clip->w,(int)player.getY() - clip->h, clip->w * 2, clip->h * 2 };
                SDL_RenderCopy(renderer, idle.texture, clip, &renderQuad);
            }
            else if( (a_pressed || d_pressed) &&player.getVelocity().y == 0)
            {
                const SDL_Rect* clip = running.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() - clip->w,(int)player.getY() - clip->h, clip->w * 2, clip->h * 2 };
                SDL_RenderCopyEx(renderer, running.texture, clip, &renderQuad,NULL,NULL, flip);
            }
            else if (player.getVelocity().y != 0)
            {
                const SDL_Rect* clip = fall.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() - clip->w,(int)player.getY() - clip->h, clip->w * 2, clip->h * 2 };
                SDL_RenderCopy(renderer, fall.texture, clip, &renderQuad);
            }
            else if (mouse_down)
            {
                if (distance < 0) {
                    const SDL_Rect* clip = ready.getCurrentClip();
                    SDL_Rect renderQuad = { (int)player.getX() - clip->w,(int)player.getY() - clip->h, clip->w * 2, clip->h * 2 };
                    SDL_RenderCopyEx(renderer, ready.texture, clip, &renderQuad,NULL,NULL, SDL_FLIP_HORIZONTAL);
                }
                else
                {
                    const SDL_Rect* clip = ready.getCurrentClip();
                    SDL_Rect renderQuad = { (int)player.getX() - clip->w,(int)player.getY() - clip->h, clip->w * 2, clip->h * 2 };
                    SDL_RenderCopy(renderer, ready.texture, clip, &renderQuad);
                }

            }

            SDL_Rect lavaSprite_rect = { 0, (int)lavaY, 1400, 48 };
            SDL_RenderCopy(renderer, lavaSprite, NULL, &lavaSprite_rect);

            SDL_Rect scoreBoxSprite_rect = { 17, 17, 102, 70 };
            SDL_RenderCopy(renderer, scoreBoxSprite, NULL, &scoreBoxSprite_rect);

            Draw_Font(renderer, score, 28, 20, 75, 64, 64, { 0, 0, 0 });
            Draw_Font(renderer, highscore, 17, 90, 74, 32, 32, { 0, 0, 0 });

            SDL_RenderPresent(renderer);
        }

    }

    SDL_DestroyTexture(playerSprite);
    SDL_DestroyTexture(lavaSprite);
    SDL_DestroyTexture(platformSprite);
    SDL_DestroyTexture(coinSprite);
    SDL_DestroyTexture(scoreBoxSprite);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(splashEggSprite);

    SDL_FreeSurface(playerSprite_surf);
    SDL_FreeSurface(lavaSprite_surf);
    SDL_FreeSurface(platformSprite_surf);
    SDL_FreeSurface(coinSprite_surf);
    SDL_FreeSurface(scoreBoxSprite_surf);
    SDL_FreeSurface(logo_surf);
    SDL_FreeSurface(splashEggSprite_surf);

    Mix_FreeChunk(fxClick);
    Mix_FreeChunk(fxLaunch);
    Mix_FreeChunk(fxDeath);
    Mix_FreeChunk(fxCoin);
    Mix_FreeChunk(fxSplash);
    Mix_FreeChunk(fxSelect);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}