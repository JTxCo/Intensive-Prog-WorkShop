#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include "position.h"
#include "player.h"
class GameBoard
{
private:
    //set to 10 x10 as that is what it is supposed to be, will change if needed later
    Position*Board[10][10];
    std::vector<Player*> Players_;
    int currentPlayerIndex;
    int diceRollValue;
public:
    GameBoard();
    void addPlayer(Player* player){Players_.push_back(player);}
};

#endif // GAMEBOARD_H
