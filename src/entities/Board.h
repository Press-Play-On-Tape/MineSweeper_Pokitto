#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "../utils/Structs.h"
#include "../utils/Queue.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

class Board {

    public:

        Board() {}  

        uint8_t getCursorX();
        uint8_t getCursorY();
        uint8_t getWidth();
        uint8_t getHeight();
        uint8_t getBombCount();
        GameMode getGameMode();
        uint8_t getTileSize();
        uint8_t getTileSpacing();

        void setCursorX(uint8_t x);
        void setCursorY(uint8_t y);
        void setGameMode(GameMode mode);

        Tiles getTile();
        Tiles getTile(uint16_t i);
        Tiles getTile(uint8_t x, uint8_t y);
        
        void setTile(uint16_t i, Tiles tile);
        void setTile(uint8_t x, uint8_t y, Tiles tile);

        Tiles getState();
        Tiles getState(uint16_t i);
        Tiles getState(uint8_t x, uint8_t y);
        
        void setState(uint16_t i, Tiles tile);
        void setState(uint8_t x, uint8_t y, Tiles tile);

        void setBoard();
        void toggleFlag();
        void exposeBoard();
        bool isComplete();
        void update();

        Tiles uncoverTile();
        Tiles uncoverTile(int8_t x, int8_t y);

    private:
        
        uint8_t board[18][32];
        uint8_t cursorX = 0;
        uint8_t cursorY = 0;
        uint8_t height = 0;
        uint8_t width = 0;
        
        GameMode gameMode = GameMode::Easy;
        Queue<TileDetails, 100> tilesToUncover;

};
