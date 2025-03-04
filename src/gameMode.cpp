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
    
    int answerPlayer2 = contact.answerUserCheckInt(value);
    
    while (answerPlayer2 + static_cast<int>(game.getPlayer().size()) > 24) {
        
        std::cout << "ERROR: All count bots < 23!\n";
        
        answerPlayer2 = contact.answerUserCheckInt(value);
    }
    
    for (int i = 0; i < answerPlayer2; i++) {
        std::string NameForBot = contact.answerUserCheckString("> Write name for bot: ");
        game.setBot(NameForBot, complexity);
    }
}

// -------------------------
void AllBots::setupForAllBots(Game& game) {
    std::cout << "Setting up AllBots mode.\n";
    
    // Set name player
    std::string answerPlayer1 = contact.answerUserCheckString("> Write your name: ");
    
    // if Character = 1, choise character
    if (game.getCharacter() == 1) {
        int act = 0;
        while (!(act == 1 || act == 2 || act == 3 || act == 4 || act == 5 || act == 6)) {
            
            act = contact.answerUserCheckInt("> Choise your class (1 - AllSeeingPlayer, 2 - CheaterPlayer , 3 - EngagedDeckPlayer , 4 - DeallersFrendPlayer , 5 - PhotographicMemoryPlayer , 6 - BettingManipulatorPlayer.): ");
            
            if (!(act == 1 || act == 2 || act == 3 || act == 4 || act == 5 || act == 6)) {
                std::cout << "ERROR: Write number in range 1 - 6";
            }
        }
        
        game.setPlayerCharacter(answerPlayer1, act);
        std::cout << "Name and character for player has been set\n";
        
    } else {
        game.setPlayer(answerPlayer1);
        std::cout << "Name for player has been set\n";
    }
    
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
void OneOnOne::setupForAllPlayers(Game& game) {
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


