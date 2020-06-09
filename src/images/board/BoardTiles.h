#pragma once

namespace Images {

    #include "Blank.h"
    #include "Bomb.h"
    #include "Tile.h"
    #include "Tile_Rev.h"
    #include "Number1.h"
    #include "Number2.h"
    #include "Number3.h"
    #include "Number4.h"
    #include "Number5.h"
    #include "Number6.h"
    #include "Number7.h"
    #include "Number8.h"
    #include "QuestionMark.h"
    #include "Fence_TL.h"
    #include "Fence_T.h"
    #include "Fence_TR.h"
    #include "Fence_L.h"
    #include "Fence_R.h"
    #include "Fence_BL.h"
    #include "Fence_B.h"
    #include "Fence_BR.h"
    #include "Pointer.h"

    #include "Flag_00.h"
    #include "Flag_01.h"
    #include "Flag_02.h"
    #include "Flag_03.h"
    #include "Flag_04.h"

    const uint8_t * const Tiles[] = { 
        Blank,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Bomb,
        Fence_TL,
        Fence_T,
        Fence_TR,
        Fence_L,
        Fence_R,
        Fence_BL,
        Fence_B,
        Fence_BR,
    };

    const uint8_t * const Flags[] = { 
        Flag_00,
        Flag_01,
        Flag_02,
        Flag_03,
        Flag_04,
    };

}