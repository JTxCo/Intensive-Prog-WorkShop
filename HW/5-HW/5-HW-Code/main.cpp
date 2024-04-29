
//Main file for my Blackjack game
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "Player.hpp"
#include "Card.hpp"
#include "Joker.hpp"
#include "Emperor.hpp"
#include "Dealer.hpp"
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*
    
Deliverable 1 
•	Create players
•	Create cards
•	X number players
•	Create CLI interface for asking basic questions
o	Will be able to ADD players by name up to chosen number
o	Will Deal cards telling people what they got 
o	No betting at this point
•	Will operate as a traditional Blackjack table	



*/
std::vector<Player*> addPlayers() {
    std::vector<Player*> players;
    int playerCount = 0;
    std::string playerName;
    while(playerCount < 8){
        std::cout << "Enter player name: ";
        getline(std::cin, playerName);

        // If the player enters "done" or inputs ENTER then stop asking for names
        if(playerName == "done" || playerName == ""){
            break;
        }
        // Create a new Player and add them to the players vector
        Player* newPlayer = new Player(playerName); // Note the usage of 'new' here.
        players.push_back(newPlayer);
        playerCount++;
    }
    // Optional: show how many players were created
    std::cout << "Total players: " << playerCount << std::endl;

    return players;
}

vector<Card*> createDeck() {
    vector<Card*> deck;
    for (int suit = 0; suit < static_cast<int>(Suit::MAX_SUITS); ++suit) {
        for (int rank = 0; rank < static_cast<int>(Rank::MAX_RANKS); ++rank) {
            
            deck.push_back(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank), true));
        }
    }
    cout<<"Deck created"<<endl;
    return deck;
}
void AddSpecialCards(std::vector<Card*> *deck, int player_count) {
    // Add Joker cards
    // Add Emperor cards    

    for (int i = 1; i < player_count*4; i++) {
        // Create and add Joker cards
        // Initialize the joker card with a value of 0 since the player will set the value
        deck->push_back(new Joker());
        cout<<"Joker added"<<endl;
    }

    // Create and add Emperor cards
    for(int i = 1; i < player_count*4; i++) {
        // Initialize the emperor card with a value of 0 since the player will set the value
        deck->push_back(new Emperor());
        cout<<"Emperor added"<<endl;
    }
}


Card jokerCard(Joker * joker){
    /*
    (Joker Class): There will be X for number of player joker cards: 
        these allow the player to set the value they want the card to be up 11
        as that is the equivalent of an ace
    */
    int value;
    cout<<"\n The Joker card is drawn. The max value is 11, minimum is 1"<<endl;
    cout<<"If an invalid value is entered, the value will be set to 1"<<endl;
    cout<<"what value do you want to set it to: ";
    cin>>value;
    if(value > 11 || value < 1){
        value = 1;
    }
    joker->SetValue(value);
    return *joker;
}


Card emperorCard(Emperor * emperor, Dealer* dealer){
    /*
    o	(Emperor Class) X num players / 2 cards, minimum 2; Emporer Card: 
        may choose one of the dealers cards or draw a new card. 
    */
    int choice;
    cout<<"Enter # to choose: "<<endl;
    cout<<"1. Choose one of the dealer's cards"<<endl;
    cout<<"2. Draw a new card"<<endl;
    cout<<"3. what does the Emperor do?"<<endl;
    cout<<"Enter choice: ";
    cin>>choice;

    if(choice == 1){
        // Choose one of the dealer's cards
        cout<<"Dealer's hand: ";
        dealer->printHand();
        cout<<"Enter the index of the card you want to choose: ";
        int index;
        cin>>index;
        return dealer->getCard(index);
    } else if(choice == 2){
        // Draw a new card
        return *emperor;
    } else if(choice == 3){
        cout<<"The Emperor can choose one of the dealer's cards or draw a new card"<<endl;
        return emperorCard(emperor, dealer);
    } else {
        cout<<"Invalid choice"<<endl;
        return *emperor;
    }
}

Card aceCard(Card ace, int value){
    /*
    o	(Ace Class) Ace Card: may be used as 1 or 11
    */
    cout<<"The Ace card is drawn. The max value is 11, minimum is 1"<<endl;
    cout<<"If an invalid value is entered, the value will be set to 1"<<endl;
    cout<<"what value do you want to set it to: ";
    cin>>value;
    if(value > 11 || value < 1){
        value = 1;
    }
    ace.setValue(value);
    return ace;
}

//need to do ace card

void shuffleDeck(vector<Card*> &deck) {
    // Obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Shuffle the deck
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

    cout << "Deck shuffled" << endl;
}

void dealCards(vector<Card*> &deck, vector<Player*> &players) {
    // Deal 2 cards to each player
    for (int i = 0; i < 2; i++) {
        for (auto player : players) {
            player->addCard(deck.back());
            deck.pop_back();
        }
    }

    // Deal 2 cards to the dealer
    players.push_back(new Player("Dealer"));
    for (int i = 0; i < 2; i++) {
        players.back()->addCard(deck.back());
        deck.pop_back();
    }

    cout << "Cards dealt" << endl;
}


