#pragma once

#include "Pokitto.h"
#include <LibAudio>

#include "utils/Enums.h"
#include "utils/Structs.h"
#include "images/Images.h"
#include "entities/Entities.h"
#include "states/States.h"

class Game {
    
    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        TitleScreenState titleScreenState;
        SplashScreenState splashScreenState;
        GamePlayState gamePlayState;
        HighScoreState highScoreState;

    private:

        GameContext gameContext;
        GameCookie *cookie;

};


