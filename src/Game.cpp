#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



void Game::setup(GameCookie *cookie) { 
    
    this->cookie = cookie;

}

void Game::loop(void) {
    
    PC::buttons.pollButtons();
    PD::clear();

    switch (this->gameContext.currentState) {

        case GameState::SplashScreen_Activate:
            this->splashScreenState.activate();
            this->gameContext.currentState = GameState::SplashScreen;
            [[fallthrough]]

        case GameState::SplashScreen:
            this->gameContext = this->splashScreenState.update(this->gameContext);
            this->splashScreenState.render();
            break;

        case GameState::TitleScreen_Activate: 
            this->titleScreenState.activate(this->gameContext, this->cookie);
            this->gameContext.currentState = GameState::TitleScreen;
            [[fallthrough]]

        case GameState::TitleScreen: 
            this->gameContext = this->titleScreenState.update(this->gameContext, this->cookie);
            this->titleScreenState.render(this->gameContext, this->cookie);
            break;

        case GameState::PlayGame_Activate: 
            this->gamePlayState.activate(this->gameContext);
            this->gameContext.currentState = GameState::PlayGame;
            [[fallthrough]]

        case GameState::PlayGame: 
            gameContext.time = 0;
            gameContext.gameComplete = false;
            gameContext = this->gamePlayState.update(this->gameContext, this->cookie);
            this->gamePlayState.render();
            break;
            
        case GameState::HighScore_Activate: 
			this->highScoreState.activate(this->gameContext, this->cookie);
			this->gameContext.currentState = GameState::HighScore;
			[[fallthrough]]

        case GameState::HighScore: 
			this->gameContext = this->highScoreState.update(this->gameContext, this->cookie);
			this->highScoreState.render(this->gameContext, this->cookie);
			break;

    }

}