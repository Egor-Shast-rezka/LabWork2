/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// -------------------------
void GameMode::setupForGameMode() {
    std::cout << "";
}

void GameMode::OutputInfoPlayers() {
    std::cout << "";
}
    
void GameMode::GameModePathGame(std::vector<bool>& DataPass, std::vector<bool>& ifActPlayerData, bool& Allin, int& raund) {
    std::cout << "";
}


// -------------------
void Timer::SetExist(bool ex) {
    
    exist = ex;
}

void Timer::setSecondForTimer(int second) {
    
    seconds = second;
    SetExist(true);
}
    
bool Timer::IsExist() {
    
    return exist;
}
    
void Timer::TimerStart() { 

    // Variable for tracking time
    auto start = std::chrono::steady_clock::now();
    
    system("rm /tmp/timerData");
    system("mkfifo /tmp/timerData");
    
    system("gnome-terminal -- bash -c \"g++ -o bin/start_timer TimerData/main_timer.cpp && ./bin/start_timer bash\"");
    
    // Loop until the specified number of seconds have passed
    while (true) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start;

        // If the specified amount of time has passed, exit the loop
        if (elapsed.count() >= seconds + 1) {
            system("echo \"Timer finished!\" > /tmp/timerData");
            break;
        }

        // Pause for 1 second so that the timer does not load the processor
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Print the remaining time
        std::string command = "echo \"Time left: " + std::to_string(seconds - static_cast<int>(elapsed.count())) + " seconds\" > /tmp/timerData";

        system(command.c_str());
        
    }
    std::cout << "--\nTimer finised, game over.\n";
    exit(0);
}


// -----------------
Game::Game() {}
Game::~Game() {}

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

std::vector<Card>& Game::getAllCardsForTable() {
    return cards;
}

// Function for adding bots
void Game::setBot(std::string name, int index) {
    
    switch(index) {
        case 1:
        
            players.push_back(std::make_unique<AIPlayer_easy>(name));
            break;
    
        case 2:
        
            players.push_back(std::make_unique<AIPlayer_normal>(name));
            break;
            
    }
}

void Game::setPlayerCharacter(std::string name, int index) {
    
    switch(index) {
        case 1:
        
            players.push_back(std::make_unique<AllSeeingPlayer>(name));
            break;
            
        case 2:
        
            players.push_back(std::make_unique<CheaterPlayer>(name));
            break;
            
        case 3:
        
            players.push_back(std::make_unique<EngagedDeckPlayer>(name));
            break;
            
        case 4:
        
            players.push_back(std::make_unique<DeallersFrendPlayer>(name));
            break;
            
        case 5:
        
            players.push_back(std::make_unique<PhotographicMemoryPlayer>(name));
            break;
            
        case 6:
        
            players.push_back(std::make_unique<BettingManipulatorPlayer>(name));
            break;
    }

}

Bank& Game::getBank() {

    return bank;
    
}

bool Game::getCharacter() {

    return Character;
    
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
    bank.setCurrentBet(0);
    bank.setPlayerMoney(0);
    
    for (auto& player : players) {
        player->delAllCards();
    }
    
    std::cout << "\n";
}

bool Game::checkContinueGame() {

    std::string act = contact.answerUserCheckString("Do you want to continue the game? (y/n): ");
    
    while (!(act == "y" || act == "n")){
    
        std::cerr << "ERROR: Write 'y' or 'n'!\n";
        
        act = contact.answerUserCheckString("Do you want to continue the game? (y/n): ");
        
    }

    return act == "y";
}

void Game::setChipsAllPlayer(int count) {
    for (auto& player : players) {
        player->setChips(count);
    }
}

