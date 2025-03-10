/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <cstring>

#ifndef GAMEMODE_H
#define GAMEMODE_H


// -------------------------
class AllBots : public Game {
public:
    ContactWithPlayer contact;
    
public:
    
    AllBots();
    ~AllBots();
    
    void setAllBots(Game& game, int complexity, std::string value);
    void setupForGameMode(Game& game) override;
};


// -------------------------
class OneOnOne : public Game {
public:
    ContactWithPlayer contact;
    
public:

    OneOnOne();
    ~OneOnOne();
    
    void setupForGameMode(Game& game) override;
};


#endif
