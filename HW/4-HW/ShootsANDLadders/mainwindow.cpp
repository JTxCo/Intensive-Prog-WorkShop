#include "position.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cellwidget.h"
#include <QLabel>
#include "gameboard.h"
#include "position.h"
#include <QSplitter>
#include <QObject>
#include <QTimer>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
    ui->setupUi(this);
    gameBoard_ = new GameBoard();
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("border: 1px solid black"); //style of big box

    // Create main layout as a horizontal box layout
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);



    /*
        Creating The Game Board

    */

    QGridLayout* gameBoardLayout = new QGridLayout();
    gameBoardLayout->setSpacing(0); //removing spacing between cells


    /*
        Zig zag pattern for the game board
        the numbers should be displayed in the following order:
        Top row: [0,0] = 100 through [0,9] = 91
        Second row: [1,0] = 81 through [1,9] = 90
        ...
        second to last row: [8,0] = 20 through [8,9] = 11
        Bottom row: [9,0] = 1 through [9,9] = 10
        should be displayed like this:
        100 99 98 97 96 95 94 93 92 91
        81 82 83 84 85 86 87 88 89 90
        80 79 78 77 76 75 74 73 72 71
        61 62 63 64 65 66 67 68 69 70
        60 59 58 57 56 55 54 53 52 51
        41 42 43 44 45 46 47 48 49 50
        40 39 38 37 36 35 34 33 32 31
        21 22 23 24 25 26 27 28 29 30
        20 19 18 17 16 15 14 13 12 11
        1 2 3 4 5 6 7 8 9 10
    */

    int number = 1;

    for(int row = 0; row < 10; ++row)  // Start from the first row
    {
        // If row index is even, go from left to right, decrementing the number
        if(row % 2 == 0)
        {
            for(int col = 0; col < 10; ++col)
            {
                Position* p = new Position(col, 9-row, number++, nullptr);
                CellWidget* cell = new CellWidget(p, nullptr, this);

                // Adjust for display layout
                gameBoardLayout->addWidget(cell, 9 - row, col);
                cellWidgets_[9 - row][col] = cell;
            }
        }
        // If row index is odd, go from right to left, decrementing the number
        else
        {
            for(int col = 9; col >= 0; --col)
            {
                Position* p = new Position(col, 9 - row, number++, nullptr);
                CellWidget* cell = new CellWidget(p, nullptr, this);

                gameBoardLayout->addWidget(cell, 9 - row, col);
                cellWidgets_[9 - row][col] = cell;
            }
        }
    }





    // Add game board layout to the main layout
    QWidget* gameBoardWidget = new QWidget();
    gameBoardWidget->setLayout(gameBoardLayout);
    mainLayout->addWidget(gameBoardWidget, 2);


    // bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    //     if (obj == gameBoardWidget && event->type() == QEvent::Resize) {
    //         overlay->setGeometry(gameBoardWidget->geometry());
    //     }
    //     return QMainWindow::eventFilter(obj, event);
    // }
    // gameBoardWidget->installEventFilter(this);







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
    currentPlayerTitle = new QLabel("Current Player: ", this);
    currentPlayerTitle->setFixedSize(200, 50);
    currentPlayerLabel = new QLabel( this);
    currentPlayerLabel->setFixedSize(200, 50);
    currentPlayerLabel->setAlignment(Qt::AlignCenter);
    currentPlayerLayout->addWidget(currentPlayerTitle);
    currentPlayerLayout->addWidget(currentPlayerLabel);

    // Center align the widgets in the layout
    currentPlayerLayout->setAlignment(currentPlayerTitle, Qt::AlignCenter);
    currentPlayerLayout->setAlignment(currentPlayerLabel, Qt::AlignCenter);


    // Create a QLabel for the time remaining on the dice roll
    timeRemainingLabel = new QLabel("Time Remaining: ", this);
    timeRemainingLabel->setFixedSize(200, 50);

    // Create a QPushButton for the dice roll
    rollDiceButton = new QPushButton("Roll Dice", this);
    rollDiceButton->setFixedSize(200, 50);

    // Create a QLabel to display the result of the dice roll
    diceRollResultLabel = new QLabel("Dice Roll Result", this);
    diceRollResultLabel->setFixedSize(200, 50);
    diceRollResultLabel->setAlignment(Qt::AlignCenter);

    // Create a QPushButton to Move the Player:
    movePlayerButton = new QPushButton("Move Player", this);
    movePlayerButton->setFixedSize(200,50);

    // Create a QPushButton to Go to the Next Player:
    nextPlayerButton = new QPushButton("Next Player", this);
    nextPlayerButton->setFixedSize(200,50);


    // Create a QPushButton for the save and quit function
    saveAndQuitButton = new QPushButton("Save and Quit", this);
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
    buttonLayout->addWidget(movePlayerButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(nextPlayerButton,0, Qt::AlignCenter);
    buttonLayout->addWidget(saveAndQuitButton, 0, Qt::AlignCenter);

    splitter->addWidget(buttonWidget);

    /*
        Connecting the Buttons and Labels to their respective actions
    */
    //When a player changes turn it shows whose turn it is at the top.
    connect(gameBoard_, &GameBoard::currentPlayerChanged, this, &MainWindow::onCurrentPlayerChanged);
    //Connecting the dice roll button to display the resul in the label
    connect(rollDiceButton, &QPushButton::clicked, this, &MainWindow::onDiceRolled);
    //connecting the move player button to the
    connect(movePlayerButton, &QPushButton::clicked, this , &MainWindow::onMovePlayerButtonClicked);
    //Connecting next player button to move to next player
    connect(nextPlayerButton, &QPushButton::clicked, this, &MainWindow::onNextPlayerButtonClicked);



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
            Position * p  = new Position(row, col, num+1);
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


    //this is creating 6 random shoots and 6 random ladders
    renderShootsAndLadders();
    OverlayWidget* overlay = new OverlayWidget(ladders, shoots, centralWidget);
    overlay->setGeometry(gameBoardWidget->geometry());
    overlay->raise();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createPlayers(){
    // initalizing 4 for now, less will be made later
    //order is the first player is added at position top left, then top right, bottom left, bottom right
    int playersAmount = 4;
    for(int num = 1; num <= playersAmount; num ++){
        qDebug()<<"player num: " <<num;
        Player *p = new Player("Player " + std::to_string(num), num);
        // Add the player to the board
        gameBoard_->addPlayer(p);
        // Create a player for the player
        int row = (num - 1) / 2;
        int col = (num - 1) % 2;
        holdingWidgets_[row][col]->addPlayer(p);
        Position * pos =holdingWidgets_[row][col]->getCellWidgetPosition();
        p->setPosition(pos);
    }
    gameBoard_->setPlayerAmount(playersAmount);
    gameBoard_->changeCurrentPlayerIndex(0);
}


void MainWindow::onCurrentPlayerChanged(int player_index){
    qDebug() << "Player name changed to index: " + QString::number(player_index);
    if(player_index > gameBoard_->getPlayers().size()){
        qDebug()<<"too big index";

    }
    else{
        std::string playerName = gameBoard_->getPlayers()[player_index]->getName();
        qDebug()<<"name: " << playerName;
        currentPlayerLabel->setText(QString("Player: ") + QString::fromStdString(playerName));
    }
}

void MainWindow::onDiceRolled(){
    qDebug()<<"Dice Roll called";
    if(gameBoard_->hasPlayerRolled()){
        qDebug()<<"Player has already rolled the dice and can not go again, sucks";
    }
    else{
        //player has not already rolled
        int diceResult = gameBoard_->rollDice();
        qDebug()<<"dice result: " << QString::number(diceResult);
        diceRollResultLabel->setText(QString("Result: ")+ QString::number(diceResult));
        gameBoard_->playerRolled();
    }
}


Position* MainWindow::calculateNextPosition(Position* currentPos){
    qDebug() << "Calculating next Pos";
    int x = currentPos->getX();
    int y = currentPos->getY();
    int number = currentPos->getNumber();
    qDebug() << "x: " + QString::number(x);
    qDebug() << "y: " + QString::number(y);
    // Calculate new position
    // If y is even then we move to the right, else we move to the left
    if (y % 2 == 0) {
        qDebug() << "Even row";
        // If we are on the end of the row then we move to the next row else we move to the right
        if(x == 0){
            y--;
            number++;
        }else{
            x--;
            number++;
        }
    } else {
        qDebug() << "Odd row";
        // If we are on the beggining of the row then we move to the next row else we move to the left
        if(x == 9){
            y--;
            number++;
        }else{
            x++;
            number++;
        }
    }
    Position* nextPos2 = cellWidgets_[y][x]->getCellWidgetPosition();
    qDebug() << "setting Position to: " + QString::number(nextPos2->getX()) + ", " + QString::number(nextPos2->getY());
    return nextPos2;
}

std::vector<Position*> MainWindow::calculatePath(Position* start, int diceRoll){
    //Calculating the full path from the start with the given diceRoll
    qDebug()<<"Calcualting Path";
    std::vector<Position*> positions;
    positions.push_back(start);
    qDebug()<<"starting at number: " + QString::number(start->getNumber());
    qDebug()<<" Position : " +  QString::number(start->getX()) + ", " +  QString::number(start->getY());

    for(int i = 0; i < diceRoll; i++)
    {
        // We assume here calculateNextPosition logic is updated to consider the last position in list
        Position *nextPos = calculateNextPosition(positions.back());
        qDebug()<<"Added Pos: " + QString::number(nextPos->getNumber());
        qDebug()<<" Position : " +  QString::number(nextPos->getX()) + ", " +  QString::number(nextPos->getY());
        positions.push_back(nextPos);
    }
    qDebug()<<"Calculated Path done";
    return positions;
}



void MainWindow::movePlayerToPosition(Player* player, Position * oldPos, Position* newPos){
    qDebug()<<"removing player from old position";
    //since this is just moving the player along the path I won't link the player and position
    //This will only render the player at the position
    cellWidgets_[oldPos->getX()][oldPos->getY()]->removePlayer(player);
    cellWidgets_[newPos->getX()][newPos->getY()]->addPlayer(player);
    qDebug()<<"add the player to the new position";
}



void MainWindow::onMovePlayerButtonClicked(){
    //checking if the player has rolled yet, in order to move has to know the roll
    if(!gameBoard_->hasPlayerRolled()){
        qDebug()<<"Player has not rolled yet";
        return;
    }
    //first need to check if player can move from the holding area, has rolled a six
    //player index 0 is top left ...
    Player *curPlayer = gameBoard_->getPlayers()[gameBoard_->getCurrentPlayerIndex()];
    Position* oldPos = curPlayer->getPosition();
    //If player is in the holding area and has rolled a 6 or better move them to the first tile
    if(curPlayer->locationHolding() && gameBoard_->getDiceRollValue()>= 6){
        //from the player and the player from the position
        qDebug()<<"Player: " +QString::fromStdString(curPlayer->getName()) +" is moving from holding";
        curPlayer->removePosition();
        holdingWidgets_[oldPos->getX()][oldPos->getY()]->removePlayer(curPlayer);
        oldPos->removePlayerFromPosition(curPlayer);
        //adding the player to the first position,  firstPos to the player
        Position* firstPos = cellWidgets_[9][0]->getCellWidgetPosition();
        cellWidgets_[9][0]->addPlayer(curPlayer);
        firstPos->addPlayerToPosition(curPlayer);
        curPlayer->setPosition(firstPos);
        qDebug() <<"Player is moving to position: " + QString::number(firstPos->getNumber());
        //setting the player to no longer to be holding
        curPlayer->moveFromHolding();
        return;
    }
    else if(curPlayer->locationHolding()){
        qDebug()<<"Player is still in holding and can not move on";
        return;
    }
    //move the Player to each position on the baord along the path
    else if(!curPlayer->locationHolding()){
        qDebug()<<"Player is not in holding and is on the board, will move forward";
        int currentNum = oldPos->getNumber()+gameBoard_->getDiceRollValue();
        if(currentNum>= 100){
            //the player has won, call winning condition
            qDebug()<<"Player: " +QString::fromStdString(curPlayer->getName())+ "has won the game";
            return;
        }
        else{
            //the game is not over and will move normally
            qDebug()<<"Moving Player Normally";

            //removing player from oldPostion and vice versa

            qDebug()<<"Player at 9,0: " + QString::number(curPlayer->getPosition()->getNumber());
            curPlayer->removePosition();
            qDebug()<<" Position : " +  QString::number(oldPos->getX()) + ", " +  QString::number(oldPos->getY()) + "num: " + QString::number(oldPos->getNumber());
            cellWidgets_[oldPos->getY()][oldPos->getX()]->removePlayer(curPlayer);
            // cellWidgets_[9][0]->removePlayer(curPlayer);
            oldPos->removePlayerFromPosition(curPlayer);
            qDebug()<<"Removed player";
            //getting the path to the end position
            std::vector<Position*> movementPath = calculatePath(oldPos, gameBoard_->getDiceRollValue());
            qDebug()<<"path size" + QString::number(movementPath.size());
            QTimer *timer = new QTimer(this);
            int currentPathIndex = 1;  // Start at the second position
            Position *lastPosition = nullptr;
            bool connected = connect(timer, &QTimer::timeout, [this, timer, curPlayer, movementPath, currentPathIndex, lastPosition]() mutable {
                qDebug()<<"path size" + QString::number(movementPath.size());
                if(currentPathIndex < movementPath.size()){
                    qDebug()<<"Started lambda function";
                    Position *nextPosition = movementPath[currentPathIndex];
                    qDebug()<<" Next Position : " +  QString::number(nextPosition->getX()) + ", " +  QString::number(nextPosition->getY()) + "num: " + QString::number(nextPosition->getNumber());
                    // Remove player from last position after a delay.
                    if(lastPosition) {
                        qDebug()<<"Removing";
                        QTimer::singleShot(100, [&, lastPosition]() {  // 1 second delay
                            cellWidgets_[lastPosition->getY()][lastPosition->getX()]->removePlayer(curPlayer);
                        });
                    }
                    // Add player to new position
                    cellWidgets_[nextPosition->getY()][nextPosition->getX()]->addPlayer(curPlayer);
                    qDebug()<<"Player is now added to the position at number: " + QString::number(nextPosition->getNumber());
                    lastPosition = nextPosition; // Update lastPosition to the current one
                    currentPathIndex++;  // Move to the next position in the path
                }
                else{
                    qDebug()<<"Path is finished";
                    Position * lastPos = movementPath.back();
                    //cellwidgets already has the player
                    cellWidgets_[lastPos->getY()][lastPos->getX()]->getCellWidgetPosition()->addPlayerToPosition(curPlayer);
                    curPlayer->setPosition(lastPos);
                    timer->stop();
                    timer->disconnect();  // Disconnect all signals from timer
                    QTimer::singleShot(0, timer, &QTimer::deleteLater);
                }
            });

            if(connected) {
                qDebug() << "Signal connected successfully!";
            } else {
                qDebug() << "Error connecting signal!";
            }
            qDebug()<<"Starting timer";
            timer->start(500);
            gameBoard_->playerRolled();
        }
    }
    //do not activate the shoots or ladders on each position
    //while moving stop buttons from being clicked
    //Reseting the playerRolled status
    gameBoard_->playerRolled();
}
void MainWindow::onNextPlayerButtonClicked(){
    qDebug()<<"Next Player button CLicked";
    int playerCount =gameBoard_->getPlayerAmount()-1;
    int curPlayerIndex = gameBoard_->getCurrentPlayerIndex();
    // if the current player is {condition} compared to total amount of players, move to next or back to first
    //final player of the group, back to the first
    if(!gameBoard_->hasPlayerRolled()){
        qDebug()<<"Player has tried to go to next player, but has not rolled";
    }
    else{
        //Player has rolled so can go to text player
        if(curPlayerIndex == playerCount){
            qDebug()<<"Player: " +QString::number(curPlayerIndex) + " just went now back to first";
            //setting current player back to the first
            gameBoard_->changeCurrentPlayerIndex(0);

        }
        //going to next player
        else if(curPlayerIndex < playerCount){
            int nextIndex = curPlayerIndex+1;
            qDebug()<<"Player: " +QString::number(curPlayerIndex) + " just went now to player: " <<QString::number(nextIndex) ;
            gameBoard_->changeCurrentPlayerIndex(nextIndex);
        }
        else{
            qDebug()<<"Eror has occured and are at an outof bounds index: " <<curPlayerIndex;
        }
        gameBoard_->playerRolled();
        diceRollResultLabel->setText("Dice Roll Result");
    }
}


QPoint MainWindow::posToPoint(Position* pos) {
    int widgetSize = cellWidgets_[0][0]->width();//they are all the same
    qDebug()<<"Widget size: "<< QString::number(widgetSize) ;
    qDebug()<<"given x: "<<QString::number(pos->getX());
    qDebug()<<"given y: "<<QString::number(pos->getY());
    int x = pos->getY() * widgetSize;
    int y = pos->getX() * widgetSize;
    qDebug()<<"\n Generated x and y: " << QString::number(x) << " , " << QString::number(y);
    return QPoint(x, y);
}


void MainWindow::addLadder(Position* startPoint, Position* endPoint)
{
    ladders.push_back(std::make_pair(posToPoint(startPoint), posToPoint(endPoint)));
}

void MainWindow::addShoot(Position* startPoint, Position* endPoint)
{
    shoots.push_back(std::make_pair(posToPoint(startPoint), posToPoint(endPoint)));
}
void MainWindow::renderShootsAndLadders()
{
    // Call for a repaint after all shoots and ladders have been added.
    //Randomly choosing points to do a shoot and ladder from.
    //Creating 6 of each, I was thinking choosing a 2 random numbers between 2 to 99 (don't want a ladder or shoot to lead from the begining or end)
    //create the shoot with the other functions:


    //test ladder:
    //starting at position 8 to 25
    //8: 9,7
    //25: 7,4
    Position* startPoint = cellWidgets_[9][7]->getCellWidgetPosition();
    Position* endPoint = cellWidgets_[7][4]->getCellWidgetPosition();
    addLadder(startPoint, endPoint);
    qDebug() << "MainWindow size: " << QString::number(this->size().width()) << " , " << QString::number(this->size().height());
    repaint();
}
/*
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);
    // Drawing ladders in green
    QPen ladderPen;
    ladderPen.setWidth(40);
    ladderPen.setColor(Qt::red);
    ladderPen.setStyle(Qt::DashLine);
    painter.setPen(ladderPen);
    // Add manual line
    ladders.push_back(qMakePair(QPoint(50,50), QPoint(200,200)));
    qDebug()<<"ladders size: " <<QString::number(ladders.size());
    qDebug()<<"ladders size: " <<QString::number(ladders.size());
    for (const auto& ladder: ladders) {
        qDebug()<<"created ladder";
        painter.drawLine(ladder.first, ladder.second);
    }

    // Drawing shoots in red
    QPen shootPen;
    shootPen.setWidth(40);
    shootPen.setColor(Qt::green);
    shootPen.setStyle(Qt::SolidLine);
    painter.setPen(shootPen);
    for (const auto& shoot: shoots) {
        painter.drawLine(shoot.first, shoot.second);
    }
    // Base paint event
    QWidget::paintEvent(event);
}
*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // painter.begin(this); This line should be removed. QPainter is already active.

    // Drawing ladders in green
    QPen ladderPen;
    ladderPen.setWidth(40);
    ladderPen.setColor(Qt::red);
    ladderPen.setStyle(Qt::DashLine);
    painter.setPen(ladderPen);

    // Add manual line
    // ladders.push_back(qMakePair(QPoint(50,50), QPoint(200,200))); This line should also be removed. It looks like it was used for testing in a previous code version.

    qDebug()<<"ladders size: " <<QString::number(ladders.size());
    for (const auto& ladder: ladders) {
        qDebug()<<"created ladder";
        painter.drawLine(ladder.first, ladder.second);
        painter.drawEllipse(ladder.first, 10, 10);
        painter.drawEllipse(ladder.second, 10, 10);
    }

    // Drawing shoots in red
    QPen shootPen;
    shootPen.setWidth(40);
    shootPen.setColor(Qt::green);
    shootPen.setStyle(Qt::SolidLine);
    painter.setPen(shootPen);

    for (const auto& shoot: shoots) {
        painter.drawLine(shoot.first, shoot.second);
    }

    // Base paint event
    QWidget::paintEvent(event);
}

