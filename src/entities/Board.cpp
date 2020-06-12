#include "Pokitto.h"
#include "Board.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

const uint8_t gameWidth[] = { 11, 18, 32 };
const uint8_t gameHeight[] = { 11, 18, 18 };


uint8_t Board::getWidth()                       { return this->width; }
uint8_t Board::getHeight()                      { return this->height; }
uint8_t Board::getCursorX()                     { return this->cursorX;}
uint8_t Board::getCursorY()                     { return this->cursorY;}
GameMode Board::getGameMode()                   { return this->gameMode; }

void Board::setCursorX(uint8_t x)               { this->cursorX = x;}
void Board::setCursorY(uint8_t y)               { this->cursorY = y;}

void Board::setGameMode(GameMode mode) { 
    
    this->gameMode = mode;
    this->width = gameWidth[ static_cast<uint8_t>(mode) ];
    this->height = gameHeight[ static_cast<uint8_t>(mode) ];

}


uint8_t Board::getBombCount() {

    switch (this->gameMode) {
        
        case GameMode::Easy:        return 1;//return GAME_MODE_EASY_BOMB_COUNT;
        case GameMode::Medium:      return GAME_MODE_MEDIUM_BOMB_COUNT;
        default:                    return GAME_MODE_HARD_BOMB_COUNT;
            
    }

}

uint8_t Board::getTileSize() {

    switch (this->gameMode) {
        
        case GameMode::Easy:        return 16;
        case GameMode::Medium:      return 16;
        default:                    return 16;
            
    }
}

uint8_t Board::getTileSpacing() {

    return this->getTileSize();

}

Tiles Board::getTile() {
    
    return static_cast<Tiles>( this->board[this->cursorY][this->cursorX] & 0x1F);
    
}

Tiles Board::getTile(uint16_t i) {
    
    return static_cast<Tiles>( this->board[i / this->width][i % this->width] & 0x1F);
    
}

Tiles Board::getTile(uint8_t x, uint8_t y) {
    
    return static_cast<Tiles>( this->board[y][x] & 0x1F);
    
}

void Board::setTile(uint16_t i, Tiles tile) {
    
    uint8_t x = i % this->width;
    uint8_t y = i / this->width;
    
    this->board[y][x] = (this->board[y][x] & 0xE0) | static_cast<uint8_t>(tile);

}

void Board::setTile(uint8_t x, uint8_t y, Tiles tile) {

    this->board[y][x] = (this->board[y][x] & 0xE0) | static_cast<uint8_t>(tile);

}

Tiles Board::getState() {
    
    return static_cast<Tiles>( this->board[this->cursorY][this->cursorX] & 0xE0);
    
}

Tiles Board::getState(uint16_t i) {
    
    return static_cast<Tiles>( this->board[i / this->width][i % this->width] & 0xE0);
    
}

Tiles Board::getState(uint8_t x, uint8_t y) {
    
    return static_cast<Tiles>( this->board[y][x] & 0xE0);
    
}

void Board::setState(uint16_t i, Tiles tile) {
    
    uint8_t x = i % this->width;
    uint8_t y = i / this->width;

    this->board[y][x] = (this->board[y][x] & 0x1F) | static_cast<uint8_t>(tile);

}

void Board::setState(uint8_t x, uint8_t y, Tiles tile) {

    this->board[y][x] = (this->board[y][x] & 0x1F) | static_cast<uint8_t>(tile);

}