std::string Game::getValidAction(std::vector<std::string> actions, std::string prompt, std::vector<bool> ifActPlayerData, int index) {
            
    std::string action;
                
    while (true) {
                
        action = contact.answerUserCheckString(prompt);
                    
        if (std::find(actions.begin(), actions.end(), action) != actions.end()) {
                    
            if (action == "act" && ifActPlayerData[index]) {
                        
                std::cerr << "ERROR: Player can only use the ability once per round.\n";
                            
            } else {
                        
                return action;
                            
            }
        } else {
                    
            std::cerr << "ERROR: Available actions: ";
                        
            for (const auto& act : actions) {
                        
                std::cerr << act << " ";
                            
            }
                        
            std::cerr << "\n";
        }
    }
}

// Main function to start the game
int Game::startGame() {
    
    // Path game
    do {
        bool Allin = false; // True if somebody make an Allin
        dealler.shuffleDeck(); // The dealer shuffles the deck
        
        // Create vector for allin and pass
        std::vector<bool> DataPass(players.size(), false);
        
        // Array for storing player character actions 
        std::vector<bool> ifActPlayerData(players.size(), false);
        
        // Distribute cards to the players
        for (auto& player : players) {
            dealler.dealCards(2, *player);
        }

        // Output information about players
        gamemode[0]->OutputInfoPlayers();

        // Array with number
        std::vector<std::string> Numbers = { "First", "Second", "Third" };

        for (int raund = 1; raund <= 3; raund++) {
            Card card = dealler.getOneCard(); // Get card from deck
            cards.push_back(card);

            std::cout << "\n> " << Numbers[raund - 1] << " card: ";
            card.display();
            
            gamemode[0]->GameModePathGame(DataPass, ifActPlayerData, Allin, raund);
            
        }

        std::vector<Player> player_refs;
        for (const auto& player : players) {
            player_refs.push_back(*player);
        }
        
        std::vector<int> answer = dealler.SearchWinner(player_refs, cards, DataPass);
        
        for (std::size_t count = 0; count < answer.size(); count++) {
        
            if (answer[count] == 123456) {
                std::cout << "All players make a pass!\n";
            } else if (answer[count] == -2) {
                std::cout << "Player: " << count + 1<< " - " << players[count]->getName() << " make a pass!\n";
            } else if (answer[count] == -3) {
                std::cout << "Player: " << count + 1 << " - " << players[count]->getName() << " fool!\n";
            } else {
                std::cout << "Player: " << count + 1 << " - " << players[count]->getName() << " win!\n";
                players[count]->setChips(players[count]->getChips() + bank.getPlayerMoney());
            }

        }

        resetGame();

    } while (checkContinueGame());

    std::cout << "Game over!\n";
    return 0;
}


void Game::setMode(){
    
    std::cout << "> To open rules, write 'rule'.\n";
    
    // Set Timer
    std::string setTimer = contact.answerUserCheckString("> Do you want to play with Timer? (y/n): ");
    while (!(setTimer == "y" || setTimer == "n")){
    
        std::cerr << "ERROR: Write 'y' or 'n'!\n";
        
        setTimer = contact.answerUserCheckString("> Do you want to play with Timer? (y/n): ");

    }
    
    if (setTimer == "y") {
        
        int second = contact.answerUserCheckInt("> Write the game time (at second): ");
        timer.setSecondForTimer(second);
        
    }
    
    // Set Character for Player
    std::string setCharacter = contact.answerUserCheckString("> Do you want to play with character? (y/n): ");
    while (!(setCharacter == "y" || setCharacter == "n")){
    
        std::cerr << "ERROR: Write integer 'y' or 'n'!\n";
        
        setCharacter = contact.answerUserCheckString("> Do you want to play with character? (y/n): ");

    }
        
    if (setCharacter == "y") {
        Character = true;
    }
    
    // Set game mode
    int modeChoice = contact.answerUserCheckInt("Choose game mode: 1 - AllBots, 2 - OneOnOne.\n> Write name game mode: ");

    while (!(modeChoice == 1 || modeChoice == 2)){
        
        std::cerr << "ERROR: Write integer 1 or 2!\n";
    
        modeChoice = contact.answerUserCheckInt("Choose game mode: 1 - AllBots, 2 - OneOnOne.\n> Write name game mode: ");
        
    } 
    switch(modeChoice) {
        case 1:
        
            gamemode.push_back(std::make_unique<AllBots>(*this));
            break;
            
        case 2:
        
            gamemode.push_back(std::make_unique<OneOnOne>(*this));
            break;
    }
    
    gamemode[0]->setupForGameMode();
    
    // Set count chips
    int answerPlayer = contact.answerUserCheckInt("> Write chips for all player: ");
    
    setChipsAllPlayer(answerPlayer);
    
    std::cout << "Chips has been set.\nGame mode has been set.\n\n========Start Play========\n";
    
    // Set Gmae
    if (timer.IsExist()) {
        
        std::thread timerThread(&Timer::TimerStart, &timer);
        
        startGame();
        
    } else {
    
        startGame();
    }
}


