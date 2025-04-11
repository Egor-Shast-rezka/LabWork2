/*
    Egor Shastin st129457@student.spbu.ru
    
    The code defines two classes for bots: AIPlayer_easy and AIPlayer_normal. 
    AIPlayer_easy chooses actions randomly, while AIPlayer_normal makes decisions based on the probability of winning, calculated from the strength of the hand.
*/

#include <iostream>
#include <vector>
#include <random>
#include <cstring>
#include <cmath>


#ifndef BOTS_H
#define BOTS_H


// ===========AIPlayer_easy=============

class AIPlayer_easy : public Player {
public:
    AIPlayer_easy(std::string name); // Create bot easy

    bool isBot() override; // Does a timer exist
    
    std::vector<int> BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot) override; // Ation bots: choose raise, call, allin, pass
};


// ===========AIPlayer_normal=============

class AIPlayer_normal : public Player {
public:
    AIPlayer_normal(std::string name); // Create bot normal

    bool isBot() override;// Does a timer exist
    
    void findOutsRecursive(const std::vector<Card>& hand, const std::vector<Card>& remainingCards, Dealler& dealler, int handStrength, int maxDepth, int& outs, int currentDepth, int startIndex);
    
    int calculateOuts(std::vector<Card>& hand, std::vector<Card>& cardsOnTable, Dealler& dealler); // Calculates the number of outs
    
    float calculateWinningProbability(std::vector<Card> hand, std::vector<Card> cardsOnTable, Dealler& dealler); // Calculate winning probability
    
    std::vector<int> BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot) override; // Ation bots: choose raise, call, allin, pass
};


#endif
