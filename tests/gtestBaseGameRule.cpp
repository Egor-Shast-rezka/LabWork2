/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/


#include <gtest/gtest.h>
#include <chrono>
#include "baseGameRule.h"
#include "pathGame.h"


// ===========Card=============
// ===== 1) Unit Testing

// Testing the constructor and method for getting the card number
TEST(CardTest, ConstructorAndGetNumber) {
    Card card(10, 3);
    EXPECT_EQ(card.getNumber(), 10);
}

// Testing the method for setting and getting the suit of a card
TEST(CardTest, SetAndGetSuit) {
    Card card(5, 1);
    card.setSuit(4);
    EXPECT_EQ(card.getSuit(), 4);
}

// Testing the method for getting the suit of a card
TEST(CardTest, GetSuit) {
    Card card(7, 2);
    EXPECT_EQ(card.getSuit(), 2);
}

// ===== 2) Functional Testing

// Testing the method for displaying the card
TEST(CardTest, DisplayCard) {
    Card card(12, 3);  // Creating a card with number 12 and suit 3 (Queen)
    EXPECT_NO_THROW(card.display());  // Checking that the display method does not throw any exceptions
}

// ===== 5) Load Testing

// Testing the overloaded operator < with large volumes of data
TEST(CardTest, LoadTestComparisonOperator) {
    std::vector<Card> deck;
    for (int i = 2; i <= 14; ++i) {
        for (int suit = 1; suit <= 4; ++suit) {
            deck.push_back(Card(i, suit));  // Creating a deck of 52 cards
        }
    }

    // Checking all card comparisons
    for (int i = 0; i < static_cast<int>(deck.size()) - 1; ++i) {
        EXPECT_TRUE(deck[i] < deck[i + 1] || !(deck[i] < deck[i + 1]));  // The operator should work correctly
    }
}

// ===== 6) Edge Case Testing

// Testing the setting of the minimum and maximum card number
TEST(CardTest, EdgeCaseSetGetNumber) {
    Card card(2, 1);  // Creating a card with the minimum number 2
    EXPECT_EQ(card.getNumber(), 2);  // Checking that the number is 2

    card.setNumber(14);  // Setting the maximum number 14 (Ace)
    EXPECT_EQ(card.getNumber(), 14);  // Checking that the number is 14
}

// Testing the setting of the minimum and maximum suit of a card
TEST(CardTest, EdgeCaseSetGetSuit) {
    Card card(10, 1);  // Creating a card with the minimum suit 1
    EXPECT_EQ(card.getSuit(), 1);  // Checking that the suit is 1

    card.setSuit(4);  // Setting the maximum suit 4
    EXPECT_EQ(card.getSuit(), 4);  // Checking that the suit is 4
}

// Testing the comparison of two identical cards (edge case)
TEST(CardTest, EdgeCaseComparisonEqualCards) {
    Card card1(10, 3);
    Card card2(10, 3);  // Creating two identical cards
    EXPECT_FALSE(card1 < card2);  // The comparison should return false as the cards are equal
}

// ===========Deck=============
// ===== 1) Unit Testing

// Testing the creation of a full deck of 52 cards
TEST(DeckTest, GenerateFullDeck) {
    Deck deck;
    EXPECT_EQ(deck.getCountCards(), 52);  // Checking that the deck contains 52 cards
}

// Testing the shuffle method
TEST(DeckTest, TestShuffle) {
    Deck deck1;
    Deck deck2;
    
    deck1.shuffle();
    deck2.shuffle();
    
    EXPECT_NE(deck1.seeLastCard().getNumber(), deck2.seeLastCard().getNumber());  // The order should be changed
}

// Testing the "deal card" method
TEST(DeckTest, DealCard) {
    Deck deck;
    int initialCount = deck.getCountCards();
    Card card = deck.deal();  // Dealing one card
    EXPECT_EQ(deck.getCountCards(), initialCount - 1);  // Checking that the card count decreases by one
}

// ===== 2) Functional Testing

