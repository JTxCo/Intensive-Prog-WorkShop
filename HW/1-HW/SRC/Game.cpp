#include "Game.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <regex>
#include <sstream>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
using std::string;
using std::pair;
using std::vector;
using std::make_pair;
using std::priority_queue;
using std::reverse;
using std::cout;
using std::endl;
using std::cin;
using std::regex;

Board::Board() : rows_(12), cols_(12) { // Set default size of board to 12x12
    // Dynamically allocate memory for the 2D array
    // Initialize all positions as available, this might change later based on how the board set up is done later
    arr_ = new SquareType*[rows_];
    isAvailable = new bool*[rows_];
    for (int i = 0; i < rows_; ++i) {
        arr_[i] = new SquareType[cols_];
        isAvailable[i] = new bool[cols_];
        for (int j = 0; j < cols_; ++j) {
            isAvailable[i][j] = true; 
        }
    }
    if(GenerateBoard(rows_, cols_)){
        setAvailableSquares();
    }
    else{
        cout << "Board was not generated correctly" << endl;
    }
}

// Custom constructor to set rows and cols
// Initialize all positions as available, this might change later 
Board::Board(int rows, int cols) : rows_(rows + 2), cols_(cols + 2){
    // the plus 2 here is meant so that i can add a wall border around the matrix so that it can't go out of the border
    // Dynamically allocate memory for the 2D array
    arr_ = new SquareType*[rows_];
    isAvailable = new bool*[rows_];
    for (int i = 0; i < rows_; ++i) {
        arr_[i] = new SquareType[cols_];
        isAvailable[i] = new bool[cols_];
        for (int j = 0; j < cols_; ++j) {
            isAvailable[i][j] = true;
            arr_[i][j] = SquareType::Empty; 
        }
    }
    if(GenerateBoard(rows_, cols_)){
        setAvailableSquares();
    }
    else{
        cout << "Board was not generated correctly" << endl;
    }  
}

// Destructor to free memory
Board::~Board() {
    for (int i = 0; i < rows_; ++i) {
        delete[] arr_[i];
    }
    delete[] arr_;
    for(auto i = 0; i < rows_; i++){
        delete[] isAvailable[i];
    }
    delete[] isAvailable;
}

SquareType Board::GetSquareValue(int row, int col){
    return arr_[row][col];
}

void Board::SetSquareValue(int row, int col, SquareType value){
    arr_[row][col] = value;
}


void Board::setAvailableSquares(){
        for(int i = 0; i < rows_; i++){
        for(int j = 0; j < cols_; j++){
            if(isAvailable[i][j]){
                availableSquares.push_back({i, j});
            }
        }
    }
}

bool Board::isSquareAvailable(int row, int col) {
    return isAvailable[row][col];
}

bool Board::notWall(int row, int col) {
    SquareType square = GetSquareValue(row, col);
    if (square == SquareType::Wall){
        return false;
    }
    return true;
}
vector<pair<int, int>> Board::GetPossibleMoves(int currRow, int currCol) {
    // Obtain the current position of the player
    // int currRow = p->get_y_pos(); redid the function from  an input of a player p
    // int currCol = p->get_x_pos();

    vector<pair<int, int>> positions;

    // Check the adjacent positions for valid moves, without considering walls
    if (currRow - 1 >= 0)
        positions.push_back(make_pair(currRow - 1, currCol));

    if (currRow + 1 < rows_)
        positions.push_back(make_pair(currRow + 1, currCol));

    if (currCol - 1 >= 0)
        positions.push_back(make_pair(currRow, currCol - 1));

    if (currCol + 1 < cols_)
        positions.push_back(make_pair(currRow, currCol + 1));

    return positions;
}



