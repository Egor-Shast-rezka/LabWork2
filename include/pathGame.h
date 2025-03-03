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
    
    int Character;
    int currentBet; // Current rate
    int Bank;
    int CountGame;
    
public:

    Game();
    ~Game();
    
    bool isNumber(std::string answer);
    
    int stringToInt(const std::string& str);
    
    int answerUserCheckInt(std::string value);
    
    std::string answerUserCheckString(std::string value);
    
    void setPlayer(std::string name);  // Creating players. 
    
    std::vector<std::unique_ptr<Player>>& getPlayer();
    
    void setBot(std::string name, int index);
    
    void setPlayerCharacter(std::string name, int index);
    
    void setDealler();  // Creating a dealer.
    
    Dealler getDealler();
    
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

    bool resetGetRule(Game& game);
    
    void getRuleOnDisplay(Game& game);
    
};


#endif