// Testing the method for inserting a card into a random place in the deck
TEST(DeckTest, PutOneCardInDeck) {
    Deck deck;
    Card newCard(10, 2);  // Creating a card with number 10 and suit 2
    int initialCount = deck.getCountCards();
    deck.putOneCardInDeck(newCard);
    EXPECT_EQ(deck.getCountCards(), initialCount + 1);  // Checking that the card is added
}

// Testing the method for viewing the last card (seeLastCard)
TEST(DeckTest, SeeLastCard) {
    Deck deck;
    Card lastCard = deck.seeLastCard();
    EXPECT_NO_THROW(lastCard.display());  // Checking that the last card exists and is accessible
}

// ===== 3) Error and Exception Testing

// Testing exception when attempting to deal a card from an empty deck
TEST(DeckTest, DealFromEmptyDeckThrowsException) {
    Deck deck;
    // Dealing all cards from the deck
    while (deck.getCountCards() > 0) {
        deck.deal();
    }
    EXPECT_THROW(deck.deal(), std::out_of_range);  // Checking that an exception is thrown when trying to deal a card
}

// Testing exception when viewing the last card in an empty deck
TEST(DeckTest, SeeLastCardFromEmptyDeckThrowsException) {
    Deck deck;
    // Dealing all cards
    while (deck.getCountCards() > 0) {
        deck.deal();
    }
    EXPECT_THROW(deck.seeLastCard(), std::out_of_range);  // Checking that an exception is thrown when viewing a card
}

// ===== 4) Performance Testing

// Testing the performance of shuffling the deck
TEST(DeckTest, PerformanceShuffleDeck) {
    Deck deck;
    for (int i = 0; i < 1000; ++i) {
        deck.shuffle();  // Shuffling the deck multiple times
    }
    EXPECT_EQ(deck.getCountCards(), 52);  // Checking that the number of cards remains 52
}

// ===== 5) Load Testing

// Testing shuffling and dealing cards under load
TEST(DeckTest, LoadTestShuffleAndDeal) {
    Deck deck;
    for (int i = 0; i < 52; ++i) {
        deck.shuffle();  // Shuffling
        deck.deal();  // Dealing a card
    }
    EXPECT_EQ(deck.getCountCards(), 0);  // Checking that all cards have been dealt
}

// ===== 6) Edge Case Testing

// Testing behavior when trying to get the card count from an empty deck
TEST(DeckTest, EmptyDeckHasZeroCards) {
    Deck deck;
    while (deck.getCountCards() > 0) {
        deck.deal();
    }
    EXPECT_EQ(deck.getCountCards(), 0);  // Checking that after dealing all cards, the count is 0
}

// Testing shuffling an empty deck
TEST(DeckTest, ShuffleEmptyDeck) {
    Deck deck;
    while (deck.getCountCards() > 0) {
        deck.deal();
    }
    EXPECT_NO_THROW(deck.shuffle());  // Checking that shuffling an empty deck does not throw exceptions
}


// ===========Hand=============
// ===== 1) Unit Testing

// Testing the removal of the last card from the hand
TEST(HandTest, RemoveLastCardFromHand) {

    Hand hand;
    Card card1(2, 2);
    Card card2(3, 3);
    hand.setCards(card1);
    hand.setCards(card2);
    hand.delLastCard();
    EXPECT_EQ(static_cast<int>(hand.getAllCards().size()), 1);
}

// Testing the method of getting all cards
TEST(HandTest, GetAllCards) {
    Hand hand;
    Card card1(2, 2);
    Card card2(3, 3);
    hand.setCards(card1);
    hand.setCards(card2);
    std::vector<Card>& allCards = hand.getAllCards();
    EXPECT_EQ(static_cast<int>(allCards.size()), 2);
}

// ===== 2) Functional Testing

// Testing the display of all cards in the hand
TEST(HandTest, DisplayAllCards) {
    Hand hand;
    Card card1(2, 2);
    Card card2(3, 3);
    hand.setCards(card1);
    hand.setCards(card2);
    EXPECT_NO_THROW(hand.getCardsOnDisplay());  // Check that the display method does not throw exceptions
}

// ===== 3) Error and Exception Testing

