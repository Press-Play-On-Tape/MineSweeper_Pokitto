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
 