vector<pair<int, int>> Board::PathToPosition(Player* p, int endRow, int endCol) {
    int startRow = p->get_y_pos();
    int startCol = p->get_x_pos();
    int n = rows_;

    // uint's used to avoid negative values, adjust accordingly.
    const unsigned int INF = (unsigned int)-1;

    // Create 2D vector for visited status and distances
    vector<vector<bool>> visited(n, vector<bool>(rows_, false));
    vector<vector<int>> dist(n, vector<int>(rows_, INF));
    vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(rows_, make_pair(-1, -1)));

    // Setting the distance from start to start as 0
    dist[startRow][startCol] = 0;

    // Priority queue with custom comparator
    auto compare = [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
        return a.second > b.second;
    };

    // The `decltype` keyword in C++ is used to determine the type of an expression at compile-time. It returns the type of the expression without actually evaluating it.
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(compare)> pq(compare);

    // Pushing start position and distance
    pq.push({{startRow, startCol}, 0});

    // While there are unvisited nodes
    while (!pq.empty()) {
        // Node with shortest path
        pair<int, int> currentPosition = pq.top().first;
        int currentDistance = pq.top().second;
        pq.pop();

        int currentRow = currentPosition.first;
        int currentCol = currentPosition.second;

        // If reached the end position, break the loop
        if (currentRow == endRow && currentCol == endCol) {
            break;
        }

        // If current node already visited, skip it
        if (visited[currentRow][currentCol]) {
            continue;
        }

        // Mark current node as visited
        visited[currentRow][currentCol] = true;

        // Get all valid adjacent positions
        vector<pair<int, int>> neighbors = GetPossibleMoves(p->get_x_pos(), p->get_y_pos());

        for (auto& neighbor : neighbors) {
            int neighborRow = neighbor.first;
            int neighborCol = neighbor.second;

            if (notWall(neighborRow, neighborCol) && !visited[neighborRow][neighborCol]) {
                int altDistance = currentDistance + 1; // We are considering each edge to have a weight equal to 1

                if (altDistance < dist[neighborRow][neighborCol]) {
                    dist[neighborRow][neighborCol] = altDistance;
                    prev[neighborRow][neighborCol] = currentPosition;
                    pq.push({{neighborRow, neighborCol}, altDistance});
                }
            }
        }
    }

    // Reconstruct the shortest path from provided coordinates
    vector<pair<int, int>> path;
    int currentRow = endRow;
    int currentCol = endCol;

    while (currentRow != -1 && currentCol != -1) {
        path.push_back({currentRow, currentCol});

        pair<int, int> previousPos = prev[currentRow][currentCol];
        currentRow = previousPos.first;
        currentCol = previousPos.second;
    }

    // Reverse path to get it from start to end
    reverse(path.begin(), path.end());
    return path;
}


// Move a player to a new position on the board. Return true if they moved successfully, false otherwise.
// need to check to do changes based on where the player lands, if there is treasure, if there is a dot, if there is an enemy, if there is a wall
bool Board::MovePlayer(Player* p, int row, int col, vector<Player*> enemylist) {
    // Check if the move is valid
    if (notWall(row, col)) {
        // Check if the position is occupied by another player
        for (auto& enemy : enemylist) {
            if (enemy->get_x_pos() == col && enemy->get_y_pos() == row) {
                return false;
            }
        }
        // Move the player to the new position
        p->SetPosition(row, col);
        return true;
    }
    return false;
}
// moves a player or enemey, any of type player, to a random location. This is for if an enemy dies or if a human player hits a trap
bool Board::MovePlayerRandom(Player* p) {
    if(availableSquares.empty()){
        return false;
    }
    // Choose a random available square
    int index = rand() % availableSquares.size();
    pair<int, int> newPosition = availableSquares[index];
    
    // Move the player to the new position
    p->SetPosition(newPosition.first, newPosition.second);
    // returns true since the player was moved successfully
    return true;
}

// Move an enemy to a new position on the board. Return true if they moved successfully, false otherwise.
// could also have this use the same function as the player
bool Board::MoveEnemy(Player* p, pair<int, int> pos) {
    // Check if the move is valid
    if (notWall(pos.first, pos.second)) {
        // Move the enemy to the new position
        p->SetPosition(pos.first, pos.second);
        return true;
    }
    return false;
}



