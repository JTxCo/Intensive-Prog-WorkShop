#include "Card.hpp"

Card::Card(Suit suit, Rank rank, bool isFaceUp)
    : m_suit(suit), m_rank(rank), m_isFaceUp(isFaceUp)
{
    // Your code here
}

void Card::Flip()
{
    m_isFaceUp = !m_isFaceUp;
}
void Card::setValue(int value)
{
    std::cout<<"setting value to: "<< value<<std::endl;
    m_value = value;
}

int Card::getValue() const
{
    int value{ 0 };
    if (m_isFaceUp)
    {
        switch(m_rank) 
        {   
            case Rank::MAX_RANKS:
                value = 0;
                // use the get value function
                if(m_special == Special::SPECIAL_JOKER)
                {
                    // std::cout<<"rank of joker"<<std::endl;
                    value = m_value;
                }
                else if(m_special == Special::SPECIAL_EMPEROR)
                {
                    // std::cout<<"rank of emperor"<<std::endl;
                    value = m_value;
                }
                break;
            case Rank::RANK_ACE:
                std::cout<<"rank of ace value: "<<m_value<<std::endl;
                value = m_value;
                break;
            case Rank::RANK_10:
            case Rank::RANK_JACK:
            case Rank::RANK_QUEEN:
            case Rank::RANK_KING:
                value = 10;
                break;
            default:
                value = static_cast<int>(m_rank) + 2;  // Adding 2 because the Rank enum starts at 0 for RANK_2
        }
    }
    return value;
}


Rank Card::getRank() const
{
    return m_rank;
}

Suit Card::getSuit() const
{
    return m_suit;
}

void  Card::setSpecial(Special special)
{

    m_special = Special::SPECIAL_MAX;
}

Special Card::getSpecial() const
{
    if(m_rank == Rank::RANK_ACE){
        return Special::SPECIAL_ACE;
    }
    return Special::SPECIAL_MAX;  // Or another default value
}
// friend std::ostream& operator<<(std::ostream& out, const Card& card)

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    // if (card.m_isFaceUp)
    // {
        const char* suit{};
        const char* rank{};

        switch (card.m_suit)
        {
        case Suit::SUIT_CLUB:
            suit = "Clubs";
            break;
        case Suit::SUIT_DIAMOND:
            suit = "Diamonds";
            break;
        case Suit::SUIT_HEART:
            suit = "Hearts";
            break;
        case Suit::SUIT_SPADE:
            suit = "Spades";
            break;
        case Suit::MAX_SUITS:
            suit = "Special";
            break;
        }

        switch (card.m_rank)
        {
        case Rank::RANK_2:
            rank = "2";
            break;
        case Rank::RANK_3:
            rank = "3";
            break;
        case Rank::RANK_4:
            rank = "4";
            break;
        case Rank::RANK_5:
            rank = "5";
            break;
        case Rank::RANK_6:
            rank = "6";
            break;
        case Rank::RANK_7:
            rank = "7";
            break;
        case Rank::RANK_8:
            rank = "8";
            break;
        case Rank::RANK_9:
            rank = "9";
            break;
        case Rank::RANK_10:
            rank = "10";
            break;
        case Rank::RANK_JACK:
            rank = "Jack";
            break;
        case Rank::RANK_QUEEN:
            rank = "Queen";
            break;
        case Rank::RANK_KING:
            rank = "King";
            break;
        case Rank::RANK_ACE:
            rank = "Ace";
            break;
        case Rank::MAX_RANKS:
            rank = " Card";
            break;
        }

        Special special = card.getSpecial();
        switch(special)
            {
            case Special::SPECIAL_ACE:
                break;
            case Special::SPECIAL_MAX:
                break;
            case Special::SPECIAL_JOKER:
                rank = "Joker";
                suit = " ";
                break;
            case Special::SPECIAL_EMPEROR:
                rank = "Emperor";
                break;
            }
        out << rank << suit;
    // }
    // else
    // {
    //     out << "XX";
    // }

    return out;
}