/*
    Egor Shastin st129457@student.spbu.ru
    
    This code defines two specific game modes for a card game: AllBots and OneOnOne.

    > AllBots: A game mode where all players are bots, with one human player. The class manages the setup of bots, either easy or normal difficulty, and handles the game flow and display of player information.
    > OneOnOne: A game mode for a match between two players (one human and one bot). This class manages the game mode setup, displays player information, and controls the game progress.

    Both classes inherit from the GameMode base class and implement the required methods for setting up the game, showing player information, and progressing through the game.
    
*/


#include <iostream>
#include <vector>
#include <cstring>


#ifndef GAMEMODE_H
#define GAMEMODE_H


// ===========AllBots=============

class AllBots : public GameMode {
public:
    ContactWithPlayer contact;
    Game& game;
    
public:
    
    AllBots(Game& game); // Create mode with all bots and 1 player
    ~AllBots();
    
    void setAllBots(int complexity, std::string value); // Set all bots: easy or normal
    
    void setupForGameMode() override; // Set game mode
    
    void OutputInfoPlayers() override; // Display information about players
    
    void GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund) override; // Game progress with selected mode
};


// ===========OneOnOne=============
class OneOnOne : public GameMode {
public:
    ContactWithPlayer contact;
    Game& game;
    
public:

    OneOnOne(Game& game); // Create mode with some player
    ~OneOnOne();
    
    void setupForGameMode() override; // Set game mode
    
    void OutputInfoPlayers() override; // Display information about players
    
    void GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund) override; // Game progress with selected mode
};


#endif