bool Board::generateBorder(){
    // i am going to put walls on the border of the board so that the player/enemies can't go out
    for(int i = 0; i < rows_; i++){
        for(int j = 0; j < cols_; j++){
            if(i == 0 || i == rows_-1 || j == 0 || j == cols_-1){
                arr_[i][j] = SquareType::Wall;
                isAvailable[i][j] = false;
            }
        }
    }
    return true;
}





// function to fill in the values: dots, treasure, walls=, and traps
bool Board::fillInBoard(){
    // need to randomly assign the dots and the treasure while also putting down walls, but in a way that they don't over do it 
    // vector<pair<int, int>> availableSquares = GetPossibleMoves();
    // starting at the top left since that is where the player will start, it will be emppty

    std::srand(std::time(0));
    int dots_added = 0;
    int treasure_added = 0;
    int walls_added = 0;
    int traps_added = 0;
    int enemySpecialTreasure_added = 0;
for (int  i = 1; i < rows_-1; i++) {
    for (int j = 1; j < cols_-1; j++) {
        // 80% chance of a dot, all are already dots so no need to change that
        // 5% chance of a wall
        // 5% chance of a trap
        // 5% chance of treasure
        // 5% chance of enemey treasure
        int random = rand() % 100 + 1;
        // walls
        if (random > 80 && random <= 85) {
            // wall
            if (walls_added < 0.15 * (rows_ * cols_)) {
                arr_[i][j] = SquareType::Wall;
                isAvailable[i][j] = false;
                walls_added++;
            } else {
                // can be a dot
                // Just to make sure setting isAvailable to true
                isAvailable[i][j] = true;
            }
        }
        // traps
        else if(random > 85 && random <= 90){
            // trap
            if (traps_added < 0.1 * (rows_ * cols_)) {
                arr_[i][j] = SquareType::Trap;
                isAvailable[i][j] = true;
                traps_added++;
            } else {
                // can be a dot
                // Just to make sure setting isAvailable to true
                isAvailable[i][j] = true;
            }
        }
        // Trasure
        else if(random > 90 && random <= 95){
            // treasure
            if (treasure_added < 0.1 * (rows_ * cols_)) {
                arr_[i][j] = SquareType::Treasure;
                isAvailable[i][j] = true;
                treasure_added++;
            } else {
                // can be a dot
                // Just to make sure setting isAvailable to true
                isAvailable[i][j] = true;
            }
        }
        // enemey treasure
        else if(random > 95 && random <= 100){
            // dot
            arr_[i][j] = SquareType::EnemySpecialTreasure;
            isAvailable[i][j] = true;
            enemySpecialTreasure_added++;
        }
    }
    
}
    SetSquareValue(1, 1, SquareType::Empty);
    // the rest of the squares can be random
    dots_added = (10*10)  - treasure_added - walls_added - traps_added - enemySpecialTreasure_added;
    dots_count_ = dots_added;
    treasure_count_ = treasure_added;
    walls_count_ = walls_added;
    traps_count_ = traps_added;
    enemySpecialTreasure_count_ = enemySpecialTreasure_added;
    return true;
}


// printing the board, this is so that the user can see the board and all in it
bool Board::GenerateBoard(int row, int col){
    // this will generate a board off of the given dimensions
    // this will also set the walls and the available squares
    rows_ = row;
    cols_ = col;
    // this is setting the Boards rows and cols to the given rows and cols


    // wall border has been added
    // need to set the available squares
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            arr_[i][j] = SquareType::Dot;
            isAvailable[i][j] = true;
        }
    }
    if(generateBorder()){
        // if the border was generated successfully
        if(fillInBoard()){
            // if the board was filled in successfully
            return true;
        }
        return false;
    }
    else{
        return false;
    }
}


Game::Game() {
    // Create a new game
    board_ = new Board();
    //setting variables
    turn_count_ = 0;
    dots_count_ = 0;
    GameOver = false;
    // Create a new player
    Player* human = new Player("Human", true); 
    players_.push_back(human);
    // Create new enemies
    for (int i = 0; i < 2; i++) {
        Player* enemy = new Player("Enemy", false);
        enemies_.push_back(enemy);
    }
    // set the game data since that will be created by the Board and now we are ready to play
    setGameData();
    playGame();
}



