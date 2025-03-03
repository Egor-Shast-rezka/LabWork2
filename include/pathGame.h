/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

#ifndef PATHGAME_H
#define PATHGAME_H


// -------------------
class Game {
protected:
    std::vector<std::unique_ptr<Player>> players; // List of players
    std::vector<Card> cards; // List of cards on the table
    Dealler dealler; // Dealer at the table
    
    ContactWithPlayer contact;
    
    int Character;
    int currentBet; // Current rate
    int Bank;
    int CountGame;
    
public:

    Game();
    ~Game();
    
    void setPlayer(std::string name);  // Creating players. 
    
    std::vector<std::unique_ptr<Player>>& getPlayer();
    
    void setBot(std::string name, int index);
    
    void setPlayerCharacter(std::string name, int index);
    
    void setDealler();  // Creating a dealer.
    
    Dealler getDealler();
    
    int getCharacter();
    
    Card seeLastCardInDeallerDeck() const; // See last card for Engaged deck
    
    void putOneCardInDeckInDeallerHand(Card card); // Put one card in deck for CheaterPlayer
    
    std::vector<Card> getAllCardsForTable();
    
    void resetGame();
    
    bool checkContinueGame();
    
    void setMode();
    
    void setChipsAllPlayer(int count);
    
    int startGame();
};


// -------------------
class Rule {
public:

    bool resetGetRule(ContactWithPlayer& contact);
    
    void getRuleOnDisplay(ContactWithPlayer& contact);
    
};


// -------------------
class Timer : public Game {
public:
    
    void setTimerForGame();
};


// -------------------
class Settings : public Game {
public:
    
    void setGameSettings();
    
};


#endif
