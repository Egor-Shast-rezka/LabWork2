/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// -------------------------
PlayerDecorator::PlayerDecorator(Player* p) : Player(p->getName()), player(p) {}

PlayerDecorator::~PlayerDecorator() { delete player; }

void PlayerDecorator::setName(std::string name) { player->setName(name); }

std::string PlayerDecorator::getName() const { return player->getName(); }

void PlayerDecorator::getNameOnDisplay() const { player->getNameOnDisplay(); }

void PlayerDecorator::setChips(int num) { player->setChips(num); }

void PlayerDecorator::getChipsOnDisplay() const { player->getChipsOnDisplay(); }

int PlayerDecorator::getChips() const { return player->getChips(); }

void PlayerDecorator::PlaceBid(int num) { player->PlaceBid(num); }

void PlayerDecorator::setCard(Card elem) { player->setCard(elem); }

std::vector<Card> PlayerDecorator::getAllCards() const { return player->getAllCards(); }

void PlayerDecorator::getCardsOnDisplay() const{ player->getCardsOnDisplay(); }

int PlayerDecorator::getCountCards() const { return player->getCountCards(); }

void PlayerDecorator::delAllCards() { player->delAllCards(); }

bool PlayerDecorator::isBot() { return player->isBot(); }

int PlayerDecorator::BotActions(int countChips, int currentBet, int Bank, int Allin) {
    return player->BotActions(countChips, currentBet, Bank, Allin);
}
    

// -----------------
AllSeeingPlayer::AllSeeingPlayer(Player* p) : PlayerDecorator(p) {}

Card AllSeeingPlayer::CheckCardEnemy(Game& game, int player, int card) {
    return players[player]->getAllCards()[card];
}

    
Card AllSeeingPlayer::CharacterActions(Game& game, int player, int card){
    return CheckCardEnemy(game, player, card);
}

/*
// -----------------
CheaterPlayer::CheaterPlayer(Player* p) : PlayerDecorator(p) {}

void CheaterPlayer::ReplaceCardInHand(Game& game, Dealler& dealler, int card) {
    std::cout << "kjefkqvkjqv\n";
    //setCard(dealler.getAllDeck().deal());
}

int CheaterPlayer::CharacterActions(){
    return 1;
}
*/
