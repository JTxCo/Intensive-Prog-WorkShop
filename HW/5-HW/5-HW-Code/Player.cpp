#include "Player.hpp"

Player::Player(string name) : name_(name){
}

// Player::~Player() {
//     for (auto card : m_Hand) {
//         delete card;
//     }
// }

std::vector<Card*>& Player::getHand() // return a reference to the hand
{
    return m_Hand;
}
int Player::GetHandValue() {
    int total = 0;
    for (auto card : m_Hand) {
        total += card->getValue();
    }
   return total;
}

void Player::addCard(Card* pCard) {
    m_Hand.push_back(pCard);
}

void Player::setCard(Card* pCard, int index) {
    m_Hand[index] = pCard;
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