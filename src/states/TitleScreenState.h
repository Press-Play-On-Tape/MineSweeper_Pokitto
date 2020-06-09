#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../utils/Structs.h"
#include "../utils/GameCookie.h"

class TitleScreenState {

    enum class ViewState : uint8_t {
    	Normal,
    	StartGame,
        Marquee,
        LevelChange
    };
    
    
    private:

        ViewState viewState;
        GameMode gameMode = GameMode::Easy;

        uint8_t counter = 0;
        uint8_t titleSeq = 0;
        uint16_t marquee = 0;
        uint16_t stateToggle = 0;
        uint8_t modeDelay = 0;

        void printSingleChar(char theChar);
        void printChar(uint8_t charIndex);
//        void printNumber(uint8_t number);
        

    public:	
        
        void activate(GameContext gameContext, GameCookie *cookie);
        GameContext update(GameContext gameContext, GameCookie *cookie);
        void render(GameContext gameContext, GameCookie *cookie);

};

