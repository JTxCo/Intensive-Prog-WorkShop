#include "Game.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
using std::string;
using std::pair;
using std::vector;
using std::make_pair;
using std::priority_queue;
using std::reverse;
Board::Board(){
    // Dynamically allocate memory for the 2D array
    arr_ = new SquareType*[rows];
    for (int i = 0; i < rows; ++i) {
        arr_[i] = new SquareType[cols];
    }
}

// Custom constructor to set rows and cols
Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    // Dynamically allocate memory for the 2D array
    arr_ = new SquareType*[rows];
    for (int i = 0; i < rows; ++i) {
        arr_[i] = new SquareType[cols];
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

bool Board::notWall(int row, int col) {
    // Accessing GetSquareValue function result
    SquareType square = arr_[row][col];
    if (square == SquareType::Wall) {
        return false;
    }
    return true;
}
vector<pair<int, int>> Board::GetMoves(Player* p) {
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
        vector<pair<int, int>> neighbors = GetMoves(p);

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



Game::Game() {}
Game::Game(Player* human, const int enemies) {}