/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// -----------------
AllSeeingPlayer::AllSeeingPlayer(std::string name) : Player(name) {}

bool AllSeeingPlayer::isCharacter() {
    return true;
}

Card AllSeeingPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler, int player, int card) {

    return players[player-1].get()->getAllCards()[card-1];
}

/*
// -----------------
CheaterPlayer::CheaterPlayer(std::string name) : Player(name) {}

bool CheaterPlayer::isCharacter() {
    return true;
}

Card CheaterPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler, int player, int card) {
    
    
    setCard();
    return ;
}
*/
