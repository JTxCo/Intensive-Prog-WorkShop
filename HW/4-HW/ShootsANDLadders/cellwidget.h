#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include "position.h"
#include "player.h"


class CellWidget : public QWidget {
    // Q_OBJECT

private:
    Position* position_;
    std::vector<Player*> m_players_;
    void updateDisplay();  // Update the widget to reflect the state of the player
public:
    CellWidget(Position* position = nullptr, Player* pawnObj = nullptr, QWidget* parent = nullptr);
    void addPlayer(Player* playerObj);
    void removePlayer(Player* playerObj);
    void paintEvent(QPaintEvent *event) override;  // Override to draw your Pawn etc.
    Position* getCellWidgetPosition(){return position_;}
};

#endif // CELLWIDGET_H
