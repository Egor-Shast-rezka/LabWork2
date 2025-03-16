/*
    Egor Shastin st129457@student.spbu.ru
    
    This code represents a simulation of a card game, incorporating various classes and methods that handle the game logic. Here's a brief overview:

    > ContactWithPlayer: Contains methods for interacting with the player, ensuring valid input (either integers or strings) and handling player responses, including providing game rules.
    > Card: Represents a playing card, storing information about its number and suit. It includes methods for displaying the card and getting its properties.
    > Deck: Represents a deck of cards, supporting operations like shuffling, dealing cards, and checking the deck's status. It also handles the addition of cards back into the deck.
    > Hand: Represents a player's hand of cards, with methods to add, remove, and display the cards.
    > Bank: Manages the betting system, tracking the current bet and the bets placed by each player.
    > Player: Represents a player, including their name, chips, and hand of cards. Methods are provided for placing bets, displaying player info, and managing cards.
    > Dealler (Dealer): Handles the card dealing process, shuffling the deck, and determining the winner by evaluating the players' hands based on various poker combinations.
    > Hand Evaluation: Methods like PowerHand and search_max_number evaluate the strength of a player's hand by analyzing their cards and returning the hand's ranking.
    
    Overall, this code simulates a card game where players can bet, receive cards, and interact with the game, with a dealer determining the winner based on the hands' strengths.

*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// ===========ContactWithPlayer=============

// Method to check if the given string consists only of digits (0-9). 
bool ContactWithPlayer::isNumber(std::string answer) {
    for (char c : answer) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

// Method to convert a string of digits into an integer. 
int ContactWithPlayer::stringToInt(const std::string& str) {
    int number = 0;
    for (char c : str) {
        number = number * 10 + (c - '0');
    }
    return number;
}

// Method to repeatedly prompt the user for input until a valid non-negative integer is entered.
// The user can also type 'rule' to display the game rules.
int ContactWithPlayer::answerUserCheckInt(std::string value) {
    std::string answer = "";
    
    while (true) {
    
        // Display the prompt and get user's input
        std::cout << value;
        std::cin >> answer;
        
        // If the input is 'rule', show the game rules using the Rule object.
        if (answer == "rule") {
            Rule rule;
            rule.getRuleOnDisplay(*this);
            std::cin.clear();
        } else {
        
            // If the input is not a valid number, show an error and prompt again.
            if (!isNumber(answer)) {
                std::cout << "ERROR: Write an integer!" << std::endl;
                std::cin.clear();
            } else {
            
                // If valid, convert the input to an integer and return it.
                return stringToInt(answer);
            }
        }
    }
    return 0;
}

// Method to prompt the user for input until a valid string (non-numeric) is entered.
// The user can also type 'rule' to display the game rules.
std::string ContactWithPlayer::answerUserCheckString(std::string value) {

    std::string answer = "";
    while (true) {
        // Display the prompt and get user's input
        std::cout << value;
        std::cin >> answer;
        
        // If input is only numeric or fails, show an error message and prompt again.
        if (std::cin.fail() || isNumber(answer)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Write what is required using letters, not only numbers!" << std::endl;
        } else {
            // If the input is 'rule', show the game rules using the Rule object.
            if (answer == "rule") {
                Rule rule;
                rule.getRuleOnDisplay(*this);
                std::cin.clear();
            } else {
                // Return the valid string answer.
                return answer;
            }
        }
    }
    return "";
}

// ===========Card=============

// Constructor to initialize a Card object with a number (rank) and suit.
Card::Card(int num, int val): number(num), suit(val) {}

// Destructor for Card class, currently empty as no special cleanup is needed.
Card::~Card() {}

// Method to set the card's number (rank).
void Card::setNumber(int num) { 
    number = num;
}

// Method to get the card's number (rank).
int Card::getNumber() const { 
    return number;
}

// Method to set the card's suit (hearts, diamonds, etc.).
void Card::setSuit (int value) { 
    suit = value;
}

// Method to get the card's suit.
int Card::getSuit() const { 
    return suit; 
}

// Method to display the card's number (rank) and suit in the console.
void Card::display() const { 
    std::cout << "Number: " << number << ", Suit: " << suit << ".\n";
}

// Overload of the less-than operator (<) to compare two cards. First, it compares by card rank (number), and if they are equal, it compares by suit.
bool Card::operator<(const Card& other) const {
    if (number != other.number) {
        return number < other.number;
    }
    return suit < other.suit;
}

// ===========Deck=============

// Constructor that generates a full deck of cards (52 cards in total). Each card has a suit (1 to 4) and a number (2 to 14).
Deck::Deck() { 
    for (int suit = 1; suit <= 4; suit++) {
        for (int num = 2; num <= 14; num++) { 
            cards.push_back(Card(num, suit));
        }
    }
}

// Destructor for Deck class, currently empty as no special cleanup is needed.
Deck::~Deck() {}

// Method to shuffle the deck of cards using a random number generator.
void Deck::shuffle() { 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

// Method to deal (remove) the last card from the deck and return it.
Card Deck::deal() { 
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the deck!"); 
    } else {
        Card Last_Card = cards.back();
        cards.pop_back();
        return Last_Card;
    }
}

// Method to view the last card in the deck without removing it.
Card Deck::seeLastCard() const {
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the deck!"); 
    } else {
        return cards.back();
    }
}

// Method to insert a card into a random position in the deck.
void Deck::putOneCardInDeck(Card card) { 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, cards.size());
    cards.insert(cards.begin() + distr(gen), card);
}

// Method to retrieve all cards in the deck (returns a reference to the card vector).
std::vector<Card>& Deck::getAllCards() { 
    return cards;
}

// Method to get the total count of remaining cards in the deck.
int Deck::getCountCards() { 
    return static_cast<int>(cards.size());
}

// ===========Hand=============

// Constructor for Hand class, initializing an empty hand.
Hand::Hand() {}

// Destructor for Hand class, currently empty as no special cleanup is needed.
Hand::~Hand() {}

// Method to add a card to the hand.
void Hand::setCards(Card card) { 
    cards.push_back(card);
}

// Method to get the total number of cards in the hand.
int Hand::getCountCards() const { 
    return cards.size();
}

// Method to retrieve all cards in the hand (returns a reference to the card vector).
std::vector<Card>& Hand::getAllCards() { 
    return cards;
}

// Method to display all cards in the hand on the console.
void Hand::getCardsOnDisplay() const { 
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the Hand!"); 
    } else {
        for (std::size_t num = 0; num < cards.size(); num++){
            cards[num].display();
        }
    }
}

// Method to remove the last card from the hand.
void Hand::delLastCard() { 
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the Hand!");
    } else {
        cards.pop_back();
    }
}

// ===========Bank=============

// Constructor for Bank class, initializing the bank.
Bank::Bank() {}

// Destructor for Bank class, currently empty as no special cleanup is needed.
Bank::~Bank() {}

// Method to set the current bet amount.
void Bank::setCurrentBet(int value) {
    CurrentBet = value;
}

// Method to initialize the vector that tracks each player's individual bet.
void Bank::setCountBetEachPlayer(int value) {
    std::vector<int> result(value, 0);
    CountBetEachPlayer = result;
}

// Method to get the current total bet amount in the bank.
int Bank::getCurrentBet() const {
    return CurrentBet;
}

// Method to calculate and return the total money bet by all players.
int Bank::getPlayerMoney() const {
    int result = 0;
    for(int elem : CountBetEachPlayer) {
        result += elem;
    }
    return result;
}

// Method to get the bet amount placed by a specific player, identified by index.
int Bank::getCountBetEachPlayer(int index) const {
    return CountBetEachPlayer[index];
}

// Method to add a specified value to the current total bet in the bank.
void Bank::addCurrentBet(int value) {
    CurrentBet += value;
}

// Method to add a specified value to the bet of an individual player, identified by index.
void Bank::addCountBetEachPlayer(int value, int index) {
    CountBetEachPlayer[index] += value;
}


// ===========Player=============

// Constructor for the Player class, which initializes the player with a given name.
Player::Player(std::string name) : Name(name) {}

// Destructor for the Player class, currently empty as no special cleanup is required.
Player::~Player() {}

// Method to set the player's name to the given value.
void Player::setName(std::string name) {
    Name = name;
}

// Method to display the player's name in the console.
void Player::getNameOnDisplay() const {
    std::cout << "Player name: ";
    for (std::size_t i = 0; i < Name.size(); i++) {
        std::cout << Name[i];
    }
    std::cout << ".\n";
}

// Method to get the player's name as a string.
std::string Player::getName() const {
    return Name;
}

// Method to set the player's chips (amount of in-game currency or points) to a specific number.
void Player::setChips(int num) {
    Chips = num;
}

// Method to display the current number of chips the player has.
void Player::getChipsOnDisplay() const {
    std::cout << "Chips count: " << Chips << ".\n";
}

// Method to get the current number of chips the player has.
int Player::getChips() const {
    return Chips;
}

// Method to subtract a specific number of chips from the player's total, representing placing a bid or bet.
void Player::PlaceBid(int num) {
    Chips -= num;
}

// Method to add a card to the player's hand.
void Player::setCard(Card elem) {
    hand.setCards(elem);
}

// Method to retrieve all cards currently held by the player.
std::vector<Card>& Player::getAllCards() {
    return hand.getAllCards();
}

// Method to display all the cards currently held by the player.
void Player::getCardsOnDisplay() const {
    hand.getCardsOnDisplay();
}

// Method to get the total number of cards currently held by the player.
int Player::getCountCards() const {
    return hand.getCountCards();
}

// Method to remove all cards from the player's hand.
void Player::delAllCards() {
    while (hand.getCountCards() > 0) {
        hand.delLastCard();
    }
}

// Method to check if the player is a bot. By default, this method returns false since the Player class represents a human player.
bool Player::isBot() {
    return false;
}

// Method to define the bot's actions during a game. This method is a placeholder and returns a vector of integers representing possible actions (raise, call, all-in, pass).
std::vector<int> Player::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot) {
    std::vector<int> action(5, 0);
    return action;
}

// Method to check if the player is a character. By default, this method returns false.
bool Player::isCharacter() {
    return false;
}

// Method to define the actions taken by a player who is a character. This method can be customized to handle specific game logic when the player has special abilities.
void Player::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) {
    std::cout << "";
}


// ===========Dealler=============

// Constructor for the Dealer class, initializes the dealer with a new deck of cards.
Dealler::Dealler() {}

// Destructor for the Dealer class, currently empty as no special cleanup is required.
Dealler::~Dealler() {}

// Method to shuffle the deck of cards.
void Dealler::shuffleDeck() {
    deck.shuffle();
}

// Method to deal a specified number of cards to a player.
void Dealler::dealCards(int num, Player& player) {
    if (num <= 0) {
        throw std::out_of_range("It is impossible to issue such a number of cards");
    }
    for (int i = 1; i <= num; i++) {
        Card card = deck.deal();
        player.setCard(card);
    }
}

// Method to draw a single card from the deck.
Card Dealler::getOneCard() {
    return deck.deal();
}

// Method to reset the deck.
void Dealler::newDeck() {
    deck = Deck();
}

// Method to insert a specific card back into the deck at a random position.
void Dealler::putOneCardInDeck(Card card) {
    deck.putOneCardInDeck(card);
}

// Method to retrieve the deck currently held by the dealer.
Deck& Dealler::getDeck() {
    return deck;
}

// the function works like this: it receives the players' hands, already processed by the hand strength function. 
// Then, by index, taking into account whether the player passed or not, it replaces the players' hands with -2 and -3 if they passed or lost respectively, and returns the hand untouched if the player won by the given card index
std::vector<std::vector<int>> Dealler::search_max_number(std::vector<std::vector<int>>& vectors, int index, std::vector<bool>& DataPass) { 

    std::vector<std::vector<int>> answer;
    int max_num = -1;
    int cnt = 0;

    for (std::vector<int>& vect : vectors) {
        if (vect.size() > static_cast<std::size_t>(index) && vect[index] > max_num && !DataPass[cnt]) {
            max_num = vect[index];
        }
        cnt++;
    }

    cnt = 0;

    for (std::vector<int>& vect : vectors) {
        if (DataPass[cnt]) {

            answer.push_back({-2});
        } else if (vect.size() > static_cast<std::size_t>(index) && vect[index] == max_num) {

            answer.push_back(vect);
        } else {

            answer.push_back({-3});
        }
        cnt++;
    }

    return answer;
}


std::vector<int> Dealler::PowerHand(std::vector<Card> allCardsPlayer) {
    
    int CardsCount = static_cast<int>(allCardsPlayer.size());
    // Matching a set of cards with 5 numbers, where 1 is the number of cards of one rank, and the other 4 are all possible suits
    std::vector<int> result = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    for (auto& card : allCardsPlayer) {
        result[card.getNumber() - 1] += 10000;
        result[card.getNumber() - 1] += pow(10, (card.getSuit() - 1));
    }

    // Search for lucky hands

    // Flash presence (search through five)
    int seekFlash = 0;

    // The presence of these card combinations
    int Flash = 0;
    int Street = 0;
    int Roal = 0;

    // Index designation: 0 - cards that appear 1 time. 1 - number of pairs of cards. 2 - number of threes. 3 - number of fours.
    std::vector<int> resultCountPair = {0, 0, 0, 0};
        
    for (int& elem : result) {
        if (elem != 0) {
            seekFlash += elem;
            elem /= 10000;
            resultCountPair[elem - 1] += 1;
        }
    }

    int index = 0; // Variable points to the number of 4 in seekFlash
    while (seekFlash > 0) {
        int digit = seekFlash % 10;
        if (digit == 5) {
            index++;
        }
        seekFlash /= 10;
    }
    if (index == 2) { // If there are 2 fours, then one is the number of cards, and 2 is 4 of the same suit, that is, a flush
        Flash++;
    }

    if (result[1] != 0 && result[2] != 0 && result[3] != 0 && result[4] != 0 && result[13] != 0) { // Street check
        Street++;
    }

    if (result[9] != 0 && result[10] != 0 && result[11] != 0 && result[12] != 0 && result[13] != 0) { // Check for a roal
        Roal++;
    }

    index = 1; // This variable now indicates the power of the hand
    
    // Search for all possible 10 lucky hands, where 1 is the high card, 10 is a royal flush
    if (resultCountPair[1] == 1) {
        index = 2;
    }
    if (resultCountPair[1] == 2) {
        index = 3;
    }
    if (resultCountPair[2] == 1) {
        index = 4;
    }
    if (resultCountPair[1] == 1 && resultCountPair[2] == 1) {
        index = 7;
    }
    if (resultCountPair[3] == 1) {
        index = 8;
    }
    if (Street == 1) {
        index = 5;
    }
    if (Flash == 1) {
        index = 6;
    }
    if (Street == 1 and Flash == 1) {
        index = 9;
    }
    if (Roal == 1 and Flash == 1) {
        index = 10;
    }
            
    // Checking the highest cards in case of a combination match
    std::vector<int> hand = {index};
        
    for (int i = 0; i < CardsCount; i++) {
        hand.push_back(0);
    }
        
    int cnt = 13;
    int count = 1;
    while (cnt > 0 && hand[CardsCount] == 0) {
        if (result[cnt] != 0) {
            if (result[cnt] > 15) {
                result[cnt] /= 10000;
            }
            hand[count] = cnt + 1;
            count++;
            result[cnt]--;
        } else {
            cnt--;
        }
    }
    
    return hand;
}

std::vector<int> Dealler::SearchWinner(std::vector<Player>& players, std::vector<Card>& cards, std::vector<bool>& DataPass) { // Search for a winner
    std::vector<int> answer; // Final number of winning players
    std::vector<std::vector<int>> handPlayers; // List of cards in players hands
    int cntPass = 0;
    
    std::size_t CountCard = cards.size();
    int CardsCount = static_cast<int>(CountCard) + players[0].getCountCards();
    
    for (std::size_t i = 0; i < players.size(); i++) {

        if (DataPass[i]) {
            cntPass++;
        } 
        
        std::vector<Card> allCardsPlayer = players[i].getAllCards(); // Getting all player cards
        allCardsPlayer.insert(allCardsPlayer.end(), cards.begin(), cards.end()); // Mixing cards on the table and cards in the player's hand
            
        handPlayers.push_back(PowerHand(allCardsPlayer));
        }
    
    // If all players make a pass
    if (cntPass == static_cast<int>(players.size())) {
        return {123456};
    }
    
    for (std::vector<int> vect : handPlayers) {
        
        std::cout << "Hand power: ";
        for (auto& elem : vect) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    
    // Finding a winner, taking into account high cards and combinations
    int cnt = 0;
    while (cnt < CardsCount) {
        handPlayers = search_max_number(handPlayers, cnt, DataPass);
        cnt++;
    }

    // Create a list of winners
    for (std::size_t i = 0; i < handPlayers.size(); i++) {

        if (static_cast<int>(handPlayers[i].size()) == CardsCount + 1) {
        
            answer.push_back(i + 1);
            
        } if (handPlayers[i][0] == -2) {
        
            answer.push_back(-2);
            
        } if (handPlayers[i][0] == -3) {
        
            answer.push_back(-3);
        }
    }
    
    std::cout << "\n";

    return answer;
}

