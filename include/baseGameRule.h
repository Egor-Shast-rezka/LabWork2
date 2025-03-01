/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>

#ifndef BASEGAMERULE_H
#define BASEGAMERULE_H

// ----------------------
class Card {
private:
    int number; // Number card (11 - Valet, 12 - Dama, 13 - Korol, 14 - Tus)
    int suit; // Card suit
    
public:

    Card(int num, int val);
    ~Card();

    void setNumber(int num); // Set number

    int getNumber() const; // Get number

    void setSuit (int value); // Set suit

    int getSuit() const; // Get Suit

    void display() const; // Show Card on screen
};


// --------------------------
class Deck {
protected:
    std::vector<Card> cards; // All cards in deck ( 52 cards )
    
public:

    Deck(); // Generate all cards
    ~Deck();

    void shuffle(); // Shuffle cards in deck

    Card deal(); // Take one card from deck
};


// --------------------------
class Hand {
private:
    std::vector<Card> cards; // All cards in hand ( 2 cards )
    
public:

    Hand();
    ~Hand();

    void setCards(Card card);  // Add Card in hand

    int getCountCards() const;  // Show count card in hand

    std::vector<Card> getAllCards() const;  // Show all card in hand

    void getCardsOnDisplay() const;  // Show all card in hand on display

    void delLastCard(); // Remove last card
};


// ----------------------
class Player {
private:
    std::string Name; // Name for player
    int Chips; // Count money (chips, deb)
    Hand hand; // Player's hand

public:

    Player(std::string name);
    ~Player();

    void setName(std::string name);  // Set Name

    void getName() const;  // Get Name

    void setChips(int num);  // Set deb

    void getChipsOnDisplay() const;

    int getChips() const;

    void PlaceBid(int num);  // Make a bed

    void setCard(Card elem);  // Set Card

    std::vector<Card> getAllCards() const;

    void getCardsOnDisplay() const;  // Get cards in hand on display

    int getCountCards() const;  // Get count card in head

    void delAllCards();  // Delete all cards after end play
    
    virtual bool isBot();

    virtual int BotActions(int countChips, int currentBet, int Bank, int Allin);
};


// --------------------
std::vector<std::vector<int>> search_max_number(std::vector<std::vector<int>>& vectors, int index);


// ---------------------
class Dealler {
private:
    Deck deck; // Dealer's deck
    
public:

    Dealler();
    ~Dealler();

    void shuffleDeck();  // Shuffer deck

    void dealCards(int num, Player& player);  // Issuing 'num' cards to a player

    Card getOneCard();  // Drawing a card from the deck
    
    void newDeck();

    std::vector<int> SearchWinner(std::vector<Player>& players, std::vector<Card>& cards, std::vector<int>& DataPass) const;  // Search for a winner
};

#endif