void Board::setBoard() {


    // Clear board ..
    
    uint8_t h = this->height;
    uint8_t w = this->width;

    for (uint8_t y = 0; y < h; y++) {

        for (uint8_t x = 0; x < w; x++) {

            this->board[y][x] = static_cast<uint8_t>(Tiles::Tile);
            
        }
        
    } 


    // Plant bombs ..

    for (uint8_t i = 0; i < this->getBombCount(); i++) {
     
        while (true) {
            
            uint16_t x = random(0, this->width - 2);
            uint16_t y = random(0, this->height - 2);
            
            if (this->getTile(x + 1, y + 1) == Tiles::Blank) {
                
                this->setTile(x + 1, y + 1, Tiles::Bomb);
                break;
                
            }
            
        }
        
    }


    // Update numbers ..

    for (uint8_t y = 1; y < this->height - 1; y++) {

        for (uint8_t x = 1; x < this->width - 1; x++) {

            if (this->getTile(x, y) != Tiles::Bomb) {

                uint8_t bombs = 0;
                
                for (int8_t y1 = y - 1; y1 <= y + 1; y1++) {

                    for (int8_t x1 = x - 1; x1 <= x + 1; x1++) {
                        
                        if (x1 >= 1 && x1 < this->width - 1 && y1 >= 1 && y1 < this->height - 1 && !(x1 == x && y1 == y)) {
                            
                            if (this->getTile(x1, y1) == Tiles::Bomb) {
                                bombs++;
                            }

                        }
                        
                    }

                }

                this->setTile(x, y, static_cast<Tiles>(bombs));

            }
            
        }
       
    } 


    // Update border ..

    for (uint8_t x = 0; x < w; x++) {

        this->board[0][x] = static_cast<uint8_t>(Tiles::Fence_T);
        this->board[h - 1][x] = static_cast<uint8_t>(Tiles::Fence_B);

    }

    for (uint8_t y = 0; y < h; y++) {

        this->board[y][0] = static_cast<uint8_t>(Tiles::Fence_L);
        this->board[y][w - 1] = static_cast<uint8_t>(Tiles::Fence_R);
        
    } 

    this->board[0][0] = static_cast<uint8_t>(Tiles::Fence_TL);
    this->board[0][w - 1] = static_cast<uint8_t>(Tiles::Fence_TR);
    this->board[h - 1][0] = static_cast<uint8_t>(Tiles::Fence_BL);
    this->board[h - 1][w - 1] = static_cast<uint8_t>(Tiles::Fence_BR);


    // Print board ..
    
    this->cursorX = 1;
    this->cursorY = 1;

}

void Board::exposeBoard() {

    for (uint8_t y = 1; y < this->height - 1; y++) {

        for (uint8_t x = 1; x < this->width - 1; x++) {
        
            this->setState(x, y, Tiles::Blank);

        }

    }

}

Tiles Board::uncoverTile() {

    return this->uncoverTile(static_cast<int8_t>(this->cursorX), static_cast<int8_t>(this->cursorY));

}

Tiles Board::uncoverTile(int8_t x, int8_t y) {

    Tiles selectedTile = this->getTile(x, y);

    this->setState(x, y, Tiles::Blank);    
  
    if (selectedTile == Tiles::Blank) {
    
        for (int8_t y1 = y - 1; y1 <= y + 1; y1++) {
    
            for (int8_t x1 = x - 1; x1 <= x + 1; x1++) {
                
                if (x1 >= 1 && x1 < this->width - 1 && y1 >= 1 && y1 < this->height - 1 && !(x1 == x && y1 == y)) {

                    Tiles tile = this->getTile(x1, y1);
                    Tiles state = this->getState(x1, y1);
    
                    if (state == Tiles::Tile) {
    
                        TileDetails tileDetails;
                        tileDetails.x = x1;
                        tileDetails.y = y1;

                        if (!this->tilesToUncover.contains(tileDetails)) {

                            tilesToUncover.enqueue(tileDetails);

                        }

                    }
    
                }
    
            }
            
        }
        
    }

    return selectedTile;

}

void Board::toggleFlag() {

    switch (this->getState()) {
        
        case Tiles::Tile:
            this->setState(this->cursorX, this->cursorY, Tiles::Flag); 
            break;
        
        case Tiles::Flag:
            this->setState(this->cursorX, this->cursorY, Tiles::QuestionMark); 
            break;
        
        case Tiles::QuestionMark:
            this->setState(this->cursorX, this->cursorY, Tiles::Tile); 
            break;
        
    }

}

void Board::update() {

    uint16_t itemsInQueue = this->tilesToUncover.getCount();

    if (itemsInQueue > 0) {

        for (uint16_t i = 0; i < itemsInQueue; i++) {

            TileDetails tileDetails;
            tileDetails = this->tilesToUncover.peek();
            this->tilesToUncover.dequeue();

            this->uncoverTile(tileDetails.x, tileDetails.y);

        }

    }

}

bool Board::isComplete() {
    
    for (uint8_t y = 1; y < this->height - 1; y++) {

        for (uint8_t x = 1; x < this->width - 1; x++) {
        
            if (this->getState(x, y) != Tiles::Blank) {
                
                if (!(this->getState(x, y) == Tiles::Flag && this->getTile(x, y) == Tiles::Bomb)) {

                    return false;

                }

            }

        }

    }

    return true;

}