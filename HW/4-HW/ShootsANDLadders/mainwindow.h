#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "gameboard.h"
#include "player.h"
#include "cellwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //  fields gameBoard, ﻿playerPawns, ﻿playerTurnButton, ﻿diceRollValueLabel
    Ui::MainWindow *ui;
    GameBoard* gameBoard_;
    std::vector<Player*> players_;
    QPushButton* playerTurnButton_;
    int diceRollValueLabel_;
    std::array<std::array<CellWidget*, 10>, 10> cellWidgets_;
    std::array<std::array<CellWidget*, 2>, 2> holdingWidgets_;
public:
    // methods: createGame(), ﻿startGame(), ﻿setupUI(), ﻿updateUI(), ﻿nextPlayerTurn(), rollDice(), ﻿createPlayerTurnButton(), ﻿createDiceRollValueLabel(), ﻿createPlayerPawns(), ﻿createPlayerPawn(Player* player)
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createGame();
    void createPlayers();
    // void createPlayerTurnButton();
    // void createDiceRollValueLabel();
    // void createPlayerPawns();
    // void createPlayerPawn(Player* player);
    // void setUpUI();
    // void updateUI();
    // void nextPlayerTurn();
    // void rollDice();
    // void startGame();
    // void endGame();

// public slots:
//     void onGameCreated();
//     void onGameStarted();
//     void onDiceRolled();
//     void onPlayerPositionChanged();
//     void onGameOver();
//     void onPlayerTurnButtonClicked();
//     void onDiceRollValueLabelChanged();
//     void onPlayerPawnMoved();
//     void onPlayerPawnCreated();
    
};
#endif // MAINWINDOW_H
