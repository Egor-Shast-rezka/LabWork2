/*
    Egor Shastin st129457@student.spbu.ru
    This file defines the behavior of all characters.
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// -----------------
AllSeeingPlayer::AllSeeingPlayer(std::string name) : Player(name) {}

// Check if it's a character or not
bool AllSeeingPlayer::isCharacter() {
    return true;
}

// Main method for AllSeeingPlayer
void AllSeeingPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {
    
    // Getting data from the player
    int player = contact.answerUserCheckInt("> Which player does the action apply to?: ");
    
    while (player < 0 || player > static_cast<int>(players.size())) {
        
        std::cerr << "ERROR: Players count: " << static_cast<int>(players.size()) << ". Please enter a valid players number!\n";
        
        player = contact.answerUserCheckInt("> Which player does the action apply to?: ");
    }
    
    int card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    
    while (card < 0 || card > players[player-1]->getCountCards()) {
        
        std::cerr << "ERROR: Cards count: " << players[player-1]->getCountCards() << ". Please enter a valid card number!\n";
        
        card = contact.answerUserCheckInt("> Which card does the action apply to?: ");
    }
    
    // Getting player card (by number) by card (by number)
    Card characterCardAct = players[player-1].get()->getAllCards()[card-1];
    
    // Card output
    std::cout << "&& Rang card: " << characterCardAct.getNumber() << ", suit card: " << characterCardAct.getSuit() << "\n";
}


// -----------------
CheaterPlayer::CheaterPlayer(std::string name) : Player(name) {}

// Check if it's a character or not
bool CheaterPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void CheaterPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {
    
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


// -------------------------
EngagedDeckPlayer::EngagedDeckPlayer(std::string name) : Player(name) {}

// Check if it's a character or not
bool EngagedDeckPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void EngagedDeckPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {

    std::cout << "Last Card in Deck: Number: " << deck.seeLastCard().getNumber() << ", Suit: " << deck.seeLastCard().getSuit() << "\n";
}


// -------------------------
DeallersFrendPlayer::DeallersFrendPlayer(std::string name) : Player(name) {}

// Check if it's a character or not
bool DeallersFrendPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void DeallersFrendPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {
    
    // Gat Last card on table
    Card LastCard = cardsOnTable.back();
    
    // Put one card in Deck
    deck.putOneCardInDeck(LastCard);
    
    // Del Last card on table
    cardsOnTable.pop_back();
    
    // New card on table
    cardsOnTable.push_back(deck.deal());
    
    std::cout << "&& A new card is put on the table.\n";
}


// -------------------------
PhotographicMemoryPlayer::PhotographicMemoryPlayer(std::string name) : Player(name) {}

// Check if it's a character or not
bool PhotographicMemoryPlayer::isCharacter() {
    return true;
}

// Check if there is a card in the deck
bool PhotographicMemoryPlayer::searchCardInDeck(Card& InFullDeck, std::vector<Card>& deck) {
    
    for (std::size_t i = 0; i < deck.size(); i++) {
        if (deck[i].getNumber() == InFullDeck.getNumber() && deck[i].getSuit() == InFullDeck.getSuit()) {
            return true;
        }
    }
    return false;
}

// Main method for CheaterPlayer
void PhotographicMemoryPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {

   std::cout << "&& Remaining cards in the deck: \n";
   
   // Create new deck
   Deck newdeck;
   
   std::vector<Card> FullDeck = newdeck.getAllCards();
   
   // Deck with remain card
   std::vector<Card> RemainDeck = deck.getAllCards();
   
   for (std::size_t i = 0; i < FullDeck.size(); i++) {
       
       if (searchCardInDeck(FullDeck[i], RemainDeck)) {
       
           // Check card
           std::cout << "&& Number: " << FullDeck[i].getNumber() << ", Suit: " << FullDeck[i].getSuit() << "\n";
       }
       
   }

}


// -------------------------
BettingManipulatorPlayer::BettingManipulatorPlayer(std::string name) : Player(name) {}
    
bool BettingManipulatorPlayer::isCharacter() {
    return true;
}

// Main method for CheaterPlayer
void BettingManipulatorPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, int indexPlayer) {
    std::cout << "";
}














