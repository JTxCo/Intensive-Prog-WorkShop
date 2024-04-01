#ifndef PAWN_H
#define PAWN_H

#include <QObject>

class Pawn : public QObject
{
    Q_OBJECT

private:
    std::pair<int,int> position_;
    int ID_;
signals:
    void positionChanged(std::pair<int,int> newPosition);
public slots:
    void onPlayerPositionChanged(std::pair<int,int> newPosition);

public:
    Pawn();
    void setID(int id){ID_ = id;}
    int getID(){return ID_;}
    std::pair<int,int> getPosition(){return position_;}
    void movePawn(std::pair<int,int> newPosition);
};

#endif // PAWN_H
