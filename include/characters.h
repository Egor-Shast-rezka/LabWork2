/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>
#include <cmath>


#ifndef CHARACTERS_H
#define CHARACTERS_H


// -------------------------
class AllSeeingPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    AllSeeingPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


// -------------------------
class CheaterPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    CheaterPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


// -------------------------
class EngagedDeckPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    EngagedDeckPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


// -------------------------
class DeallersFrendPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    DeallersFrendPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


// -------------------------
class PhotographicMemoryPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    PhotographicMemoryPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


// -------------------------
class BettingManipulatorPlayer : public Player {
private:
    ContactWithPlayer contact;
    
public:
    
    BettingManipulatorPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) override;
};


#endif
