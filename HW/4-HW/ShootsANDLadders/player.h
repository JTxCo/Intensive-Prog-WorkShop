#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <string>
#include <utility>

using std::string;
using std::pair;

class Position;

class Player : public QObject
{
    Q_OBJECT

private:
    string name_;
    Position* position_;
    int playerID_;
    bool inHolding = true;
signals:
    void positionChanged(Position* newPosition);
public slots:
    void onPlayerPositionChanged(Position* position){position_ = position;}
public:
    Player();
    Player(string name, int playerID);

    void setName(string name){name_ = name;}
    string getName() const {return name_;}
    void setPosition(Position* position);
    Position* getPosition(){return position_;}
    void removePosition();
    void setPlayerID(int playerID){playerID_ = playerID;}
    int getId() const {return playerID_;}

    bool locationHolding(){return inHolding;}
    void moveFromHolding(){inHolding = false;}
    // ~Player() {delete position_;}  // Look at comment below
};

#endif // PLAYER_H