Game::Game(int row, int col, int enemies_count) {
    // Create a new game
    board_ = new Board(row, col);
    //setting variables
    turn_count_ = 0;
    dots_count_ = 0;
    GameOver = false;
    // Create a new player
    Player* human = new Player("Human", true);
    players_.push_back(human);
    // Create new enemies
    for (int i = 0; i < enemies_count; i++) {
        Player* enemy = new Player("Enemy", false);
        enemies_.push_back(enemy);
    }
    setGameData();
    playGame();
}

Game::~Game() {
    // Free memory
    delete board_;
    for (auto& player : players_) {
        delete player;
    }
    for(auto& enemy : enemies_){
        delete enemy;
    }
}

    



bool Game::setGameData(){
    if(!setDotsCount(board_->getDotsCount())){
        return false;
    }
    if(!setTreasureCount(board_->getTreasureCount())){
        return false;
    }
    if(!setTurnCount(0)){
        return false;
    }
    return true;
}




pair<int,int> Game::PresentMoveOptions(Player *p){
    // Obtain the current position of the player
    pair<int, int> chosenMove = make_pair(-100, -100);
    // Check the adjacent positions for valid moves, will not allow to move into walls
    vector<pair<int, int>> positions = board_->GetPossibleMoves(p->get_x_pos(), p->get_y_pos());
    // Present the options to the player
    cout << "Possible moves: " << endl;
    for (int i = 0; i < positions.size(); i++) {
        cout << i << ": " << positions[i].first << ", " << positions[i].second << endl;
    }
    // Take the input from the player
    std::regex coordinate_pattern("\\((\\d+),(\\d+)\\)");
    int choice;
    cout << "Enter the number of the position you want to move to: ";
    cin >> choice;
    if (choice >= 0 && choice < positions.size()) {
        chosenMove = positions[choice];
        std::cout << "X: " << positions[choice].first << ", Y: " << positions[choice].second << std::endl;
    } else {
        std::cout << "Invalid input.\n";
    }
    return chosenMove;
}





bool Game::UpdatePlayerData(Player *p, int row, int col){
    p->SetPosition(row, col);
    turn_count_++;
    p->setMovesTaken(p->getMovesTaken() + 1);
    return true;
}