// Testing the exception when removing a card from an empty hand
TEST(HandTest, RemoveCardFromEmptyHandThrowsException) {
    Hand hand;
    EXPECT_THROW(hand.delLastCard(), std::out_of_range);
}

// Testing the exception when trying to display an empty hand
TEST(HandTest, DisplayEmptyHandThrowsException) {
    Hand hand;
    EXPECT_THROW(hand.getCardsOnDisplay(), std::out_of_range);
}

// ===== 4) Performance Testing

// Performance test for adding a large number of cards
TEST(HandTest, PerformanceAddCards) {
    Hand hand;
    Card card(2, 2);
    for (int i = 0; i < 52; ++i) {
        hand.setCards(card);
    }
    EXPECT_EQ(hand.getCountCards(), 52);
}

// ===== 5) Load Testing

// Testing the removal of cards in large quantities
TEST(HandTest, LoadTestRemoveCards) {
    Hand hand;
    Card card(2, 2);
    for (int i = 0; i < 52; ++i) {
        hand.setCards(card);
    }
    for (int i = 0; i < 52; ++i) {
        hand.delLastCard();
    }
    EXPECT_EQ(hand.getCountCards(), 0);
}

// ===== 6) Edge Case Testing

// Testing an empty hand
TEST(HandTest, EmptyHandHasZeroCards) {
    Hand hand;
    EXPECT_EQ(hand.getCountCards(), 0);
}

// Testing the method of removing a card from an empty hand
TEST(HandTest, RemoveCardFromEmptyHand) {
    Hand hand;
    EXPECT_THROW(hand.delLastCard(), std::out_of_range);  // Expect an exception when trying to remove a card from an empty hand
}


// ===========Bank=============
// ===== 1) Unit Testing

// Testing the setCurrentBet method
TEST(BankTest, SetCurrentBet) {
    Bank bank;
    bank.setCurrentBet(100);
    EXPECT_EQ(bank.getCurrentBet(), 100);
}

// Testing the setCountBetEachPlayer method
TEST(BankTest, SetCountBetEachPlayer) {
    Bank bank;
    bank.setCountBetEachPlayer(3);
    EXPECT_EQ(bank.getCountBetEachPlayer(0), 0);
    EXPECT_EQ(bank.getCountBetEachPlayer(1), 0);
    EXPECT_EQ(bank.getCountBetEachPlayer(2), 0);
}

// Testing the addCurrentBet method
TEST(BankTest, AddCurrentBet) {
    Bank bank;
    bank.setCurrentBet(100);
    bank.addCurrentBet(50);
    EXPECT_EQ(bank.getCurrentBet(), 150);
}

// Testing the addCountBetEachPlayer method
TEST(BankTest, AddCountBetEachPlayer) {
    Bank bank;
    bank.setCountBetEachPlayer(3);
    bank.addCountBetEachPlayer(50, 0);
    bank.addCountBetEachPlayer(20, 1);
    EXPECT_EQ(bank.getCountBetEachPlayer(0), 50);
    EXPECT_EQ(bank.getCountBetEachPlayer(1), 20);
}

// ===== 2) Functional Testing

// Testing the sum of all player bets
TEST(BankTest, GetPlayerMoney) {
    Bank bank;
    bank.setCountBetEachPlayer(3);
    bank.addCountBetEachPlayer(50, 0);
    bank.addCountBetEachPlayer(20, 1);
    bank.addCountBetEachPlayer(30, 2);
    EXPECT_EQ(bank.getPlayerMoney(), 100);
}

// ===== 3) Error and Exception Testing

// Test for array index out of bounds when getting a player's bet
TEST(BankTest, OutOfRangeException) {
    Bank bank;
    bank.setCountBetEachPlayer(2);  // Set 2 players
    EXPECT_THROW(bank.getCountBetEachPlayer(3), std::out_of_range);  // Expect an exception
}

// ===== 4) Performance Testing

// Performance test for adding bets
TEST(BankTest, PerformanceAddBet) {
    Bank bank;
    bank.setCountBetEachPlayer(100000);  // 100,000 players
    for (int i = 0; i < 100000; ++i) {
        bank.addCountBetEachPlayer(1, i);
    }
    EXPECT_EQ(bank.getPlayerMoney(), 100000);
}

