#include <iostream>
#include <vector>
#include "Player.hpp"
#include   <cassert>



std::vector<Player*> addPlayers(const std::vector<std::string>& playerNames) {
    std::vector<Player*> players;
    if(playerNames.size() > 8) {
        std::cout << "Too many players" << std::endl;
        return players;
    }
    for (const std::string& name : playerNames){
        Player* newPlayer = new Player(name); 
        players.push_back(newPlayer);
    }
    std::cout << "Total players: " << players.size() << std::endl;
    return players;
}

void testAddPlayers() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    std::vector<Player*> players = addPlayers(names);
    assert(players.size() == names.size());
    for(int i = 0; i < players.size(); i++) {
        assert(players[i]->getName() == names[i]);
    }


    for(auto player : players) {
        delete player;
    }
}

void testAdd9Players() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Heidi", "Ivan"};
    std::vector<Player*> players = addPlayers(names);
    assert(players.size() == names.size());
    for(int i = 0; i < players.size(); i++) {
        assert(players[i]->getName() == names[i]);
    }

   
    for(auto player : players) {
        delete player;
    }
}

int main() {
    testAddPlayers();
    testAdd9Players();
    return 0;
}