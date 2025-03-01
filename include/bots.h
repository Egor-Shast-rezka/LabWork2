/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <random>
#include <cstring>
#include <cmath>


#ifndef BOTS_H
#define BOTS_H

// -------------
class AIPlayer_easy : public Player {
private:
    std::string Name; // Name for bot
    int Chips; // Count money (chips, deb)
    Hand hand; // Player's hand

public:
    AIPlayer_easy(std::string name);

    bool isBot() override;

    int chipRandom(int countChips, int Allin);
    
    int BotActions(int countChips, int currentBet, int Bank, int Allin) override;
};


// -------------
class AIPlayer_normal : public Player {
public:
    AIPlayer_normal(std::string name);

    bool isBot() override;
    
    // None
};


// -------------
class AIPlayer_hard : public Player {
public:
    AIPlayer_hard(std::string name);
    
    bool isBot() override;
    
    // None
};

#endif
