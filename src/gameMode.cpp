/*
    Egor Shastin st129457@student.spbu.ru
    
    This file contains the implementation of game modes involving bots and players in the game. It implements the basic functions for managing bots and their actions, setting up the game mode, as well as the game logic for each player, including actions such as pass, bet, raise, and "all in".
    > The AllBots class is used to manage bots, create them, and perform game actions depending on their complexity. It also manages the output of information about players and the progress of the game.
    > The OneOnOne class is used to set up the game mode between players, displays information about them, and supports the main game loop with the ability to use character abilities.
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// ===========AllBots=============

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

void AllBots::OutputInfoPlayers() {

    for (auto& player : game.getPlayer()) {
    
        player->getNameOnDisplay();
        player->getChipsOnDisplay();
        
        if (!player->isBot()) {
        
            player->getCardsOnDisplay();
            
        }
        std::cout << "\n";
    }
    
}

void AllBots::GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund) {
    
    bool repeatBetting = true;
    bool repeatBettingForBot = false;
            
    // Player and Bot actions
    while(repeatBetting) {
            
        repeatBetting = false;
                
                
        for (std::size_t a = 0; a < game.getPlayer().size(); a++) {

            if (DataPass[a]) continue;

            game.getPlayer()[a]->getNameOnDisplay();

            if (game.getPlayer()[a]->isBot()) {
                
                /*
                    Returns an array of 5 numbers: 
                    1 - 0 or 1 - the bot agrees with the current bet or not, 
                    2 - 0 or 1 - the bot passes or not, 
                    3 - 0 or 1 - goes all-in or not, 
                    4 - the bot raises the current bet by some number of coins, (raise)
                    5 - the bot changes the bet (call)
                */
                std::vector<int> BotBet = game.getPlayer()[a]->BotActions(game.getPlayer()[a], game.getAllCardsForTable(), game.getDealler(), game.getBank().getCurrentBet(), Allin, raund, repeatBettingForBot);

                // If the bot agrees with the bet
                if (BotBet[0] == 1 || BotBet[3] == 0 || BotBet[4] == game.getBank().getCurrentBet()) {

                    std::cout << "Bot " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" agrees with the current bet.\n";
                    
                    game.getPlayer()[a]->PlaceBid(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a));
                    
                    game.getBank().addCountBetEachPlayer(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a), a);

                } 
                else if (BotBet[1] == 1) { // If the bot passes

                    std::cout << "Bot " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" pass." << "\n";

                    ifActPlayerData[a] = true;

                }
                else if (BotBet[2] == 1) { // If the bot goes all-in

                    std::cout << "Bot " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" get All in!" << "\n";

                    Allin = true;
                    
                    game.getBank().addCountBetEachPlayer(game.getPlayer()[a]->getChips(), a);
                        
                    game.getPlayer()[a]->PlaceBid(game.getPlayer()[a]->getChips());

                }
                else if (BotBet[3] != 0) { // If the bot makes a raise

                    std::cout << "Bot " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" make a raise: " << BotBet[3] << ".\n";

                    game.getBank().addCurrentBet(BotBet[3]);

                    game.getPlayer()[a]->PlaceBid(BotBet[3]);
                    
                    game.getBank().addCountBetEachPlayer(BotBet[3], a);

                    repeatBetting = true;
                    
                } else { // If the bot makes a call
                    
                    std::cout << "Bot " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" make a call: " << BotBet[4] << ".\n";

                    game.getPlayer()[a]->PlaceBid(BotBet[4] - game.getBank().getCurrentBet());
                    
                    game.getBank().addCountBetEachPlayer(BotBet[4] - game.getBank().getCurrentBet(), a);
                    
                    game.getBank().setCurrentBet(BotBet[4]);

                    repeatBetting = true;

                }
                
                std::cout << "Remain chips: " << game.getPlayer()[a]->getChips() << ".\n";

                std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

                std::cout << "\n";

            }
            else {
            
                // Get correct user answer: pass, call, allin or act
                std::string act = game.getValidAction(
            
                    game.getCharacter() ? 
                        (Allin ? std::vector<std::string>{"pass", "allin", "act"} : std::vector<std::string>{"pass", "raise", "call", "allin", "act"}) :
                        (Allin ? std::vector<std::string>{"pass", "allin"} : std::vector<std::string>{"pass", "call", "raise", "allin"}),
                    
                    game.getCharacter() ? 
                        (Allin ? "Your answer (pass, allin, act): " : "Your answer (pass, call, raise, allin, act): ") :
                        (Allin ? "Your answer (pass, allin): " : "Your answer (pass, call, raise, allin): "),
                    
                    ifActPlayerData, a);
            
                // If user pass
                if (act == "pass") {

                    std::cout << "Player passed.\n";

                    DataPass[a] = true;

                } 
                else if (act == "allin") { // If user make a allin

                    std::cout << "Player bets everything. All in.\n";
                    Allin = true;
                    
                    if (game.getBank().getCurrentBet() < game.getPlayer()[a]->getChips()) {
                    
                        game.getBank().setCurrentBet(game.getPlayer()[a]->getChips());
                        
                    }

                    game.getBank().addCountBetEachPlayer(game.getPlayer()[a]->getChips(), a);

                    game.getPlayer()[a]->PlaceBid(game.getPlayer()[a]->getChips());
                    
                }
                else if (act == "act") {

                    std::cout << "The player uses the character's ability.\n";

                    game.getPlayer()[a]->CharacterActions(game.getPlayer(), game.getAllCardsForTable(), game.getDealler().getDeck(), game.getBank(), a);

                    ifActPlayerData[a] = true;

                    a--;

                }
                else if (act == "call") { // If user make a call

                    int PlayerBet = contact.answerUserCheckInt("Your bet: ");

                    // Check answer player
                    while (PlayerBet < game.getBank().getCurrentBet() || PlayerBet > game.getPlayer()[a]->getChips()) {

                        std::cerr << "ERROR: Write valid bet!\n";

                        PlayerBet = contact.answerUserCheckInt("Your bet: ");
                    }
                    
                    if (PlayerBet == game.getBank().getCurrentBet()) {

                        std::cout << "Player " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" agrees with the current bet.\n";
                        
                        game.getPlayer()[a]->PlaceBid(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a));
                    
                        game.getBank().addCountBetEachPlayer(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a), a);
                        
                    } 
                    else {
                        
                        game.getBank().addCountBetEachPlayer(PlayerBet - game.getBank().getCurrentBet(), a);
                        
                        game.getPlayer()[a]->PlaceBid(PlayerBet - game.getBank().getCurrentBet());
                        
                        game.getBank().setCurrentBet(PlayerBet);

                        repeatBetting = true;
                    }

                    std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                    std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                    std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

                }
                else if (act == "raise") { // If user make a raise

                    int PlayerBet = contact.answerUserCheckInt("Your bet: ");

                    // Check answer player
                    while (PlayerBet > game.getPlayer()[a]->getChips()) {

                        std::cerr << "ERROR: Write valid bet!\n";

                        PlayerBet = contact.answerUserCheckInt("Your bet: ");
                    }
                    
                    if (PlayerBet == 0) {

                        std::cout << "Player " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" agrees with the current bet.\n";

                    } 
                    else {
                    
                        game.getBank().addCurrentBet(PlayerBet);
                        
                        game.getBank().addCountBetEachPlayer(PlayerBet, a);

                        game.getPlayer()[a]->PlaceBid(PlayerBet);

                        repeatBetting = true;
                    }

                    std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                    std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                    std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

                }
                std::cout << "\n";
            }
        }
        
        if (repeatBetting) {
            repeatBettingForBot = true;
        }
        
    }
}


