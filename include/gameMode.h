/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include <iostream>
#include <vector>
#include <cstring>


#ifndef GAMEMODE_H
#define GAMEMODE_H


// -------------------------
class AllBots : public GameMode {
public:
    ContactWithPlayer contact;
    Game& game;
    
public:
    
    AllBots(Game& game);
    ~AllBots();
    
    void setAllBots(int complexity, std::string value);
    
    void setupForGameMode() override;
    
    void GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, bool& repeatBettingForBot, bool& repeatBetting, int& raund) override;
};


// -------------------------
class OneOnOne : public GameMode {
public:
    ContactWithPlayer contact;
    Game& game;
    
public:

    OneOnOne(Game& game);
    ~OneOnOne();
    
    void setupForGameMode() override;
    
    void GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, bool& repeatBettingForBot, bool& repeatBetting, int& raund) override;
};


#endif
