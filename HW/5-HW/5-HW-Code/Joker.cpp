#ifndef JOKER_CPP
#define JOKER_CPP
#include "Joker.hpp"

Joker::Joker()
    : Card(Suit::MAX_SUITS, Rank::MAX_RANKS, true)
{
    m_value =0;    
}

void Joker::SetValue(int value)
{
    m_value = value;
}
Special Joker::getSpecial() const 
{
    return m_special;
}

#endif /* JOKER_CPP */