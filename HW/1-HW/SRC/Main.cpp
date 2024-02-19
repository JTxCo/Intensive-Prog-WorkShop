#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "../SRC/Game.h"
#include "../SRC/Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
int main() {
    // Create a new game
    Game *game = new Game();
    for(auto enemy : game->getEnemies()){
    pair<int, int> currentPos = {enemy->get_x_pos(), enemy->get_y_pos()};
    game->getBoard()->getEnemyLastPos()[enemy] = {currentPos, game->getBoard()->GetSquareValue(currentPos.first, currentPos.second)};
    }
    while(!game->IsGameOver(game->getPlayers()[0])){
        game->playGame();
    }
    delete game->getBoard();
    delete game;
    return 0;
}