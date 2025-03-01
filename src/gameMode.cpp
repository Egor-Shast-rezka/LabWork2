/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"

// ---------------
EaggedDeck::EaggedDeck() : Deck() {}

void EaggedDeck::viewNextCard() {
    if (cards.empty()) {
        std::cout << "No cards left in the deck!" << std::endl;
    }
    else {
        Card card = cards.back();
        card.display();
    }
}

/*
// -------------------------
void AllBots::setup(Game& game) {
    std::cout << "Setting up AllBots mode.\n";
    for (int i = 0; i < 4; ++i) {
        game.setBot("Bot" + std::to_string(i + 1), 1);
    }
}


// -------------------------
void MoreChances::setup(Game& game) {
    std::cout << "Setting up MoreChances mode.\n";
        // Здесь могут быть добавлены дополнительные возможности для игроков
}


// -------------------------
void OneOnOne::setup(Game& game) {
    std::cout << "Setting up OneOnOne mode.\n";
    game.setPlayer("Player1");
    game.setPlayer("Player2");
}


// -------------------------
void WithoutCards::setup(Game& game) {
    std::cout << "Setting up WithoutCards mode.\n";
        // Здесь можно реализовать логику игры без карт
}
*/
