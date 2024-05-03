#pragma once
#pragma once
#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Player.h"
#include "Platform.h"
#include "defs.h"
#include "Score.h"
int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;



    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;
    SDL_SetRenderDrawColor(renderer, 243, 208, 215, 0);
    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;



    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

Platform platforms[10] = { {0}, {1}, {2}, {3}, {4}, {5},{6},{7},{8},{9} };
Player player(platforms[0].getX() + platforms[0].getWidth() / 2 + 32 / 2, platforms[0].getY() - player.getHeight() -32, 64, 64);
struct Graphics {
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool freefall = false;
    bool playCoinFX = true;
    bool played = false;
    bool gameOver = false;
    bool restart = false;
    bool firstTime = true;
    double lavaY = SCREEN_HEIGHT - 40;
    double timer = 0;
    int mouseDownX, mouseDownY;
    Mix_Chunk* fxLaunch = Mix_LoadWAV("resources/launch.wav");
    Mix_Chunk* fxClick = Mix_LoadWAV("resources/click.wav");
    Mix_Chunk* fxDeath = Mix_LoadWAV("resources/die.wav");
    Mix_Chunk* fxCoin = Mix_LoadWAV("resources/coin.wav");
    Mix_Chunk* fxSplash = Mix_LoadWAV("resources/splash1.wav");
    Mix_Chunk* fxSelect = Mix_LoadWAV("resources/select1.wav");
    Mix_Chunk* fxguide = Mix_LoadWAV("resources/enterguide.wav");
    Score score;


    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow("SUNNYLAND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        std::cout << SCREEN_HEIGHT << " " << SCREEN_WIDTH << std::endl;

        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_Surface* icon = IMG_Load("resources/icon.png");
        SDL_SetWindowIcon(window, icon);
        TTF_Init();
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
        score.LoadHighScore();
        score.resetScore();

    }

    void update(Graphics& graphics, SDL_Texture* returntex, SDL_Texture* menu,int& timer1, bool& mouse_pressed, bool& mouse_released, bool& mouse_down, int& mouse_x, int& mouse_y, Mix_Chunk* fxLaunch, Mix_Chunk* fxClick, Mix_Chunk* fxDeath, Mix_Chunk* fxCoin)
    {
        if (playCoinFX) {
            Mix_PlayChannel(-1, fxCoin, 0);
            playCoinFX = false;
        }
        if (player.isOnPlatform())
        {
            freefall = false;
        }
        else freefall = true;

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

        checkPlayerCollision(playCoinFX);
        player.updatePosition();

        if (player.getY() > SCREEN_HEIGHT) {
            if (!played) {
                played = true;
                Mix_PlayChannel(-1, fxDeath, 0);
                gameOver = true;
            }
            if (restart) { resetGame(mouse_down); }
        }
        for (int i = 0; i < 10; i++) {
            platforms[i].updatePosition();
        }

        lavaY = SCREEN_HEIGHT - 50 - sin(timer) * 5;
        timer += 0.05;
        timer1++;
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    void quit()
    {
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Texture* loadTexture(const char* filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void Draw_Font(const char* str, int x, int y, int width, int height, int size, SDL_Color color, const char* path) {
        TTF_Font* font = TTF_OpenFont(path, size);

        SDL_Surface* message_surf = TTF_RenderText_Blended(font, str, color);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, message_surf);
        SDL_Rect Message_rect = { x, y, width, height };
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

        SDL_DestroyTexture(Message);
        SDL_FreeSurface(message_surf);
        TTF_CloseFont(font);
    }

    void resetGame(bool& mouse_down) {
        restart = false;
        freefall = false;
        mouse_down = false;
        score.resetScore();
        played = false;
        gameOver = false;
        for (int i = 0; i < 10; i++)
            platforms[i] = Platform(i);
        player.setVelocity(0, 0);
        player.setX((int)platforms[0].getX() + (int)platforms[0].getWidth() / 2 - 26 / 2);
        player.setY((int)platforms[0].getY() - (int)player.getHeight());

    }

    void checkPlayerCollision(bool& playCoinFX) {
        bool onPlatform = false;

        for (int i = 0; i < 10; i++) {
            if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
                score.addScore(1);
                platforms[i].setHasCoin(false);
                playCoinFX = true;
            }

            if (player.getX() + 21 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() -21 > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) {
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

    Mix_Music* loadMusic(const char* path)
    {
        Mix_Music* gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music* gMusic, bool& stopmusic)
    {
        if (gMusic == nullptr) return;
        if (!stopmusic) {
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(gMusic, -1);
            }
            else if (Mix_PausedMusic() == 1) {
                Mix_ResumeMusic();
            }
        }
        else
        {
            Mix_PauseMusic();
        }
    }

};

#endif // _GRAPHICS__H