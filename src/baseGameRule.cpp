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

// Method to check if it is a number or not
bool ContactWithPlayer::isNumber(std::string answer) {
    for (char c : answer) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

// Method to convert string to int
int ContactWithPlayer::stringToInt(const std::string& str) {
    int number = 0;
    for (char c : str) {
        number = number * 10 + (c - '0');
    }
    return number;
}

// Method to check if the player's answer is a non-negative integer or 'rule'
int ContactWithPlayer::answerUserCheckInt(std::string value) {
    std::string answer = "";
    
    while (true) {
        
        // Get players answer
        std::cout << value;
        std::cin >> answer;
        
        // If player write 'rule' return obj Rule
        if (answer == "rule") {
            
            Rule rule;
            rule.getRuleOnDisplay(*this);
            std::cin.clear();
        } else {
            
            // Check players answer
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

// Method to check if the player's answer is a string or 'rule'
std::string ContactWithPlayer::answerUserCheckString(std::string value) {

    std::string answer = "";
    while (true) {
        
        // Get players answer
        std::cout << value;
        std::cin >> answer;
        
        // Check players answer
        if (std::cin.fail() || answer.empty() || isNumber(answer)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Write what is required using letters, not only numbers!" << std::endl;
        } else {
            
            // If player write 'rule' return obj Rule
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


// ===========Card=============

Card::Card(int num, int val): number(num), suit(val){}
Card::~Card() {}

void Card::setNumber(int num) { // Set number
    number = num;
}

int Card::getNumber() const { // Get number
    return number;
}

void Card::setSuit (int value) { // Set suit
    suit = value;
}

int Card::getSuit() const { // Get Suit
    return suit; 
}

void Card::display() const { // Show Card on screen
    std::cout << "Number: " << number << ", Suit: " << suit << ".\n";
}


// ===========Deck=============

Deck::Deck() { // Generate all cards
    for (int suit = 1; suit <= 4; suit++) {
        for (int num = 2; num <= 14; num++) { 
            cards.push_back(Card(num, suit));
        }
    }
}
Deck::~Deck() {}

void Deck::shuffle() { // Shuffle cards in deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::deal() { // Take one card from deck
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the deck!"); // Error if in deck none cards
    }
    else {
        Card Last_Card = cards.back();
        cards.pop_back();
        return Last_Card;
    }
}

Card Deck::seeLastCard() const {
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the deck!"); // Error if in deck none cards
    }
    else {
        return cards.back();
    }
}

void Deck::putOneCardInDeck(Card card) {  // Put one card in deck for CheaterPlayer

     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<> distr(0, cards.size());

     cards.insert(cards.begin() + distr(gen), card);

}
    
std::vector<Card>& Deck::getAllCards() { // Get all cards
    return cards;
}

int Deck::getCountCards() { // Get count cards
    return static_cast<int>(cards.size());
}
    
// ===========Hand=============

Hand::Hand() {};
Hand::~Hand() {};

void Hand::setCards(Card card) { // Add Card in hand
    cards.push_back(card);
}

int Hand::getCountCards() const{ // Show count card in hand
    return cards.size();
}

std::vector<Card>& Hand::getAllCards() { // Show all card in hand
    return cards;
}

void Hand::getCardsOnDisplay() const { // Show all card in hand on display
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the Hand!"); // Error if in hand none cards
    } 
    else {
        for (std::size_t num = 0; num < cards.size(); num++){
            cards[num].display();
        }
    }
}

void Hand::delLastCard() { // Remove last card
    if (cards.size() == 0) {
        throw std::out_of_range("No cards left in the Hand!");
    }
    else {
        cards.pop_back();
    }
}


// ===========Bank=============

Bank::Bank() {}
Bank::~Bank() {}

// Set for Bank
void Bank::setCurrentBet(int value) {
    CurrentBet = value;
}

void Bank::setCountBetEachPlayer(int value) {
    
    std::vector<int> result(value, 0);
    CountBetEachPlayer = result;
}
    
// Get for Bank
int Bank::getCurrentBet() const {
    return CurrentBet;
}
    
int Bank::getPlayerMoney() const {
    
    int result = 0;
    for(int elem : CountBetEachPlayer) {
        result += elem;
    }
    return result;
}

int Bank::getCountBetEachPlayer(int index) const {
    return CountBetEachPlayer[index];
}

// Add for Bank    
void Bank::addCurrentBet(int value) {
    CurrentBet += value;
}

void Bank::addCountBetEachPlayer(int value, int index) {
    CountBetEachPlayer[index] += value;
}


// ===========Player=============

Player::Player(std::string name) : Name(name) {}
Player::~Player() {}

void Player::setName(std::string name) { // Set Name
    Name = name;
}

void Player::getNameOnDisplay() const { // Get Name on display
    std::cout << "Player name: ";
    for (std::size_t i = 0; i < Name.size(); i++) {
        std::cout << Name[i];
    }
    std::cout << ".\n";
}

std::string Player::getName() const { // Get Name
    return Name;
}

void Player::setChips(int num) { // Set deb
    Chips = num;
}

void Player::getChipsOnDisplay() const { //Get Chips
    std::cout << "Chips count: " << Chips << ".\n";
}

int Player::getChips() const { //Get Chips
    return Chips;
}

void Player::PlaceBid(int num) { // Make a bed
    Chips -= num;
}

void Player::setCard(Card elem) { // Set Card
    hand.setCards(elem);
}

std::vector<Card>& Player::getAllCards() { // Get all cards
    return hand.getAllCards();
}

void Player::getCardsOnDisplay() const { // Get cards in hand on display
    hand.getCardsOnDisplay();
}

int Player::getCountCards() const { // Get count card in head
    return hand.getCountCards();
}

void Player::delAllCards() {// Delete all cards 

    while (hand.getCountCards() > 0) {
    
        hand.delLastCard();
    }
}

bool Player::isBot() { // Check to player is bot

    return false;
}

std::vector<int> Player::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot){ // Bot Actions if player its bot 
    
    std::vector<int> action(5, 0);
    
    return action;
}

bool Player::isCharacter(){ // Check to player is character

    return false;
}

void Player::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card>& cardsOnTable, Deck& deck, Bank& bank, int indexPlayer) { // Bot Actions if player its character

    std::cout << "";
}


// ===========Dealler=============

Dealler::Dealler() {}
Dealler::~Dealler() {}

void Dealler::shuffleDeck() { // Shuffer deck
    deck.shuffle();
}

void Dealler::dealCards(int num, Player& player) { // Issuing 'num' cards to a player
    if (num <= 0) {
        throw std::out_of_range("It is impossible to issue such a number of cards");
    }
    for (int i = 1; i <= num; i++) {
        Card card = deck.deal();
        player.setCard(card);
    }
}

Card Dealler::getOneCard() { // Drawing a card from the deck
    return deck.deal();
}

void Dealler::newDeck() { // Dealler get new deck if reset game and is nothing in deck
    deck = Deck();
}

void Dealler::putOneCardInDeck(Card card) { // Put one card in deck for CheaterPlayer
    deck.putOneCardInDeck(card);
}


Deck& Dealler::getDeck() { // Get deck 
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

