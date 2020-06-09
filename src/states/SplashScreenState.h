#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class SplashScreenState {

    private:

        uint8_t counter = 0;

    public:

        void activate();
        GameContext update(GameContext gameContext);
        void render();

};