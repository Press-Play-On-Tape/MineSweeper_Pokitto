#include "GamePlayState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


const bool scroll[] = { false, true, true };

const uint8_t marginLeft[] =        { 0, 0, 0 };
const uint8_t marginRight[] =       { 0, 0, 0 };
const uint8_t marginTop[] =         { 0, 0, 0 };
const uint8_t marginBottom[] =      { 0, 0, 0 };

const uint8_t xScroll_Left[] =      { 0, 7, 7 };
const uint8_t xScroll_Right[] =     { 0, 11, 25 };
const uint8_t yScroll_Top[] =       { 0, 5, 5 };
const uint8_t yScroll_Bottom[] =    { 0, 12, 12 };

const int8_t shakeXOffset[] =       { -1,  0, 0, 1, 0, 0, 1, -1,  0, -1,  0, 1,  0, -2, 0, 2, 0, 2,  0, -2 };
const int8_t shakeYOffset[] =       {  0, -1, 0, 0, 1, 0, 0,  1, -1,  0, -1, 0, -1,  0, 2, 0, 2, 0, -2,  0 };

const int8_t soldierX[] =           { -20, -32, -42, -52, -18, -29, -40 };
const uint8_t soldierY[7][272] =    {
                                    { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, // 16
                                      30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 32, 32, 32, 32, // 32
                                      31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, // 48
                                      31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, // 64
                                      31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, // 80
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 96
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 112
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 128
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 144
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 160
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 176
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 192
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 208
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 224
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 240
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 256
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, // 272
                                       },
                                    { 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 16
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 32
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 48
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 64
                                      38, 38, 38, 38, 38, 37, 37, 37, 37, 36, 36, 36, 36, 35, 35, 35, // 80
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 96
                                      32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, // 112
                                      36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, // 128
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 144
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 160
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 176
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 192
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 208
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 224
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 240
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 256
                                      38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, // 272
                                       },
                                    { 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 16
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 32
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 48
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 64
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, // 80
                                      27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, // 96
                                      31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 112
                                      32, 32, 31, 31, 31, 30, 30, 30, 29, 29, 29, 28, 28, 28, 27, 27, // 128
                                      27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 144
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 160
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 176
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 192
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 208
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 224
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 240
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 256
                                      26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, // 272
                                       },
                                    { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 32
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 48
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 64
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 80
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 96
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 112
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 128
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 144
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 160
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 176
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 192
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 208
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 224
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 240
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 256
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 272
                                       },
                                    { 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 16
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 32
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 48
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 125, 125, // 64
                                      125, 125, 124, 124, 124, 124, 124, 124, 124, 124, 125, 125, 125, 125, 126, 126, // 80
                                      126, 126, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, // 96
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 112
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 128
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 144
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 160
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 176
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 192
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 208
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 224
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 240
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 256
                                      126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, // 272
                                       },
                                    { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 16
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 32
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 48
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 64
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 80
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 129, 129, 130, 130, // 96
                                      130, 130, 130, 130, 130, 130, 130, 130, 129, 129, 129, 129, 129, 128, 128, 128, // 112
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 128
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 144
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 160
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 176
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 192
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 208
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 224
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 240
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 256
                                      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, // 272
                                       },
                                    { 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 16
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 32
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 48
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 64
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 80
                                      122, 122, 122, 122, 122, 122, 123, 123, 123, 123, 124, 124, 124, 124, 125, 125, // 96
                                      125, 125, 126, 126, 126, 126, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, // 112
                                      128, 128, 128, 127, 127, 127, 127, 126, 126, 126, 126, 125, 125, 125, 125, 124, // 128
                                      124, 124, 124, 123, 123, 123, 123, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 144
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 160
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 176
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 192
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 208
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 224
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 240
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 256
                                      122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, // 272
                                       }
                                    };


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void GamePlayState::activate(GameContext gameContext) {

    this->board.setGameMode(gameContext.mode);
    this->board.setBoard();
    this->board.setCursorX(1);
    this->board.setCursorY(1);

    this->xOffset = 0;
    this->yOffset = 0;
    this->gameOver = false;
    this->gameComplete = false;
    this->time = 0;
    this->bombCount = 0;
    this->bombExplosion = 0;
    this->counter = 0;
    this->idx = 0;

    for (uint8_t i = 0; i < 7; i++) {

        this->soldiers[i].x = soldierX[i];
        this->soldiers[i].y = soldierY[i][0];
        this->soldiers[i].stance = Stance::Walking;

    }

    for (uint8_t i = 0; i < 4; i++) {

        this->bullets[i].x = -10;
        this->bullets[i].y = -10;

    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameContext GamePlayState::update(GameContext gameContext, GameCookie *cookie) { 

    bool scrollBoard = scroll[ static_cast<uint8_t>(this->board.getGameMode()) ];

    if (!this->gameOver && Utils::isFrameCount(30) && this->time < 999) {
        this->time++;
    }

    if (this->bombExplosion > 0) {
        
        this->bombExplosion--;

        if (this->bombExplosion == 0) {

            this->board.exposeBoard();

        }

    }


    for (uint8_t i = 0; i < 2; i++) {

        if (this->puffs[i].counter > 0) {
            
            this->puffs[i].counter--;

            if (this->puffs[i].counter == 0) {

                this->puffs[i].x = -10;

            }
            else if (puffs[i].counter == 8) {

                this->board.setTile(puffs[i].tileX, puffs[i].tileY, puffs[i].tile);

            }

        }

    }


    if (this->counter > 0) {

        this->counter--;
printf("%i %i \n", counter, idx);

        switch (counter) {

            case 910 ... 999:
            
                if (Utils::getFrameCount(4) == 0) {

                    if (this->xOffset > -4) this->xOffset--;
                    if (this->yOffset > 0)  this->yOffset--;
                }
                
                if (this->xOffset == -4 && this->yOffset == 0) this->counter = 910;
                break;
                
            case 865 ... 909:
            case 560 ... 799:

                for (uint8_t i = 0; i < 7; i++) {

                    this->soldiers[i].x++;
                    this->soldiers[i].y = soldierY[i][idx];
                    this->soldiers[i].stance = Stance::Walking;

                }
                idx++;
                break;

            case 559:
                gameContext.gameComplete = this->gameComplete;
                gameContext.time = this->time;
                gameContext.currentState = GameState::HighScore_Activate;
                break;
          
            case 854 ... 864:

                for (uint8_t i = 0; i < 7; i++) {

                    this->soldiers[i].stance = Stance::Standing;

                }
                break;
          
            case 853:
                this->bullets[0].x = this->soldiers[0].x + 9;
                this->bullets[0].y = this->soldiers[0].y + 7;
                break;

            case 836:
                this->updateBullets();
                this->bullets[1].x = this->soldiers[4].x + 9;
                this->bullets[1].y = this->soldiers[4].y + 7;
                break;

            case 824:
                this->updateBullets();
                this->bullets[2].x = this->soldiers[0].x + 9;
                this->bullets[2].y = this->soldiers[0].y + 7;
                break;

            case 816:
                this->updateBullets();
                this->bullets[3].x = this->soldiers[4].x + 9;
                this->bullets[3].y = this->soldiers[4].y + 7;
                break;

            case 837 ... 852:
            case 825 ... 835:
            case 817 ... 823:
            case 800 ... 815:
                this->updateBullets();
                break;


                
        }

    }
    
    this->board.update();



    uint8_t xLeftScroll = xScroll_Left[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t xRightScroll = xScroll_Right[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t yTopScroll = yScroll_Top[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t yBottomScroll = yScroll_Bottom[ static_cast<uint8_t>(gameContext.mode) ];


    // Handle player actions ..

    if (this->counter == 0) {

        if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 3)) {

            if (this->board.getCursorX() > 1) this->board.setCursorX(board.getCursorX() - 1);

            if (scrollBoard) {

                if (this->board.getCursorX() >= xLeftScroll && this->board.getCursorX() < xRightScroll) {
                    this->xOffset--;
                }

            }
            
        }

        if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 3)) {
            
            if (this->board.getCursorX() < this->board.getWidth() - 2) this->board.setCursorX(this->board.getCursorX() + 1);

            if (scrollBoard) {

                if (this->board.getCursorX() > xLeftScroll && this->board.getCursorX() <= xRightScroll) {
                    this->xOffset++;
                }

            }

        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 3)) {
            
            if (board.getCursorY() > 1) board.setCursorY(board.getCursorY() - 1);

            if (scrollBoard) {

                if (this->board.getCursorY() >= yTopScroll && this->board.getCursorY() < yBottomScroll) {
                    this->yOffset--;
                }

            }
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 3)) {
            
            if (board.getCursorY() < board.getHeight() - 2) board.setCursorY(board.getCursorY() + 1);
            
            if (scrollBoard) {

                if (this->board.getCursorY() > yTopScroll && this->board.getCursorY() <= yBottomScroll) {
                    this->yOffset++;
                }

            }

        }

    }

    if (!this->gameOver) {

        if (PC::buttons.pressed(BTN_A) && board.getState() == Tiles::Tile) {
            
            Tiles tile = board.uncoverTile();

            if (tile == Tiles::Bomb) {

                this->xCursor_GameOver = this->board.getCursorX();
                this->yCursor_GameOver = this->board.getCursorY();
                this->gameOver = true;
                this->bombExplosion = 29;

            }
            else if (this->board.isComplete()) {

                this->gameComplete = true;
                this->gameOver = true;

            }
            
        }

        if (PC::buttons.pressed(BTN_B) && (board.getState() == Tiles::Tile || board.getState() == Tiles::Flag || board.getState() == Tiles::QuestionMark)) {
            
            if (board.getState() == Tiles::Tile) {
                this->bombCount++;
            }
            else if (board.getState() == Tiles::Flag) {
                this->bombCount--;
            }

            board.toggleFlag();

            if (this->board.isComplete()) {

                this->gameComplete = true;
                this->gameOver = true;
                this->counter = 1000;

            }
            
        }

    }
    else {

        if (PC::buttons.pressed(BTN_A)) {

            gameContext.gameComplete = this->gameComplete;
            gameContext.time = this->time;
            gameContext.currentState = GameState::HighScore_Activate;

        }

    }

    return gameContext;

}