// ===========OneOnOne=============

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

void OneOnOne::OutputInfoPlayers() {
    for (auto& player : game.getPlayer()) {
        
        player->getNameOnDisplay();
        player->getChipsOnDisplay();
        player->getCardsOnDisplay(); 
        
        int playerAnswer = contact.answerUserCheckInt("> Write 1 to hide hards: ");
        
        if (playerAnswer == 1) {
            std::cout << "\033[F\033[K\033[F\033[K\033[F\033[K";
        }

        std::cout << "\n";
    }
}

void OneOnOne::GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund) {
    bool repeatBetting = true;
            
    // Player and Bot actions
    while(repeatBetting) {
            
        repeatBetting = false;
                
                
        for (std::size_t a = 0; a < game.getPlayer().size(); a++) {

            if (DataPass[a]) continue;

            game.getPlayer()[a]->getNameOnDisplay();
            
            // Get correct user answer: pass, call, allin or act
            std::string act = game.getValidAction(

                game.getCharacter() ?
                (Allin ? std::vector<std::string>{"pass", "allin", "act"} : std::vector<std::string>{ "pass", "raise", "call", "allin", "act" }) :
                (Allin ? std::vector<std::string>{"pass", "allin"} : std::vector<std::string>{ "pass", "call", "raise", "allin" }),

                game.getCharacter() ?
                (Allin ? "Your answer (pass, allin, act): " : "Your answer (pass, call, raise, allin, act): ") :
                (Allin ? "Your answer (pass, allin): " : "Your answer (pass, call, raise, allin): "),

                ifActPlayerData, a);

            // If user pass
            if (act == "pass") {

                std::cout << "Player passed.\n";

                DataPass[a] = true;

            }
            else if (act == "allin") { // If user make a allin

                std::cout << "Player bets everything. All in.\n";
                Allin = true;

                if (game.getBank().getCurrentBet() < game.getPlayer()[a]->getChips()) {

                    game.getBank().setCurrentBet(game.getPlayer()[a]->getChips());

                }

                game.getBank().addCountBetEachPlayer(game.getPlayer()[a]->getChips(), a);

                game.getPlayer()[a]->PlaceBid(game.getPlayer()[a]->getChips());

            }
            else if (act == "act") {

                std::cout << "The player uses the character's ability.\n";

                game.getPlayer()[a]->CharacterActions(game.getPlayer(), game.getAllCardsForTable(), game.getDealler().getDeck(), game.getBank(), a);

                ifActPlayerData[a] = true;

                a--;

            }
            else if (act == "call") { // If user make a call

                int PlayerBet = contact.answerUserCheckInt("Your bet: ");

                // Check answer player
                while (PlayerBet < game.getBank().getCurrentBet() || PlayerBet > game.getPlayer()[a]->getChips()) {

                    std::cerr << "ERROR: Write valid bet!\n";

                    PlayerBet = contact.answerUserCheckInt("Your bet: ");
                }

                if (PlayerBet == game.getBank().getCurrentBet()) {

                    std::cout << "Player " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" agrees with the current bet.\n";

                    game.getPlayer()[a]->PlaceBid(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a));

                    game.getBank().addCountBetEachPlayer(game.getBank().getCurrentBet() - game.getBank().getCountBetEachPlayer(a), a);

                }
                else {

                    game.getBank().addCountBetEachPlayer(PlayerBet - game.getBank().getCurrentBet(), a);

                    game.getPlayer()[a]->PlaceBid(PlayerBet - game.getBank().getCurrentBet());

                    game.getBank().setCurrentBet(PlayerBet);

                    repeatBetting = true;
                }

                std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

            }
            else if (act == "raise") { // If user make a raise

                int PlayerBet = contact.answerUserCheckInt("Your bet: ");

                // Check answer player
                
                // Check answer player
                while (PlayerBet > game.getPlayer()[a]->getChips()) {

                    std::cerr << "ERROR: Write valid bet!\n";

                    PlayerBet = contact.answerUserCheckInt("Your bet: ");
                }
                    
                if (PlayerBet == 0) {

                    std::cout << "Player " << a + 1 << ": \"" << game.getPlayer()[a]->getName() << "\" agrees with the current bet.\n";

                } 
                else {
                    
                    game.getBank().addCurrentBet(PlayerBet);
                        
                    game.getBank().addCountBetEachPlayer(PlayerBet, a);

                    game.getPlayer()[a]->PlaceBid(PlayerBet);

                    repeatBetting = true;
                }

                std::cout << "Remain Chips: " << game.getPlayer()[a]->getChips() << ".\n";

                std::cout << "Current Bet: " << game.getBank().getCurrentBet() << ".\n";

                std::cout << "Bank: " << game.getBank().getPlayerMoney() << ".\n";

            }
            std::cout << "\n";
            
        }
    }
}



