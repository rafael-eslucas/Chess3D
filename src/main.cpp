#include <iostream>
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
        std::cout << std::endl;
        board.print(1);
        board.ray();
        std::cout << std::endl;
        cin >> movestr;
        move = Move::decode(movestr);
        board.move(move, turno);

        if (Rules::isThisTheEnd(board)) return 0;

        std::cout << "\033[2J\033[H";


        turno = (turno == Side::White) ? Side::Black : Side::White;
    }

    return 0;
}