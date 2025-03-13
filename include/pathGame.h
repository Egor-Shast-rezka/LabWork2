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

#include <cstdlib>
#include <fstream>

#ifndef PATHGAME_H
#define PATHGAME_H


// -------------------------
class GameMode {
public:

    virtual void setupForGameMode();
    
    virtual void OutputInfoPlayers();
    
    virtual void GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund);
};


// -------------------
class Timer {
private:

    bool exist;
    int seconds;
    
public:
    
    void SetExist(bool ex);
    
    void setSecondForTimer(int second);
    
    bool IsExist();
    
    void TimerStart();
    
};


// -------------------
class Game {
private:
    std::vector<std::unique_ptr<Player>> players; // List of players
    std::vector<Card> cards; // List of cards on the table
    Dealler dealler; // Dealer at the table
    
    ContactWithPlayer contact; // Add obj for contact with player
    Bank bank;
    Timer timer;
    std::vector<std::unique_ptr<GameMode>> gamemode;
    
    bool Character; // Exist character
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
    
    std::vector<Card>& getAllCardsForTable(); // Returns all cards on the table
    
    Bank& getBank();
    
    bool getCharacter();

    // Game path
    void resetGame(); // Reset game in case player wants to continue playing
    
    bool checkContinueGame(); // Checking if the player wants to continue playing
    
    void setMode(); // Set mode, character, count chips ...
    
    std::string getValidAction(std::vector<std::string> actions, std::string prompt, std::vector<bool> ifActPlayerData, int index);
    
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


#endif
