#pragma once

#include <raylib.h>
#include "Game.h"
#include <optional>

#include "Board.h"

enum class ScreenState {
    welcome,
    play
};

class Screen {
    int screenWidth = 1680.0f;
    int screenHeight = 900.0f;
    ScreenState state;

    int TITLE_SIZE;
    int PARAGRAPH_SIZE;
    int CELL_SIZE;
    int BOARD_SIZE;
    int MARGIN_X;
    int MARGIN_Y;

    Piece* selected = nullptr;
    Position to;

    Texture2D textures[2][6];

    public:
        Screen(int xsize, int ysize, int t, int p, int c) :
            screenWidth(xsize), screenHeight(ysize),
            state(ScreenState::welcome),
            TITLE_SIZE(t), PARAGRAPH_SIZE(p),
            CELL_SIZE(c), BOARD_SIZE(6*CELL_SIZE),
            MARGIN_X((screenWidth - 3 * BOARD_SIZE) / 6.0f),
            MARGIN_Y((screenHeight - 2 * BOARD_SIZE) / 5.0f) {}
        void show(Game& game);
        void welcome();
        void play(Game& game);

        void drawBoard2D(Game& game, int x, int y, int z);
        void drawBoard3D(Game& game);
        Texture2D textureof(Piece* piece);

        std::optional<Position> IsAnyPositionBeingClickedAndIfYesWhichOne(Game& game) const;
};