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
    char act;
    std::cout << "Do you want to continue the game? (y/n): ";
    std::cin >> act;
    return act == 'y';
}

void Game::setMode(){

    int answerPlayer1 = 0; // Number for chips
    std::string answerPlayer2 = "NewPlayer";
    
    // Set name player
    std::cout << "> Write your name: ";
    std::cin >> answerPlayer2;
    
    setPlayer(answerPlayer2);
    
    std::cout << "Name has been set\n";
    /*
    // Set game mode
    
    int modeChoice = 0;
    while (!(modeChoice == 1 || modeChoice == 2 || modeChoice == 3 || modeChoice == 4)){
    
        std::cout << "Choose game mode: 1 - AllBots, 2 - MoreChances, 3 - OneOnOne, 4 - WithoutCards.\n";
        std::cout << "> Write name game mode: ";
        std::cin >> modeChoice;
        std::cout << "\n";
        
    } 
    
    if (modeChoice == 1) {
        AllBots.setur(*this);
    } if (modeChoice == 2) {
        MoreChances.setur(*this);
    } if (modeChoice == 3) {
        OneOnOne.setur(*this);
    } if (modeChoice == 4) {
        WithoutCards.setur(*this);
    }
    
    std::cout << "Game mode has been set.\n";
    */
    // Set count chips
    std::cout << "> Write chips for all player: ";
    std::cin >> answerPlayer1;
    
    setChipsAllPlayer(answerPlayer1);
    
    std::cout << "Chips has been set" << "\n";
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
                    char act = 'p';
                    std::cout << "Your answer (p - pass, c - call): ";
                    std::cin >> act;

                    if (act == 'p') {
                        player->getName();
                        std::cout << "Player passed.\n";
                    }
                    else if (act == 'c') {
                        int bet = 0;
                        std::cout << "Your bet: ";
                        std::cin >> bet;

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


