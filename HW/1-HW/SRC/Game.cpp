#include "Game.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <regex>
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

Board::Board() : rows(10), cols(10) { // Set default size of board to 10x10
    // Dynamically allocate memory for the 2D array
    // Initialize all positions as available, this might change later based on how the board set up is done later
    arr_ = new SquareType*[rows];
    isAvailable = new bool*[rows];
    for (int i = 0; i < rows; ++i) {
        arr_[i] = new SquareType[cols];
        isAvailable[i] = new bool[cols];
        for (int j = 0; j < cols; ++j) {
            isAvailable[i][j] = true; 
        }
    }
}

// Custom constructor to set rows and cols
// Initialize all positions as available, this might change later 
Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    // Dynamically allocate memory for the 2D array
    arr_ = new SquareType*[rows];
    isAvailable = new bool*[rows];
    for (int i = 0; i < rows; ++i) {
        arr_[i] = new SquareType[cols];
        isAvailable[i] = new bool[cols];
        for (int j = 0; j < cols; ++j) {
            isAvailable[i][j] = true; 
        }
    }
}
// Destructor to free memory
Board::~Board() {
    for (int i = 0; i < rows; ++i) {
        delete[] arr_[i];
    }
    delete[] arr_;
}

SquareType Board::GetSquareValue(int row, int col){
    return arr_[row][col];
}

void Board::SetSquareValue(int row, int col, SquareType value){
    arr_[row][col] = value;
}


void Board::setAvailableSquares(){
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
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
    // Accessing GetSquareValue function result
    SquareType square = arr_[row][col];
    if (square == SquareType::Wall) {
        return false;
    }
    return true;
}
vector<pair<int, int>> Board::GetPossibleMoves(Player* p) {
    // Obtain the current position of the player
    int currRow = p->get_y_pos();
    int currCol = p->get_x_pos();

    vector<pair<int, int>> positions;

    // Check the adjacent positions for valid moves, without considering walls
    if (currRow - 1 >= 0)
        positions.push_back(make_pair(currRow - 1, currCol));

    if (currRow + 1 < rows)
        positions.push_back(make_pair(currRow + 1, currCol));

    if (currCol - 1 >= 0)
        positions.push_back(make_pair(currRow, currCol - 1));

    if (currCol + 1 < cols)
        positions.push_back(make_pair(currRow, currCol + 1));

    return positions;
}



vector<pair<int, int>> Board::PathToPosition(Player* p, int endRow, int endCol) {
    int startRow = p->get_y_pos();
    int startCol = p->get_x_pos();
    int n = rows;

    // uint's used to avoid negative values, adjust accordingly.
    const unsigned int INF = (unsigned int)-1;

    // Create 2D vector for visited status and distances
    vector<vector<bool>> visited(n, vector<bool>(rows, false));
    vector<vector<int>> dist(n, vector<int>(rows, INF));
    vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(rows, make_pair(-1, -1)));

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
        // Modify this as needed based on the rules of your game
        vector<pair<int, int>> neighbors = GetPossibleMoves(p);

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
bool Board::MovePlayerRandom(Player* p, vector<Player*> enemylist) {
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







Game::Game() {
    // Create a new game
    Board* board = new Board();
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
        players_.push_back(enemy);
    }
}
Game::Game(Player* human, const int enemies) {
    // Create a new game
    Board* board = new Board();
    //setting variables
    turn_count_ = 0;
    dots_count_ = 0;
    GameOver = false;
    // Create a new player
    players_.push_back(human);
    // Create new enemies
    for (int i = 0; i < enemies; i++) {
        Player* enemy = new Player("Enemy", false);
        players_.push_back(enemy);
    }
}

Game::~Game() {
    // Free memory
    delete board_;
    for (auto& player : players_) {
        delete player;
    }
}




pair<int,int> Game::PresentMoveOptions(Player *p){
    // Obtain the current position of the player
    int currRow = p->get_y_pos();
    int currCol = p->get_x_pos();
    pair<int, int> choosenMove = make_pair(-100, -100);
    // Check the adjacent positions for valid moves, will not allow to move into walls
    vector<pair<int, int>> positions = board_->GetPossibleMoves(p);
    // Present the options to the player
    cout << "Possible moves: " << endl;
    for (int i = 0; i < positions.size(); i++) {
        cout << i << ": " << positions[i].first << ", " << positions[i].second << endl;
    }
    // Take the input from the player
    std::regex coordinate_pattern("\\((\\d+),(\\d+)\\)");
    string choice;
    cout << "Enter the number of the position you want to move to: ";
    cin >> choice;
    std::smatch result;
    if (std::regex_match(choice, result, coordinate_pattern)) {
        int x = std::stoi(result[1]);
        int y = std::stoi(result[2]);
        choosenMove = make_pair(x, y);
        std::cout << "X: " << x << ", Y: " << y << std::endl;
    } else {
        std::cout << "Invalid input.\n";
    }
    return choosenMove;
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
            dots_count_--;
            board_->SetSquareValue(move.first, move.second, SquareType::Empty);
            p->ChangePoints(1);
            // Move the player to the new position
            board_->MovePlayer(p, move.first, move.second, players_);
            break;
        case SquareType::Empty:
            break;
        case SquareType::Enemy:
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
                            enemy->setHasTreasure();
                
                            
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
        case SquareType::Treasure:
            p->setHasTreasure();
            p->ChangePoints(100);
            // remove the treasure from the board
            board_->SetSquareValue(move.first, move.second, SquareType::Empty);
            // Move the player to the new position since it is valid
            board_->MovePlayer(p, move.first, move.second, players_); 
            break;
        case SquareType::Trap:
            p->has_died();
            p->setLives(p->getLives() - 1);
            // player has hit a trap so they are moved to a random location
            break;
        case SquareType::EnemySpecialTreasure:

        default:
            break;
    }





    // Check if the player landed on the treasure, if they have set the treasure flag and add points 100
    // if (board_->GetSquareValue(row, col) == SquareType::Treasure) {
    //     p->setHasTreasure();
    //     p->ChangePoints(100);
    // }
    // Check if the player landed on an enemy
    for (auto& enemy : players_) {
        if (enemy->isHuman() == false) {
            if (enemy->get_x_pos() == col && enemy->get_y_pos() == row) {
                p->has_died();
                p->setLives(p->getLives() - 1);
                // need to call a respawn function
                // move the player to the same location it died at
            }
        }
    }

    // Check if the player landed on the enemy special treasure
    if (board_->GetSquareValue(row, col) == SquareType::EnemySpecialTreasure) {
        // Move the player to a random position
        int randomRow = rand() % board_->rows;
        int randomCol = rand() % board_->cols;
        board_->MovePlayer(p, randomRow, randomCol, players_);
    }
    // Check if the player landed on a trap
    if (board_->GetSquareValue(row, col) == SquareType::Trap) {
        p->has_died();
        p->setLives(p->getLives() - 1);
    }
    // Check if the player has won
    if (dots_count_ == 0)


}

