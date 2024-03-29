#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <string>
#include <utility>
#include "Player.h"
#include <map>
using std::vector;
using std::pair;
using std::string;
// you may change this enum as you need
enum class SquareType { Wall, Dot, Pacman, Treasure, Enemy, Empty, PowerUP, Trap, EnemySpecialTreasure };

// TODO: implement
std::string SquareTypeStringify(SquareType sq);

class Board {
private:
	int rows_; // might be convenient but not necessary
	int cols_;
	int dots_count_;
	int treasure_count_;
	int walls_count_;
	int traps_count_;
	int enemySpecialTreasure_count_;
	std::map<Player*, std::pair<std::pair<int, int>, SquareType>> enemyLastPos;
	SquareType **arr_;//this is how the board is stored, this is based on the default constructor
	// if you want to set to another size then this will be set based on the input
	// SquareType arr_[rows][cols];
	bool **isAvailable;
	vector<pair<int, int>> availableSquares;
	// this is the amount of rows and columns in the board
	int moveMin;//this is the minimum amount of moves that the player can make in order to get every dot and every treasure
	// you may add more fields, as needed
public:
	// // TODO: implement
	// this would be a default 10 x 10 board
	Board();
	Board(int rows, int cols);
	~Board();
	vector<pair<int, int>> PathToPosition(Player *p, int row, int col);

	// // already implemented in line
	int get_rows() const {return rows_; }  // you should be able to change the size of your
	// default board by changing these numbers and the numbers in the arr_ field
	int get_cols() const {return cols_; }  // board by changing these numbers and the numbers in the arr_ field
	SquareType** get_arr() const {return arr_; }  // board by changing these numbers and the numbers in the arr_ field

	// get the count of the dots, walls, traps, treasures, and enemy special treasures
	int getDotsCount() const {return dots_count_; }
	int getTreasureCount() const {return treasure_count_; }
	int getWallsCount() const {return walls_count_; }
	int getTrapsCount() const {return traps_count_; }
	int getEnemySpecialTreasureCount() const {return enemySpecialTreasure_count_; }
	void setEnemyLastPos(Player *p, std::pair<int, int> pos, SquareType sq){
		enemyLastPos[p] = {pos, sq};
	}
	std::map<Player*, std::pair<std::pair<int, int>, SquareType>> getEnemyLastPos() const {return enemyLastPos; }
	SquareType getEnemyLastPos(Player *p){
		return enemyLastPos[p].second;
	}
	// // TODO: you MUST implement the following functions
	// SquareType get_square_value(Position pos) const;
	SquareType GetSquareValue(int row, int col);
	// this function looks into the isAvailable array and checks if the postion is available to move to
	// this will return true if the position is available and false if it is not
	// the only positions available are dots and empty, all else are not available 
	bool isSquareAvailable(int row, int col);
	bool notWall(int row, int col);
	// // set the value of a square to the given SquareType
	// void SetSquareValue(Position pos, SquareType value);
	void SetSquareValue(int row, int col, SquareType value);
	// look in the array and set the value of the square to the given SquareType
	// this will use the row n

	void setAvailableSquares();
	bool **getAvailableSquares() const {return isAvailable; }
	// // get the possible Positions that a Player/Enemy could move to
	// // (not off the board or into a wall)
	// std::vector<Position> GetMoves(Player *p);
	vector<pair<int, int>> GetPossibleMoves(int currRow, int currCol);
	// this will return a vector of possible positions that a player can move to
	// this will be based on the current position of the player and the board
	// this will also take into account the walls and the other players
	// I rewrote this to just use rows and columns 
	// i would return this below:
	// std::vector<std::pair<int, int>> positions;
	// the function would be:
	// std::vector<std::pair<int, int>> GetMoves(Player *p);
	// this will return a vector of possible positions that a player can move to in the coventional x and y coordinates as ints


	//




	// // Move a player to a new position on the board. Return
	// // true if they moved successfully, false otherwise.
	// bool MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist);
	// this will move the player to a new position on the board
	// this will return true if they moved successfully, false otherwise
	// this will also take into account the other players and the walls
	// this will also take into account the enemies
	// this will also take into account the dots and the treasure

	// if i rewrite this i would have:
	bool MovePlayer(Player *p, int row, int col, vector<Player*> enemylist);
	// this would just use the conventional int pair cordinates

