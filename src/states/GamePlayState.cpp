#include "GamePlayState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


const bool scroll[] = { false, true, true };

const uint8_t marginLeft[] =      { 0, 0, 0 };
const uint8_t marginRight[] =     { 0, 0, 0 };
const uint8_t marginTop[] =       { 0, 0, 0 };
const uint8_t marginBottom[] =    { 0, 0, 0 };

const uint8_t xScroll_Left[] =    { 0, 7, 7 };
const uint8_t xScroll_Right[] =   { 0, 11, 25 };
const uint8_t yScroll_Top[] =     { 0, 5, 5 };
const uint8_t yScroll_Bottom[] =  { 0, 12, 12 };

const int8_t shakeXOffset[] =     { -1,  0, 0, 1, 0, 0, 1, -1,  0, -1,  0, 1,  0, -2, 0, 2, 0, 2,  0, -2 };
const int8_t shakeYOffset[] =     {  0, -1, 0, 0, 1, 0, 0,  1, -1,  0, -1, 0, -1,  0, 2, 0, 2, 0, -2,  0 };

const int8_t soldierX[] =         { -20, -32, -42, -52, -18, -29, -40 };
const int8_t soldierY[] =         { 30, 38, 26, 32, 70, 72, 66 };

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

    for (uint8_t x = 0; x < 7; x++) {

        this->soldiers[x].x = soldierX[x];
        this->soldiers[x].y = soldierY[x];
        this->soldiers[x].stance = Stance::Walking;

    }

    for (uint8_t x = 0; x < 4; x++) {

        this->bullets[x].x = -10;
        this->bullets[x].y = -10;

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

    if (this->counter > 0) {

        this->counter--;
printf("%i \n", counter);

        switch (counter) {

            case 910 ... 999:
            
                if (Utils::getFrameCount(4) == 0) {

                    if (this->xOffset > -4) this->xOffset--;
                    if (this->yOffset > 0)  this->yOffset--;
                }
                break;
                
            case 865 ... 909:

                for (uint8_t x = 0; x < 7; x++) {

                    this-soldiers[x].x++;

                }
                break;
          
            case 854 ... 864:

                for (uint8_t x = 0; x < 7; x++) {

                    this->soldiers[x].stance = Stance::Standing;

                }
                break;
          
            case 853:
                this->bullets[0].x = this->soldiers[0].x + 4;
                this->bullets[0].y = this->soldiers[0].y + 4;
                break;

            case 836:
                this->updateBullets;
                this->bullets[1].x = this->soldiers[4].x + 4;
                this->bullets[1].y = this->soldiers[4].y + 4;
                break;

            case 824:
                this->updateBullets;
                this->bullets[2].x = this->soldiers[0].x + 4;
                this->bullets[2].y = this->soldiers[0].y + 4;
                break;

            case 816:
                this->updateBullets;
                this->bullets[3].x = this->soldiers[4].x + 4;
                this->bullets[3].y = this->soldiers[4].y + 4;
                break;

            case 837 ... 852:
            case 825 ... 835:
            case 817 ... 823:
                this->updateBullets;
                break;

            case 856:

                
        }

    }
    
    this->board.update();



    uint8_t xLeftScroll = xScroll_Left[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t xRightScroll = xScroll_Right[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t yTopScroll = yScroll_Top[ static_cast<uint8_t>(gameContext.mode) ];
    uint8_t yBottomScroll = yScroll_Bottom[ static_cast<uint8_t>(gameContext.mode) ];


    // Handle player actions ..

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

    for (uint8_t x = 0; x < 7; x++) {

        switch (this->soldiers[x].stance) {

            case Stance::Walking:
                PD::drawBitmap(this->soldiers[x].x, this->soldiers[x].y, Images::Soldiers[Utils::getFrameCount(4) / 2]);
                break;

            case Stance::Standing:
                PD::drawBitmap(this->soldiers[x].x, this->soldiers[x].y, Images::Soldiers[0]);
                break;

        }

    }

    for (uint8_t x = 0; x < 4; x++) {

        if (this->bullets[x].x > 0) {

            PD::drawPixel(this->bullets[x].x, this->bullets[x].y, 0);

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

    if (this->bombExplosion == 0) {

        uint8_t xMarginLeft = marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t xMarginRight = marginRight[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t yMarginTop = marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ];
        uint8_t yMarginBottom = marginBottom[ static_cast<uint8_t>(this->board.getGameMode()) ];
        
        PD::drawBitmap(xMarginLeft + ((board.getCursorX() - this->xOffset) * this->board.getTileSpacing()) - 1 + 3, yMarginTop + ((board.getCursorY() - this->yOffset) * this->board.getTileSpacing()) - 1 + 3, Images::Pointer);
        
    }
    
}

void GamePlayState::updateBullets() {

    for (uint8_t x = 0; x < 4; x++) {

        if (this->bullets[x].x > 0) {
            
            this->bullets[x].x = this->bullets[x].x + 3;

            if (this->bullets[x].x > 72) this->bullets[x].x = -1;

        }

    }

}