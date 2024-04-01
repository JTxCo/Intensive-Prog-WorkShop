#include "position.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cellwidget.h"
#include <QLabel>
#include "gameboard.h"
#include "position.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
    ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("border: 1px solid black"); //style of big box

    // Create main layout as a horizontal box layout
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);



    /*
        Creating The Game Board

    */

    QGridLayout* gameBoardLayout = new QGridLayout();
    gameBoardLayout->setSpacing(0); //removing spacing between cells

    int number = 1;  // Initialize number counter

    for(int row = 0; row < 10; ++row)
    {
        if(row % 2 == 0) { // If row index is even, go from left to right.
            for(int col = 0; col < 10; ++col)
            {
                Position* p = new Position(col, 9 - row , number, nullptr); // Creating position object
                CellWidget* cell = new CellWidget(p,nullptr ,this); //assigning the cell as a child of the position
                gameBoardLayout->addWidget(cell, 9 - row, col); //adding cell to board
                cellWidgets_[row][col] = cell;
                number++;
            }
        } else { // If row index is odd, go from right to left.
            for(int col = 9; col >= 0; --col)
            {
                Position* p = new Position(col, 9 - row , number, nullptr); // Creating position object
                CellWidget* cell = new CellWidget(p , nullptr,this); //assigning the cell as a child of the position
                gameBoardLayout->addWidget(cell, 9 - row, col); //adding cell to board
                cellWidgets_[row][col] = cell;
                number++;
            }
        }
    }
    // Add game board layout to the main layout
    mainLayout->addLayout(gameBoardLayout, 2);

    createGame();

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    /*
    Adding the Buttons
    */

    // Create a new widget and layout for the buttons and text fields
    QWidget* buttonWidget = new QWidget(this);
    QVBoxLayout* outerLayout = new QVBoxLayout(buttonWidget);//This is the OUTER layout
    QVBoxLayout* buttonLayout = new QVBoxLayout;  // This is the INNER layout

    // Create a QLabel to display the current player
    QVBoxLayout *currentPlayerLayout = new QVBoxLayout;
    currentPlayerLayout->setSpacing(.1);
    QLabel* currentPlayerTitle = new QLabel("Current Player: ", this);
    currentPlayerTitle->setFixedSize(200, 50);
    QLabel* currentPlayerLabel = new QLabel( this);
    currentPlayerLabel->setFixedSize(200, 50);
    currentPlayerLayout->addWidget(currentPlayerTitle);
    currentPlayerLayout->addWidget(currentPlayerLabel);

    // Center align the widgets in the layout
    currentPlayerLayout->setAlignment(currentPlayerTitle, Qt::AlignCenter);
    currentPlayerLayout->setAlignment(currentPlayerLabel, Qt::AlignCenter);


    // Create a QLabel for the time remaining on the dice roll
    QLabel* timeRemainingLabel = new QLabel("Time Remaining: ", this);
    timeRemainingLabel->setFixedSize(200, 50);

    // Create a QPushButton for the dice roll
    QPushButton* rollDiceButton = new QPushButton("Roll Dice", this);
    rollDiceButton->setFixedSize(200, 50);

    // Create a QLabel to display the result of the dice roll
    QLabel* diceRollResultLabel = new QLabel("Dice Roll Result: ", this);
    diceRollResultLabel->setFixedSize(200, 50);

    // Create a QPushButton for the save and quit function
    QPushButton* saveAndQuitButton = new QPushButton("Save and Quit", this);
    saveAndQuitButton->setFixedSize(200, 50);

    // Add the labels and buttons to the layout
    outerLayout->addStretch();
    outerLayout->addLayout(buttonLayout);
    outerLayout->addStretch();

    // Inside buttonLayout, align everything in the center
    buttonLayout->addLayout(currentPlayerLayout, Qt::AlignCenter);
    buttonLayout->addWidget(timeRemainingLabel, 0, Qt::AlignCenter);
    buttonLayout->addWidget(rollDiceButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(diceRollResultLabel, 0, Qt::AlignCenter);
    buttonLayout->addWidget(saveAndQuitButton, 0, Qt::AlignCenter);

    splitter->addWidget(buttonWidget);





    /*
    Adding the Holding Area
    This uses the same structure as the Game board but in a separate location
    */

    QWidget *holdingBox = new QWidget();
    QGridLayout *holdingBoxLayout = new QGridLayout(holdingBox);

    int num = 0;
    for(int row=0; row<2; row++){
        for(int col=0; col<2; col++){
            // Creating the Position 0,0 through 1,1
            Position * p  = new Position(row, col, num);
            // creating the cellwidget just like the game board
            CellWidget* cw = new CellWidget(p, nullptr);
            // Position the cw in the holding box according to row and col
            holdingBoxLayout->addWidget(cw, row, col);
            holdingWidgets_[row][col] = cw;
            num++;
        }
    }

    splitter->addWidget(holdingBox);

    // customize the distribution of initial space
    splitter->setSizes(QList<int>() << 400 << 150);

    // Add splitter to the main layout
    mainLayout->addWidget(splitter, 1);


    // Set the main layout to the central widget
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setWindowState(Qt::WindowMaximized);
    this->show();
    createPlayers();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGame(){
    // Create a board
    gameBoard_ = new GameBoard();
    // // Create a player
    // Player *p = new Player("test", 1);
    // // Add the player to the board
    // gameBoard_->addPlayer(p);
    // // Create a pawn for the player
    // Pawn *aPawn = new Pawn();
    // p->setPawn(aPawn);
    // aPawn->setID(p->getId());
    // gameBoard_->addPawn(aPawn);
    // // cellWidgets_[0][1]->addPawn(p->getPawn());
    // //pawn 2
    // // Create a player
    // Player *p2 = new Player("test", 0);
    // // Add the player to the board
    // gameBoard_->addPlayer(p2);
    // // Create a pawn for the player
    // Pawn *aPawn2 = new Pawn();
    // p2->setPawn(aPawn2);
    // aPawn2->setID(p2->getId());
    // gameBoard_->addPawn(aPawn2);
    // // cellWidgets_[0][0]->addPawn(p2->getPawn());
}

void MainWindow::createPlayers(){
    // initalizing 4 for now, less will be made later
    for(int num = 1; num <= 4; num ++){
        qDebug()<<"player num: " <<num;
        Player *p = new Player("test", num-1);
        // Add the player to the board
        gameBoard_->addPlayer(p);
        // Create a pawn for the player
        Pawn *aPawn = new Pawn();
        p->setPawn(aPawn);
        aPawn->setID(num-1);
        gameBoard_->addPawn(aPawn);
        int row = (num - 1) / 2;
        int col = (num - 1) % 2;

        holdingWidgets_[row][col]->addPawn(aPawn);
    }
}