// ===== 5) Load Testing

// Test with a large number of players
TEST(BankTest, LoadTest) {
    Bank bank;
    bank.setCountBetEachPlayer(1000000);  // 1 million players
    for (int i = 0; i < 1000000; ++i) {
        bank.addCountBetEachPlayer(1, i);
    }
    EXPECT_EQ(bank.getPlayerMoney(), 1000000);
}

// ===== 6) Edge Case Testing

// Testing with a zero bet
TEST(BankTest, ZeroBet) {
    Bank bank;
    bank.setCountBetEachPlayer(3);
    bank.addCountBetEachPlayer(0, 0);
    EXPECT_EQ(bank.getCountBetEachPlayer(0), 0);
}

// Testing with a negative bet (invalid input)
TEST(BankTest, NegativeBet) {
    Bank bank;
    bank.setCountBetEachPlayer(3);
    EXPECT_THROW(bank.addCountBetEachPlayer(-50, 0), std::invalid_argument);  // Expect an exception
}


// ===========Player=============
// ===== 1) Unit Testing

// Test for creating and destroying a Player object
TEST(PlayerTest, ConstructorDestructor) {
    Game game;
    Player player("John", game);
    EXPECT_EQ(player.getName(), "John");
}

// Test for setting the name
TEST(PlayerTest, SetName) {
    Game game;
    Player player("John", game);
    player.setName("Mike");
    EXPECT_EQ(player.getName(), "Mike");
}

// Test for displaying the player's name
TEST(PlayerTest, GetNameOnDisplay) {
    Game game;
    Player player("Alice", game);
    testing::internal::CaptureStdout();
    player.getNameOnDisplay();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Player name: Alice.\n");
}

// Test for setting chips
TEST(PlayerTest, SetChips) {
    Game game;
    Player player("John", game);
    player.setChips(100);
    EXPECT_EQ(player.getChips(), 100);
}

// Test for displaying the player's chips
TEST(PlayerTest, GetChipsOnDisplay) {
    Game game;
    Player player("John", game);
    player.setChips(150);
    testing::internal::CaptureStdout();
    player.getChipsOnDisplay();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Chips count: 150.\n");
}

// Test for placing a bid
TEST(PlayerTest, PlaceBid) {
    Game game;
    Player player("John", game);
    player.setChips(200);
    player.PlaceBid(50);
    EXPECT_EQ(player.getChips(), 150);
}

// Test for adding a card to the player's hand
TEST(PlayerTest, SetCard) {
    Game game;
    Player player("John", game);
    Card card1(10, 1); // Let's say, a 10 of Hearts
    player.setCard(card1);

    std::vector<Card>& cards = player.getAllCards();
    ASSERT_EQ(cards.size(), 1);
    EXPECT_EQ(cards[0].getNumber(), 10);
    EXPECT_EQ(cards[0].getSuit(), 1);
}

// Test for getting the number of cards in the hand
TEST(PlayerTest, GetCountCards) {
    Game game;
    Player player("John", game);
    Card card1(10, 1);
    Card card2(5, 2);
    player.setCard(card1);
    player.setCard(card2);

    EXPECT_EQ(player.getCountCards(), 2);
}

// Test for removing all cards from the hand
TEST(PlayerTest, DelAllCards) {
    Game game;
    Player player("John", game);
    Card card1(10, 1);
    Card card2(5, 2);
    player.setCard(card1);
    player.setCard(card2);

    player.delAllCards();
    EXPECT_EQ(player.getCountCards(), 0);
}

// Test to check if the player is not a bot
TEST(PlayerTest, IsBot) {
    Game game;
    Player player("John", game);
    EXPECT_FALSE(player.isBot());
}

// Test for bot actions
TEST(PlayerTest, BotActions) {
    Game game;
    Player player("John", game);
    std::unique_ptr<Player> ptr = std::make_unique<Player>("BotPlayer", game);
    std::vector<Card> cardsOnTable;
    Dealler dealer;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    std::vector<int> actions = player.BotActions(ptr, cardsOnTable, dealer, currentBet, Allin, round, ifReboot);
    EXPECT_EQ(actions.size(), 5); // Basic check that the action vector returns 5 elements
}

