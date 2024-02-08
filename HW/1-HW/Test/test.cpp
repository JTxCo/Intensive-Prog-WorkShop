#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../SRC/Game.h"
#include "../SRC/Player.h"
#include "string"

// testing if all the options for creating the game work
TEST_CASE("Game with 15 x16 and 4 enemies"){
    Game *game = new Game(15, 16, 4);
    REQUIRE(game->getBoard()->get_rows() == 17);//2 more since there is a border around all of it
    REQUIRE(game->getBoard()->get_cols() == 18);
    REQUIRE(game->getEnemies().size() == 4);
    delete game;
}



// these 2 tests are only testing if the board gets initialized correctly
TEST_CASE("does the board get constructed correctly"){
    Game *game = new Game();
    Board* board = game->getBoard();
    REQUIRE(board->get_rows() == 12);
    REQUIRE(board->get_cols() == 12);    
    delete game;    
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

    