#include "Game.h"
#include "Player.h"
#include "string"

using std::cout;
using std::endl;
int main() {
    // Create a new game
    Game game;
    // Run the game
    Player *human = new Player("Human", true);
    Board *board = new Board();
    cout << "Game Over: "  << endl;
}