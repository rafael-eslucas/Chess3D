#include "Screen.h"

#include <optional>
#include <iostream>
#include <ostream>
#include <raylib.h>

#include "../utils/utils.h"

void Screen::show(Game& game) {
    InitWindow(screenWidth, screenHeight, "Chess3D");
    SetTargetFPS(40);
    for (auto piece : game.getBoard()->getPieces()) {
        std::string path = "assets/textures/" + piece->getId().substr(0,2) + ".png";
        std::cout<< path <<std::endl;
        textures[utils::idx(piece->getSide())][utils::idx(piece->getType())] = LoadTexture(path.c_str());
    }

    while (!WindowShouldClose()) {
        if (state == ScreenState::welcome)
            welcome();
        if (state == ScreenState::play)
            play(game);
    }
    UnloadTexture(textures[utils::idx(Side::Black)][utils::idx(Type::Pawn)]);
    UnloadTexture(textures[utils::idx(Side::White)][utils::idx(Type::Pawn)]);
    CloseWindow();
}

void Screen::welcome() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Welcome to Chess3D!",
        (screenWidth - MeasureText("Welcome to Chess3D!", TITLE_SIZE))/2,
        screenHeight/3,
        50,
             BLACK);

    float playposx = (screenWidth - MeasureText("Play", PARAGRAPH_SIZE)) / 2;
    float playposy = screenHeight*2/3;
    Rectangle button = {playposx, playposy, float(MeasureText("Play", 50)), 50};
    DrawText("Play", playposx, playposy, PARAGRAPH_SIZE, BLACK);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, button)) {
            state = ScreenState::play;
        }
    }
    EndDrawing();
}

void Screen::play(Game& game) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawBoard3D(game);

    DrawText((game.getTurn() == Side::White? "White" : "Black"), 10, 10, 20, BLACK);

    std::optional<Position> pos = IsAnyPositionBeingClickedAndIfYesWhichOne(game);
    if (pos) {
        if (!selected) {
            if (game.getBoard()->whatIsInSpaceAt(pos->x, pos->y, pos->z)->getSide() == game.getTurn()) {
                selected = game.getBoard()->whatIsInSpaceAt(pos->x, pos->y, pos->z);
            }
        } else {
            this->to = *pos;
            Move move(selected->getId(), to);
            if (game.getBoard()->play(move, game.getTurn())) {
                game.changeTurn();
            }
            selected = nullptr;
        }
    }
    EndDrawing();
}

void Screen::drawBoard3D(Game& game) {
    for (int z = 0; z < 6; z++) {
        int row = z / 3;
        int col = z % 3;

        int x = 2*MARGIN_X + col*(BOARD_SIZE + MARGIN_X);
        int y = 2*MARGIN_Y + row*(BOARD_SIZE + MARGIN_Y);

        drawBoard2D(game, x, y, z);
    }
}

void Screen::drawBoard2D(Game& game, int x, int y, int z) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            Piece* piece = game.getBoard()->whatIsInSpaceAt(i, j, z);
            if (selected && selected == piece) {
                DrawRectangle(i*CELL_SIZE+x, j*CELL_SIZE+y, CELL_SIZE, CELL_SIZE, GREEN);
            } else {
                DrawRectangle(i*CELL_SIZE+x, j*CELL_SIZE+y, CELL_SIZE, CELL_SIZE, (i+j)%2==0? LIGHTGRAY : DARKGRAY);
            }
            if (piece) {
                if (piece->getSide() == Side::White || piece->getSide() == Side::Black) {
                    float scale = (float)CELL_SIZE / std::max(textures[utils::idx(piece->getSide())][utils::idx(piece->getType())].width, textures[utils::idx(piece->getSide())][utils::idx(piece->getType())].height);
                    DrawTextureEx(textures[utils::idx(piece->getSide())][utils::idx(piece->getType())], {(float)i*CELL_SIZE+x, (float)j*CELL_SIZE+y}, 0, scale, WHITE);
                } else {
                    DrawText(piece->getId().c_str(), i*CELL_SIZE+x, j*CELL_SIZE+y, 20, (piece->getSide() == Side::White? WHITE : BLACK));
                }
            }
        }
    }
}

std::optional<Position> Screen::IsAnyPositionBeingClickedAndIfYesWhichOne(Game& game) const {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return std::nullopt;

    Vector2 mouse = GetMousePosition();

    for (int z = 0; z < 6; z++) {
        int row = z / 3;
        int col = z % 3;

        int x = 2*MARGIN_X + col*(BOARD_SIZE + MARGIN_X);
        int y = 2*MARGIN_Y + row*(BOARD_SIZE + MARGIN_Y);

        Rectangle rect = {(float)x, (float)y, (float)BOARD_SIZE, (float)BOARD_SIZE};

        if (CheckCollisionPointRec(mouse, rect)) {
            int boardRow = (mouse.x - x) / CELL_SIZE;
            int boardCol = (mouse.y - y) / CELL_SIZE;

            Position pos(boardRow, boardCol, z);

            return pos;
        }
    }
    return std::nullopt;
}

Texture2D Screen::textureof(Piece *piece) {
    return textures[utils::idx(piece->getSide())]
                   [utils::idx(piece->getType())];
}
