/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// -------------------------
void AllBots::setAllBots(Game& game, int complexity, std::string value){
    int answerPlayer2 = game.answerUserCheckInt(value);
    
    for (int i = 0; i < answerPlayer2; i++) {
        std::string NameForBot = game.answerUserCheckString("> Write name for bot: ");
        game.setBot(NameForBot, complexity);
    }
}

// -------------------------
void AllBots::setupForAllBots(Game& game) {
    std::cout << "Setting up AllBots mode.\n";
    
    // Set name player
    std::string answerPlayer1 = game.answerUserCheckString("> Write your name: ");
    
    game.setPlayer(answerPlayer1);
    
    std::cout << "Name for player has been set\n";
    
    // Set count bot
    
    // Easy bot
    setAllBots(game, 1, "> Write count bot complexity easy: ");
    
    // Normal bot
    setAllBots(game, 1, "> Write count bot complexity normal: ");
    
    // Hard bot
    setAllBots(game, 1, "> Write count bot complexity hard: ");
    
    std::cout << "Names for bots has been set\n";
    
}


// -------------------------
void OneOnOne::setupForAllBots(Game& game) {
    std::cout << "Setting up OneOnOne mode.\n";
    /*
    std::string answerPlayer1 = "NewPlayer";
    int answerPlayer2 = 0;
    
    // Set name player
    std::cout << "> Write count players: ";
    std::cin >> answerPlayer;
    
    setPlayer(answerPlayer);
    
    std::cout << "Name has been set\n";
    */
}


