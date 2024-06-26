#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Player.hpp"

using std::vector;

class Dealer : public Player
{
    public:
        explicit Dealer(string name);
        virtual ~Dealer();
        Card* getCard(int index);
        void FlipFirstCard();
        void FlipAllCards();
        int sizeOfHand();
        vector<Card*>* getRealHand();
};