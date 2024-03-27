#ifndef PAWN_H
#define PAWN_H

#include <QObject>
#include "player.h"

class pawn : public QObject
{
    Q_OBJECT

private:
    Player* pawnsPlayer_;
    std::pair<int,int> position_;

public slots:
    void onPlayerPositionChanged(std::pair<int,int> newPosition);

public:
    pawn(Player* player);
    void setPlayer(Player* player){pawnsPlayer_ = player;}
    Player* getPlayer(){return pawnsPlayer_;}
    std::pair<int,int> getPosition(){return position_;}
    void movePawn(std::pair<int,int> newPosition){position_ = newPosition;}
};

#endif // PAWN_H
