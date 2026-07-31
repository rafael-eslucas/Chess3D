#include <iostream>
#include <raylib.h>

#include "Move.h"
#include "Board.h"
#include "Rules.h"
#include "Screen.h"

using namespace std;

int main() {
    Game game;
    Screen screen(1600, 900, 50, 30, 60);

    string movestr;
    Move move("", 0, 0, 0);

    Side turno = Side::White;
    Position pos;
    Piece* selected;
    screen.show(game);




    /*Board board;
    std::string movestr; Move move;
    Side turno = Side::White;

    while (true) {
        board.print(0);
        std::cout << std::endl;
        std::cout << "Turno das " << (turno == Side::White ? "brancas" : "pretas") << "\n\n";
        std::cout << std::endl;
        cin >> movestr;
        move = Move::decode(movestr);

        if (board.play(move, turno)) {
            turno = (turno == Side::White) ? Side::Black : Side::White;
            std::cout << "\nVÁLIDO\n";
        } else {
            std::cout << "\nINVÁLIDO\n";
        }

        if (Rules::isThisTheEnd(board)) return 0;

        std::cout << "\033[2J\033[H";

        if (Rules::isCheck(board, Side::White)) std::cout << "Check white!";
        if (Rules::isCheck(board, Side::Black)) std::cout << "Check black!";
    }*/

    return 0;
}
