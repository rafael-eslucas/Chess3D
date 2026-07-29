#include <iostream>
#include <raylib.h>

#include "Move.h"
#include "Board.h"
#include "Rules.h"

using namespace std;

int main() {
    Board board;

    string movestr;
    Move move("", 0, 0, 0);

    Side turno = Side::White;

    while (true) {
        std::cout << "Turno das " << (turno == Side::White ? "brancas" : "pretas") << "\n\n";
        board.print(0);
        board.print(1);
        std::cout << std::endl;
        std::cout << std::endl;
        cin >> movestr;
        move = Move::decode(movestr);
        board.move(move, turno);

        if (Rules::isThisTheEnd(board)) return 0;

        std::cout << "\033[2J\033[H";

        if (Rules::isCheck(board, Side::White)) std::cout << "Check white";
        if (Rules::isCheck(board, Side::Black)) std::cout << "Check black";


        turno = (turno == Side::White) ? Side::Black : Side::White;
    }

    return 0;
}