#include "GamePlayState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


const bool scroll[] = { false, true, true };
const uint8_t marginLeft[] = { 0, 0, 0 };
const uint8_t marginRight[] = { 0, 0, 0 };
const uint8_t marginTop[] = { 0, 0, 0 };
const uint8_t marginBottom[] = { 0, 0, 0 };


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

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameContext GamePlayState::update(GameContext gameContext, GameCookie *cookie) { 

    bool scrollBoard = scroll[ static_cast<uint8_t>(this->board.getGameMode()) ];

    if (!this->gameOver && Utils::isFrameCount(30) && this->time < 1000) {
        this->time++;
    }

    
    this->board.update();


    uint16_t xOverlap = board.getOverallWidth() - 220;
    uint16_t yOverlap = board.getOverallHeight() - 176;
    uint8_t xOverlapTiles = (xOverlap / this->board.getTileSpacing()) + (xOverlap % this->board.getTileSpacing() != 0 ? 1 : 0);
    uint8_t yOverlapTiles = (yOverlap / this->board.getTileSpacing()) + (yOverlap % this->board.getTileSpacing() != 0 ? 1 : 0);
    uint8_t xCentreTile = board.getWidth() / 2;
    uint8_t yCentreTile = board.getHeight() / 2;


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 3)) {

        if (this->board.getCursorX() > 1) this->board.setCursorX(board.getCursorX() - 1);

        if (scrollBoard && this->board.getCursorX() <= xCentreTile && this->xOffset > 0) {
            this->xOffset--;
        }
        
    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 3)) {
        
        if (this->board.getCursorX() < this->board.getWidth() - 2) this->board.setCursorX(this->board.getCursorX() + 1);
        
        if (scrollBoard && this->board.getCursorX() > xCentreTile && this->xOffset < xOverlapTiles) {
            this->xOffset++;
        }

    }

    if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 3)) {
        
        if (board.getCursorY() > 1) board.setCursorY(board.getCursorY() - 1);

        if (scrollBoard && this->board.getCursorY() <= yCentreTile && this->yOffset > 0) {
            this->yOffset--;
        }
        
    }

    if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 3)) {
        
        if (board.getCursorY() < board.getHeight() - 2) board.setCursorY(board.getCursorY() + 1);
        
        if (scrollBoard && this->board.getCursorY() > yCentreTile && this->yOffset < yOverlapTiles) {
            this->yOffset++;
        }        
    }

    if (!this->gameOver) {

        if (PC::buttons.pressed(BTN_A) && board.getState() == Tiles::Tile) {
            
            Tiles tile = board.uncoverTile();

            if (tile == Tiles::Bomb) {

                this->xCursor_GameOver = this->board.getCursorX();
                this->yCursor_GameOver = this->board.getCursorY();
                this->board.exposeBoard();
                this->gameOver = true;

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

    uint8_t width = this->board.getWidth();
    uint8_t height = this->board.getHeight();

    uint8_t xMarginLeft = marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t xMarginRight = marginRight[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t yMarginTop = marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t yMarginBottom = marginBottom[ static_cast<uint8_t>(this->board.getGameMode()) ];
    
    uint8_t tileSpacing = this->board.getTileSpacing();

    PD::fillScreen(11);

    for (uint8_t y = 0; y < height; y++) {

        for (uint8_t x = 0; x < width; x++) {
            
            Tiles state = board.getState(x, y);

            switch (state) {
                
                case Tiles::Blank:
                    {
                        Tiles tile = board.getTile(x, y);

                        if (this->gameOver && !this->gameComplete && this->xCursor_GameOver == x && this->yCursor_GameOver == y && Utils::getFrameCount(32) >= 16) {

                            PD::drawBitmap(xMarginLeft + (x - this->xOffset) * tileSpacing, yMarginTop + (y - this->yOffset) * tileSpacing, Images::Blank);                        

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


    // Draw border.

    PD::setColor(0);
    PD::fillRect(0, 0, 220, yMarginTop);
    PD::fillRect(0, 176 - yMarginBottom, 220, yMarginBottom);
    PD::fillRect(0, 0, xMarginLeft, 176);
    PD::fillRect(220 - xMarginRight, 0, xMarginRight, 176);


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
    PD::fillRect(190, 166, 40, 10);
    PD::setCursor(192, 168);
    PD::setColor(3, 0);
    if (this->bombCount < 100)   { PD::print("0"); }
    if (this->bombCount < 10)    { PD::print("0"); }
    PD::print(this->bombCount, 10);    


    // Draw complete ..

    if (this->gameOver && this->gameComplete) {

        PD::drawBitmap(40, 70, Images::Congratulations);
        
    }

}


void GamePlayState::renderCursor() {

    uint8_t xMarginLeft = marginLeft[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t xMarginRight = marginRight[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t yMarginTop = marginTop[ static_cast<uint8_t>(this->board.getGameMode()) ];
    uint8_t yMarginBottom = marginBottom[ static_cast<uint8_t>(this->board.getGameMode()) ];
    
    PD::drawBitmap(xMarginLeft + ((board.getCursorX() - this->xOffset) * this->board.getTileSpacing()) - 1, yMarginTop + ((board.getCursorY() - this->yOffset) * this->board.getTileSpacing()) - 1, Images::Pointer);
    
}

