#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <utility>
#include "pawn.h"

using std::string;
using std:: pair;


class Player
{
private:
    string name_;
    pair<int,int> position_;
    int playerID_;
    Pawn* pawn_;
public:
    Player();
    Player(string name, int playerID);

    void setName(string name){name_ = name;}
    string getName() const {return name_;}
    void setPosition(pair<int,int> position){position_ = position;}
    pair<int,int> getPosition() const {return position_;}
    void setPlayerID(int playerID){playerID_ = playerID;}
    int getId() const {return playerID_;}
    void setPawn(Pawn* p){pawn_ = p;}
    Pawn* getPawn(){return pawn_;}
    ~Player() {delete pawn_;}
};

#endif // PLAYER_H
