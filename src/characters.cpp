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

void AllSeeingPlayer::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler) {
    
    //int player = answerUserCheckInt("Which player does the action apply to?: ");
    //int card = answerUserCheckInt("Which card does the action apply to?: ");
    
    //Card characterCardAct = players[player-1].get()->getAllCards()[card-1];
    
    std::cout << "Rang card: " /*<< characterCardAct.getNumber() << ", suit card: " << characterCardAct.getSuit() << "\n"*/;
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
