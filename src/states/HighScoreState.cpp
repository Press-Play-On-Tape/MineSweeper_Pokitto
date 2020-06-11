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
        
    if (index != NO_SCORE) {
    
        PD::setColor(11);
        PD::fillRect(18, 80, 184, 11);
        PD::drawBitmap(21, 82, Images::Char_E);
        PD::drawBitmap(31, 82, Images::Char_N);
        PD::drawBitmap(41, 82, Images::Char_T);
        PD::drawBitmap(51, 82, Images::Char_E);
        PD::drawBitmap(61, 82, Images::Char_R);

        PD::drawBitmap(76, 82, Images::Char_Y);
        PD::drawBitmap(86, 82, Images::Char_O);
        PD::drawBitmap(96, 82, Images::Char_U);
        PD::drawBitmap(106, 82, Images::Char_R);

        PD::drawBitmap(121, 82, Images::Char_I);
        PD::drawBitmap(131, 82, Images::Char_N);
        PD::drawBitmap(141, 82, Images::Char_I);
        PD::drawBitmap(151, 82, Images::Char_T);
        PD::drawBitmap(161, 82, Images::Char_I);
        PD::drawBitmap(171, 82, Images::Char_A);
        PD::drawBitmap(181, 82, Images::Char_L);
        PD::drawBitmap(191, 82, Images::Char_S);

        uint8_t digits[8] = {};
        Utils::extractDigits(digits, cookie->lastScore);


        // Render Highlights ..
        
        PD::drawBitmap(38, 115 + (index * 11), Images::HS_Highlight);
        PD::drawBitmap(180, 115 + (index * 11), Images::HS_Highlight);



        // Render score and name entry ..
        
        for (uint8_t j = 3; j > 0; --j) {
        
            PD::drawBitmap(78 - (j * 10), 115 + (index * 11), Images::HS_Font[digits[j - 1] + 27]);
        
        }

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                PD::drawBitmap(144 + (x * 10), 115 + (index * 11), Images::HS_Font[cookie->initials[mode][index][x]]);
                
            }

        }

    }
    else {

        PD::setColor(11);
        PD::fillRect(48, 80, 131, 11);
        PD::drawBitmap(47, 82, Images::Char_T);
        PD::drawBitmap(57, 82, Images::Char_O);
        PD::drawBitmap(67, 82, Images::Char_P);
        PD::drawBitmap(82, 82, Images::Char_F);
        PD::drawBitmap(92, 82, Images::Char_I);
        PD::drawBitmap(102, 82, Images::Char_V);
        PD::drawBitmap(112, 82, Images::Char_E);

        PD::drawBitmap(127, 82, Images::Char_T);
        PD::drawBitmap(137, 82, Images::Char_I);
        PD::drawBitmap(147, 82, Images::Char_M);
        PD::drawBitmap(157, 82, Images::Char_E);
        PD::drawBitmap(167, 82, Images::Char_S);

    }
        


    // Render remaining scores ..
    
    PD::drawBitmap(43, 102, Images::Char_T);
    PD::drawBitmap(53, 102, Images::Char_I);
    PD::drawBitmap(63, 102, Images::Char_M);
    PD::drawBitmap(73, 102, Images::Char_E);

    PD::drawBitmap(139, 102, Images::Char_N);
    PD::drawBitmap(149, 102, Images::Char_A);
    PD::drawBitmap(159, 102, Images::Char_M);
    PD::drawBitmap(169, 102, Images::Char_E);

    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[3] = {};
        Utils::extractDigits(digits, cookie->score[mode][y]);
        
        if (index != y) {

            for (uint8_t j = 3; j > 0; --j) {
            
                PD::drawBitmap(78 - (j * 10), 115 + (y * 11), Images::HS_Font[digits[j - 1] + 27]);
            
            }

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::drawBitmap(144 + (x * 10), 115 + (y * 11), Images::HS_Font[cookie->initials[mode][y][x]]);

            }

        }
        
    }

}
