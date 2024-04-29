#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>
#include "Card.hpp"
using std::string;
//Player class for the Blackjack game
//Child class will be Dealer class
class Player
{

protected:
    std::vector<Card*> m_Hand;
    string name_;
public:
    Player(string name);
    virtual ~Player() = default;
    std::vector<Card*> getHand();
    int GetHandValue();
    void addCard(Card* pCard);
    void ClearHand();
    bool IsBusted();
    void printHand();
    string getName();

};

#endif // PLAYER_HPP