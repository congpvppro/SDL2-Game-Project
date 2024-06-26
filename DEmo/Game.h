#pragma once
#pragma once
#ifndef _GAME__H
#define _GAME__H
#include "Graphics.h"
#include "ScrollingBackground.h"
#include "defs.h"
#include <map>
#include "SDL_mixer.h"
struct Game {
    bool playedSelect = true;
    bool pause = false;
    bool playedsound = false;
    bool bsoundoff = false;
    bool bmusicoff = false;
    Mix_Chunk* fxSplash = Mix_LoadWAV("resources/splash1.wav");
    Mix_Chunk* fxSelect = Mix_LoadWAV("resources/select1.wav");
    Mix_Chunk* fxguide = Mix_LoadWAV("resources/enterguide.wav");
    Mix_Chunk* fxchoose = Mix_LoadWAV("resources/choose.wav");
    SDL_Rect return_rect = { 32 , 32, 50 , 50 };
    SDL_Rect preturn_rect = { 37 , 37, 40 , 40 };
    SDL_Rect item2_rect = { SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 - 300, 800 , 200 };
    SDL_Rect item4_rect = { SCREEN_WIDTH / 2 - 380, SCREEN_HEIGHT / 2 - 350, 760 , 300 };
    SDL_Rect item3_rect = { SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT / 2 , 460 , 400 };
    SDL_Rect item5_rect1 = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50, 300 , 80 };
    SDL_Rect item5_rect2 = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 115 + 50, 300 , 80 };
    SDL_Rect item5_rect3 = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 230 + 50, 300 , 80 };
    SDL_Rect lightning_rect = { SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 - 10 + 50, 70 , 100 };
    SDL_Rect award_rect = { SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 + 220 + 50, 70 , 100 };
    SDL_Rect crown_rect = { SCREEN_WIDTH / 2 - 55, SCREEN_HEIGHT / 2 - 220, 110 , 80 };
    SDL_Rect chamthan_rect = { SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 + 105 + 50, 50 , 100 };
    SDL_Rect M_rect = { SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 280, 80 , 92 };
    SDL_Rect E_rect = { SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 294, 80 , 92 };
    SDL_Rect N_rect = { SCREEN_WIDTH / 2 + 82, SCREEN_HEIGHT / 2 - 294, 80 , 92 };
    SDL_Rect U_rect = { SCREEN_WIDTH / 2 + 161, SCREEN_HEIGHT / 2 - 280, 80 , 92 };
    SDL_Rect musicon_rect = { SCREEN_WIDTH - 82, SCREEN_HEIGHT - 82, 50, 50 };
    SDL_Rect musicoff_rect = { SCREEN_WIDTH - 82, SCREEN_HEIGHT - 82, 50, 50 };
    SDL_Rect soundon_rect = { SCREEN_WIDTH - 82, SCREEN_HEIGHT - 142, 50, 50 };
    SDL_Rect soundoff_rect = { SCREEN_WIDTH - 82, SCREEN_HEIGHT - 142, 50, 50 };
    SDL_Rect pmusicon_rect = { SCREEN_WIDTH - 72, SCREEN_HEIGHT - 77, 40, 40 };
    SDL_Rect pmusicoff_rect = { SCREEN_WIDTH - 72, SCREEN_HEIGHT - 77, 40, 40 };
    SDL_Rect psoundon_rect = { SCREEN_WIDTH - 72, SCREEN_HEIGHT - 137, 40, 40 };
    SDL_Rect psoundoff_rect = { SCREEN_WIDTH - 72, SCREEN_HEIGHT - 137, 40, 40 };
    SDL_Rect play_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100 , 100 };
    SDL_Rect rplay_rect = { SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 30, 60, 60 };
    Mix_Music* music = Mix_LoadMUS("resources/arcade.ogg");
    
    void UpdateAnim(Animation& running, Animation& idle, Animation& ready, Animation& fall, int& timer1) {
        if (timer1 % 5 == 0) {
            idle.tick();
            running.tick();
            fall.tick();
            ready.tick();
        }
    }

    void renderTexture(Graphics& graphics, SDL_Texture* texture, int x, int y, int w, int h)
    {
        SDL_Rect dest = { x, y, w, h };
        SDL_RenderCopy(graphics.renderer, texture, NULL, &dest);
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    void renderBackground(ScrollingBackground& background, Graphics& graphics, int y, int w, int h)
    {
        renderTexture(graphics, background.texture, background.scrollingOffset, y, w, h);
        renderTexture(graphics, background.texture, background.scrollingOffset - SCREEN_WIDTH, y, w, h);
    }

    void renderStartScreen(Graphics& graphics, bool& mouse_pressed, SDL_Texture* logo, bool& titleScreen) {
        if (!playedSelect) {
            Mix_PlayChannel(-1, fxSelect, 0);
            playedSelect = true;
        }

        SDL_SetRenderDrawColor(graphics.renderer, 238, 228, 225, 255);
        SDL_RenderClear(graphics.renderer);

        SDL_Rect logo_rect = { SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 - 285 - 30, 800, 570 };
        SDL_RenderCopy(graphics.renderer, logo, NULL, &logo_rect);


        graphics.Draw_Font("CLICK ANYWHERE TO BEGIN", SCREEN_WIDTH / 2 - 134, SCREEN_HEIGHT / 2 + 50, 268, 32, 32, { 178, 150, 125 }, "resources/font.otf");

        graphics.presentScene();

        if (mouse_pressed) {
            Mix_PlayChannel(-1, fxSelect, 0);
            titleScreen = false;

        }
    }

    void renderPreStart(Graphics& graphics, SDL_Texture* splashEggSprite, double& splashTimer,int & timer1, bool& playedSplash, Animation& running, Animation& idle, Animation& ready, Animation& fall)
    {
        UpdateAnim(running, idle, ready, fall, timer1);
        if (!playedSplash) {
            Mix_PlayChannel(-1, fxSplash, 0);
            playedSplash = true;
        }

        SDL_SetRenderDrawColor(graphics.renderer, 238, 228, 225, 255);
        SDL_RenderClear(graphics.renderer);

        graphics.Draw_Font("LE ProcG", SCREEN_WIDTH / 2 - 54, SCREEN_HEIGHT / 2 + 3, 108, 32, 32, { 213, 128, 90 }, "resources/font.otf");

        
        const SDL_Rect* clip = running.getCurrentClip();
        SDL_Rect renderQuad = { SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 - 32 - 35, 64, 64 };
        SDL_RenderCopyEx(graphics.renderer, running.texture, clip, &renderQuad, NULL, NULL, SDL_FLIP_NONE);

        graphics.presentScene();

        splashTimer += 1;
        timer1 += 1;
    }

    void renderMenu(Graphics& graphics ,bool& mouse_down, bool& play, bool& instruction, bool& bestscore, int& mouse_x, int& mouse_y, bool& mouse_pressed, SDL_Texture* musicon, SDL_Texture* musicoff, SDL_Texture* soundon, SDL_Texture* soundoff,SDL_Texture* M, SDL_Texture* E, SDL_Texture* N, SDL_Texture* U, SDL_Texture* chamthan, SDL_Texture* item2, SDL_Texture* item3, SDL_Texture* item4, SDL_Texture* item5, SDL_Texture* lightning, SDL_Texture* crown, SDL_Texture* award)
    {
        graphics.play(music, bmusicoff);
        SDL_SetRenderDrawColor(graphics.renderer, 240, 235, 227, 0);
        SDL_RenderClear(graphics.renderer);
        SDL_RenderDrawCircle(graphics.renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 400);
        SDL_RenderFillCircle(graphics.renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 400);
        SDL_RenderCopy(graphics.renderer, item2, NULL, &item2_rect);
        SDL_RenderCopy(graphics.renderer, item4, NULL, &item4_rect);
        SDL_RenderCopy(graphics.renderer, item3, NULL, &item3_rect);
        SDL_RenderCopy(graphics.renderer, item5, NULL, &item5_rect1);
        SDL_RenderCopy(graphics.renderer, item5, NULL, &item5_rect2);
        SDL_RenderCopy(graphics.renderer, item5, NULL, &item5_rect3);
        SDL_RenderCopy(graphics.renderer, crown, NULL, &crown_rect);
        SDL_RenderCopy(graphics.renderer, chamthan, NULL, &chamthan_rect);
        SDL_RenderCopyEx(graphics.renderer, M, NULL, &M_rect, -10.0f, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(graphics.renderer, E, NULL, &E_rect, -10.0f, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(graphics.renderer, N, NULL, &N_rect, 10.0f, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(graphics.renderer, U, NULL, &U_rect, 10.0f, NULL, SDL_FLIP_NONE);
       
        if (mouse_x >= SCREEN_WIDTH / 2 - 150 && mouse_x <= SCREEN_WIDTH / 2 + 150 && mouse_y >= SCREEN_HEIGHT / 2 + 50 && mouse_y <= SCREEN_HEIGHT / 2 + 80 + 50)
        {

            graphics.Draw_Font("PLAY", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 20 + 50 , 130, 40, 100, { 170, 215, 217 }, "resources/Kaph.otf");
            graphics.Draw_Font("INSTRUCTION", SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 130 + 50 , 180, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            graphics.Draw_Font("HIGHSCORE", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 245 + 50 , 170, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            if (!playedsound)
            {
                Mix_PlayChannel(-1, fxchoose, 0);
                playedsound = true;
            }
            if (mouse_pressed)
            {
                play = true;
            }
        }
        else if (mouse_x >= SCREEN_WIDTH / 2 - 150 && mouse_x <= SCREEN_WIDTH / 2 + 150 && mouse_y >= SCREEN_HEIGHT / 2 + 115 + 50 && mouse_y <= SCREEN_HEIGHT / 2 + 195 + 50)
        {
            if (!playedsound)
            {
                Mix_PlayChannel(-1, fxchoose, 0);
                playedsound = true;
            }
            graphics.Draw_Font("INSTRUCTION", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 135 + 50, 150, 40, 100, { 170, 215, 217 }, "resources/Kaph.otf");
            graphics.Draw_Font("PLAY", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 15 + 50, 150 , 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            graphics.Draw_Font("HIGHSCORE", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 245 + 50, 170, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            if (mouse_pressed)
            {
                instruction = true;
            }
        }
        else if (mouse_x >= SCREEN_WIDTH / 2 - 150 && mouse_x <= SCREEN_WIDTH / 2 + 150 && mouse_y >= SCREEN_HEIGHT / 2 + 230 + 50 && mouse_y <= SCREEN_HEIGHT / 2 + 310 + 50)
        {
            if (!playedsound)
            {
                Mix_PlayChannel(-1, fxchoose, 0);
                playedsound = true;
            }
            graphics.Draw_Font("HIGHSCORE", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 250 + 50, 150, 40, 100, { 170, 215, 217 }, "resources/Kaph.otf");
            graphics.Draw_Font("PLAY", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 15 + 50, 150, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            graphics.Draw_Font("INSTRUCTION", SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 130 + 50, 180, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            if (mouse_pressed)
            {
                bestscore = true;
            }
        }
        else {
            playedsound = false;
            graphics.Draw_Font("PLAY", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 15 + 50, 150, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            graphics.Draw_Font("INSTRUCTION", SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 130 + 50, 180, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
            graphics.Draw_Font("HIGHSCORE", SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 245 + 50, 170, 50, 100, { 255,255,255 }, "resources/Kaph.otf");
        }

        manageAudioandMusic(graphics,musicon, musicoff,soundon, soundoff,mouse_pressed,mouse_x, mouse_y);
        SDL_RenderCopy(graphics.renderer, lightning, NULL, &lightning_rect);
        SDL_RenderCopy(graphics.renderer, crown, NULL, &crown_rect);
        SDL_RenderCopy(graphics.renderer, award, NULL, &award_rect);
        graphics.presentScene();

    }

    void renderInstruction(Graphics& graphics, bool& mouse_pressed, bool& instruction, int& mouse_x, int& mouse_y, SDL_Texture* return_tex)
    {
        SDL_SetRenderDrawColor(graphics.renderer, 240, 235, 227, 0);
        SDL_RenderClear(graphics.renderer);
        graphics.Draw_Font("Press A, D or <-, -> to move, drag and release left mouse button to jump.", SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 64, 900, 32, 50, { 178, 150, 125 }, "resources/font.otf");
        graphics.Draw_Font("You can bounce when you hit the wall", SCREEN_WIDTH / 2 - 221, SCREEN_HEIGHT / 2 -32  , 443, 32, 50, { 178, 150, 125 }, "resources/font.otf");
        graphics.Draw_Font("Press ESC to pause", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 , 221, 32, 50, { 178, 150, 125 }, "resources/font.otf");
        graphics.Draw_Font("1 coin = 1 point", SCREEN_WIDTH / 2 - 86, SCREEN_HEIGHT / 2 + 32, 173, 32, 50, { 178, 150, 125 }, "resources/font.otf");

         if (mouse_x >= 32 && mouse_x <= 82 && mouse_y >= 32 && mouse_y <= 82)
        {
            SDL_RenderCopy(graphics.renderer, return_tex, NULL, &preturn_rect);

            if (mouse_pressed)
            {
                instruction = false;
            }
        }
        else        SDL_RenderCopy(graphics.renderer, return_tex, NULL, &return_rect);

        graphics.presentScene();
    }

    void renderBestScore(Graphics& graphics, bool& mouse_pressed, bool& bestscore, int& mouse_x, int& mouse_y, SDL_Texture* return_tex)
    {
        SDL_SetRenderDrawColor(graphics.renderer, 240, 235, 227, 0);
        SDL_RenderClear(graphics.renderer);
        graphics.Draw_Font(graphics.score.highscore, SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 16, 80, 32, 32, { 0, 0, 0 }, "resources/font.otf");
        if (mouse_x >= 32 && mouse_x <= 82 && mouse_y >= 32 && mouse_y <= 82)
        {
            SDL_RenderCopy(graphics.renderer, return_tex, NULL, &preturn_rect);

            if (mouse_pressed)
            {
                bestscore = false;
            }
        }
        else        SDL_RenderCopy(graphics.renderer, return_tex, NULL, &return_rect);

        graphics.presentScene();

    }

    void renderGame(Graphics& graphics, ScrollingBackground& background, ScrollingBackground& sky, SDL_RendererFlip& flip, int& timer1,bool& play,bool& mouse_pressed, bool& a_pressed, bool& mouse_down, bool& d_pressed, int& mouse_x, int& mouse_y, Animation& idle, Animation& running, Animation& fall, Animation& ready, SDL_Texture* lavaSprite, SDL_Texture* scoreBoxSprite, SDL_Texture* platformSprite, SDL_Texture* coinSprite, SDL_Texture* return_tex, SDL_Texture*menu)
    {
        graphics.play(music, bmusicoff);
        UpdateAnim(running, idle, ready, fall, timer1);

        
        background.scroll(3);
        sky.scroll(1);
       
        SDL_SetRenderDrawColor(graphics.renderer, 238, 228, 225, 255);
        SDL_RenderClear(graphics.renderer);
        renderBackground(sky, graphics, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        renderBackground(background, graphics, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

        if (mouse_down && player.isOnGround()) {
            SDL_SetRenderDrawColor(graphics.renderer, 178, 150, 125, 255);
            SDL_RenderDrawLine(
                graphics.renderer,
                graphics.mouseDownX + (int)(player.getX() - graphics.mouseDownX) + (int)(player.getWidth() / 2),
                graphics.mouseDownY + (int)(player.getY() - graphics.mouseDownY) + (int)(player.getHeight() / 2),
                mouse_x + (int)(player.getX() - graphics.mouseDownX) + (int)(player.getWidth() / 2),
                mouse_y + (int)(player.getY() - graphics.mouseDownY) + (int)(player.getHeight() / 2)
            );
        }

        for (int i = 0; i < 10; i++) {
            SDL_Rect platformSprite_rect = { (int)platforms[i].getX(),(int)platforms[i].getY(), 100, 32 };
            SDL_RenderCopy(graphics.renderer, platformSprite, NULL, &platformSprite_rect);

            if (platforms[i].getHasCoin()) {
                SDL_Rect coinSprite_rect = { platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24 };
                SDL_RenderCopy(graphics.renderer, coinSprite, NULL, &coinSprite_rect);
            }
        }
        double distance = (double)mouse_x - player.getX();
        if (!a_pressed && !d_pressed && player.getVelocity().y == 0 && !mouse_down)
        {
            const SDL_Rect* clip = idle.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2 , clip->h * 2 };
            SDL_RenderCopy(graphics.renderer, idle.texture, clip, &renderQuad);
        }
        else if ((a_pressed || d_pressed) && player.getVelocity().y == 0)
        {
            const SDL_Rect* clip = running.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
            SDL_RenderCopyEx(graphics.renderer, running.texture, clip, &renderQuad, NULL, NULL, flip);
        }
        else if (player.getVelocity().y != 0)
        {
            const SDL_Rect* clip = fall.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2 , clip->h * 2 };
            SDL_RenderCopy(graphics.renderer, fall.texture, clip, &renderQuad);
        }
        else if (mouse_down)
        {
            if (distance < 0) {
                const SDL_Rect* clip = ready.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
                SDL_RenderCopyEx(graphics.renderer, ready.texture, clip, &renderQuad, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
            else
            {
                const SDL_Rect* clip = ready.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
                SDL_RenderCopy(graphics.renderer, ready.texture, clip, &renderQuad);
            }

        }
        SDL_Rect lavaSprite_rect = { 0, (int)graphics.lavaY, SCREEN_WIDTH, 60 };
        SDL_RenderCopy(graphics.renderer, lavaSprite, NULL, &lavaSprite_rect);

        SDL_Rect scoreBoxSprite_rect = { 17, 17, 102, 70 };
        SDL_RenderCopy(graphics.renderer, scoreBoxSprite, NULL, &scoreBoxSprite_rect);

        graphics.Draw_Font(graphics.score.score, 28, 20, 75, 64, 100, { 0, 0, 0 }, "resources/font.otf");
        graphics.Draw_Font(graphics.score.highscore, 28, 90, 74, 32, 100, { 0, 0, 0 }, "resources/font.otf");
        if (graphics.gameOver)
        {
            SDL_Rect restart_rect = { SCREEN_WIDTH / 2 - 100 - 30, SCREEN_HEIGHT / 2 - 50, 100, 100 };
            SDL_Rect prestart_rect = { SCREEN_WIDTH / 2 - 90 - 30, SCREEN_HEIGHT / 2 - 40, 80, 80 };

            SDL_Rect menu_rect = { SCREEN_WIDTH / 2  + 30, SCREEN_HEIGHT / 2 - 50, 100, 100 };
            SDL_Rect pmenu_rect = { SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 40, 80, 80 };

            if (mouse_x >= SCREEN_WIDTH / 2 - 100 - 30 && mouse_x <= SCREEN_WIDTH / 2 - 30 && mouse_y >= SCREEN_HEIGHT / 2 - 50 && mouse_y <= SCREEN_HEIGHT / 2 + 50)
            {
                SDL_RenderCopy(graphics.renderer, return_tex, NULL, &prestart_rect);

                if (mouse_pressed)
                {
                    graphics.gameOver = false;
                    graphics.restart = true;
                }
            }
            else SDL_RenderCopy(graphics.renderer, return_tex, NULL, &restart_rect);

            if (mouse_x >= SCREEN_WIDTH / 2 + 30 && mouse_x <= SCREEN_WIDTH / 2 +130 && mouse_y >= SCREEN_HEIGHT / 2 - 50 && mouse_y <= SCREEN_HEIGHT / 2 + 50)
            {
                SDL_RenderCopy(graphics.renderer, menu, NULL, &pmenu_rect);


                if (mouse_pressed)
                {
                    play = false;
                    graphics.gameOver = false;
                    graphics.freefall = false;
                    graphics.resetGame(mouse_down);
                    
                }
            }
            else  SDL_RenderCopy(graphics.renderer, menu, NULL, &menu_rect);

        }

        graphics.presentScene();
    }

    void renderPause(Graphics& graphics, ScrollingBackground& background, ScrollingBackground& sky, SDL_RendererFlip& flip, int& timer1,bool& play, bool& mouse_pressed, bool& a_pressed, bool& mouse_down, bool& d_pressed, int& mouse_x, int& mouse_y, Animation& idle, Animation& running, Animation& fall, Animation& ready, SDL_Texture* lavaSprite, SDL_Texture* scoreBoxSprite, SDL_Texture* platformSprite, SDL_Texture* coinSprite, SDL_Texture* return_tex, SDL_Texture* menu, SDL_Texture* playbutton) {
        SDL_RenderClear(graphics.renderer);
        SDL_SetRenderDrawColor(graphics.renderer, 238, 228, 225, 255);
        SDL_RenderClear(graphics.renderer);
        renderBackground(sky, graphics, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        renderBackground(background, graphics, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
        if (mouse_down && player.isOnGround()) {
            SDL_SetRenderDrawColor(graphics.renderer, 178, 150, 125, 255);
            SDL_RenderDrawLine(
                graphics.renderer,
                graphics.mouseDownX + (int)(player.getX() - graphics.mouseDownX) + (int)(player.getWidth() / 2),
                graphics.mouseDownY + (int)(player.getY() - graphics.mouseDownY) + (int)(player.getHeight() / 2),
                mouse_x + (int)(player.getX() - graphics.mouseDownX) + (int)(player.getWidth() / 2),
                mouse_y + (int)(player.getY() - graphics.mouseDownY) + (int)(player.getHeight() / 2)
            );
        }

        for (int i = 0; i < 10; i++) {
            SDL_Rect platformSprite_rect = { (int)platforms[i].getX(),(int)platforms[i].getY(), 100, 32 };
            SDL_RenderCopy(graphics.renderer, platformSprite, NULL, &platformSprite_rect);

            if (platforms[i].getHasCoin()) {
                SDL_Rect coinSprite_rect = { platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24 };
                SDL_RenderCopy(graphics.renderer, coinSprite, NULL, &coinSprite_rect);
            }
        }
        double distance = (double)mouse_x - player.getX();
        if (!a_pressed && !d_pressed && player.getVelocity().y == 0 && !mouse_down)
        {
            const SDL_Rect* clip = idle.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2 , clip->h * 2 };
            SDL_RenderCopy(graphics.renderer, idle.texture, clip, &renderQuad);
        }
        else if ((a_pressed || d_pressed) && player.getVelocity().y == 0)
        {
            const SDL_Rect* clip = running.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
            SDL_RenderCopyEx(graphics.renderer, running.texture, clip, &renderQuad, NULL, NULL, flip);
        }
        else if (player.getVelocity().y != 0)
        {
            const SDL_Rect* clip = fall.getCurrentClip();
            SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2 , clip->h * 2 };
            SDL_RenderCopy(graphics.renderer, fall.texture, clip, &renderQuad);
        }
        else if (mouse_down)
        {
            if (distance < 0) {
                const SDL_Rect* clip = ready.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
                SDL_RenderCopyEx(graphics.renderer, ready.texture, clip, &renderQuad, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
            else
            {
                const SDL_Rect* clip = ready.getCurrentClip();
                SDL_Rect renderQuad = { (int)player.getX() ,(int)player.getY() , clip->w * 2, clip->h * 2 };
                SDL_RenderCopy(graphics.renderer, ready.texture, clip, &renderQuad);
            }

        }
        SDL_Rect lavaSprite_rect = { 0, (int)graphics.lavaY, SCREEN_WIDTH, 60 };
        SDL_RenderCopy(graphics.renderer, lavaSprite, NULL, &lavaSprite_rect);

        SDL_Rect scoreBoxSprite_rect = { 17, 17, 102, 70 };
        SDL_RenderCopy(graphics.renderer, scoreBoxSprite, NULL, &scoreBoxSprite_rect);

        graphics.Draw_Font(graphics.score.score, 28, 20, 75, 64, 100, { 0, 0, 0 }, "resources/font.otf");
        graphics.Draw_Font(graphics.score.highscore, 28, 90, 74, 32, 100, { 0, 0, 0 }, "resources/font.otf");
        if (mouse_x >= SCREEN_WIDTH / 2 - 50 && mouse_x <= SCREEN_WIDTH / 2 + 50 && mouse_y >= SCREEN_HEIGHT / 2 - 50 && mouse_y <= SCREEN_HEIGHT / 2 + 50)
        {
            SDL_RenderCopy(graphics.renderer, playbutton, NULL, &rplay_rect);

            if (mouse_pressed)
            {
                graphics.mouseDownX = mouse_x;
                graphics.mouseDownY = mouse_y;
                pause = false;
              
            }
        }
        else SDL_RenderCopy(graphics.renderer, playbutton, NULL, &play_rect);
        SDL_RenderPresent(graphics.renderer);
    }

    void manageAudioandMusic(Graphics &graphics, SDL_Texture* musicon, SDL_Texture* musicoff, SDL_Texture* soundon, SDL_Texture* soundoff, bool &mouse_pressed, int& mouse_x, int& mouse_y)
    {
        if (!bmusicoff)
        {
            if (mouse_x >= SCREEN_WIDTH - 82 && mouse_x <= SCREEN_WIDTH - 32 && mouse_y >= SCREEN_HEIGHT - 82 && mouse_y <= SCREEN_HEIGHT - 32)
            {
                SDL_RenderCopy(graphics.renderer, musicon, NULL, &pmusicon_rect);

                if (mouse_pressed)
                {
                    bmusicoff = true;
                }
            }
            else
                SDL_RenderCopy(graphics.renderer, musicon, NULL, &musicon_rect);

        }
        else
        {
            if (mouse_x >= SCREEN_WIDTH - 82 && mouse_x <= SCREEN_WIDTH - 32 && mouse_y >= SCREEN_HEIGHT - 82 && mouse_y <= SCREEN_HEIGHT - 32)
            {
                SDL_RenderCopy(graphics.renderer, musicoff, NULL, &pmusicon_rect);

                if (mouse_pressed)
                {
                    bmusicoff = false;
                }
            }
            else
                SDL_RenderCopy(graphics.renderer, musicoff, NULL, &musicon_rect);

        }
        if (!bsoundoff)
        {
            if (mouse_x >= SCREEN_WIDTH - 82 && mouse_x <= SCREEN_WIDTH - 32 && mouse_y >= SCREEN_HEIGHT - 142 && mouse_y <= SCREEN_HEIGHT - 92)
            {
                SDL_RenderCopy(graphics.renderer, soundon, NULL, &psoundon_rect);

                if (mouse_pressed)
                {
                    bsoundoff = true;
                }
            }
            else
            {
                SDL_RenderCopy(graphics.renderer, soundon, NULL, &soundon_rect);

            }
        }
        else
        {
            Mix_PauseAudio(1);
            if (mouse_x >= SCREEN_WIDTH - 82 && mouse_x <= SCREEN_WIDTH - 32 && mouse_y >= SCREEN_HEIGHT - 142 && mouse_y <= SCREEN_HEIGHT - 92)
            {
                SDL_RenderCopy(graphics.renderer, soundoff, NULL, &psoundoff_rect);

                if (mouse_pressed)
                {
                    Mix_PauseAudio(0);
                    bsoundoff = false;
                }
            }
            else SDL_RenderCopy(graphics.renderer, soundoff, NULL, &soundoff_rect);


        }
    }
};

#endif