#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>
#include <utility>
using std::string;
using std::pair;
using std::vector;
using std::cout;




class Player {
public:

	private:
	// I will change the constructor to take 2 ints for the position
	// I will also add default values for the other fields
		string name;
		bool is_human;
		int x_pos;
		int y_pos;
		bool has_Treasure_ = false;
		bool isDead_ = false;
		int lives_ = 3;
	public:
    	Player(string name, bool is_human, int x=0, int y=0) : // Added default values for x and y
        name(name), is_human(is_human), x_pos(x), y_pos(y) { } 
	// these are just a bunch of getters for the player class
		string get_name() const {return name;}  
		int get_x_pos() const {return x_pos; }
		int get_y_pos() const {return y_pos; }
		pair<int, int> get_position() const {return std::make_pair(x_pos,y_pos); }
		bool isHuman() const {return is_human; }
		bool hasTreasure() const {return has_Treasure_; } 
		bool isDead() const {return isDead_; }  
		void has_died() {isDead_ = true;}
		int getLives() const {return lives_; }  
		void setLives(int lives) {lives_ = lives; }  
		void setHasTreasure() {has_Treasure_ = true; }  



		// // TODO: implement the following functions
		// // You MUST implement the following functions
		void ChangePoints(const int x){
			x_pos += x;
			y_pos += x;
		}
		// // this will change the points of the player by the value of x
		// to me this seems like an odd way to do it since it has less control than just setting the points to a value

		// // set a new position for this player
		void SetPosition(const int row, const int col){
			x_pos = row;
			y_pos = col;
		}
		// vector<pair<int,int>>PathToPosition(int row, int col); decided to move this to the game class
		void PrintPlayerData(){
			cout << "Name: " << name << " Position: " << x_pos << ", " << y_pos;
		}

}; // class Player

#endif  // _PLAYER_H_