	bool MovePlayerRandom(Player *p);

	

    // // Move an enemy to a new position on the board. Return
	// // true if they moved successfully, false otherwise.
    // bool MoveEnemy(Player *p, Position pos);
	// this will move the enemy to a new position on the board
	// this will return true if they moved successfully, false otherwise
	// this will also take into account the other players and the walls
	// this will also take into account the enemies
	// this will also take into account the dots and the treasure

	// if i rewrite this i would have:
	bool MoveEnemy(Player *p, std::pair<int, int> pos);


	// this generates a border around it so that the player cannot move off the board
	bool generateBorder();
	// this will generate the board off of a given dimension
	bool GenerateBoard(int row, int col);


	// function to fill in the walls and other stuff
	bool fillInBoard();//this is random fill


	
	// // You probably want to implement this
	friend std::ostream& operator<<(std::ostream& os, const Board &b);
	// this will print the board to the console
	// this will be based on the current state of the board
	// this will also take into account the players and the enemies
	// this will also take into account the walls and the dots
	// this will also take into account the treasure and the traps
	// this will also take into account the powerful pacman and the enemy special treasure


};  // class Board

class Game {
private:
	Board *board_;
	std::vector<Player *> players_;
	int turn_count_;
    int dots_count_;
	int treasure_count_;
    bool GameOver;
	// Array of enemies
	vector<Player *> enemies_;
	// you may add more fields, as needed
public:
	// TODO: implement these functions
	Game(); // constructor
		// // initialize a new game, given one human player and
	// // a number of enemies to generate
	Game(int row, int col, const int enemies);
	// seems like this would not get used often so i would probably not implement this
	Board* getBoard() const {return board_; }  // this will return the board
	vector<Player*> getPlayers() const {return players_; }  // this will return the players
	vector<Player*> getEnemies() const {return enemies_; }  // this will return the enemies
	// free memory
	~Game();
	// this function sets the player, pacman, and the enemies
	// it also sets the game conifguration
	bool setGameData();
	bool setTurnCount(int turn_count){
		turn_count_ = turn_count;
		return true;
	};
	int getTurnCount() const {return turn_count_; }
	bool setDotsCount(int dots_count){
		dots_count_ = dots_count;
		return true;};
	int getDotsCount() const {return dots_count_; }
	bool setTreasureCount(int treasure_count){
		treasure_count_ = treasure_count;
		return true;};
	int getTreasureCount() const {return treasure_count_; }
	//for the player this will display the available options and then take the input
	pair<int,int> PresentMoveOptions(Player *p);

	// this function is used to visit every dot and treasure on the board and count how mnay that is to see if the game is over
	bool visitEveryDot_Treasure();
	// this will update the players data based on what has happened
	bool UpdatePlayerData(Player *p, int row, int col);
	// // have the given Player take their turn
	// void TakeTurn(Player *p,std::vector<Player*> enemylist);
	// this will have the given player take their turn
	// this will also take in the list of enemies
	// i think that this should not need to take in the list of enemies because the enemies should be on the board
	// since the board should know 
	// this will also take into account the other players and the walls
	bool TakeTurn(Player *p);
	// this will have the given player take their turn

	// //have the enemy take turn
	bool TakeTurnEnemy(Player *enemy);
	// this will have the enemy take their turn


	// if the enemy is killed by a player with treasure then a new enemy will respawn at a random location
	bool respawnEnemy();


	// this will check if the game is over
	bool IsGameOver(Player *p);
	

	// // return true if all pellets have been collected
	bool CheckifdotsOver(){
		if(dots_count_ == 0){
			return true;
		}
		return false;
	};
	// this will return true if all the dots have been collected
	// return false if there are still dots on the board


	// this is the function that plays the game
	void playGame();

	// function to output the baord of the game display the report
	void DisplayGame();


	// // You probably want to implement these functions as well
	// // string info about the game's conditions after it is over
	string GenerateReport(Player *p);
	// this will generate a report about the game's conditions after it is over
	// this will take in the player and return a string
	// this will also take into account the other players and what has all happened during the game



	friend std::ostream& operator<<(std::ostream& os, const Game &m);
	// this will print the game to the console
	// this will be based on the current state of the game
	// this will also take into account the players and the enemies




	// you may add more fields, as needed

};  // class Game

#endif  // _GAME_H_
