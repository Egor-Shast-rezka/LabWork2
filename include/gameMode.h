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
private:
    ContactWithPlayer contact;
    
public:

    void setAllBots(Game& game, int complexity, std::string value);
    void setupForAllBots(Game& game);
};


// -------------------------
class OneOnOne : public Game {
public:

    void setupForAllPlayers(Game& game);
};


#endif
