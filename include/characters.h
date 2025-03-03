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
public:
    
    AllSeeingPlayer(std::string name);
    
    bool isCharacter() override;
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler) override;
};

/*
// -------------------------
class CheaterPlayer : public Player {
public:
    
    CheaterPlayer(std::string name);
    
    bool isCharacter() override;
    
    Card CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler, int player, int card);
};
*/

#endif
