#ifndef _SUIT_H_ // this is the header guard
#define _SUIT_H_

// Create an enum class, Suit to represent the suit in a deck of cards
enum class Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};



// Create a struct, Card, to represent a card in a deck of cards.  You must
// use your Suit enum.  You may use any other values that you choose.

struct Card {
    int value;
    Suit suit;

    bool operator==(const Card &other) const {
        return (value == other.value) && (suit == other.suit);
    }
};



// Override operator== in your Card struct.

// Design a class, Deck.  Write down the fields and methods that this class should have.  
// Don’t implement them!

//the Deck class would need a vector of cards, a shuffle method, a deal method, and a constructor
//the constructor would initialize the vector of cards with all 52 cards in a deck
//the constructor would also be of time cards
//the shuffle method would shuffle the vector of cards
//the deal method would deal a card from the top of the deck
//the deal method would also remove the card from the deck


#endif // _SUIT_H_
