#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "../utils/GameCookie.h"
#include "../images/Images.h"

class HighScoreState {

  private:

    uint8_t counter = 0;
    uint8_t cursor = 0;

  public:	
  
    void activate(GameContext gameContext, GameCookie *cookie);
    GameContext update(GameContext gameContext, GameCookie *cookie);
    void render(GameContext gameContext, GameCookie *cookie);

};