bool Game::TakeTurn(Player *p){

    // Getting the current position of the player
    // int row = p->get_y_pos();
    // int col = p->get_x_pos();
    // get the choice of move from the player
    pair<int, int> move = PresentMoveOptions(p);
    if (move==make_pair(-100, -100)) {
        return false;
    }


    // Check if the player landed on a dot, if it has remove the dot from the board and add points 1
    SquareType landedPostion = board_->GetSquareValue(move.first, move.second);
    
    // switch staement to check what the player landed on
    switch(landedPostion){
        case SquareType::Dot:
            cout<<"Landed on a dot"<<endl;
            dots_count_--;
            board_->SetSquareValue(move.first, move.second, SquareType::Empty);
            p->ChangePoints(1);
            // Move the player to the new position
            board_->MovePlayer(p, move.first, move.second, players_);
            UpdatePlayerData(p, move.first, move.second);
            break;
        case SquareType::Empty:
            cout<<"Landed on an empty square"<<endl;
            break;
        case SquareType::Enemy:
            cout<<"Landed on an enemy"<<endl;
            if(p->hasTreasure()){
                // the enemey has died if it does not have treasure
                 for (auto& enemy : players_) {
                    if (enemy->isHuman() == false) {
                        // if the enemy is not human
                        // move first is the x cordinate and move second is the y cordinate
                        if (enemy->get_x_pos() == move.second && enemy->get_y_pos() == move.first && !enemy->hasTreasure()) {
                            // if the enemy is not human and does not have treasure
                            enemy->has_died();
                            enemy->setLives(enemy->getLives() - 1);
                            // need to call a respawn function
                            // move the player to the same location it died at
                        }
                        else if(enemy->get_x_pos() == move.second && enemy->get_y_pos() == move.first && enemy->hasTreasure()){
                            // if the enemy is not human and does have treasure
                            // nothign should happen since they are both boosted by treasure
                            // thus they loose their treasure
                            enemy->setLostTreasure();
                            p->setLostTreasure();
                        }      
                    }
                 }
            }
            //if the player does not have treasure they have died
            else{
                p->has_died();
                p->setLives(p->getLives() - 1);
                // need to call a respawn function
                // move the player to the same location it died at

                // Move the player to the new position
                // board_->MovePlayer(p, move.first, move.second, players_);
            }
            break;
        case SquareType::Pacman:
            cout<<"Landed on a pacman"<<endl;
            // if the player lands on the pacman something has gone wrong since they are the same player
            // if it is the enemy then the player has lost a life/died
            if(p->isHuman()){
                // Move the player to the new position
                // don't move the player since for right now this is an error
            }

            // right now code below is unused because it is used in the case of the enemy landing on the player
            // if i don't use it i need to make a function for moving the enemy and not have them in the same function

            // else{
            //     if(p->hasTreasure()&& enemy->hasTreasure()){
            //         // if the enemy has treasure and the player has treasure then nothing happens
            //         // the player looses their treasure
            //         p->setLostTreasure();
            //         enemy->setLostTreasure();
            //     }
            //     else if(p->hasTreasure()&&!enemy->hasTreasure()){
            //         // if the enemy does not have treasure and the player does then the enemy has died
            //         enemy->has_died();
            //         enemy->setLives(enemy->getLives() - 1);
            //         // need to call a respawn function
            //         // move the player to the same location it died at
            //     }
            //     else if(!p->hasTreasure()&&enemy->hasTreasure()){
            //         // if the enemy has treasure and the player does not then the player has died
            //         p->has_died();
            //         p->setLives(p->getLives() - 1);
            //         // need to call a respawn function
            //         // move the player to the same location it died at
            //     }
            //     else if(!p->hasTreasure()&&!enemy->hasTreasure()){
            //         // if the enemy does not have treasure and the player does not then the player has died
            //         p->has_died();
            //         p->setLives(p->getLives() - 1);
            //         // need to call a respawn function
            //         // move the player to the same location it died at

            //     }
            //     p->has_died();
            //     p->setLives(p->getLives() - 1);
            //     // need to call a respawn function
            //     // move the player to the same location it died at
            // }

        case SquareType::Treasure:
            cout<<"Landed on a treasure"<<endl;
            p->setHasTreasure();
            p->ChangePoints(100);
            // remove the treasure from the board
            board_->SetSquareValue(move.first, move.second, SquareType::Empty);
            // Move the player to the new position since it is valid
            board_->MovePlayer(p, move.first, move.second, players_); 
            break;
        case SquareType::Trap:
            cout<<"Landed on a trap"<<endl;
            p->has_died();
            p->setLives(p->getLives() - 1);
            // player has hit a trap so they are moved to a random location
            break;
        case SquareType::EnemySpecialTreasure:
            cout<<"Landed on an enemy special treasure"<<endl;
            // a human player has landed on the enemy special treasure
            // this will do nothing for them
            // if an enemy lands on it then they will gain treasure
            if(p->isHuman()){
                // THe player has gone to an invalid location for a player thus they can not go here
                // board_->MovePlayer(p, move.first, move.second, players_);
                cout<<"landed on enemy treasure as a human so nothing happens"<<endl;
            }
            else{
                p->setHasTreasure();
                // remove the treasure from the board
                board_->SetSquareValue(move.first, move.second, SquareType::Empty);
                // not moving the enemy in this function at this momment
                // Move the player to the new position since it is valid
                // board_->MovePlayer(p, move.first, move.second, players_);
                // might need to use the move enemey function
            }
            break;
        case SquareType::Wall:
            cout<<"Landed on a wall"<<endl;
            // if the player lands on a wall then they are not moved
            // this is an invalid move
            // an error has occured
            break;
        default:
            break;
    }

    // Check if the player has won
    if (dots_count_ == 0){
        GameOver = true;
        return true;
    }
    //returning false since game is not over
    return false;
}



