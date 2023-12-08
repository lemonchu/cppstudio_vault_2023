#include "board.h"
#include "game.h"
#include "player.h"

int main() {
    gobang::Board board;
    gobang::Player player1(true, "Xiyangyang"), player2(false, "Huitailang");
    gobang::Game game(&player1, &player2, &board);
    game.Start();
}
