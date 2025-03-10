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
public:
    AIPlayer_easy(std::string name);

    bool isBot() override;
    
    std::vector<int> BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Deck& deck, int currentBet, bool Allin, bool ifReboot) override;
};


// -------------
class AIPlayer_normal : public Player {
public:
    AIPlayer_normal(std::string name);

    bool isBot() override;
    
};


#endif