bool Game::respawnEnemy(){
    // enemy died so now a new enemy must be spawned at a random location
    Player* enemy = new Player("Enemy", false);
    enemies_.push_back(enemy);
    // Move the player to the new random position
    bool moved = board_->MovePlayerRandom(enemy);
    if(moved){
        // if the player was moved successfully then the player has respawned
        return true;
    }
        // if the player was not moved successfully then the player has not respawned
    return false;
}


bool Game::IsGameOver(Player *p){
    // Check if the player has lost all their lives
    if (p->getLives() <= 0){
        GameOver = true;
        return true;
    }
    else if(GameOver){
        return true;
    }
    else if(dots_count_ == 0&&treasure_count_ == 0){
        GameOver = true;
        return true;
    }
    return false;
}

bool Game::TakeTurnEnemy(Player*enemy){
    // this will use the same structure as the take turn for player function but is based on the enemy
    // the enemey will use the path to position function to find the shortest path to the player
    // then it will move to that position as quick as possible
    // if the enemy lands on the player then the player will loose a life


    // Getting the current position of the player
    // since the only player is pacman, in the player list at this time the first player is the human player
    int player_row = players_[0]->get_y_pos();
    int player_col = players_[0]->get_x_pos();
    Player* target_player = players_[0];
    // find the shortest path to the player
    // this takes in the enemy player and the position of the player it is trying to get to
    // If there are 2 players, pacmen, then i could compare who is closer and then move to that player
    vector<pair<int, int>> path = board_->PathToPosition(enemy, player_row, player_col);

    // Move the enemy to the new position
    pair<int, int> enemey_move = path[1];
    // Check to see if the landed on a valid position
    // if the enemy was moved to a valid spot then it returns true
    switch(board_->GetSquareValue(enemey_move.first, enemey_move.second)){
        case SquareType::Dot:
            // The enemy does not pick up the dot
            // Move the player to the new position
            return board_->MoveEnemy(enemy, enemey_move);
            break;
        case SquareType::Empty:
            // Move the player to the new position
            return board_->MoveEnemy(enemy, enemey_move);
            break;
        case SquareType::Enemy:
            // if the enemy lands on another enemy then they do not move
            return true;
            break;
        case SquareType::Pacman:
            // if the player lands on the pacman something has gone wrong since they are the same player
            // if it is the enemy then the player has lost a life/died

                if(target_player->hasTreasure()&& enemy->hasTreasure()){
                    // if the enemy has treasure and the player has treasure then nothing happens
                    // the player looses their treasure
                    target_player->setLostTreasure();
                    enemy->setLostTreasure();
                    return true;
                }
                else if(target_player->hasTreasure()&&!enemy->hasTreasure()){
                    // if the enemy does not have treasure and the taget player does then the enemy has died
                    // the enemy will respan at a random location
                    enemy->has_died();
                    respawnEnemy(); 
                    // need to call a respawn function
                    // move the player to the same location it died at
                    return true;
                }
                else if((!target_player->hasTreasure() && !enemy->hasTreasure() )|| (!target_player->hasTreasure()&&enemy->hasTreasure())){
                    // if the enemy has treasure and the player does not then the player has died
                    target_player->has_died();
                    target_player->setLives(target_player->getLives() - 1);
                    if(target_player->getLives() <= 0){
                        IsGameOver(target_player);
                    }
                    return true;
                }
                else{
                    // something has gone wrong here
                    return false;
                }
            break;
        case SquareType::Treasure:
            // the enemy does not pick up the treasure
            // Move the player to the new position
            return board_->MoveEnemy(enemy, enemey_move);
            break;
        default:
            return false;
            break;
    }
}

