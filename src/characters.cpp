/*
    Egor Shastin st129457@student.spbu.ru
    
    This code defines several specialized player classes for a card game, each implementing different character actions. Each class inherits from a base Player class and overrides the CharacterActions method to define unique abilities.

    > AllSeeingPlayer: This player can inspect the cards of other players.
    > CheaterPlayer: Allows a player to replace one of their cards with a new one from the deck.
    > EngagedDeckPlayer: This player can see the last card in the deck.
    > DeallersFrendPlayer: Allows a player to manipulate the cards on the table by replacing the last card with a new one from the deck.
    > PhotographicMemoryPlayer: This player can remember and display the remaining cards in the deck.
    > BettingManipulatorPlayer: Allows a player to steal chips from another player.
    
    Each class contains a CharacterActions method where the unique abilities of the respective player are implemented. These abilities include manipulating cards, checking the deck, or stealing chips from other players. The classes make use of various game elements like Card, Deck, Bank, and Player to perform their actions.
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// ===========AllSeeingPlayer=============

AllSeeingPlayer::AllSeeingPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}

// Check if it's a character or not
bool AllSeeingPlayer::isCharacter() {
    return true;
}

// Main method for AllSeeingPlayer
void AllSeeingPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    
    // Getting data from the player
    int player = contact.answerUserCheckInt("> Which player does the action apply to?: ");
    
    if (player < 1 || player > static_cast<int>(players.size())) throw std::out_of_range("Invalid player index!");

    while (player < 1 || player > static_cast<int>(players.size())) {
        
        std::cerr << "ERROR: Players count: " << static_cast<int>(players.size()) << ". Please enter a valid players number!\n";
        
        player = contact.answerUserCheckInt("> Which player does the action apply to?: ");
    }
    
    int card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    
    if (card < 1 || card > players[player - 1]->getCountCards()) throw std::out_of_range("Invalid card index!");

    while (card < 1 || card > players[player-1]->getCountCards()) {
        
        std::cerr << "ERROR: Cards count: " << players[player-1]->getCountCards() << ". Please enter a valid card number!\n";
        
        card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    }
    
    // Getting player card (by number) by card (by number)
    Card characterCardAct = players[player-1].get()->getAllCards()[card-1];
    
    // Card output
    std::cout << "&& Rang card: " << characterCardAct.getNumber() << ", suit card: " << characterCardAct.getSuit() << "\n";
}


// ===========CheaterPlayer=============

CheaterPlayer::CheaterPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}

// Check if it's a character or not
bool CheaterPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void CheaterPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    
    // Getting data from the player
    int card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    
    while (card > players[indexPlayer]->getCountCards() || card < 0) {
        
        std::cerr << "ERROR: Cards count: " << players[indexPlayer]->getCountCards() << ". Please enter a valid card number!\n";
        
        card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    }
    
    // Get all cards player and save their
    std::vector<Card> allCardsPlayer = players[indexPlayer]->getAllCards();
    
    // Delete all players card in your hand
    players[indexPlayer].get()->delAllCards();
    
    // Put one card in Deck
    deck.putOneCardInDeck(allCardsPlayer[card-1]);
    
    // Remove one card
    allCardsPlayer.erase(allCardsPlayer.begin() + card - 1);
    
    // Add card in new hands player
    allCardsPlayer.push_back(deck.deal());
    
    std::cout << "\n&& " << players[indexPlayer]->getName() << "\n&& New cards in players hand:\n";
    
    for (std::size_t i = 0; i < allCardsPlayer.size(); i++) {
    
        // Set card for player
        players[indexPlayer]->setCard(allCardsPlayer[i]);
        
        // Check card
        std::cout << "\n&& Number: " << allCardsPlayer[i].getNumber() << ", Suit: " << allCardsPlayer[i].getSuit();
    }
    
    std::cout << "\n";
}


// ===========EngagedDeckPlayer=============

EngagedDeckPlayer::EngagedDeckPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}

// Check if it's a character or not
bool EngagedDeckPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void EngagedDeckPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {

    std::cout << "Last Card in Deck: Number: " << deck.seeLastCard().getNumber() << ", Suit: " << deck.seeLastCard().getSuit() << "\n";
}


// ===========DeallersFrendPlayer=============

DeallersFrendPlayer::DeallersFrendPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}

// Check if it's a character or not
bool DeallersFrendPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void DeallersFrendPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    if (cardsOnTable.empty()) {
        throw std::runtime_error("No cards on the table!");
    }

    Card LastCard = cardsOnTable.back();
    deck.putOneCardInDeck(LastCard);
    cardsOnTable.pop_back();

    try {
        cardsOnTable.push_back(deck.deal());
    }
    catch (const std::out_of_range& e) {
        cardsOnTable.push_back(LastCard);
        throw;
    }
}


// ===========PhotographicMemoryPlayer=============

PhotographicMemoryPlayer::PhotographicMemoryPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}

// Check if it's a character or not
bool PhotographicMemoryPlayer::isCharacter() {
    return true;
}

// Check if there is a card in the deck
bool PhotographicMemoryPlayer::searchCardInDeck(Card& InFullDeck, std::vector<Card>& deck) {
    
    if (deck.empty()) return false;

    for (std::size_t i = 0; i < deck.size(); i++) {
        if (deck[i].getNumber() == InFullDeck.getNumber() && deck[i].getSuit() == InFullDeck.getSuit()) {
            return true;
        }
    }
    return false;
}

// Main method for CheaterPlayer
void PhotographicMemoryPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    std::vector<Card>& RemainDeck = deck.getAllCards();
    if (RemainDeck.empty()) {
        std::cout << "&& Deck is empty!\n";
        return;
    }

    Deck FullDeck;
    std::vector<Card>& FullDeckCards = FullDeck.getAllCards();

    for (Card& card : FullDeckCards) {
        if (searchCardInDeck(card, RemainDeck)) {
            std::cout << "&& Number: " << card.getNumber() << ", Suit: " << card.getSuit() << "\n";
        }
    }
}


// ===========BettingManipulatorPlayer=============

BettingManipulatorPlayer::BettingManipulatorPlayer(std::string name, Game& game) : Player(name, game) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty!");
}
bool BettingManipulatorPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void BettingManipulatorPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    
    if (players.empty()) {
        throw std::invalid_argument("No players available!");
    }

    // Chose player
    int actionPlayer1 = contact.answerUserCheckInt("&& Which player do you want to steal from: ");
    
    while (actionPlayer1 > static_cast<int>(players.size()) || actionPlayer1 == indexPlayer) {
        
        if (actionPlayer1 > static_cast<int>(players.size())) std::cerr << "ERROR: Such a player does not exist!\n";
        if (actionPlayer1 == indexPlayer) std::cerr << "Cannot steal from yourself!\n";
        
        actionPlayer1 = contact.answerUserCheckInt("&& Which player do you want to steal from: ");
        
    }
    // Steal money from Player
    int actionPlayer2 = contact.answerUserCheckInt("&& How manu do you want to steal: ");
    
    while (actionPlayer2 > players[actionPlayer1]->getChips()) {
        
        std::cerr << "ERROR: You want to steal too much!\n";
        
        actionPlayer2 = contact.answerUserCheckInt("&& How manu do you want to steal: ");
        
    }
    
    players[actionPlayer1]->PlaceBid(actionPlayer2);
    
    players[indexPlayer]->setChips(players[indexPlayer]->getChips() + actionPlayer2);
        
}
