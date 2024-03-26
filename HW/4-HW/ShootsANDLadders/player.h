#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <utility>

using std::string;
using std:: pair;

class Player
{
private:
    string name_;
    pair<int,int> position_;
public:
    Player();
    void setName(string name){name_ = name;}
    string getName() const {return name_;}
    void setPosition(pair<int,int> position){position_ = position;}
    pair<int,int> getPosition() const {return position_;}
};

#endif // PLAYER_H
