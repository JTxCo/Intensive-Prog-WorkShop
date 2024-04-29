#include "Player.hpp"

Player::Player(string name) {
    name_ = name;
}

// Player::~Player() {
//     for (auto card : m_Hand) {
//         delete card;
//     }
// }

std::vector<Card*> Player::getHand() {
    return m_Hand;
}
int Player::GetHandValue() {
    int total = 0;
    int numAces = 0;

    for (auto card : m_Hand) {
        if (card->getValue() == 1) {
            numAces++;
        }
        
        total += card->getValue();
    }
    while (total <= 11 && numAces > 0) {
        total += 10;
        numAces--;
    }
    return total;
}

void Player::addCard(Card* pCard) {
    m_Hand.push_back(pCard);
}

void Player::ClearHand() {
    m_Hand.clear();
}

bool Player::IsBusted() {
    return GetHandValue() > 21;
}

void Player::printHand() {
    std::cout << name_ << " has: ";
    for (auto card : m_Hand) {
        std::cout << *card << " ";
    }
    std::cout << std::endl;
}

string Player::getName() {
    return name_;
}