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

const int8_t soldierX[] =           { -20, -56, -69, -106, -20, -56, -69, -106 };
const uint8_t soldierY[3][336] =    {
                                    { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, // 16
                                      48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, // 32
                                      48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, // 48
                                      48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, // 64
                                      48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, // 80
                                      48, 48, 48, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, // 96
                                      42, 41, 41, 40, 40, 39, 39, 38, 38, 37, 37, 36, 36, 35, 35, 34, // 112
                                      34, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 128
                                      33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, // 144
                                      38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, // 160
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 176
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 192
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 208
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 224
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 240
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 256
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 272
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 288
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 304
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 320
                                      43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, // 336
                                       },
                                    { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 16
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 32
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 48
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 64
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 80
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, // 96
                                      19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, // 112
                                      27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 32, 32, 32, 32, // 128
                                      32, 32, 32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, // 144
                                      25, 25, 24, 24, 23, 23, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18, // 160
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 176
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 192
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 178
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 224
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 240
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 256
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 272
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 288
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 304
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 320
                                      17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, // 336
                                       },
                                    { 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 16
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 28
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 48
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 64
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 80
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 96
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 112
                                      28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, // 128
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 144
                                      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 160
                                      31, 31, 30, 30, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 176
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 192
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 224
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 240
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 256
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 256
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 272
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 288
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 304
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 320
                                      28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, // 336
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

    for (uint8_t i = 0; i < 8; i++) {

        this->soldiers[i].x = soldierX[i];
        this->soldiers[i].y = 0;
        this->soldiers[i].stance = Stance::Walking;

    }

    for (uint8_t i = 0; i < 4; i++) {

        this->bullets[i].x = -10;
        this->bullets[i].y = -10;

    }

    for (uint8_t i = 0; i < 2; i++) {
        
        this->puffs[i].counter = 0;

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

        switch (counter) {

            case 910 ... 999:
            
                if (this->scroll_distance < (this->scroll_increment * this->scroll_fastest)) {

                    this->scroll_count++;

                    if (this->scroll_count >= scroll_increment) {

                        this->scroll_count = 0;
                        this->scroll_speed++;

                    }

                }
                else if (this->scroll_distance >= scroll_overall - (this->scroll_fastest * (1 + this->scroll_increment))) {

                    this->scroll_count++;

                    if (this->scroll_count >= this->scroll_increment) {

                        this->scroll_count = 0;
                        if (this->scroll_speed > 1) this->scroll_speed--;

                    }

                }
                else {

                    this->scroll_count = 0;

                }

                if (this->xOffset > -this->board.getTileSpacing() * 4)  this->xOffset = this->xOffset - scroll_speed;
                if (this->yOffset > 0)                                  this->yOffset = this->yOffset - scroll_speed;
                
                if ((this->xOffset <= -this->board.getTileSpacing() * 4) && this->yOffset <= 0) this->counter = 910;

                this->scroll_distance  =this->scroll_distance + scroll_speed;

                break;
                
            case 865 ... 909:
            case 585 ... 799:
                idx = updateSoldiers(true, idx);
                break;

            case 584: 
                gameContext.gameComplete = this->gameComplete;
                gameContext.time = this->time;
                gameContext.currentState = GameState::HighScore_Activate;
                break;
          
            case 854 ... 864:
                this->soldiers[0].stance = Stance::Standing;
                this->soldiers[4].stance = Stance::Standing;
                idx = updateSoldiers(false, idx);
                break;
          
            case 853:
                this->bullets[0].x = this->soldiers[0].x + 9;
                this->bullets[0].y = this->soldiers[0].y + 7;
                this->playSoundEffect(SoundEffect::Bullet, 1);
                idx = updateSoldiers(false, idx);
                break;

            case 836:
                this->updateBullets();
                this->bullets[1].x = this->soldiers[4].x + 9;
                this->bullets[1].y = this->soldiers[4].y + 7;
                this->playSoundEffect(SoundEffect::Bullet, 1);
                idx = updateSoldiers(false, idx);
                break;

            case 830:
                this->updateBullets();
                this->bullets[2].x = this->soldiers[0].x + 9;
                this->bullets[2].y = this->soldiers[0].y + 7;
                this->playSoundEffect(SoundEffect::Bullet, 1);
                idx = updateSoldiers(false, idx);
                break;

            case 820:
                this->updateBullets();
                this->bullets[3].x = this->soldiers[4].x + 9;
                this->bullets[3].y = this->soldiers[4].y + 7;
                this->playSoundEffect(SoundEffect::Bullet, 1);
                idx = updateSoldiers(false, idx);
                break;

            case 837 ... 852:
            case 831 ... 835:
            case 821 ... 829:
            case 800 ... 819:
                this->updateBullets();
                idx = updateSoldiers(false, idx);
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
                    this->xOffset = this->xOffset - this->board.getTileSpacing();
                }

            }
            
        }

        if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 3)) {
            
            if (this->board.getCursorX() < this->board.getWidth() - 2) this->board.setCursorX(this->board.getCursorX() + 1);

            if (scrollBoard) {

                if (this->board.getCursorX() > xLeftScroll && this->board.getCursorX() <= xRightScroll) {
                    this->xOffset = this->xOffset + this->board.getTileSpacing();
                }

            }

        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 3)) {
            
            if (board.getCursorY() > 1) board.setCursorY(board.getCursorY() - 1);

            if (scrollBoard) {

                if (this->board.getCursorY() >= yTopScroll && this->board.getCursorY() < yBottomScroll) {
                    this->yOffset = this->yOffset - this->board.getTileSpacing();
                }

            }
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 3)) {
            
            if (board.getCursorY() < board.getHeight() - 2) board.setCursorY(board.getCursorY() + 1);
            
            if (scrollBoard) {

                if (this->board.getCursorY() > yTopScroll && this->board.getCursorY() <= yBottomScroll) {
                    this->yOffset = this->yOffset + this->board.getTileSpacing();
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
                this->playSoundEffect(SoundEffect::LargeExplosion, 1);

            }
            else if (this->board.isComplete()) {

                this->gameComplete = true;
                this->gameOver = true;
                this->startScroll();
                this->playSoundEffect(SoundEffect::Fanfare, 0);

            }
            else {

                this->playSoundEffect(SoundEffect::Dig, 1);

            }
            
        }

        if (PC::buttons.pressed(BTN_B) && (board.getState() == Tiles::Tile || board.getState() == Tiles::Flag || board.getState() == Tiles::QuestionMark)) {
            
            if (board.getState() == Tiles::Tile) {
                this->bombCount++;
                this->playSoundEffect(SoundEffect::Flag, 1);
            }
            else if (board.getState() == Tiles::Flag) {
                this->bombCount--;
            }

            board.toggleFlag();

            if (this->board.isComplete()) {

                this->gameComplete = true;
                this->gameOver = true;
                this->startScroll();
                this->playSoundEffect(SoundEffect::Fanfare, 0);

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

                                PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Bomb);   
                                
                            }
                            else {

                                PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Blank);   
                                
                            }


                            if (this->bombExplosion >= 10 && this->bombExplosion <= 25) {

                                uint8_t frame = (25 - this->bombExplosion) / 4;
                                PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Puff[frame]);   

                            }  


                        }
                        else {

                            PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Tiles[ static_cast<uint8_t>(tile) ]);                        

                        }
                    }
                    break;
                    
                case Tiles::QuestionMark:
                    PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::QuestionMark);
                    break;
                    
                case Tiles::Tile:

                    if ((x + (y %2 )) % 2 == 0) {
                        PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Tile);
                    }
                    else {
                        PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Tile_Rev);
                    }
                    break;

                case Tiles::Flag:
                    {
                        uint8_t frame = Utils::getFrameCount(24) / 5;
                        PD::drawBitmap((xMarginLeft + (x * tileSpacing)) - this->xOffset, (yMarginTop + (y * tileSpacing)) - this->yOffset, Images::Flags[frame]);
                    }
                    break;
                    
                
            }

        }
        
    }


    // Draw Soldiers ..

    for (uint8_t i = 0; i < 8; i++) {

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

    PD::drawBitmap(178, 0, Images::TimePanel);
    PD::setCursor(193, 2);
    PD::setColor(7, 0);
    if (this->time < 100)   { PD::print("0"); }
    if (this->time < 10)    { PD::print("0"); }
    PD::print(this->time, 10);    


    // Draw bombs ..

    PD::drawBitmap(178, 163, Images::BombPanel);
    PD::setCursor(193, 167);
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
    
        uint8_t tileSpacing = this->board.getTileSpacing();
        uint8_t xMarginLeft = marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t yMarginTop = marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ];
        
        PD::drawBitmap(xMarginLeft + (this->board.getCursorX() * tileSpacing) - this->xOffset + 2, yMarginTop + (this->board.getCursorY() * tileSpacing) - this->yOffset + 2, Images::Pointer);
        
    }
    
}

