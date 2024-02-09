#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../SRC/Game.h"
#include "../SRC/Player.h"
#include "string"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

// testing if all the options for creating the game work
TEST_CASE("Game with 15 x16"){
    Board *board = new Board(15, 16);
    REQUIRE(board->get_rows() == 17);//2 more since there is a border around all of it
    REQUIRE(board->get_cols() == 18);
    delete board;
}



// these 2 tests are only testing if the board gets initialized correctly
TEST_CASE("does the board get constructed correctly"){
    // Game *game = new Game();
    Board* board = new Board();
    REQUIRE(board->get_rows() == 12);
    REQUIRE(board->get_cols() == 12);    
    delete board;    
}

TEST_CASE("does the board get constructed correctly with the given size"){
    Board* board = new Board(10, 10);
    REQUIRE(board->get_rows() == 12);
    REQUIRE(board->get_cols() == 12);    
    delete board;    
}

// testing if generating the board works correctly
TEST_CASE("does the board get generated correctly"){
    Board* board = new Board();
    REQUIRE(board->get_arr()[0][0] == SquareType ::Wall);
    REQUIRE(board->get_arr()[0][1] == SquareType ::Wall);
    REQUIRE(board->get_arr()[1][0] == SquareType ::Wall);
    REQUIRE(board->get_arr()[11][11] == SquareType ::Wall);
    REQUIRE(board->get_arr()[2][2] == SquareType ::Dot);
}
// TEST_CASE("Does the board print correctly"){
//     std::stringstream output; // Create a stringstream object to capture the output
//     std::streambuf* coutBuffer = std::cout.rdbuf(); // Save the current cout buffer

//     std::cout.rdbuf(output.rdbuf()); // Redirect cout to the stringstream

//     Game* game = new Game();
//     std::cout << *game << std::endl; // Output the game with the redirected cout

//     std::cout.rdbuf(coutBuffer); // Restore the original cout buffer

//     std::string printedOutput = output.str(); // Get the printed content from the stringstream

//     // Test assertions based on the printed output
//     REQUIRE(printedOutput == "expected output");

//     delete game;
// }


// TEST_CASE("Does the board print correctly for larger dimmensions"){
//     std::stringstream output; // Create a stringstream object to capture the output
//     std::streambuf* coutBuffer = std::cout.rdbuf(); // Save the current cout buffer
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//     printf ("lines %d\n", w.ws_row);
//     printf ("columns %d\n", w.ws_col);
//     std::cout.rdbuf(output.rdbuf()); // Redirect cout to the stringstream

//     Game* game = new Game(20,40,5);
//     std::cout<<std::setw(70);
//     std::cout << *game << std::endl; // Output the game with the redirected cout

//     std::cout.rdbuf(coutBuffer); // Restore the original cout buffer

//     std::string printedOutput = output.str(); // Get the printed content from the stringstream

//     // Test assertions based on the printed output
//     REQUIRE(printedOutput == "expected output");

//     delete game;
// }

// TEST_CASE("Testing Player Position Selection"){
//     Game *game = new Game();
//     Player* player = game->getPlayers()[0];
//     game->PresentMoveOptions(player);
//     REQUIRE(player->get_x_pos() == 1);
//     REQUIRE(player->get_y_pos() == 0);
//     delete game;
// }



// testing to see if the enemy ghost can track the player packman
TEST_CASE("testing ghost tracking player"){
    Game* game = new Game();
    Player* player = game->getPlayers()[0];
    Player *ghost = game->getEnemies()[0];
    player->SetPosition(1,1);
    ghost->SetPosition(1,8);
    vector<pair<int, int>> path = game->getBoard()->PathToPosition(player,ghost->get_x_pos(), ghost->get_y_pos());

    REQUIRE(path[0].first == 1);
    REQUIRE(path[0].second == 1);
    REQUIRE(path[1].first == 1);
    REQUIRE(path[1].second == 2);

    delete game;
}