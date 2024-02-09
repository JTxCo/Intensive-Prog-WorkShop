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
    // Game *game = new Game();
    // game->playGame();
    // Player* player = game->getPlayers()[0];
    // cout<<"dots: "<<game->getBoard()->getDotsCount()<<endl;

    // cout<<game->GenerateReport(player)<<endl;
    // game->getBoard()->SetSquareValue(1,1, SquareType::Pacman);


    Game* game = new Game();
    Player* player = game->getPlayers()[0];
    Player *ghost = game->getEnemies()[0];
    player->SetPosition(1,1);
    ghost->SetPosition(1,8);
    vector<pair<int, int>> path = game->getBoard()->PathToPosition(player,ghost->get_x_pos(), ghost->get_y_pos());
    cout<<"path: "<<path.size()<<endl;
    return 0;
}