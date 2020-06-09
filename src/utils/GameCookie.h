#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint32_t score[3][5] = { 999, 998, 997, 996, 995, 999, 998, 997, 996, 995,999, 998, 997, 996, 995, };
		uint8_t initials[3][5][3] = { 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1,  };
		uint32_t lastScore = 0;
		uint32_t lastScoreIndex = 0;
        GameMode gameMode;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->gameMode = GameMode::Easy;

			for (uint8_t mode = 0; mode < 3; mode++) {

				this->score[mode][0] = 995;
				this->score[mode][1] = 996;
				this->score[mode][2] = 997;
				this->score[mode][3] = 998;
				this->score[mode][4] = 999;

				for (uint8_t x = 0; x < 5; x++) {
			
					for (uint8_t y = 0; y < 3; y++) {

						this->initials[mode][x][y] = x + 1;

					}
			
				}

			}

			this->lastScore = 0;
			this->lastScoreIndex = 0;
			this->saveCookie();

		}
		

		uint32_t getScoreIndex() {

			return lastScoreIndex;

		}


		uint32_t setLastScore(GameMode gameMode, uint32_t score) {

            uint32_t index = NO_SCORE;
            uint32_t mode = static_cast<uint8_t>(gameMode);
            
			for (uint32_t x = 0; x < 5; x++) {

				if (score <= this->score[mode][x]) {

				    index = x;
				    break;
				    
				}

			}

			if (index != NO_SCORE) {

			    for (int32_t x = 3; x >= index; x--) {
			        
			        this->score[mode][x + 1] = this->score[mode][x];
			        this->initials[mode][x + 1][0] = this->initials[mode][x][0];
			        this->initials[mode][x + 1][1] = this->initials[mode][x][1];
			        this->initials[mode][x + 1][2] = this->initials[mode][x][2];
			        
			    }

				this->score[mode][index] = score;
				this->initials[mode][index][0] = 0;
				this->initials[mode][index][1] = 0;
				this->initials[mode][index][2] = 0;

			}

			this->lastScore = score;
			this->lastScoreIndex = index;

			return index;

		}

};