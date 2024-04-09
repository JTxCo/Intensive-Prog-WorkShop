#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "gameboard.h"
#include "player.h"
#include "cellwidget.h"
#include "position.h"
#include <QPainter>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //  fields gameBoard, ﻿playerTurnButton, ﻿diceRollValueLabel
    Ui::MainWindow *ui;
    GameBoard* gameBoard_;
    int diceRollValueLabel_;
    std::array<std::array<CellWidget*, 10>, 10> cellWidgets_;
    std::array<std::array<CellWidget*, 2>, 2> holdingWidgets_;

    //Storing the shoots and ladders
    std::vector<std::pair<QPoint, QPoint>> ladders;
    std::vector<std::pair< QPoint, QPoint>> shoots;

    //Labels and buttons
    QLabel* currentPlayerLabel;
    QLabel* currentPlayerTitle;

    QLabel* timeRemainingLabel;
    QPushButton* rollDiceButton;
    QLabel* diceRollResultLabel;

    QPushButton* movePlayerButton;

    QPushButton* saveAndQuitButton;

    QPushButton* nextPlayerButton;
    //Functions:

    Position * calculateNextPosition(Position * startPos);
    // void movePlayerOneStep(Position* startPos, Position* destPos, Player* player);
    void movePlayerToPosition(Player* player, Position * oldPos, Position* newPos);
    std::vector<Position*> calculatePath(Position* start, int diceRoll);
public:
    // methods: createGame(), ﻿startGame(), ﻿setupUI(), ﻿updateUI(), ﻿nextPlayerTurn(), rollDice(), ﻿createPlayerTurnButton(), ﻿createDiceRollValueLabel(),
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createPlayers();
    QPoint posToPoint(Position* pos);
    void paintEvent(QPaintEvent* event);
    void renderShootsAndLadders();
    void addLadder(Position* startPos, Position * endPos);
    void addShoot(Position* startPoint, Position* endPoint);
    // void createPlayerTurnButton();
    // void createDiceRollValueLabel();

    // void setUpUI();
    // void updateUI();
    // void nextPlayerTurn();
    // void rollDice();
    // void startGame();
    // void endGame();

public slots:
//     void onGameCreated();
//     void onGameStarted();
    void onDiceRolled();
    void onMovePlayerButtonClicked();
    // void onPlayerPositionChanged();
    void onCurrentPlayerChanged(int currentPlayerIndex);
//     void onGameOver();
//     void onPlayerTurnButtonClicked();
//     void onDiceRollValueLabelChanged();

    void onNextPlayerButtonClicked();
};
#endif // MAINWINDOW_H

//this is to render the shoots and ladders
class OverlayWidget : public QWidget {
    Q_OBJECT
public:
    explicit OverlayWidget(std::vector<std::pair<QPoint, QPoint>> &ladders, std::vector<std::pair<QPoint, QPoint>> &shoots, QWidget *parent = nullptr)
        : QWidget(parent), ladders_(ladders), shoots_(shoots) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::red);

        painter.setPen(pen);
        for (const auto &ladder: ladders_) {
            painter.drawLine(ladder.first, ladder.second);
        }
    }

private:
    std::vector<std::pair<QPoint, QPoint>> &ladders_;
    std::vector<std::pair<QPoint, QPoint>> &shoots_;
};