void GamePlayState::render() {

    this->renderBoard();
    this->renderCursor();

}


void GamePlayState::renderBoard() {

    int8_t shakeX = (this->bombExplosion < 10 ? 0 : shakeXOffset[this->bombExplosion - 10]);
    int8_t shakeY = (this->bombExplosion < 10 ? 0 : shakeYOffset[this->bombExplosion - 10]);

    uint8_t width = this->board.getWidth();
    uint8_t height = this->board.getHeight();

    int8_t xMarginLeft =   marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ] + shakeX;
    int8_t xMarginRight =  marginRight[ static_cast<uint8_t>(this->board.getGameMode()) ] + shakeY;
    int8_t yMarginTop =    marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ] + shakeX;
    int8_t yMarginBottom = marginBottom[ static_cast<uint8_t>(this->board.getGameMode()) ] + shakeY;
    
    uint8_t tileSpacing = this->board.getTileSpacing();

    PD::fillScreen(11);

    for (uint8_t y = 0; y < height; y++) {

        for (uint8_t x = 0; x < width; x++) {
            
            Tiles state = board.getState(x, y);

            switch (state) {
                
                case Tiles::Blank:
                    {
                        Tiles tile = board.getTile(x, y);

                        if (this->gameOver && !this->gameComplete && this->xCursor_GameOver == x && this->yCursor_GameOver == y) {

                            if (this->bombExplosion > 0 || (this->bombExplosion == 0 && Utils::getFrameCount(32) >= 16)) {

                                PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Bomb);   
                                
                            }
                            else {

                                PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Blank);   
                                
                            }


                            if (this->bombExplosion >= 10 && this->bombExplosion <= 25) {

                                uint8_t frame = (25 - this->bombExplosion) / 4;
                                PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Puff[frame]);   

                            }  


                        }
                        else {

                            PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Tiles[ static_cast<uint8_t>(tile) ]);                        

                        }
                    }
                    break;
                    
                case Tiles::QuestionMark:
                    PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::QuestionMark);
                    break;
                    
                case Tiles::Tile:

                    if ((x + (y %2 )) % 2 == 0) {
                        PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Tile);
                    }
                    else {
                        PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Tile_Rev);
                    }
                    break;

                case Tiles::Flag:
                    {
                        uint8_t frame = Utils::getFrameCount(24) / 5;
                        PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Flags[frame]);
                    }
                    break;
                    
                
            }

        }
        
    }


    // Draw Soldiers ..

    for (uint8_t i = 0; i < 7; i++) {

        switch (this->soldiers[i].stance) {

            case Stance::Walking:

                PD::drawBitmap(this->soldiers[i].x, this->soldiers[i].y, Images::Soldiers[Utils::getFrameCount(4) / 2]);
                break;

            case Stance::Standing:
                PD::drawBitmap(this->soldiers[i].x, this->soldiers[i].y, Images::Soldiers[0]);
                break;

        }

    }

    for (uint8_t i = 0; i < 4; i++) {

        if (this->bullets[i].x > 0) {

            PD::drawPixel(this->bullets[i].x, this->bullets[i].y, 0);

        }

    }

    for (uint8_t i = 0; i < 2; i++) {

        if (this->puffs[i].x > 0) {

            uint8_t frame = (15 - this->puffs[i].counter) / 4;
            PD::drawBitmap(this->puffs[i].x, this->puffs[i].y, Images::Puff[frame]);

        }

    }


    // Draw counter ..

    PD::setColor(0, 3);
    PD::fillRect(190, 0, 40, 10);
    PD::setCursor(192, 2);
    PD::setColor(3, 0);
    if (this->time < 100)   { PD::print("0"); }
    if (this->time < 10)    { PD::print("0"); }
    PD::print(this->time, 10);    


    // Draw bombs ..

    PD::setColor(0, 3);
    PD::fillRect(190, 165, 40, 10);
    PD::setCursor(192, 167);
    PD::setColor(3, 0);
    if (this->bombCount < 100)   { PD::print("0"); }
    if (this->bombCount < 10)    { PD::print("0"); }
    PD::print(this->bombCount, 10);    


    // Draw complete ..

    if (this->gameOver && this->gameComplete) {

        PD::drawBitmap(40, 70, Images::Congratulations);
        
    }

    if (this->gameOver && !this->gameComplete && this->bombExplosion == 0) {

        PD::drawBitmap(40, 70, Images::YouLose);
        
    }
    

}


