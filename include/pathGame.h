/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

// For timer
#include <chrono>
#include <thread>

#ifndef PATHGAME_H
#define PATHGAME_H


// -------------------
class Game {
protected:
    std::vector<std::unique_ptr<Player>> players; // List of players
    std::vector<Card> cards; // List of cards on the table
    Dealler dealler; // Dealer at the table
    
    ContactWithPlayer contact; // Add obj for contact with player
    
    int Character; // 1 or 0 - exist character
    int currentBet; // Current rate
    int Bank; //Initial bet
    int CountGame; // Count game
    
public:

    Game();
    ~Game();
    
    // Set all data for Game
    void setPlayer(std::string name);  // Creating players
    
    void setBot(std::string name, int index); // Creating bots
    
    void setPlayerCharacter(std::string name, int index); // Creating character
    
    void setDealler();  // Creating a dealer
    
    void setChipsAllPlayer(int count); // Set chips for all player
    
    // Get all data for Game
    std::vector<std::unique_ptr<Player>>& getPlayer(); // Returns all cards to players
    
    Dealler getDealler(); // Get all dealer data
    
    int getCharacter(); // Add Character varriable
    
    std::vector<Card>& getAllCardsForTable(); // Returns all cards on the table
    
    // Game path
    void resetGame(); // Reset game in case player wants to continue playing
    
    bool checkContinueGame(); // Checking if the player wants to continue playing
    
    void setMode(); // Set mode, character, count chips ...
    
    int startGame(); // Start all game
};


// -------------------
class Rule {
public:
    
    // Check if player wants reset Rule
    bool resetGetRule(ContactWithPlayer& contact);
    
    // Get Rule on Display
    void getRuleOnDisplay(ContactWithPlayer& contact);
    
};


// -------------------
class Timer : public Game {
public:
    
    // Set Timer
    bool setTimerForGame(int seconds);
};


// -------------------
class Settings : public Game {
public:
    
    void setGameSettings();
    
};


#endif
