/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// -------------------------
AllBots::AllBots(Game& game) : game(game) {}
AllBots::~AllBots() {}


void AllBots::setAllBots(int complexity, std::string value){
    
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

void AllBots::setupForGameMode() {
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
    setAllBots(1, "> Write count bot complexity easy: ");
    
    // Normal bot
    setAllBots(2, "> Write count bot complexity normal: ");
    
    std::cout << "Names for bots has been set\n";
    
}

void AllBots::GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, bool& repeatBettingForBot, bool& repeatBetting, int& raund) {
    
    for (std::size_t a = 0; a < game.getPlayer().size(); a++) {

        if (DataPass[a]) continue;

        game.getPlayer()[a]->getNameOnDisplay();

        if (game.getPlayer()[a]->isBot()) {

            std::vector<int> BotBet = game.getPlayer()[a]->BotActions(game.getPlayer()[a], game.getAllCardsForTable(), game.getDealler().getDeck(), game.getBank().getCurrentBet(), Allin, repeatBettingForBot);

            // If it's the first game, then everyone places a bet, not raises it
            if (raund != 1 && BotBet[0] != 0) {
                BotBet[0] -= game.getBank().getCurrentBet();
            }

            // If the bot agrees with the bet
            if (BotBet[0] == 0) {

                std::cout << "Bot " << a + 1 << ": " << game.getPlayer()[a]->getName() << " agrees with the current bet.\n";

                // If the bot goes all-in
            }
            else if (BotBet[2] == 1) {

                std::cout << "Bot " << a + 1 << ": " << game.getPlayer()[a]->getName() << " get All in!" << "\n";

                Allin = true;

                if (game.getPlayer()[a]->getChips() > 0) {

                    game.getPlayer()[a]->PlaceBid(game.getPlayer()[a]->getChips());

                    game.getBank().addPlayerMoney(BotBet[0]);
                }

                // If the bot passes
            }
            else if (BotBet[1] == 1) {

                std::cout << "Bot " << a + 1 << ": " << game.getPlayer()[a]->getName() << " pass." << "\n";

                ifActPlayerData[a] = true;

                // If the bot makes a bet
            }
            else {

                std::cout << "Bot " << a + 1 << ": " << game.getPlayer()[a]->getName() << " take Bet: " << BotBet[0] << ".\n";

                game.getBank().setCurrentBet(BotBet[0]);

                game.getPlayer()[a]->PlaceBid(BotBet[0]);

                game.getBank().addPlayerMoney(BotBet[0]);

                repeatBetting = true;

                std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";
            }


            std::cout << "\n";

        }
        else {

            std::string act;

            if (game.getCharacter()) {
                if (!Allin) {

                    act = contact.answerUserCheckString("Your answer (pass, call, allin, act): ");

                    while (!(act == "pass" || act == "call" || act == "allin" || act == "act") || (act == "act" && ifActPlayerData[a])) {

                        if (!(act == "pass" || act == "call" || act == "allin" || act == "act")) {
                            std::cerr << "ERROR: Available actions: pass, call, allin, act.\n";
                        } if (act == "act" && ifActPlayerData[a]) {
                            std::cerr << "ERROR: Player can only use the ability once per round.\n";
                        }

                        act = contact.answerUserCheckString("Your answer (pass, call, allin, act): ");
                    }
                } else {

                    act = contact.answerUserCheckString("Your answer (pass, allin, act): ");

                    while (!(act == "allin" || act == "pass" || act == "act") || (act == "act" && ifActPlayerData[a])) {

                        act = contact.answerUserCheckString("Your answer (pass, allin, act): ");

                        if (!(act == "pass" || act == "allin" || act == "act")) {
                            std::cerr << "ERROR: Available actions: pass, allin, act.\n";
                        } if (act == "act" && ifActPlayerData[a]) {
                            std::cerr << "ERROR: Player can only use the ability once per round.\n";
                        }
                    }
                }
            }
            else {
                if (!Allin) {

                    act = contact.answerUserCheckString("Your answer (pass, call, allin): ");

                    while (!(act == "pass" || act == "call" || act == "allin")) {

                        std::cout << "Available actions: pass, call, allin.\n";

                        act = contact.answerUserCheckString("Your answer (pass, call, allin): ");

                    }
                }
                else {

                    act = contact.answerUserCheckString("Your answer (pass, allin): ");

                    while (!(act == "allin" || act == "pass")) {

                        std::cout << "All in was made, bet all or pass.\n";

                        act = contact.answerUserCheckString("Your answer (pass, allin): ");

                    }
                }
            }

            if (act == "pass") {

                std::cout << "Player passed.\n";

                DataPass[a] = true;

            }
            else if (act == "call") {

                int PlayerBet = contact.answerUserCheckInt("Your bet (write 0 if you wishn`t make a chip): ");

                // Check answer player
                while (PlayerBet < game.getBank().getCurrentBet()) { // add 0

                    if (PlayerBet == 0) {
                        break;
                    }

                    std::cerr << "ERROR: Write valid bet!\n";

                    PlayerBet = contact.answerUserCheckInt("Your bet (write 0 if you wishn`t make a chip): ");
                }


                // If it's the first game, then everyone places a bet, not raises it
                if (PlayerBet != 0 && raund != 1) {

                    PlayerBet -= game.getBank().getCurrentBet();

                }

                if (PlayerBet == 0) {

                    std::cout << "Player " << game.getPlayer()[a]->getName() << " agrees with the current bet.\n";

                }
                else if (PlayerBet > game.getPlayer()[a]->getChips()) {

                    act = "allin";

                }
                else {

                    game.getBank().setCurrentBet(PlayerBet);

                    game.getBank().addPlayerMoney(PlayerBet);

                    game.getPlayer()[a]->PlaceBid(PlayerBet);

                    repeatBetting = true;

                }

                std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

            }
            if (act == "allin") {

                std::cout << "Player bets everything. All in.\n";
                Allin = true;

                if (game.getBank().getCurrentBet() < game.getPlayer()[a]->getChips()) {

                    game.getBank().setCurrentBet(game.getPlayer()[a]->getChips());

                    game.getBank().addPlayerMoney(game.getPlayer()[a]->getChips());

                    game.getPlayer()[a]->PlaceBid(game.getPlayer()[a]->getChips());

                }

            }
            else if (act == "act") {

                std::cout << "The player uses the character's ability.\n";

                game.getPlayer()[a]->CharacterActions(game.getPlayer(), game.getAllCardsForTable(), game.getDealler().getDeck(), game.getBank(), a);

                ifActPlayerData[a] = true;

                a--;

            }
            std::cout << "\n";
        }
    }
}


// -------------------------
OneOnOne::OneOnOne(Game& game) : game(game) {}
OneOnOne::~OneOnOne() {}

void OneOnOne::setupForGameMode() {
    std::cout << "Setting up AllBots mode.\n";
    
    // Get players count
    int answerPlayer1 = contact.answerUserCheckInt("> Write count players (less to 25): ");
    while (answerPlayer1 > 25) {
        
        std::cerr << "ERROR: Write correct integer (less to 25)!";
        
        answerPlayer1 = contact.answerUserCheckInt("> Write count players (less to 25): ");
        
    }
    
    // Set all players
    while (answerPlayer1 > 0) {
        answerPlayer1--;
        
        std::string NameForPlayer = contact.answerUserCheckString("> Write name for player: ");
        game.setPlayer(NameForPlayer);
        
    }
}

void OneOnOne::GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, bool& repeatBettingForBot, bool& repeatBetting, int& raund) {
    std::cout << "";
}



