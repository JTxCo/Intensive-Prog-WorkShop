#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include "position.h"
#include "pawn.h"
class Position;

class CellWidget : public QWidget {
    // Q_OBJECT

private:
    Position* position_;
    std::vector<Pawn*> m_Pawns_;
    void updateDisplay();  // Update the widget to reflect the state of the Pawn
public:
    CellWidget(Position* position = nullptr, Pawn* pawnObj = nullptr, QWidget* parent = nullptr);
    void addPawn(Pawn* pawnObj);
    void removePawn(Pawn* pawnObj);
    void paintEvent(QPaintEvent *event) override;  // Override to draw your Pawn etc.
};

#endif // CELLWIDGET_H
