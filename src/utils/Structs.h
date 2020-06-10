#pragma once

#include "Pokitto.h"
#include "Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

struct GameContext {

    bool gameComplete;
    uint16_t time;
    GameState currentState;
    GameMode mode;

};

struct Entity {

    int16_t x;
    int16_t y;
    int8_t counter;
    Stance stance;
    Tiles tile;
    int8_t tileX;
    int8_t tileY;

};

struct TileDetails {

    int8_t x;
    int8_t y;

    bool operator== (const TileDetails &c2) const {

        return (this->x == c2.x &&
                this->y == c2.y);
    }
 
    bool operator!= (const TileDetails &c2) const {
        return !(this->x == c2.x &&
                this->y == c2.y);
    }

};
 
