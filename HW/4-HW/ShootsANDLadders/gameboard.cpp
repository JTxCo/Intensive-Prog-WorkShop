#include "gameboard.h"
#include <random>

GameBoard::GameBoard(){}






int GameBoard::rollDice() {

    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 6); // Define the range

    // Generate and return a random number between 1 and 6 for each dice Then add them together:

    diceRollValue = distr(gen) + distr(gen);
    return diceRollValue;
}