void playerTurn(vector<Card*> &deck, vector<Player*> &players) {
    // Player's turn
    for (auto player : players) {
        if (player->getName() == "Dealer") {
            continue;
        }

        cout << player->getName() << "'s turn" << endl;
        cout << "Your hand: ";
        player->printHand();

        // Looking in cards to see if there are any special cards, there are, then do the special card action
        for (auto card : player->getHand()) {
            if (card->getSpecial() == Special::SPECIAL_JOKER) {
                cout<<"You have a joker card"<<endl;
                jokerCard(static_cast<Joker*>(card));
            } else if (card->getSpecial() == Special::SPECIAL_EMPEROR) {
                cout<<"You have an emperor card"<<endl;
                emperorCard(static_cast<Emperor*>(card), static_cast<Dealer*>(players.back()));
            }
            else if(card->getSpecial() == Special::SPECIAL_ACE){
                cout<<"You have an Ace card"<<endl;
                aceCard(*card, 1);
            }
        }
        cout << "Your hand value: " << player->GetHandValue() << endl;

        // Ask the player if they want to hit or stand
        char choice;
        do {
            cout << "Do you want to hit or stand? (h/s): ";
            cin >> choice;
            if (choice == 'h') {
                Card* card = deck.back();
                deck.pop_back();
                player->addCard(card);



                cout << "Your hand: ";
                player->printHand();
                cout << "Your hand value: " << player->GetHandValue() << endl;
            }
            if(player->IsBusted()){
                cout<<"Player is busted"<<endl;
                break;
            }
        } while (choice == 'h' && !player->IsBusted());
    }
}

void dealerTurn(Player* dealer, vector<Card*> &deck) {
    // Dealer's turn
    cout << "Dealer's turn" << endl;
    cout << "Dealer's hand: ";
    dealer->printHand(); 
    cout << "Dealer's hand value: " << dealer->GetHandValue() << endl;

    while (dealer->GetHandValue() < 17) {
        dealer->addCard(deck.back());
        deck.pop_back();
        cout << "Dealer's hand: ";
        dealer->printHand();
        cout << "Dealer's hand value: " << dealer->GetHandValue() << endl;
        if(dealer->IsBusted()){
            cout<<"Dealer is busted"<<endl;
            break;
        }
    }
}

void PrintResults( vector<Player*> &players) {
    // Print the results
    cout <<"Round is over"<<endl;
    cout << "Results: " << endl;
    // Outputting each player's hand and hand value
    for (auto player : players) {
        if (player->getName() == "Dealer") {
            continue;
        }

        cout << player->getName() << "'s hand: ";
        player->printHand();
        cout << player->getName() << "'s hand value: " << player->GetHandValue() << endl;
    }

    // Outputting the dealer's hand and hand value
    cout << "Dealer's hand: ";
    players.back()->printHand();
    cout << "Dealer's hand value: " << players.back()->GetHandValue() << endl;

    // Outputting the winner
    // iterate through the players,, if they are busted go to next
    // who ever is closest to 21 wins, without going over
    // If dealer is busted all who are not busted win
    // If dealer is not busted, all who are not busted and have a higher value than the dealer win
    int dealerHandValue = players.back()->GetHandValue();

    for (auto player : players) {
        if (player->getName() == "Dealer") {
            continue;
        }
        if (player->IsBusted()) {
            cout << player->getName() << " is busted" << endl;
        } else if (players.back()->IsBusted() || player->GetHandValue() > dealerHandValue) {
            cout << player->getName() << " wins!" << endl;
        } else if (player->GetHandValue() == dealerHandValue) {
            cout << player->getName() << " ties with the dealer" << endl;
        } else {
            cout << player->getName() << " loses" << endl;
        }
    }
}


//Playing the game with the deck and Playuers
//input of the deck and players
void PlayBlackjack( vector<Player*> &players) {
    // clear the cards of each player for a new game
    for (auto player : players) {
        player->ClearHand();
    }
    //Task 1: Create a deck of cards
    std::vector<Card*> deck = createDeck();
    //Adding the dealer
    //Task 3: Add special cards to the deck
    AddSpecialCards(&deck, players.size());

    shuffleDeck(deck);
    // Deal the cards
    dealCards(deck, players);

    // Player's turn
    playerTurn(deck, players);
    // Dealer's turn
    dealerTurn(players.back(), deck);

    // Print the results
    PrintResults(players);

}
int main()
{
    //Task 2: Add players to the game
    vector<Player*> players_ = addPlayers();

    players_.push_back(new Dealer("Dealer"));

    char choice = 'y';
    while(choice == 'y'){
        PlayBlackjack(players_);
        cout<<"Do you want to play again? (y/n): ";
        cin>>choice;
    }

    for (auto player : players_) {
        delete player;
    }
    return 0;
}




