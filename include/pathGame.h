/*
    Egor Shastin st129457@student.spbu.ru
   
   This code defines a set of classes that manage different aspects of a card game, including game modes, timing, game flow, rules, and player interactions.

    > GameMode: An abstract class that outlines methods for setting up a game mode, displaying player information, and controlling the flow of the game based on the selected mode.
Timer: A class that manages a timer for the game. It allows for creating a timer, setting its duration, and starting it, with functionality to check if the timer exists.
    > Game: The main game class that holds all game-related data, including players, cards, the dealer, bank, timer, and game modes. It manages game setup (creating players, bots, and characters), game flow (checking if players want to continue, resetting the game), and player actions (choosing actions like raising, calling, or going all-in).
    > Rule: A class that handles the game rules. It allows the player to view and reset the rules and displays them when needed.

    These classes work together to create and manage the game, control its flow, and provide players with actions and options during the game.
    
*/


#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <map>

// For timer
#include <chrono>
#include <thread>
#include <cstdlib>
#include <atomic>

#ifndef PATHGAME_H
#define PATHGAME_H


// ===========Timer=============
class Game;
class Timer {
private:
    Game& game;
    bool exist; // Does a timer exist
    int seconds; // Time for timer
    
public:
    
    Timer(Game& game);
    
    void SetExist(bool ex); // Create a timer
    
    void setSecondForTimer(int second); // Set time for timer
    
    bool IsExist(); // Does a timer exist
    
    void TimerStart(); // Start a timer
    
};


// ===========Game=============

class GameMode;
class InfiniteMelodyPlayer;
class AudioEngine;
class RandomMelodyGenerator;

class Game {
private:
    std::vector<std::unique_ptr<Player>> players; // List of players
    std::vector<Card> cards; // List of cards on the table
    Dealler dealler; // Dealer at the table
    
    ContactWithPlayer contact; // Add obj for contact with player
    Bank bank; // Bank with players money and current game for game
    std::unique_ptr<Timer> timer; // Timer with player
    std::vector<std::unique_ptr<GameMode>> gamemode;

    std::unique_ptr<InfiniteMelodyPlayer> melody; // Music for game
    std::unique_ptr<AudioEngine> engine; // Engine for music
    std::unique_ptr<RandomMelodyGenerator> melodyGenerator; // Generator for music
    std::thread musicThread;
    
    bool Character; // Exist character
    int CountGame; // Count game
    
public:

    Game();
    ~Game();
    
    std::atomic<bool> timeIsUp{false};
    
    // Set all data for Game
    void setPlayer(std::string name);  // Creating players
    
    void setBot(std::string name, int index); // Creating bots
    
    void setPlayerCharacter(std::string name, int index); // Creating character
    
    void setDealler();  // Creating a dealer
    
    void setChipsAllPlayer(int count); // Set chips for all player
    
    // Get all data for Game
    std::vector<std::unique_ptr<Player>>& getPlayer(); // Returns all cards to players
    
    Dealler& getDealler(); // Get all dealer data
    
    std::vector<Card>& getAllCardsForTable(); // Returns all cards on the table
    
    Bank& getBank(); // Get Bank
    
    bool getCharacter(); // Does a character exist

    // Game path
    void resetGame(); // Reset game in case player wants to continue playing
    
    bool checkContinueGame(); // Checking if the player wants to continue playing
    
    void setMode(); // Set mode, character, count chips ...
    
    std::string getValidAction(std::vector<std::string> actions, std::string prompt, std::vector<bool> ifActPlayerData, int index); // Player choose: act, pass, raise, call, allin
    
    int startGame(); // Start all game
    
};


// ===========Rule=============

class Rule {
public:
    
    // Check if player wants reset Rule
    bool resetGetRule(ContactWithPlayer& contact);
    
    // Get Rule on Display
    void getRuleOnDisplay(ContactWithPlayer& contact);
    
};


#endif