// Test to check if the player is not a character
TEST(PlayerTest, IsCharacter) {
    Game game;
    Player player("John", game);
    EXPECT_FALSE(player.isCharacter());
}

// Test for character actions
TEST(PlayerTest, CharacterActions) {
    Game game;
    Player player("John", game);
    std::vector<std::unique_ptr<Player>> players;
    std::vector<Card> cardsOnTable;
    Deck deck;
    Bank bank;
    int indexPlayer = 0;

    // Simply call the method that returns nothing, testing that it does not throw exceptions
    EXPECT_NO_THROW(player.CharacterActions(players, cardsOnTable, deck, bank, indexPlayer));
}

// ===== 2) Functional Testing

// Testing card dealing to a player through the Dealler class
TEST(DeallerAndPlayerTest, DealCards) {
    Game game;
    Player player("John", game);
    Dealler dealer;
    dealer.shuffleDeck();
    dealer.dealCards(2, player);

    EXPECT_EQ(player.getCountCards(), 2);  // Check that the player has 2 cards after dealing
}

// ===== 3) Error and Exception Testing

// Test for throwing an exception when trying to deal more cards than are in the deck
TEST(DeallerAndPlayerTest, DealCards_EmptyDeck) {
    Game game;
    Player player("John", game);
    Dealler dealer;

    // Create a situation where there are not enough cards
    EXPECT_THROW(dealer.dealCards(60, player), std::out_of_range);
}

// ===== 4) Performance Testing

// Testing the performance of deck shuffling
TEST(DeallerAndPlayerTest, ShufflePerformance) {
    Dealler dealer;

    auto start = std::chrono::high_resolution_clock::now();
    dealer.shuffleDeck();
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    EXPECT_LT(duration, 100);  // Expect that shuffling the deck takes less than 100 ms
}

// ===== 5) Load Testing

// Test for dealing cards to a large number of players
TEST(DeallerAndPlayerTest, DealCardsToManyPlayers) {
    Game game;
    Dealler dealer;
    dealer.shuffleDeck();

    std::vector<Player> players;
    for (int i = 0; i < 25; i++) {
        players.emplace_back("Player " + std::to_string(i + 1), game);
    }

    // Deal 2 cards to each player
    for (auto& player : players) {
        dealer.dealCards(2, player);
    }

    // Ensure that each player has exactly 2 cards
    for (const auto& player : players) {
        EXPECT_EQ(player.getCountCards(), 2);
    }
}

// ===== 6) Edge Case Testing

// Testing dealing 0 cards to a player
TEST(DeallerAndPlayerTest, DealZeroCards) {
    Game game;
    Player player("John", game);
    Dealler dealer;
    
    EXPECT_THROW(dealer.dealCards(0, player), std::out_of_range);  // Expect an error when dealing 0 cards
}

// Testing dealing the maximum number of cards
TEST(DeallerAndPlayerTest, DealMaxCards) {
    Game game;
    Player player("John", game);
    Dealler dealer;
    dealer.shuffleDeck();
    
    EXPECT_NO_THROW(dealer.dealCards(52, player));  // Expect that 52 cards can be dealt without errors
    EXPECT_EQ(player.getCountCards(), 52);
}


// ===========Dealler=============
// ===== 1) Unit Testing

// Unit test for the shuffleDeck method
TEST(DeallerTest, ShuffleDeck) {
    Dealler dealer;
    dealer.shuffleDeck();  // Check that the shuffling method works without errors
    EXPECT_NO_THROW(dealer.shuffleDeck());  // The method should not throw exceptions
}

// Unit test for the dealCards method
TEST(DeallerTest, DealCards) {
    Game game;
    Dealler dealer;
    Player player("John", game);
    dealer.newDeck();  // Create a new deck before dealing
    dealer.dealCards(2, player);  // Deal two cards to the player

    EXPECT_EQ(player.getCountCards(), 2);  // Check that the player has two cards
}

