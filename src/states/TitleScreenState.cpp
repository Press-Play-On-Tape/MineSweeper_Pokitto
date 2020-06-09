#include "TitleScreenState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

constexpr const static uint8_t UPLOAD_DELAY = 16;




// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(GameContext gameContext, GameCookie *cookie) {

    this->counter = 30;
    this->stateToggle = 150;
    this->viewState = ViewState::Normal;
    this->gameMode = cookie->gameMode;
    
}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameContext TitleScreenState::update(GameContext gameContext, GameCookie *cookie) {
  
    if (this->modeDelay > 0) {

        this->modeDelay--;

        if (this->modeDelay == 0) {

            this->viewState = ViewState::Normal;

        }

    }

    if (this->counter > 0) {
        
        this->counter--;
        
    }
 


    // Update highlight ..
    
    if (Utils::getFrameCount(5) == 0) {

        this->titleSeq++;

        if (this->titleSeq > 16) this->titleSeq = 0;

    }


    // Update states ..
    
    switch (this->viewState) {

        case ViewState::Marquee:

            if (Utils::getFrameCount(2) == 0) {

                this->marquee++;

                if (this->marquee > 680) {
                    
                    this->marquee = 0;
                    this->stateToggle = 150;
                    this->viewState = ViewState::Normal;

                }

            }

            break;

        case ViewState::LevelChange:
        case ViewState::Normal:

            this->stateToggle--;

            if (this->stateToggle == 0) {
                
                this->marquee = 0;
                this->viewState = ViewState::Marquee;

            }

            break;

    }


    
	// Handle other input ..

	if (PC::buttons.pressed(BTN_A)) {

        gameContext.mode = this->gameMode;
        gameContext.currentState = GameState::PlayGame_Activate; 

	}

	if (PC::buttons.pressed(BTN_UP)) {

        this->viewState = ViewState::LevelChange;
        this->modeDelay = 60;
        this->stateToggle = 300;

        switch (this->gameMode) {
            
            case GameMode::Easy:
                break;
            
            case GameMode::Medium:
                this->gameMode = GameMode::Easy;
                break;
            
            case GameMode::Hard:
                this->gameMode = GameMode::Medium;
                break;
        
        }

        cookie->gameMode = this->gameMode;
        cookie->saveCookie();

    }

	if (PC::buttons.pressed(BTN_DOWN)) {

        this->viewState = ViewState::LevelChange;
        this->modeDelay = 60;
        this->stateToggle = 300;

        switch (this->gameMode) {
            
            case GameMode::Easy:
                this->gameMode = GameMode::Medium;
                break;
            
            case GameMode::Medium:
                this->gameMode = GameMode::Hard;
                break;
            
            case GameMode::Hard:
                break;
        
        }

        cookie->gameMode = this->gameMode;
        cookie->saveCookie();

    }

	if (PC::buttons.pressed(BTN_B)) {

        gameContext.gameComplete = false;
        gameContext.currentState = GameState::HighScore_Activate; 
        
    }

    return gameContext;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(GameContext gameContext, GameCookie *cookie) {

    uint8_t mode = static_cast<uint8_t>(gameContext.mode);
    
    PD::clear();
    PD::drawBitmap(0, 0, Images::TitleScreen);

    if ((this->viewState == ViewState::Normal && this->counter == 0) || (this->viewState == ViewState::StartGame && ((this->counter / 20) % 2) == 1)) {
        
        PD::setCursor(47, 140);
        PD::setColor(5, 11);
        PD::print("Press A to Start");
        
    }

    if (this->viewState == ViewState::LevelChange) {
        
        PD::setCursor(47, 140);
        PD::setColor(5, 11);
        PD::print("Level: ");

        switch (this->gameMode) {

            case GameMode::Easy:
                PD::print("Easy");
                break;
            
            case GameMode::Medium:
                PD::print("Medium");
                break;
            
            case GameMode::Hard:
                PD::print("Hard");
                break;

        }
        
    }

    if (this->viewState == ViewState::Marquee) {

        const char highScores[] = { 'H', 'I', 'G', 'H', ' ', 'S', 'C', 'O', 'R', 'E', 'S' };
        uint8_t x = 0;

        uint8_t marqueeOffset = this->marquee % 10;
        uint8_t marquee10 = this->marquee / 10;

        PD::setCursor(47 - (this->marquee % 10), 140);
        PD::setColor(5, 11);

        for (uint8_t i = marquee10; i < marquee10 + 16; i++) {

            switch (i) {

                case 16 ... 19:
                    PD::setColor(5, 11);
                    this->printSingleChar(highScores[i - 16]);
                    break;

                case 21 ... 26:
                    PD::setColor(5, 11);
                    this->printSingleChar(highScores[i - 16]);
                    break;

                // Player 0

                case 29 ... 31:
                    PD::setColor(5, 11);
                    this->printChar(cookie->initials[mode][0][i - 29]);
                    break;

                case 33 ... 35:
                    {
                        PD::setColor(8, 11);
                        uint8_t digits[3] = {};
                        Utils::extractDigits(digits, cookie->score[mode][0]);
                        PD::print(digits[35 - i], 10);
                    }
                    break;

                // Player 1

                case 37 ... 39:
                    PD::setColor(5, 11);
                    this->printChar(cookie->initials[mode][1][i - 37]);
                    break;

                case 41 ... 43:
                    {
                        PD::setColor(8, 11);
                        uint8_t digits[3] = {};
                        Utils::extractDigits(digits, cookie->score[mode][1]);
                        PD::print(digits[43 - i], 10);
                    }
                    break;

                // Player 2

                case 45 ... 47:
                    PD::setColor(5, 11);
                    this->printChar(cookie->initials[mode][2][i - 45]);
                    break;

                case 49 ... 51:
                    {
                        PD::setColor(8, 11);
                        uint8_t digits[3] = {};
                        Utils::extractDigits(digits, cookie->score[mode][2]);
                        PD::print(digits[51 - i], 10);
                    }
                    break;

                // Player 3

                case 53 ... 55:
                    PD::setColor(5, 11);
                    this->printChar(cookie->initials[mode][3][i - 53]);
                    break;

                case 57 ... 59:
                    {
                        PD::setColor(8, 11);
                        uint8_t digits[3] = {};
                        Utils::extractDigits(digits, cookie->score[mode][3]);
                        PD::print(digits[59 - i], 10);
                    }
                    break;

                // Player 4

                case 61 ... 63:
                    PD::setColor(5, 11);
                    this->printChar(cookie->initials[mode][4][i - 61]);
                    break;

                case 65 ... 67:
                    {
                        PD::setColor(8, 11);
                        uint8_t digits[3] = {};
                        Utils::extractDigits(digits, cookie->score[mode][4]);
                        PD::print(digits[67 - i], 10);
                    }
                    break;                    

                default:
                    PD::setColor(11, 11);
                    PD::print('-');
                    break;

            }

        }


        PD::setColor(11);
        PD::fillRect(36, 140, 10, 10);
        PD::fillRect(174, 140, 15, 10);
    }
    
}


void TitleScreenState::printSingleChar(char theChar) {

    char output[] = { ' ', '\0' };
    memcpy(&output, &theChar, 1);
    PD::print(&output[0]);
    
}

void TitleScreenState::printChar(uint8_t charIndex) {

    switch (charIndex) {

        case 1 ... 26:
            charIndex = charIndex + 64;
            break;

        case 27 ... 36:
            charIndex = charIndex + 21;
            break;

        case 37:
            charIndex = 46;
            break;
        
    }

    char output[] = { ' ', '\0' };
    memcpy(&output, &charIndex, 1);
    PD::print(&output[0]);
    
}