void GamePlayState::renderCursor() {

    if (this->bombExplosion == 0 && this->counter == 0) {

        uint8_t xMarginLeft = marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t xMarginRight = marginRight[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t yMarginTop = marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t yMarginBottom = marginBottom[ static_cast<uint8_t>(this->board.getGameMode()) ];
        
        PD::drawBitmap(xMarginLeft + ((board.getCursorX() - this->xOffset) * this->board.getTileSpacing()) - 1 + 3, yMarginTop + ((board.getCursorY() - this->yOffset) * this->board.getTileSpacing()) - 1 + 3, Images::Pointer);
        
    }
    
}

void GamePlayState::updateBullets() {

    const uint8_t puffX = 64;
    const uint8_t puffY[] = { 32, 128 };
    
    for (uint8_t i = 0; i < 4; i++) {

        if (this->bullets[i].x > 0) {
            
            this->bullets[i].x = this->bullets[i].x + 3;

            if (this->bullets[i].x > 72 && this->bullets[i].x < 76) {

                if (i >= 2) {

                    this->puffs[i % 2].x = puffX;
                    this->puffs[i % 2].y = puffY[i % 2];
                    this->puffs[i % 2].counter = 15;
                    this->puffs[i % 2].tile = Tiles::Fence_L_Broken;
                    this->puffs[i % 2].tileX = 0;
                    this->puffs[i % 2].tileY = (i % 2 == 0 ? 2 : 8);

                }
            
                this->bullets[i].x = -1;

            }

        }

    }

}