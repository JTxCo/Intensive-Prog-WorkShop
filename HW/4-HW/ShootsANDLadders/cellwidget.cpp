#include "cellwidget.h"
#include "position.h" // You have used class Position in this file, so you need to include its header.
#include <QLabel>
#include <QSharedPointer>
#include <QPainter>
CellWidget::CellWidget(Position* position, Pawn* pawnObj, QWidget *parent) : QWidget(parent), position_(position)
{
    if (pawnObj) {
        // Only add pawnObj if it is not nullptr
        addPawn(pawnObj);
    }
    this->setStyleSheet("background-color: lightgrey; border: 1px solid black;"); // Customize as per need.
    
    // Create a new QLabel
    QLabel* label = new QLabel(this);

    // Set its text to be the position number

    if (position)
    {
        label->setText(QString::number(position->getNumber()));
    }
    else
    {
        label->setText("0");  // Default text
    }

    // Set alignment of the label to top-right
    label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

    // Set the size of the label to match the size of the widget
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set auto-fill background of the label to enable the widget's background color also fill up to label's area
    label->setAutoFillBackground(true);
}


void CellWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Check if there are any pawns associated with this cell
    for(auto& m_Pawn: m_Pawns_) {
        // A circle represents the pawn
        QPointF center(this->width()/2.0, this->height()/2.0);
        float radius = qMin(this->width(), this->height()) / 2.0 - 5;  // Reserve 5px for padding

        // Set the color based on the player to which the pawn belongs
        QColor color;

        switch(m_Pawn->getID()) {
        case 0: color = QColor("red"); break;
        case 1: color = QColor("green"); break;
        case 2: color = QColor("blue"); break;
        case 3: color = QColor("yellow"); break;
        default: color = QColor("black");
        }

        painter.setBrush(color);

        // Draw the pawn as a circle
        painter.drawEllipse(center, radius, radius);
    }
}
void CellWidget::addPawn(Pawn* pawnObj) {
    if(pawnObj  == nullptr) {
        return;
    }
    m_Pawns_.push_back(pawnObj);
    // Connect 'positionChanged' signal to 'updateDisplay' for new pawn
    connect(pawnObj, &Pawn::positionChanged, this, &CellWidget::updateDisplay);

    // Trigger redraw
    update();
}

void CellWidget::removePawn(Pawn* pawnObj) {
    auto it = std::remove(m_Pawns_.begin(), m_Pawns_.end(), pawnObj);

    // If the pawnObj was found and removed from the vector
    if(it != m_Pawns_.end()) {
        m_Pawns_.erase(it, m_Pawns_.end());
        // Disconnect 'positionChanged' signal from 'updateDisplay' for removed pawn
        disconnect(pawnObj, &Pawn::positionChanged, this, &CellWidget::updateDisplay);

        // Trigger redraw
        update();
    }
}
void CellWidget::updateDisplay(){
    update();
}
