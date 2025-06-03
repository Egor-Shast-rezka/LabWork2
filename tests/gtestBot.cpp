/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/


#include <gtest/gtest.h>
#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"


// ===========AIPlayer_easy=============
// ===== 1) Unit Testing

// Testing the constructor of AIPlayer_easy
TEST(AIPlayer_easyTest, Constructor) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    EXPECT_EQ(bot.getName(), "EasyBot");  // Ensure the name is set correctly
}

// Testing the isBot method of AIPlayer_easy
TEST(AIPlayer_easyTest, IsBot) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    EXPECT_TRUE(bot.isBot());  // Ensure the method returns true for a bot
}

// Testing the BotActions method of AIPlayer_easy with a random decision
TEST(AIPlayer_easyTest, BotActionsRandomDecision) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_easy>("EasyBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 2));
    Dealler dealler;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;
    player->setChips(10);
    std::vector<int> actions = bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot);
    EXPECT_EQ(static_cast<int>(actions.size()), 5);  // Ensure the action vector has 5 elements
}

// ===== 2) Functional Testing

// Testing the BotActions method of AIPlayer_easy with an all-in condition
TEST(AIPlayer_easyTest, BotActionsAllInCondition) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_easy>("EasyBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 2));
    Dealler dealler;
    int currentBet = 50;
    bool Allin = true;    // Force all-in condition
    int round = 1;
    bool ifReboot = false;

    std::vector<int> actions = bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot);
    EXPECT_EQ(actions[2], 1);  // Ensure the bot goes all-in
}

// ===== 3) Error and Exception Testing

// Testing the BotActions method of AIPlayer_easy with invalid input (negative current bet)
TEST(AIPlayer_easyTest, BotActionsInvalidInputNegativeBet) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_easy>("EasyBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 2));
    Dealler dealler;
    int currentBet = -50;  // Invalid current bet
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    EXPECT_THROW(bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot), std::invalid_argument);  // Expect an exception for invalid input
}

// ===== 5) Load Testing

// Testing the BotActions method of AIPlayer_easy with a large number of players
TEST(AIPlayer_easyTest, BotActionsLoadTest) {
    Game game; // Added Game object
    AIPlayer_easy bot("EasyBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_easy>("EasyBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 2));
    Dealler dealler;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;
    player->setChips(10);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot));  // Ensure the method handles a large number of calls
    }
}


// ===========AIPlayer_normal=============
// ===== 1) Unit Testing

// Testing the constructor of AIPlayer_normal
TEST(AIPlayer_normalTest, Constructor) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    EXPECT_EQ(bot.getName(), "NormalBot");  // Ensure the name is set correctly
}

// Testing the isBot method of AIPlayer_normal
TEST(AIPlayer_normalTest, IsBot) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    EXPECT_TRUE(bot.isBot());  // Ensure the method returns true for a bot
}

// Testing the calculateOuts method of AIPlayer_normal
TEST(AIPlayer_normalTest, CalculateOuts) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::vector<Card> hand = {Card(10, 1), Card(11, 1)};  // Example hand
    std::vector<Card> cardsOnTable = {Card(12, 1), Card(13, 1), Card(14, 1)};  // Example table cards
    Dealler dealler;

    int outs = bot.calculateOuts(hand, cardsOnTable, dealler);
    EXPECT_GE(outs, 0);  // Ensure the number of outs is non-negative
}

// Testing the calculateWinningProbability method of AIPlayer_normal
TEST(AIPlayer_normalTest, CalculateWinningProbability) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::vector<Card> hand = {Card(10, 1), Card(11, 1)};  // Example hand
    std::vector<Card> cardsOnTable = {Card(12, 1), Card(13, 1), Card(14, 1)};  // Example table cards
    Dealler dealler;

    float probability = bot.calculateWinningProbability(hand, cardsOnTable, dealler);
    EXPECT_GE(probability, 0.0f);  // Ensure the probability is non-negative
    EXPECT_LE(probability, 1.0f);  // Ensure the probability is less than or equal to 1
}

// ===== 2) Functional Testing

// Testing the BotActions method of AIPlayer_normal with a high win probability
TEST(AIPlayer_normalTest, BotActionsHighWinProbability) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_normal>("NormalBot", game); // Pass game object
    std::vector<Card> hand = {Card(10, 1), Card(11, 1)};  // Example hand
    std::vector<Card> cardsOnTable = {Card(12, 1), Card(13, 1), Card(14, 1)};  // Example table cards
    Dealler dealler;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    player->setCard(hand[0]);
    player->setCard(hand[1]);

    std::vector<int> actions = bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot);
    EXPECT_EQ(actions[2], 1);  // Ensure the bot goes all-in with a high win probability
}

// ===== 3) Error and Exception Testing

// Testing the BotActions method of AIPlayer_normal with invalid input (negative current bet)
TEST(AIPlayer_normalTest, BotActionsInvalidInputNegativeBet) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_normal>("NormalBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    Dealler dealler;
    int currentBet = -50;  // Invalid current bet
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    EXPECT_THROW(bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot), std::invalid_argument);  // Expect an exception for invalid input
}

// ===== 4) Performance Testing

// Testing the performance of the BotActions method of AIPlayer_normal
TEST(AIPlayer_normalTest, BotActionsPerformance) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_normal>("NormalBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 1)); // Add some cards to ensure calculation is not trivial
    cardsOnTable.push_back(Card(3, 1));
    player->setCard(Card(14, 1)); // Ace of Spades
    player->setCard(Card(13, 1)); // King of Spades

    Dealler dealler;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> actions = bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 100);  // Increased threshold to 100ms for performance
}

// ===== 5) Load Testing

// Testing the BotActions method of AIPlayer_normal with a large number of players
TEST(AIPlayer_normalTest, BotActionsLoadTest) {
    Game game; // Added Game object
    AIPlayer_normal bot("NormalBot", game); // Pass game object
    std::unique_ptr<Player> player = std::make_unique<AIPlayer_normal>("NormalBot", game); // Pass game object
    std::vector<Card> cardsOnTable;
    cardsOnTable.push_back(Card(2, 1)); // Add some cards for consistent behavior
    cardsOnTable.push_back(Card(3, 1));
    player->setCard(Card(14, 1)); // Ace of Spades
    player->setCard(Card(13, 1)); // King of Spades

    Dealler dealler;
    int currentBet = 50;
    bool Allin = false;
    int round = 1;
    bool ifReboot = false;

    for (int i = 0; i < 1000; ++i) {
        EXPECT_NO_THROW(bot.BotActions(player, cardsOnTable, dealler, currentBet, Allin, round, ifReboot));  // Ensure the method handles a large number of calls
    }
}
