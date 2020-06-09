#pragma once

enum class Tiles : uint8_t {
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
    QuestionMark = 32,
    Flag = 64,
    Tile = 128,
};

enum class GameMode : uint8_t {
    Easy,
    Medium,
    Hard
};

enum class GameState : uint8_t {
	SplashScreen_Activate,
	SplashScreen,
	TitleScreen_Activate,
	TitleScreen,
	PlayGame_Activate,
	PlayGame,
	HighScore_Activate,
	HighScore
};