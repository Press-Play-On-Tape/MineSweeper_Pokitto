#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../utils/Structs.h"
#include "../utils/GameCookie.h"
#include "../entities/Entities.h"

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
        Entity soldiers[8];

        uint8_t counter = 0;
        uint8_t titleSeq = 0;
        uint16_t marquee = 0;
        uint16_t stateToggle = 0;
        uint8_t modeDelay = 0;
        File mainThemeFile;

        void printSingleChar(char theChar);
        void printChar(uint8_t charIndex);

    public:	
        
        void activate(GameContext gameContext, GameCookie *cookie);
        GameContext update(GameContext gameContext, GameCookie *cookie);
        void render(GameContext gameContext, GameCookie *cookie);

};

