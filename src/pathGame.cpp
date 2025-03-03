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

bool Game::isNumber(std::string answer) {
    for (char c : answer) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}
     
int Game::stringToInt(const std::string& str) {
    int number = 0;
    for (char c : str) {
        number = number * 10 + (c - '0');
    }
    return number;
}

// Check answer user
int Game::answerUserCheckInt(std::string value) {
    std::string answer = "";
    while (true) {
        std::cout << value;
        std::cin >> answer;

        if (answer == "rule") {
            
            Rule rule;
            rule.getRuleOnDisplay(*this);
            std::cin.clear();
        } else {
        
            if (!isNumber(answer)) {
                std::cout << "ERROR: Write integer!" << std::endl;
                std::cin.clear();
            } else {

                return stringToInt(answer);
            }
        }
    }
    return 0;
}

std::string Game::answerUserCheckString(std::string value) {

    std::string answer = "";
    while (true) {
        std::cout << value;
        std::cin >> answer;
        
        if (std::cin.fail() || answer.empty() || isNumber(answer)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Write what is required using letters, not only numbers!" << std::endl;
        } else {
        
            if (answer == "rule"){
            
                Rule rule;
                rule.getRuleOnDisplay(*this);
                std::cin.clear();
                
            } else {
            
                return answer;
            }
        }
        
    }
    return "";
}

// Creating players
void Game::setPlayer(std::string name) {
    players.push_back(std::make_unique<Player>(name));
}

std::vector<std::unique_ptr<Player>>& Game::getPlayer() {
    return players;
}

void Game::setDealler() { // Creating a dealer.
    Dealler diller;
    dealler = diller;
}

Dealler Game::getDealler() {
    return dealler;
}

Card Game::seeLastCardInDeallerDeck() const { // See last card for Engaged deck
    return dealler.seeLastCard();
}
    
void Game::putOneCardInDeckInDeallerHand(Card card) { // Put one card in deck for CheaterPlayer
    dealler.putOneCardInDeck(card);
}

std::vector<Card> Game::getAllCardsForTable() {
    return cards;
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

void Game::setPlayerCharacter(std::string name, int index) {
    
    if (index == 1) {
        players.push_back(std::make_unique<AllSeeingPlayer>(name));
    }
    // finish writing
}

void Game::resetGame() {
    
    if ((static_cast<int>(players.size()) * 2 + 3) * (CountGame + 2) > 52) {
    
        CountGame = 0;
        dealler.newDeck();
        dealler.shuffleDeck();
        
        std::cout << "> The cards are out. Get new colode!\n";
    }
    
    CountGame++;
    
    cards.clear();
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


// -------------------
bool Rule::resetGetRule(Game& game) {
    std::string answer = game.answerUserCheckString("> Do you want to know any other rules?");
    while (!(answer == "y" || answer == "n")) {
        std::cout << "ERROR: Write 'y' or 'n'\n";
        
        answer = game.answerUserCheckInt("> Do you want to know any other rules? (y, n)");
    }
    return answer == "y";
}

void Rule::getRuleOnDisplay(Game& game) {
    std::cout << "\n\n===============Game Rule===============\n";
    do {
        int act = game.answerUserCheckInt("> Select the rules you want to know (1-Bot rule, 2-Player rule, 3-Characters rule, 4-Game Rule, 5-...): ");
        while (!(act == 1 || act == 2 || act == 3 || act == 4 || act == 5 || act == 6)) {
            std::cout << "ERROR: Choise integer in range 1 - 6\n";
        
            act = game.answerUserCheckInt("> Select the rules you want to know (1-Bot rule, 2-Player rule, 3-Characters rule, 4-Game Rule, 5-...): ");
        }
    
        if (act == 1) {
            std::cout << "\n\n===============Bot Rule===============\nThere are 3 types of bots: simple, normal and complex. The maximum number of bots is 23 (excluding the player and with standard rules of the game with 2 cards for the player and 3 cards on the table). \n1) A simple bot acts completely randomly, does not pass, and only goes all-in if the player does so.\n2) A normal bot calculates the chance of winning based on the cards in hand and the remaining cards in the deck, can pass and go all-in.\n3) A complex bot is a simple AI, can pass and go all-in.\n4) Bots cannot be assigned characters, or have their difficulty changed during the game.\n";
        } if (act == 2) {
            std::cout << "> There are no rules yet.";
        } if (act == 3) {
            std::cout << "> There are no rules yet.";
        } if (act == 4) {
            std::cout << "> There are no rules yet.";
        } if (act == 5) {
            std::cout << "> There are no rules yet.";
        } if (act == 6) {
            std::cout << "> There are no rules yet.";
        } 
    } while (resetGetRule(game));
}


// -------------------  
void Timer::setTimerForGame() { 
    std::cout << "Add Timer\n";
}



// -------------------
void Settings::setGameSettings() {
    std::cout << "Add Settings\n";
}
    

