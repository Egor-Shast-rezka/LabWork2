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
    }

    return act == "y";
}

void Game::setMode(){

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
        gamepath.setupForAllBots(*this);
    } 
    
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
    
    do {
        //bool Allin = false;
        dealler.shuffleDeck(); // The dealer shuffles the deck

        for (auto& player : players) {
            dealler.dealCards(2, *player); // We distribute cards to the players
        }

        for (auto& player : players) {
            player->getName();
            player->getChipsOnDisplay();
            if (!player->isBot()) {
                player->getCardsOnDisplay();
            }
            std::cout << "\n";
        }

        std::vector<std::string> Numbers = { "First", "Second", "Third" };

        for (int i = 1; i <= 3; i++) {
            Card card = dealler.getOneCard(); // Get card
            cards.push_back(card);

            std::cout << "\n" << Numbers[i - 1] << " card: ";
            card.display();

            // Player actions
            for (auto& player : players) {
                if (player->isBot()) {
                    int new_currentBet = player->BotActions(player->getChips(), currentBet);
                    player->getName();
                    if (new_currentBet == player->getChips()) {
                        std::cout << "Allin!" << "\n";
                        //Allin = true;
                    }
                    else {
                        std::cout << "Make Bet: " << new_currentBet - currentBet << "\n";
                        currentBet = new_currentBet;
                        std::cout << "Current Bet: " << currentBet << "\n";
                    }
                }
                else {
                
                    std::string act = "";
                    while (!(act == "pass" || act == "call" || act == "allin")){
                        act = answerUserCheckString("Your answer (pass, call, allin): ");
                    }

                    if (act == "pass") {
                        player->getName();
                        std::cout << "Player passed.\n";
                    }
                    else if (act == "call") {
                        int bet = answerUserCheckInt("Your bet: ");

                        currentBet += bet;
                        player->PlaceBid(bet);
                        player->getChipsOnDisplay();
                    }
                }
            }
        }

        std::vector<Player> player_refs;
        for (const auto& player : players) {
            player_refs.push_back(*player);
        }
        
        std::vector<int> answer = dealler.SearchWinner(player_refs, cards);

        if (answer.size() == 1) {
            std::cout << "Player " << answer[0] << " wins!\n";
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


