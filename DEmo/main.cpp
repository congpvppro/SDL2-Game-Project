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
#include <map>

#include "Animation.h"
#include "Game.h"
#include "player.h"
#include "platform.h"
#include "Graphics.h"

const double pi = 3.1415926535897;
const int gravity = 1;

bool titleScreen = true;
bool startScreen = true;
bool playCoinFX = false;
bool quit = false;

bool died = false;
bool mouse_down = false;

bool a_pressed = false, d_pressed = false;


bool playedsound = false;

SDL_RendererFlip flip = SDL_FLIP_NONE;

int mouse_x, mouse_y;
bool play = false, instruction = false, bestscore = false;


const int FPS = 144;
const int frameDelay = 1000 / FPS;
double splashTimer = 0;
int timer1 = 0;
bool firstTime = true;
bool playedSplash = false;
bool playedSelect = false;
int main(int argc, char** argv) {



    Graphics graphics;

    graphics.init();
    Game game;
    ScrollingBackground background, sky;
    background.setTexture(graphics.loadTexture("resources/mountains.png"));
    sky.setTexture(graphics.loadTexture("resources/sky.png"));
    Animation idle, running, fall, ready;



    SDL_Texture* return_tex = graphics.loadTexture("resources/return.png");
    SDL_Texture* item2 = graphics.loadTexture("resources/Item2.png");
    SDL_Texture* item5 = graphics.loadTexture("resources/Item5.png");
    SDL_Texture* item3 = graphics.loadTexture("resources/Item3.png");
    SDL_Texture* item4 = graphics.loadTexture("resources/Item4.png");
    SDL_Texture* lightning = graphics.loadTexture("resources/lightning.png");
    SDL_Texture* award = graphics.loadTexture("resources/award.png");
    SDL_Texture* crown = graphics.loadTexture("resources/crown.png");
    SDL_Texture* charactertex = graphics.loadTexture("resources/player.png");
    SDL_Texture* playerSprite = graphics.loadTexture("resources/egg1.png");
    SDL_Texture* lavaSprite = graphics.loadTexture("resources/lava.png");
    SDL_Texture* platformSprite = graphics.loadTexture("resources/platform1.png");
    SDL_Texture* coinSprite = graphics.loadTexture("resources/coin.png");
    SDL_Texture* scoreBoxSprite = graphics.loadTexture("resources/scorebox.png");
    SDL_Texture* logo = graphics.loadTexture("resources/title.png");
    SDL_Texture* splashEggSprite = graphics.loadTexture("resources/splash_egg.png");
    SDL_Texture* chamthan = graphics.loadTexture("resources/chamthan.png");
    SDL_Texture* M = graphics.loadTexture("resources/M.png");
    SDL_Texture* E = graphics.loadTexture("resources/E.png");
    SDL_Texture* N = graphics.loadTexture("resources/N.png");
    SDL_Texture* U = graphics.loadTexture("resources/U.png");
    SDL_Texture* soundon = graphics.loadTexture("resources/soundon.png");
    SDL_Texture* soundoff = graphics.loadTexture("resources/soundoff.png");
    SDL_Texture* musicon = graphics.loadTexture("resources/musicon.png");
    SDL_Texture* musicoff = graphics.loadTexture("resources/musicoff.png");
    SDL_Texture* menu = graphics.loadTexture("resources/menu.png");
    SDL_Texture* playbutton = graphics.loadTexture("resources/play.png");
    Mix_Chunk* fxLaunch = Mix_LoadWAV("resources/launch.wav");
    Mix_Chunk* fxClick = Mix_LoadWAV("resources/click.wav");
    Mix_Chunk* fxDeath = Mix_LoadWAV("resources/die.wav");
    Mix_Chunk* fxCoin = Mix_LoadWAV("resources/coin.wav");
    
    

    idle.init(charactertex, IDLE_FRAMES, IDLE_CLIPS);
    running.init(charactertex, RUNNING_FRAMES, RUNNING_CLIPS);
    fall.init(charactertex, FALL_FRAMES, FALL_CLIPS);
    ready.init(charactertex, READY_FRAMES, READY_CLIPS);



    while (!quit) {
        SDL_Event e;
        bool mouse_released = false;
        bool mouse_pressed = false;

        
        while (SDL_PollEvent(&e) ) {
            if (!graphics.freefall ) {
                
                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        player.setVelocity(-3, 0);
                        a_pressed = true;
                        flip = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_RIGHT:
                        player.setVelocity(3, 0);
                        d_pressed = true;
                        break;
                    case SDLK_a:
                        player.setVelocity(-3, 0);
                        a_pressed = true;
                        flip = SDL_FLIP_HORIZONTAL;
                        startScreen = false;
                        break;
                    case SDLK_d:
                        player.setVelocity(3, 0);
                        d_pressed = true;
                        startScreen = false;
                        break;
                    case SDLK_ESCAPE:
                        game.pause = true;
                        break;
                    default:
                        startScreen = false;
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
                    case SDLK_LEFT:
                        player.setVelocity(0, 0);
                        a_pressed = false;
                        flip = SDL_FLIP_NONE;
                        break;
                    case SDLK_RIGHT:
                        player.setVelocity(0, 0);
                        d_pressed = false;
                        break;
                    }
                }
                else {
                    switch (e.type) {

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
           
            if (graphics.gameOver) {
                switch (e.type) {

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
            switch (e.type) {
            case SDL_QUIT: {
                quit = true;
            } break;
            }

        }

        SDL_PumpEvents();
        SDL_GetMouseState(&mouse_x, &mouse_y);

        SDL_Delay(16);

        if (titleScreen) {
            if (splashTimer > 120) {
                game.renderStartScreen(graphics, mouse_pressed, logo, titleScreen);
            }
            else {
                game.renderPreStart(graphics, splashEggSprite, splashTimer,timer1, playedSplash, running, idle, ready, fall);
            }
        }
        else {
            if (!play && !instruction && !bestscore) {

                game.renderMenu(graphics,mouse_down, play, instruction, bestscore, mouse_x, mouse_y, mouse_pressed,musicon,musicoff,soundon, soundoff,M,E,N,U,chamthan, item2, item3, item4, item5, lightning, crown, award);
            }
            else if (instruction)
            {
                game.renderInstruction(graphics, mouse_pressed, instruction, mouse_x, mouse_y, return_tex);
            }

            else if (bestscore)
            {
                game.renderBestScore(graphics, mouse_pressed, bestscore, mouse_x, mouse_y, return_tex);
            }
            else if (play && !game.pause)
            {
                graphics.update(graphics, return_tex, menu,timer1, mouse_pressed, mouse_released, mouse_down, mouse_x, mouse_y,fxLaunch, fxClick, fxDeath, fxCoin);
                    game.renderGame(graphics, background, sky, flip,timer1,play,mouse_pressed, a_pressed, mouse_down, d_pressed, mouse_x, mouse_y, idle, running, fall, ready, lavaSprite, scoreBoxSprite, platformSprite, coinSprite, return_tex, menu);
               
                
            }
            else if (play && game.pause)
            {
                game.renderPause(graphics, background, sky, flip, timer1, play, mouse_pressed, a_pressed, mouse_down, d_pressed, mouse_x, mouse_y, idle, running, fall, ready, lavaSprite, scoreBoxSprite, platformSprite, coinSprite, return_tex, menu, playbutton);
            }
            


        }

    }


    graphics.quit();

    return 0;
}