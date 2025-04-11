/*
    Egor Shastin st129457@student.spbu.ru
    
    This code defines a series of character classes that inherit from the Player class. Each character has its own unique abilities and behaviors related to the game, overriding certain methods to introduce special actions.

    > AllSeeingPlayer: This player can inspect the cards of other players.
    > CheaterPlayer: Allows a player to replace one of their cards with a new one from the deck.
    > EngagedDeckPlayer: This player can see the last card in the deck.
    > DeallersFrendPlayer: Allows a player to manipulate the cards on the table by replacing the last card with a new one from the deck.
    > PhotographicMemoryPlayer: This player can remember and display the remaining cards in the deck.
    > BettingManipulatorPlayer: Allows a player to steal chips from another player.

    Each of these character classes overrides the isCharacter() method to confirm it is a character and the CharacterActions() method to define their unique actions during the game.
    
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>
#include <cmath>


#ifndef CHARACTERS_H
#define CHARACTERS_H


// ===========AllSeeingPlayer=============

class AllSeeingPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    AllSeeingPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


// ===========CheaterPlayer=============

class CheaterPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    CheaterPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


// ===========EngagedDeckPlayer=============

class EngagedDeckPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    EngagedDeckPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


// ===========DeallersFrendPlayer=============

class DeallersFrendPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    DeallersFrendPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


// ===========PhotographicMemoryPlayer=============

class PhotographicMemoryPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    PhotographicMemoryPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    bool searchCardInDeck(Card& InFullDeck, std::vector<Card>& deck); // Search some card among the remaining cards in deck
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


// ===========BettingManipulatorPlayer=============

class BettingManipulatorPlayer : public Player {
private:
    ContactWithPlayer contact; // Connection connection with character
    
public:
    
    BettingManipulatorPlayer(std::string name); // Create Characters
    
    bool isCharacter() override; // Check it is characters or not
    
    void CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) override; // Character Actions
};


#endif
