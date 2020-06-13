#include "HighScoreState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void HighScoreState::activate(GameContext gameContext, GameCookie *cookie) {
	
	this->cursor = 0;

    if (gameContext.gameComplete) {

        uint32_t index = cookie->setLastScore(gameContext.mode, gameContext.time);

        if (index == 0) {

            //Utils::playMusicStream(SDStream::ScoreTop);
        
        }
        else if (index < 5) {

            //Utils::playMusicStream(SDStream::ScoreOther);         
            
        }

    }
    else {

        cookie->setLastScore(gameContext.mode, 1000);

    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameContext HighScoreState::update(GameContext gameContext, GameCookie *cookie) {
	
    bool flash = Utils::getFrameCountHalf(48);
    uint32_t index = cookie->getScoreIndex();
    uint8_t mode = static_cast<uint8_t>(gameContext.mode);


	// Handle other input ..

    if (index != NO_SCORE) {

        if (PC::buttons.pressed(BTN_LEFT) && this->cursor > 0) {
            this->cursor--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->cursor < 2) {
            this->cursor++;
        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 16)) {

            uint32_t val = cookie->initials[mode][index][this->cursor];
            val++;
            if (val > 38) val = 0;
            cookie->initials[mode][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 16)) {

            uint32_t val = cookie->initials[mode][index][this->cursor];
            if (val == 0) val = 38;
            val--;
            cookie->initials[mode][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_A) && cookie->initials[mode][index][0] != 0 && cookie->initials[mode][index][1] != 0 && cookie->initials[mode][index][2] != 0) {

            cookie->saveCookie();
            cookie->setLastScore(GameMode::Easy, 1000);
            
        }

    }
    else {
     
        if (PC::buttons.pressed(BTN_A)) {
        	gameContext.currentState = GameState::TitleScreen_Activate; 
        }
   
    }

    return gameContext;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void HighScoreState::render(GameContext gameContext, GameCookie *cookie) {
	
    bool flash = Utils::getFrameCountHalf(48);
    uint32_t index = cookie->getScoreIndex();
    uint8_t mode = static_cast<uint8_t>(gameContext.mode);

    PD::clear();
    PD::setColor(8, 3);   
    PD::drawBitmap(0, 0, Images::Highscore);



    // Has a new High Score been set ?

    PD::setColor(11);

    if (index != NO_SCORE) {
    
        PD::setColor(11);
        uint8_t digits[8] = {};
        Utils::extractDigits(digits, cookie->lastScore);


        // Render Highlights ..
        
        PD::drawBitmap(113, 104 + (index * 11), Images::HS_Highlight);
        PD::drawBitmap(204, 104 + (index * 11), Images::HS_Highlight);



        // Render score and name entry ..

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                PD::drawBitmap(122 + (x * 10), 104 + (index * 11), Images::HS_Font[cookie->initials[mode][index][x]]);
                
            }

        }
        
        for (uint8_t j = 3; j > 0; --j) {
        
            PD::drawBitmap(200 - (j * 10), 104 + (index * 11), Images::HS_Font[digits[j - 1] + 27]);
        
        }

    }


    // Render remaining scores ..

    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[3] = {};
        Utils::extractDigits(digits, cookie->score[mode][y]);
        
        if (index != y) {

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::drawBitmap(122 + (x * 10), 104 + (y * 11), Images::HS_Font[cookie->initials[mode][y][x]]);

            }

            for (uint8_t j = 3; j > 0; --j) {
            
                PD::drawBitmap(200 - (j * 10), 104 + (y * 11), Images::HS_Font[digits[j - 1] + 27]);
            
            }

        }
        
    }

}