// -------------------
bool Rule::resetGetRule(ContactWithPlayer& contact) {
    std::string answer = contact.answerUserCheckString("> Do you want to know any other rules?(y, n)");
    while (!(answer == "y" || answer == "n")) {
        std::cout << "ERROR: Write 'y' or 'n'\n";
        
        answer = contact.answerUserCheckInt("> Do you want to know any other rules? (y, n)");
    }
    return answer == "y";
}

void Rule::getRuleOnDisplay(ContactWithPlayer& contact) {
    std::cout << "\n\n===============Game Rule===============\n";
    do {
        int act = contact.answerUserCheckInt("> Select the rules you want to know (1-Bot rule, 2-Player rule, 3-Characters rule, 4-Game Rule, 5-Mode Rule, 6-...): ");
        while (!(act == 1 || act == 2 || act == 3 || act == 4 || act == 5 || act == 6)) {
            std::cout << "ERROR: Choise integer in range 1 - 6\n";
        
            act = contact.answerUserCheckInt("> Select the rules you want to know (1-Bot rule, 2-Player rule, 3-Characters rule, 4-Game Rule, 5-Mode Rule, 6-...): ");
        }
    
        if (act == 1) {
            std::cout << "\n\n===============Bot Rule===============\nThere are 2 types of bots: simple, normal. The maximum number of bots is 23 (excluding the player and with standard rules of the game with 2 cards for the player and 3 cards on the table). \n1) A simple bot acts completely randomly, does not pass, and only goes all-in if the player does so.\n2) A normal bot calculates the chance of winning based on the cards in hand and the remaining cards in the deck, can pass and go all-in.\n3) Bots cannot be assigned characters, or have their difficulty changed during the game.\n";
        } if (act == 2) {
            std::cout << "\n\n==============Player Rule=============\n1) In the all bots game mode there is one player who can be one of 6 characters. He can call, allin, act (if it is a character) and pass.\n2) In the one-on-one game mode you can add up to 24 players, each can be given one of 6 characters. They can call, allin, act (if it is a character) and pass.\n";
        } if (act == 3) {
            std::cout << "\n\n===========Characters Rule============\n1) AllSeeingPlayer - Player who can look at any one card of any player.\n2) CheaterPlayer - Player who can replace one of his cards with the first card from the deck, his old card is sent back to the deck in a random place.\n3) EngagedDeckPlayer - Player who can look at the top card of the deck.\n4) DeallersFrendPlayer - Player who can replace the last card put on the table.\n5) PhotographicMemoryPlayer - Player who can look at the remaining cards in the deck.\n6) BettingManipulatorPlayer - Player who can change the current bet.\n";
        } if (act == 4) {
            std::cout << "\n\n==============Game Rule===============\n";
        } if (act == 5) {
            std::cout << "\n\n==============Mode Rule===============\n";
        } if (act == 6) {
            std::cout << "\n\n===============No Rule================\n";
        }
        
    } while (resetGetRule(contact));
    
    std::cout << "=============Exit Game Rule===========\n\n";
}



