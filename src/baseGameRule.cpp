/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// ---------------------------
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


// -----------------------------
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

void Deck::putOneCardInDeck(Card card) {

     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<> distr(0, cards.size());

     cards.insert(cards.begin() + distr(gen), card);

}
    
    
// -----------------------------
Hand::Hand() {};
Hand::~Hand() {};

void Hand::setCards(Card card) { // Add Card in hand
    cards.push_back(card);
}

int Hand::getCountCards() const{ // Show count card in hand
    return cards.size();
}

std::vector<Card> Hand::getAllCards() const { // Show all card in hand
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


// -------------------------
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

std::vector<Card> Player::getAllCards() const {
    return hand.getAllCards();
}

void Player::getCardsOnDisplay() const { // Get cards in hand on display
    hand.getCardsOnDisplay();
}

int Player::getCountCards() const { // Get count card in head
    return hand.getCountCards();
}

void Player::delAllCards() { // Delete all cards after end play
    if (hand.getCountCards() == 0) {
        throw std::out_of_range("No cards in the hand!"); // Error if in hand none card
    }
    else {
        for (int i = 0; i <= hand.getCountCards(); i++) {
            hand.delLastCard();
        }
    }
}

bool Player::isBot() {
    return false;
}

int Player::BotActions(int countChips, int currentBet, int Bank, int Allin) {
    return 0;
}

bool Player::isCharacter(){
    return false;
}

Card Player::CharacterActions(std::vector<std::unique_ptr<Player>>& players, std::vector<Card> cardsOnTable, std::vector<Card> cardsByDealler, int player, int card) {
    Card empty(1, 1);
    return empty;
}


//----------------------
std::vector<std::vector<int>> search_max_number(std::vector<std::vector<int>>& vectors, int index) {
    std::vector<std::vector<int>> answer;
    int max_num = -1;

    for (std::vector<int>& vect : vectors) {
        if (vect.size() > static_cast<std::size_t>(index) && vect[index] > max_num) {
            max_num = vect[index];
        }
    }

    for (std::vector<int>& vect : vectors) {
        if (vect.size() > static_cast<std::size_t>(index) && vect[index] == max_num) {
            answer.push_back(vect);
        }
        else {
            answer.push_back({ });
        }
    }

    return answer;
}


// ------------------------
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

void Dealler::newDeck() {
    deck = Deck();
}

Card Dealler::seeLastCard() const { // See last card for Engaged deck
    return deck.seeLastCard();
}

void Dealler::putOneCardInDeck(Card card) { // Put one card in deck for CheaterPlayer
    deck.putOneCardInDeck(card);
}

std::vector<int> Dealler::SearchWinner(std::vector<Player>& players, std::vector<Card>& cards, std::vector<int>& DataPass) const { // Search for a winner
    std::vector<int> answer; // Final number of winning players
    std::vector<std::vector<int>> handPlayer; // List of cards in players hands
    int cntPass = 0;
    
    std::size_t CountCard = cards.size();
    int CardsCount = static_cast<int>(CountCard) + players[0].getCountCards();
    
    for (std::size_t i = 0; i < players.size(); i++) {
        
        if (DataPass[i] == 1) {
        
            std::vector<int> hand;
            for (int i = 0; i <= CardsCount; i++) {
                hand.push_back(0);
            }
            
            handPlayer.push_back(hand);
            cntPass++;
            
            // For checking
            std::cout << "Player " << i+1 << " passed.\n";
            
        } else {
        
            std::vector<Card> allCardsPlayer = players[i].getAllCards(); // Getting all player cards
            allCardsPlayer.insert(allCardsPlayer.end(), cards.begin(), cards.end()); // Mixing cards on the table and cards in the player's hand
    
            // Matching a set of cards with 5 numbers, where 1 is the number of cards of one rank, and the other 4 are all possible suits
            std::vector<int> result = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
            for (auto& card : allCardsPlayer) {
                result[card.getNumber() - 1] += 10000;
                result[card.getNumber() - 1] += pow(10, (card.getSuit() - 1));
            }

            // Search for lucky hands

            // Flash presence (search through fours)
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
                if (digit == 4) {
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
                }
                else {
                    cnt--;
                }
            }
            handPlayer.push_back(hand);
            
            // For checking
            std::cout << "Player " << i+1 << ": Power Hand: ";
            for (int& elem : hand) {
                std::cout << elem << " ";
            }
            std::cout << "\n";

        }
    }
    
    // If all players make a pass
    if (cntPass == static_cast<int>(players.size())) {
        return {123456};
    }
    
    // Finding a winner, taking into account high cards and combinations
    int cnt = 0;
    while (cnt < CardsCount) {
        handPlayer = search_max_number(handPlayer, cnt);
        cnt++;
    }

    // Create a list of winners
    for (std::size_t i = 0; i < handPlayer.size(); i++) {
        if (handPlayer[i].size() != 0) {
            answer.push_back(i + 1);
        }
    }

    return answer;
}


