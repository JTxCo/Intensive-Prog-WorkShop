#ifndef PAWN_H
#define PAWN_H
#include <QObject>
class Position;

class Pawn : public QObject
{
    Q_OBJECT

private:
    Position* position_;
    int ID_;

signals:
    void positionChanged(Position* newPosition);
public slots:
    void onPlayerPositionChanged(Position* postion);

public:
    Pawn();
    void setID(int id){ID_ = id;}
    int getID(){return ID_;}
    Position* getPosition(){return position_;}
    void movePawn(Position* position);

};

#endif // PAWN_H
