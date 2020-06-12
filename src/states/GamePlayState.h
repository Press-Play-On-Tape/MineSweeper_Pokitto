#pragma once

#include "Pokitto.h"
#include "../entities/Entities.h"
#include "../utils/Enums.h"
#include "src/utils/GameCookie.h"
#include <LibAudio>

class GamePlayState {

    private:

        Board board;
        Entity soldiers[8];
        Entity bullets[4];
        Entity puffs[2];

        int16_t xOffset;
        int16_t yOffset;
        int16_t xOffset_Scroll;
        int16_t yOffset_Scroll;
        uint16_t time;
        uint16_t bombCount;
        uint8_t xCursor_GameOver;
        uint8_t yCursor_GameOver;
        uint8_t bombExplosion;
        uint16_t counter;
        uint16_t idx;

        bool gameOver;
        bool gameComplete;
        
        File mainThemeFile;
        File soundEffectFile;

        uint16_t scroll_overall;
        uint16_t scroll_increment;
        uint16_t scroll_fastest;
        uint16_t scroll_count;
        uint16_t scroll_distance;
        uint16_t scroll_speed;


    public:

        void activate(GameContext gameContext);
        GameContext update(GameContext gameContext, GameCookie *cookie);
        void render();

    private:

        void renderBoard();
        void renderCursor();
        void updateBullets();
        uint16_t updateSoldiers(bool allSoldiers, uint16_t idx);
        void playSoundEffect(SoundEffect soundEffect, uint8_t channel);
        void startScroll();


};





