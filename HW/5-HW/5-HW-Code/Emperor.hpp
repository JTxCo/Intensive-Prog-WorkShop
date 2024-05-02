// Emperor.hpp
#ifndef EMPEROR_HPP
#define EMPEROR_HPP

#include "Card.hpp"

// Emporer Card: may choose one of the dealers cards or draw a new card. 

class Emperor : public Card {
public:
    Emperor();
    int getValue() const override;
    Special getSpecial() const override;
    friend std::ostream& operator<<(std::ostream& out, const Emperor& emperor);
};

#endif // EMPEROR_HPP