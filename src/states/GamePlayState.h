#pragma once

#include "Pokitto.h"
#include "../entities/Entities.h"
#include "../utils/Enums.h"
#include "src/utils/GameCookie.h"

class GamePlayState {

    private:

        Board board;
        int16_t xOffset;
        int16_t yOffset;
        uint16_t time;
        uint16_t bombCount;
        uint8_t xCursor_GameOver;
        uint8_t yCursor_GameOver;

        bool gameOver;
        bool gameComplete;
    
    public:

        void activate(GameContext gameContext);
        GameContext update(GameContext gameContext, GameCookie *cookie);
        void render();

    private:

        void renderBoard();
        void renderCursor();

};





