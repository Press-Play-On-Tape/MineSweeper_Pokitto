#include "Pokitto.h"
#include "PokittoCookie.h"
#include <LibAudio>
#include "src/Game.h"

#include "src/entities/Board.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;

Game game;
GameCookie cookie;

Audio::Sink<4, PROJ_AUD_FREQ> audio;

int main() {


    // Initialise pokitto ..

    cookie.begin("MINESWEE", sizeof(cookie), (char*)&cookie);
    
    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(75);



    // Has the cookie been initialised?

    if (cookie.initialised != COOKIE_INITIALISED) {

        cookie.initialise();

    }


    // Play game!

    game.setup(&cookie);

    while (PC::isRunning()) {
    
    if (!PC::update()) continue;
    
        game.loop();
    
    }
    
    return 0;
}

