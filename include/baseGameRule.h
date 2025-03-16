/*
    Egor Shastin st129457@student.spbu.ru
    
    This code defines a set of classes that manage the mechanics of a card game, focusing on players, cards, bets, and the dealer.

    > ContactWithPlayer: Utility class to handle various input validation, such as checking if a string is an integer or string.
    > Card: Represents a single playing card, including its number and suit. It provides methods to display the card and manipulate its attributes.
    > Deck: Represents the deck of cards, allowing actions like shuffling, dealing cards, and adding/removing cards from the deck.
    > Hand: Represents the player's hand, storing cards and offering methods to manage the hand, such as adding, removing, and displaying cards.
    > Bank: Handles the current bet and the chips placed by each player during the game. It also provides methods to manipulate and access bet-related data.
    > Player: Represents a player, including their name, chips, and hand of cards. It provides various methods for setting and displaying the player's attributes, placing bets, and interacting with the game. It also has virtual methods to handle bot or character-specific actions.
    > Dealler: Represents the dealer, managing the deck and dealing cards to players. It also includes methods for shuffling the deck, creating a new deck, and determining the winner based on hand power.
    
Each class is structured to manage specific parts of the game, from player interactions to the handling of game resources like cards and bets.

*/


#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>
#include <memory>


#ifndef BASEGAMERULE_H
#define BASEGAMERULE_H


// ===========ContactWithPlayer=============

class ContactWithPlayer {
public:
    bool isNumber(std::string answer); // Check is number or no
    
    int stringToInt(const std::string& str); // Convert string to integer
    
    int answerUserCheckInt(std::string value); // Check is integer or no
    
    std::string answerUserCheckString(std::string value); // Check is string or no
};

// ===========Card=============

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
    
    bool operator<(const Card& other) const;
};


// ===========Deck=============

class Deck {
private:
    std::vector<Card> cards; // All cards in deck ( 52 cards )
    
public:

    Deck(); // Generate all cards
    ~Deck();

    void shuffle(); // Shuffle cards in deck

    Card deal(); // Take one card from deck
    
    Card seeLastCard() const; // See last card for Engaged deck
    
    void putOneCardInDeck(Card card); // Put one card in deck for CheaterPlayer
    
    std::vector<Card>& getAllCards();
    
    int getCountCards();
    
};


// ===========Hand=============

class Hand {
private:
    std::vector<Card> cards; // All cards in hand ( 2 cards )
    
public:

    Hand();
    ~Hand();
    
    void setCards(Card card);  // Add Card in hand
    
    int getCountCards() const;  // Show count card in hand

    std::vector<Card>& getAllCards();  // Show all card in hand

    void getCardsOnDisplay() const;  // Show all card in hand on display

    void delLastCard(); // Remove last card
};


// ===========Bank=============

class Bank {
private:
    int CurrentBet; // Current rate
    std::vector<int> CountBetEachPlayer; // The number of chips each player placed during the round
    
public:

    Bank();
    ~Bank();
    
    // Set for Bank
    void setCurrentBet(int value); // Set current bet
    
    void setCountBetEachPlayer(int value); // Set for CountBetEachPlayer
    
    // Get for Bank
    int getCurrentBet() const; // Get current bet
    
    int getPlayerMoney() const; // Get summ for CountBetEachPlayer
    
    int getCountBetEachPlayer(int index) const; // Get for CountBetEachPlayer
    
    // Add for Bank
    void addCurrentBet(int value); // Add current bet
    
    void addCountBetEachPlayer(int value, int index); // Add for CountBetEachPlayer
    
};


// ===========Player=============
// Forward declaration of Dealler class
class Dealler;

class Player {
private:
    std::string Name; // Name for player
    int Chips; // Count money (chips, deb)
    Hand hand; // Player's hand

public:

    Player(std::string name);
    ~Player();

    void setName(std::string name);  // Set Name

    void getNameOnDisplay() const; // Write Name on display

    std::string getName() const; // Get Name

    void setChips(int num);  // Set deb

    void getChipsOnDisplay() const; // Write Chips on display

    int getChips() const; // Get Chips

    void PlaceBid(int num);  // Make a bed

    void setCard(Card elem);  // Set Card

    std::vector<Card>& getAllCards(); // Get all cards

    void getCardsOnDisplay() const;  // Get cards in hand on display

    int getCountCards() const;  // Get count card in head

    void delAllCards();  // Delete all cards after end play
    
    virtual bool isBot(); // Check is Bot or no

    virtual std::vector<int> BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot); // Ation bots: choose raise, call, allin, pass // Action if Player it is Bot
    
    virtual bool isCharacter(); // Check is Character or no
    
    virtual void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer); // Action if Player it is Character
    
};


// ===========Dealler=============

class Dealler {
private:
    Deck deck; // Dealer's deck
    
public:

    Dealler();
    ~Dealler();

    void shuffleDeck();  // Shuffer deck

    void dealCards(int num, Player& player);  // Issuing 'num' cards to a player

    Card getOneCard();  // Drawing a card from the deck
    
    void newDeck(); // Create new deck after reload game
    
    void putOneCardInDeck(Card card); // Put one card in deck for CheaterPlayer
    
    Deck& getDeck(); // Get deck
    
    std::vector<std::vector<int>> search_max_number(std::vector<std::vector<int>>& vectors, int index, std::vector<bool>& DataPass); // Search max number for Search Winner
    
    std::vector<int> PowerHand(std::vector<Card> allCardsPlayer); // Search power hand for Search Winner and normal bot

    std::vector<int> SearchWinner(std::vector<Player>& players, std::vector<Card>& cards, std::vector<bool>& DataPass);  // Search for a winner
};


#endif
