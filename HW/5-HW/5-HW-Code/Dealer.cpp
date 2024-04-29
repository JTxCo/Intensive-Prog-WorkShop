#include "Dealer.hpp"
#include "Player.hpp"


Dealer::Dealer(string name) : Player(name) {}


Dealer::~Dealer() {
    ClearHand();
}

void Dealer::FlipFirstCard() {
    m_Hand[0]->Flip();
}

void Dealer::FlipAllCards() {
    for (auto card : m_Hand) {
        card->Flip();
    }
}

Card Dealer::getCard(int index) {
    return *m_Hand[index];
}