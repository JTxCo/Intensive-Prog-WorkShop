#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QObject>
#include <QDebug>
#include <vector>
#include "position.h"
#include "player.h"


class GameBoard : public QObject
{
    Q_OBJECT
private:
    //set to 10 x10 as that is what it is supposed to be, will change if needed later

    Position*Board[10][10];
    std::vector<Player*> players_;
    //std::vector<Pawn*> pawns_; removed a list of pawns as i combined the pawns into the Player class
    int playersAmount;
    int currentPlayerIndex;
    int diceRollValue;
    bool hasRolled = false;//manages if the player has rolled or not so they can only do it once

public:
    GameBoard();
    void setPlayerAmount(int pl_am){playersAmount = pl_am;}
    int getPlayerAmount(){return playersAmount;}
    void addPlayer(Player* player){players_.push_back(player);}
    void removePlayer(Player* player){players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());}
    std::vector<Player*>getPlayers(){return players_;}
    //this will return the dice roll of 2 dice. 1-12 options
    //also sets the diceRollValue
    int rollDice();
    int getDiceRollValue(){return diceRollValue;}
    void registerPlayers(std::vector<Player*> players) {players_ = players;}
    // this will move the player to the new position, taking in their new position and the player that is being moved
    void movePlayer(Position* newPosition, Player* player){player->setPosition(newPosition);}
    void changeCurrentPlayerIndex(int curPlayer){currentPlayerIndex = curPlayer; emit currentPlayerChanged(curPlayer);
        qDebug()<<"gameboard player index: "<<curPlayer;}
    int getCurrentPlayerIndex(){return currentPlayerIndex;}
    //updating the has player rolled functions every turn f
    bool hasPlayerRolled(){return hasRolled;}
    void playerRolled(){hasRolled = !hasRolled;}

signals:
    void currentPlayerChanged(int currentPlayerIndex);
};
#endif // GAMEBOARD_H
