#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Player.hpp"

using std::vector;

class Dealer : public Player
{
    private:
        vector<Card*> m_Hand;
    public:
        Dealer(string name);
        virtual ~Dealer();
        Card* getCard(int index);
        void FlipFirstCard();
        void FlipAllCards();
};