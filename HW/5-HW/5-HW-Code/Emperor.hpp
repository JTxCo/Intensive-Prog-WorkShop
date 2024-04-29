// Emperor.hpp
#ifndef EMPEROR_HPP
#define EMPEROR_HPP

#include "Card.hpp"

// Emporer Card: may choose one of the dealers cards or draw a new card. 

class Emperor : public Card {
private:
    Special m_special = Special::SPECIAL_EMPEROR;
    int m_value;
public:
    Emperor();
    int getValue() const override;
    void setValue(int value);
    Special getSpecial() const override;
    friend std::ostream& operator<<(std::ostream& out, const Emperor& emperor);
};

#endif // EMPEROR_HPP