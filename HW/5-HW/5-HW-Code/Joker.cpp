#ifndef JOKER_CPP
#define JOKER_CPP
#include "Joker.hpp"

Joker::Joker()
    : Card(Suit::MAX_SUITS, Rank::MAX_RANKS, true)
{
    m_special = Special::SPECIAL_JOKER;  
    m_value =0;    
}


Special Joker::getSpecial() const 
{
    return m_special;
}

#endif /* JOKER_CPP */