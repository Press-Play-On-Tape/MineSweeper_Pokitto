#pragma once

#include "Pokitto.h"
#include "../entities/Entities.h"
#include "../utils/Enums.h"
#include "src/utils/GameCookie.h"
#include <LibAudio>

class GamePlayState {

    private:

        Board board;
        Entity soldiers[7];
        Entity bullets[4];
        Entity puffs[2];

        int16_t xOffset;
        int16_t yOffset;
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

    public:

        void activate(GameContext gameContext);
        GameContext update(GameContext gameContext, GameCookie *cookie);
        void render();

    private:

        void renderBoard();
        void renderCursor();
        void updateBullets();
        void playSoundEffect(SoundEffect soundEffect, uint8_t channel);


};