void GamePlayState::updateBullets() {

    const uint8_t puffX = 64;
    const uint8_t puffY[] = { 32, 128 };
    
    for (uint8_t i = 0; i < 4; i++) {

        if (this->bullets[i].x > 0) {
            
            this->bullets[i].x = this->bullets[i].x + 3;

            if (this->bullets[i].x > 72 && this->bullets[i].x < 76) {

                this->playSoundEffect(SoundEffect::SmallExplosion, 1);

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

uint16_t GamePlayState::updateSoldiers(bool allSoldiers, uint16_t idx) {

    for (uint8_t i = 0; i < 8; i++) {

        if (allSoldiers || (i != 0 && i != 4)) {

            switch (i) {

                case 0:
                    this->soldiers[i].x++;
                    this->soldiers[i].y = 32;
                    this->soldiers[i].stance = Stance::Walking;
                    break;

                case 1 ... 3:
                    this->soldiers[i].x++;
                    this->soldiers[i].y = soldierY[i - 1][idx];
                    this->soldiers[i].stance = Stance::Walking;
                    break;

                case 4:
                    this->soldiers[i].x++;
                    this->soldiers[i].y = 128;
                    this->soldiers[i].stance = Stance::Walking;
                    break;

                case 5 ... 7:
                    this->soldiers[i].x++;
                    this->soldiers[i].y = (128 + 32) - soldierY[i - 5][idx];
                    this->soldiers[i].stance = Stance::Walking;
                    break;

            }

        }

    }

    return ++idx;

}

void GamePlayState::playSoundEffect(SoundEffect soundEffect, uint8_t channel) {

    char sounds[6][19] = { "music/mineswe1.raw", "music/mineswe2.raw", "music/mineswe3.raw", "music/mineswe4.raw", "music/mineswe5.raw", "music/mineswe6.raw" };

    switch (channel) {

        case 0:
            if (mainThemeFile.openRO(sounds[ static_cast<uint8_t>(soundEffect) ])) {
                auto &music = Audio::play<1>(mainThemeFile);
                music.setLoop(false);
            } 
            break;

        case 1:
            if (soundEffectFile.openRO(sounds[ static_cast<uint8_t>(soundEffect) ])) {
                auto &music = Audio::play<0>(soundEffectFile);
                music.setLoop(false);
            } 
            break;
            

    }

}

void GamePlayState::startScroll() {

    this->counter = 1000;

    this->scroll_overall = this->xOffset + (4* this->board.getTileSpacing());
    this->scroll_speed = 1;
    this->scroll_count = 0;
    this->scroll_distance = 0;

    switch (scroll_overall) {

        case 0 ... 64:
            this->scroll_increment = 4;
            this->scroll_fastest = 4;
            break;

        case 65 ... 100:
            this->scroll_increment = 8;
            this->scroll_fastest = 4;
            break;

        case 101 ... 200:
            this->scroll_increment = 6;
            this->scroll_fastest = 8;
            break;

        case 201 ... 400:
            this->scroll_increment = 4;
            this->scroll_fastest = 8;
            break;

        default:
            this->scroll_increment = 4;
            this->scroll_fastest = 8;
            break;

    }
    
    printf("overall %i, inc %i, fastest %i, slow %i\n", this->scroll_overall, this->scroll_increment, this->scroll_fastest, scroll_overall - ((this->scroll_fastest - 1) * this->scroll_increment));

}