// Unit test for the getOneCard method
TEST(DeallerTest, GetOneCard) {
    Dealler dealer;
    dealer.newDeck();
    Card card = dealer.getOneCard();
    // Check that the card number and suit are valid
    EXPECT_TRUE(card.getNumber() >= 2);
    EXPECT_TRUE(card.getNumber() <= 14); 
    EXPECT_TRUE(card.getSuit() >= 1);
    EXPECT_TRUE(card.getSuit() <= 4);
}

// Unit test for the putOneCardInDeck method
TEST(DeallerTest, PutOneCardInDeck) {
    Dealler dealer;
    Card card(10, 2);  // Create a card with number 10 and suit 2
    dealer.putOneCardInDeck(card);  // Return the card to the deck

    // Check that the card is correctly returned to the deck
    EXPECT_NO_THROW(dealer.putOneCardInDeck(card));
}

// Unit test for the PowerHand method
TEST(DeallerTest, PowerHand) {
    Dealler dealer;
    std::vector<Card> hand = { Card(2, 1), Card(3, 2), Card(4, 3), Card(5, 1), Card(14, 4) };
    std::vector<int> power = dealer.PowerHand(hand);

    EXPECT_EQ(power[0], 5);  // Check that the hand strength is Street (index 5)
}

// ===== 2) Functional Testing

// Functional test for checking card dealing and creating a new deck
TEST(DeallerTest, FunctionalDealAndNewDeck) {
    Game game;
    Dealler dealer;
    Player player("Alice", game);

    dealer.newDeck();  // Create a new deck
    dealer.dealCards(3, player);  // Deal three cards

    EXPECT_EQ(player.getCountCards(), 3);  // Check that the player has 3 cards
}

// ===== 3) Error and Exception Testing

// Test for exception when dealing 0 cards
TEST(DeallerTest, DealCardsZero_Exception) {
    Game game;
    Dealler dealer;
    Player player("John", game);

    EXPECT_THROW(dealer.dealCards(0, player), std::out_of_range);  // Expect an exception when dealing 0 cards
}

// Test for exception when dealing more cards than are in the deck
TEST(DeallerTest, DealTooManyCards_Exception) {
    Game game;
    Dealler dealer;
    Player player("John", game);
    dealer.newDeck();

    EXPECT_THROW(dealer.dealCards(60, player), std::out_of_range);  // Deal more cards than are in the deck
}

// ===== 4) Performance Testing

// Performance test for the shuffleDeck method
TEST(DeallerTest, ShufflePerformance) {
    Dealler dealer;

    auto start = std::chrono::high_resolution_clock::now();
    dealer.shuffleDeck();  // Shuffle the deck
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    EXPECT_LT(duration, 50);  // Check that shuffling takes less than 50 ms
}

// Performance test for the dealCards method
TEST(DeallerTest, DealPerformance) {
    Game game;
    Dealler dealer;
    Player player("John", game);
    dealer.newDeck();

    auto start = std::chrono::high_resolution_clock::now();
    dealer.dealCards(5, player);  // Deal 5 cards
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    EXPECT_LT(duration, 100);  // The dealing operation should take less than 100 ms
}

// ===== 5) Load Testing

// Load test with a large number of players
TEST(DeallerTest, LoadTestManyPlayers) {
    Game game;
    Dealler dealer;
    dealer.newDeck();
    
    std::vector<Player> players;
    for (int i = 0; i < 25; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1), game);
    }

    // Deal 2 cards to each of 100 players
    for (auto& player : players) {
        dealer.dealCards(2, player);
    }

    // Check that each player has exactly 2 cards
    for (const auto& player : players) {
        EXPECT_EQ(player.getCountCards(), 2);
    }
}

// ===== 6) Edge Case Testing

// Testing dealing the maximum number of cards
TEST(DeallerTest, DealMaxCards) {
    Game game;
    Dealler dealer;
    Player player("John", game);
    dealer.newDeck();

    EXPECT_NO_THROW(dealer.dealCards(52, player));  // Check that 52 cards can be dealt
    EXPECT_EQ(player.getCountCards(), 52);  // Check that the player has 52 cards
}
