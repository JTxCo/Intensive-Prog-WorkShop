// Emperor.cpp
#include "Emperor.hpp"

Emperor::Emperor() : Card(Suit::MAX_SUITS, Rank::MAX_RANKS, true)  {
    m_value =0;
}

int Emperor::getValue() const{
    return m_value;
}

void Emperor::setValue(int value){
    m_value = value;
}

std::ostream& operator<<(std::ostream& out, const Emperor& emperor) {
    out << "Emperor card with value " << emperor.getValue();
    return out;
}

Special Emperor::getSpecial() const {
    return m_special;
}

// Fill in operator<< function.
