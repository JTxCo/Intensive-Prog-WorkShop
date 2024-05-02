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

Card* Dealer::getCard(int index) {
    // printing the hand to see if the card is being removed
    std::cout<<"printing hand to see if card is being removed"<<std::endl;
    for(auto card : m_Hand)
    {
        std::cout<<"card in hand: "<<*card<<std::endl;
    }
    // size of hand 
    std::cout<<"size of hand: "<<m_Hand.size()<<std::endl;
    // printing out the hand:
    for (auto card : m_Hand) {
        std::cout << *card << " ";
    }




    index -= 1; // Adjust index to 0-based
    if(index < m_Hand.size() && index >= 0) { // Check if index is within bounds
        std::cout<<"Dealer's card: "<<*m_Hand[index]<<"\n";
        Card* cardToReturn = m_Hand[index];
        std::cout<<"Dealer's card: "<<*cardToReturn<<"\n";
        m_Hand.erase(m_Hand.begin() + index); // Remove card from dealer's hand
        return cardToReturn;
    }
    return nullptr; // Return null if no card at given index, you should check this in your main code
}


int Dealer::sizeOfHand() {
    return m_Hand.size();
}

vector<Card*>* Dealer::getRealHand() {
    return &m_Hand;
}