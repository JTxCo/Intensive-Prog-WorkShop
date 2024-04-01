#ifndef POSITION_H
#define POSITION_H
#include "player.h"
#include <vector>
#include <utility>
class Position
{
private:
    int x_,y_;
    std::vector<Player*> players_;
    //store the end point of a shoot or ladder, since there can only be one or the other do not need to store what type only thsat position
    int number_;
    Position* shootOrLadderEnd_;
public:
    Position(int x, int y , int number, Position* shootOrLadderEnd=nullptr): x_(x) , y_(y), number_(number),  shootOrLadderEnd_(shootOrLadderEnd){}
    const std::vector<Player*> getPlayers(){return players_;}
    void addPlayerToPosition(Player* player){players_.push_back(player);}
    //this is used to populate from a csv or saved state, probably won't be used much but is good to have
    void addPlayerVector(std::vector<Player*> players){players_ = players;}
    //looks for a player and removes it
    void removePlayerFromPosition(Player* player){players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());}
    Position* getShootLadderEnd(){return shootOrLadderEnd_;}
    std::pair<int, int> getCordinates(){return {x_,y_};}
    int getNumber(){return number_;}
    void setNumber(int number){number_ = number;}
};

#endif // POSITION_H
