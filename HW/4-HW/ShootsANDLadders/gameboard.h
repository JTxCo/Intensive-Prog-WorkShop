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
    std::vector<Player*> players_;
    int currentPlayerIndex;
    int diceRollValue;
public:
    GameBoard();
    void addPlayer(Player* player){players_.push_back(player);}
    void removePlayer(Player* player){players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());}
    //this will return the dice roll of 2 dice. 1-12 options
    int rollDice();
    //Registers the players for the game, it will take in their name and amount of players that want to play, 2-4
    void registerGame();
    // this will move the player to the new position, taking in their new position and the player that is being moved
    void movePlayer(std::pair<int,int> newPosition, Player* player);
};

#endif // GAMEBOARD_H