void Game::playGame(){
    DisplayGame();
    // this will be the main function that will be used to play the game
    // It will be repeated many times
    // set Pacman location to 1,1
    board_->SetSquareValue(1, 1, SquareType::Pacman);
    DisplayGame();
    cout<<"Player's turn\n "<<endl;
    cout<<"What does the player want to do? "<<endl;
    // pair<int, int> move = PresentMoveOptions(players_[0]); 
    // if(move.first == -100 && move.second == -100){
    //     cout<<"Player has chosen to not move"<<endl;
    // }
    // else{
    //     cout<<"Player has chosen to move to: "<<move.first<<", "<<move.second<<endl;
    // }
    // cout<<"Player has chosen to move to: "<<move.first<<", "<<move.second<<endl;
    // UpdatePlayerData(players_[0], move.first, move.second);
    // // player data is updated confirmation:
    TakeTurn(players_[0]);
    cout<<"Player's data: "<<players_[0]->get_name()<<endl;
    cout<<"Player's points: "<<players_[0]->getPoints()<<endl;
    cout<<"Player's lives: "<<players_[0]->getLives()<<endl;
    cout<<"Player's moves taken: "<<players_[0]->getMovesTaken()<<endl;
    cout<<"Player is at: "<<players_[0]->get_x_pos()<<", "<<players_[0]->get_y_pos()<<endl;
}


string Game::GenerateReport(Player *p){
    // this will generate a report about the game's conditions after it is over
    // this will take in the player and return a string
    // this will also take into account the other players and what has all happened during the game
    string report = "Player: " + p->get_name() + " has " + std::to_string(p->getPoints()) + " points.\n";
    report +="There are " + std::to_string(dots_count_) + " dots left and there are: " + std::to_string(treasure_count_) + " treasures left.\n ";
    report +="Player has taken: " + std::to_string(p->getMovesTaken()) + " moves.\n";
    if(p->getLives() <= 0){
        report = "Game Over: ";
        report += "You have lost all your lives. ";
    }
    else if(dots_count_ == 0){
        report += "You have won the game. ";
    }
    else if(GameOver){
        report += "The game is over. ";
    }
    return report;
}

std::ostream& operator<<(std::ostream& os, const Game &m) {
    os << "Game: \n";
    os << "Players: \n";
    for (auto& player : m.players_) {
        os << "Name: " << player->get_name() << ", Points: " << player->getPoints() << ", Lives: " << player->getLives() << "\n";
    }
    os << "Board: \n";
    for (int i = 0; i < m.board_->get_rows(); i++) {
        for (int j = 0; j < m.board_->get_cols(); j++) {
            switch(m.board_->GetSquareValue(i, j)) {
                case SquareType::Empty: 
                    os << "🪹"; // Empty Basket meaning nothing
                    break;
                case SquareType::Wall: 
                    os << "🧱"; // Brick
                    break;
                case SquareType::Dot:
                    os << "🍩"; // Donut for the dot
                    break;
                case SquareType::Pacman:
                    os << "😃"; // Grinning face
                    break;
                case SquareType::Treasure:
                    os << "💰"; // Money bag 
                    break;
                case SquareType::Enemy:
                    os << "👾"; // Alien monster aka the GHOST
                    break;
                case SquareType::PowerUP:
                    os << "🔋"; // Battery
                    break;
                case SquareType::Trap:
                    os << "⚠️"; // Warning
                    break;
                case SquareType::EnemySpecialTreasure:
                    os << "👑"; // Crown
                    break;
            }
        }
        os << "\n";
    }
    return os;
}


void Game::DisplayGame(){
    std::stringstream output; // Create a stringstream object to capture the output
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Save the current cout buffer

    std::cout.rdbuf(output.rdbuf()); // Redirect cout to the stringstream output

    std::cout << *this << std::endl; // Output the game with the redirected cout

    std::string printedOutput = output.str(); // Store the output in a string

    std::cout.rdbuf(coutBuffer); // Restore the original cout buffer

    std::cout << printedOutput; // Print the captured output
}


bool Game::visitEveryDot_Treasure(){
    // this function is used to see what the minimum moves are to get to every dot and treasure on the board
    // this is used as a comparison for how long the game could take

    // first build a matrix that finds the shortest path from the startring position to every dot and treasure
    // this is entirely for testing. Make sure to change for finding every value
    int distance = board_->PathToPosition(players_[0], 2,2).size();
    if(distance == 0){
        return false;
    }
    return true;
}

