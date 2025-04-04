/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/


#include <gtest/gtest.h>
#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"


// ===========PathGame=============
// ===== 1) Unit Testing

// Testing the setupForGameMode method of GameMode
TEST(PathGameTest, SetupForGameMode) {
    GameMode gameMode;
    EXPECT_NO_THROW(gameMode.setupForGameMode());  // Ensure the method does not throw exceptions
}

// Testing the GameModePathGame method of GameMode
TEST(PathGameTest, GameModePathGame) {
    GameMode gameMode;
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;

    EXPECT_NO_THROW(gameMode.GameModePathGame(DataPass, ifActPlayerData, Allin, raund));  // Ensure the method does not throw exceptions
}

// ===== 2) Functional Testing

// Testing the setupForGameMode method with valid input
TEST(PathGameTest, SetupForGameModeValidInput) {
    GameMode gameMode;
    EXPECT_NO_THROW(gameMode.setupForGameMode());  // Ensure the method works with valid input
}

// ===== 3) Performance Testing

// Testing the performance of the GameModePathGame method
TEST(PathGameTest, GameModePathGamePerformance) {
    GameMode gameMode;
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;

    auto start = std::chrono::high_resolution_clock::now();
    gameMode.GameModePathGame(DataPass, ifActPlayerData, Allin, raund);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 100);  // Ensure the method completes in less than 100 ms
}

// ===== 4) Load Testing

// Testing the GameModePathGame method with a large number of players
TEST(PathGameTest, GameModePathGameLoadTest) {
    GameMode gameMode;
    std::vector<bool> DataPass(100, false);
    std::vector<bool> ifActPlayerData(100, false);
    bool Allin = false;
    int raund = 1;

    EXPECT_NO_THROW(gameMode.GameModePathGame(DataPass, ifActPlayerData, Allin, raund));  // Ensure the method handles a large number of players
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
