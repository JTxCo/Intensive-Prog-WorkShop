#include "cellwidget.h"
#include "position.h" // You have used class Position in this file, so you need to include its header.
#include <QLabel>
#include <QSharedPointer>
#include <QPainter>
CellWidget::CellWidget(Position* position, Player* playerObj, QWidget *parent) : QWidget(parent), position_(position)
{
    if (playerObj) {
        // Only add playeObj if it is not nullptr
        addPlayer(playerObj);
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
    painter.setPen(Qt::black); // Sets color for drawing text

    // Determine the spacing for each player avatar
    float playerSpacing = this->width() / static_cast<float>(m_players_.size() + 1);
    float radius = qMin(this->width(), this->height()) / (m_players_.size() / 2.0 + 1) / 2.0 - 5;  // Reserve 5px for padding
    QFont font = painter.font();
    font.setPointSize(radius - 10);
    painter.setFont(font);

    for(size_t i = 0; i < m_players_.size(); i++) {
        // Calculate the center for each player
        QPointF center(playerSpacing * (i + 1), this->height() / 2.0);


        // Set the color based on the player to which the Player belongs
        QColor color;

        switch(m_players_[i]->getId()-1) {
        case 0: color = QColor("red"); break;
        case 1: color = QColor("green"); break;
        case 2: color = QColor("blue"); break;
        case 3: color = QColor("yellow"); break;
        default: color = QColor("black");
        }

        painter.setBrush(color);

        // Draw the Player as a circle
        QRectF rect(center.x() - radius, center.y() - radius, 2*radius, 2*radius);
        painter.drawEllipse(rect);

        // Draw the Player number in the center of circle
        painter.drawText(rect, Qt::AlignCenter, QString::number(m_players_[i]->getId()));
    }
}

void CellWidget::addPlayer(Player* PlayerObj) {
    if(PlayerObj  == nullptr) {
        return;
    }
    m_players_.push_back(PlayerObj);
    // Connect 'positionChanged' signal to 'updateDisplay' for new player
    connect(PlayerObj, &Player::positionChanged, this, &CellWidget::updateDisplay);
    qDebug()<<"added player to cell wdiget and list";
    // Trigger redraw
    update();
}

void CellWidget::removePlayer(Player* playerObj) {
    auto it = std::remove(m_players_.begin(), m_players_.end(), playerObj);
    qDebug()<<"List size: "+ QString::number(m_players_.size());
    if(it != m_players_.end()) {
        qDebug()<<"Removed player in cellwidget";
        m_players_.erase(it, m_players_.end());
        update();
        disconnect(playerObj, &Player::positionChanged, this, &CellWidget::updateDisplay);
    }
}
void CellWidget::updateDisplay(){
    update();
}
