/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"

// -----------------
Game::Game() {}
Game::~Game() {}

// Check answer user
int Game::answerUserCheckInt(std::string value) {

    int answer = -100;
    while (true) {
        std::cout << value;
        std::cin >> answer;
        
        if (std::cin.fail() || answer < 0){
            std::cin.clear();
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Write integer!" << std::endl;
        } else {
            return answer;
        }
        
    }
    return 0;
}

std::string Game::answerUserCheckString(std::string value) {

    std::string answer = "";
    while (true) {
        std::cout << value;
        std::cin >> answer;
        

        bool isNumberOnly = true;
        for (char c : answer) {
            if (c < '0' || c > '9') {
                isNumberOnly = false;
                break;
            }
        }

        if (std::cin.fail() || answer.empty() || isNumberOnly) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Write what is required using letters, not only numbers!" << std::endl;
        } else {
            return answer;
        }
        
    }
    return "";
}

// Creating players
void Game::setPlayer(std::string name) {
    players.push_back(std::make_unique<Player>(name));
}

void Game::setDealler() { // Creating a dealer.
    Dealler diller;
    dealler = diller;
}

// Function for adding bots
void Game::setBot(std::string name, int index) {
    if (index == 1) {
        players.push_back(std::make_unique<AIPlayer_easy>(name));
    }
    else if (index == 2) {
        players.push_back(std::make_unique<AIPlayer_normal>(name));
    }
    else if (index == 3) {
        players.push_back(std::make_unique<AIPlayer_hard>(name));
    }
}

void Game::resetGame() {
    cards.clear();
    dealler.newDeck();
    dealler.shuffleDeck();
    currentBet = 0;
    for (auto& player : players) {
        player->delAllCards();
    }
    std::cout << "\n";
}

bool Game::checkContinueGame() {

    std::string act = "";
    while (!(act == "y" || act == "n")){
        act = answerUserCheckString("Do you want to continue the game? (y/n): ");
        
        if (!(act == "y" || act == "n")) {
        
            std::cout << "ERROR: Write integer 'y' or 'n'!\n";
        }
    }

    return act == "y";
}

void Game::setMode(){
    
    // Set Character for Player
    std::string setCharacter = "";
    while (!(setCharacter == "y" || setCharacter == "n")){
        setCharacter = answerUserCheckString("> Do you want to play with character? (y/n): ");
        
        if (!(setCharacter == "y" || setCharacter == "n")) {
        
            std::cout << "ERROR: Write integer 'y' or 'n'!\n";
        }
    }
        
    if (setCharacter == "y") {
        Character = 1;
    }
    
    // Set game mode
    int modeChoice = 0;
    std::cout << "Choose game mode: 1 - AllBots, 2 - OneOnOne.\n";
    while (!(modeChoice == 1 || modeChoice == 2)){
    
        modeChoice = answerUserCheckInt("> Write name game mode: ");
        
        if (!(modeChoice == 1 || modeChoice == 2)) {
            std::cout << "ERROR: Write integer 1 or 2!\n";
        }
        
    } 
    
    if (modeChoice == 1) {
        AllBots gamepath;
        gamepath.setupForAllBots(*this);
    } if (modeChoice == 2) {
        OneOnOne gamepath;
        gamepath.setupForAllPlayers(*this);
    }
    
    // Set count chips
    int answerPlayer = answerUserCheckInt("> Write chips for all player: ");
    
    setChipsAllPlayer(answerPlayer);
    
    Bank = answerPlayer;
    
    std::cout << "Chips has been set" << "\n";
    
    std::cout << "Game mode has been set.\n\n========Start Play========\n";
    
}

void Game::setChipsAllPlayer(int count) {
    for (auto& player : players) {
        player->setChips(count);
    }
}

// Main function to start the game
int Game::startGame() {

    setMode();
    
    // Path game
    do {
        int Allin = 0;
        dealler.shuffleDeck(); // The dealer shuffles the deck
        
        // Create vector for allin and pass
        std::vector<int> DataPass;
        
        for (std::size_t i = 0; i < players.size(); i++) {
            DataPass.push_back(0);
        }
        
        // Distribute cards to the players
        for (auto& player : players) {
            dealler.dealCards(2, *player);
        }

        for (auto& player : players) {
            player->getNameOnDisplay();
            player->getChipsOnDisplay();
            if (!player->isBot()) {
                player->getCardsOnDisplay();
            }
            std::cout << "\n";
        }

        std::vector<std::string> Numbers = { "First", "Second", "Third" };

        for (int i = 1; i <= 3; i++) {
            Card card = dealler.getOneCard(); // Get card from deck
            cards.push_back(card);

            std::cout << "\n> " << Numbers[i - 1] << " card: ";
            card.display();

            // Player actions
            for (std::size_t i = 0; i < players.size(); i++) {
                if (DataPass[i] != 1) {
                    if (players[i]->isBot()) {
                
                        int BotBet = players[i]->BotActions(players[i]->getChips(), currentBet, Bank, Allin);
                        players[i]->getNameOnDisplay();
                        if (BotBet == Bank - currentBet) {
                    
                            std::cout << "Bot get All in!" << "\n";
                            Allin = 1;
                        }
                        else {
                    
                            std::cout << "Make Bet: " << BotBet << "\n";
                            currentBet += BotBet;
                            std::cout << "Current Bet: " << currentBet << "\n";
                        }
                        std::cout << "\n";
                        
                    } else {
                        std::string act = "";
                        
                        if (Allin == 0) {
                            while (!(act == "pass" || act == "call" || act == "allin")){
                                act = answerUserCheckString("Your answer (pass, call, allin): ");
                                
                                if (!(act == "pass" || act == "call" || act == "allin")) {
                                    std::cout << "Available actions: pass, call, allin.\n";
                                }
                            }
                        } else {
                            while (!(act == "allin" || act == "pass")){
                                act = answerUserCheckString("Your answer (pass, allin): ");
                                
                                if (!(act == "allin" || act == "pass")) {
                                    std::cout << "All in was made, bet all or pass.\n";
                                }
                            }
                        }
                        
                        players[i]->getNameOnDisplay();
                        
                        if (act == "pass") {
                        
                            std::cout << "Player passed.\n";
                            DataPass[i] = 1;
                            
                        } if (act == "call") {
                            
                            int bet = answerUserCheckInt("Your bet (write 0 if you wishn`t make a chip): ");

                            currentBet += bet;
                            players[i]->PlaceBid(bet);
                            players[i]->getChipsOnDisplay();
                            
                        } if (act == "allin") {
                        
                            std::cout << "Player bets everything. All in.\n";
                            Allin = 1;
                            currentBet += players[i]->getChips();
                            players[i]->PlaceBid(players[i]->getChips());
                            
                        }
                        std::cout << "\n";
                    }
                }
            }
        }

        std::vector<Player> player_refs;
        for (const auto& player : players) {
            player_refs.push_back(*player);
        }
        
        std::vector<int> answer = dealler.SearchWinner(player_refs, cards, DataPass);
        
        if (answer.size() == 1) {
            if (answer[0] == 123456){
                std::cout << "All players make a pass!\n";
            } else {
                std::cout << "Player " << answer[0] << " wins!\n";
            }
        }
        else {
            std::cout << "Draw between players: ";
            for (const auto& winner : answer) {
                std::cout << winner << " ";
            }
            std::cout << "\n";
        }

        resetGame();

    } while (checkContinueGame());

    std::cout << "Game over!\n";
    return 0;
}


