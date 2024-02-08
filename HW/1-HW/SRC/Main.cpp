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

    // Player* player = game->getPlayers()[0];
    // cout<<"dots: "<<game->getBoard()->getDotsCount()<<endl;

    // cout<<game->GenerateReport(player)<<endl;
    // game->getBoard()->SetSquareValue(1,1, SquareType::Pacman);
    return 0;
}