#include <iostream>
#include "Card.hpp"






//Special type of card 
// (Joker Class): There will be X for number of player joker cards: these allow the player to set the value they want the card to be up 11 as that is the equivalent of an ace


class Joker : public Card
{
    private:  
        Special m_special = Special::SPECIAL_JOKER;  
        int m_value;
    public:
        Joker();
        void SetValue(int value);//value is going to be set by the player for what they want it to be
        Special getSpecial() const override;
        friend std::ostream& operator<< (std::ostream& out, const Joker& joker);
};