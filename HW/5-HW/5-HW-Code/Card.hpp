#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>

enum class Suit
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS,
};

enum class Rank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

enum class Special
{
    SPECIAL_JOKER,
    SPECIAL_EMPEROR,
    SPECIAL_ACE,
    SPECIAL_MAX
};

class Card
{
    protected:
        Suit m_suit;
        Rank m_rank;
        int m_value = 0;
        bool m_isFaceUp;
        Special m_special;
    public:
        Card(Suit suit, Rank rank, bool isFaceUp);  // Add this constructor
        void Flip();
        void setValue(int value);  
        virtual int getValue() const;  // Mark GetValue as virtual
        Rank getRank() const;
        Suit getSuit() const;
        virtual void setSpecial(Special special);
        virtual Special getSpecial() const;
        friend std::ostream& operator<<(std::ostream& out, const Card& card);
        virtual ~Card() = default;
};

#endif // CARD_HPP
