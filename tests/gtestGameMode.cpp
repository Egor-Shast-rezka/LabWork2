/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/


#include <gtest/gtest.h>
#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"


// ===========AllBots=============
// ===== 1) Unit Testing

// Testing the constructor and destructor of AllBots
TEST(AllBotsTest, ConstructorDestructor) {
    Game game;
    AllBots allBots(game);
    EXPECT_NO_THROW(allBots.~AllBots());  // Ensure the destructor does not throw exceptions
}

// Testing the setAllBots method of AllBots
TEST(AllBotsTest, SetAllBots) {
    Game game;
    AllBots allBots(game);

    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());

    EXPECT_NO_THROW(allBots.setAllBots(1, "> Write count bot complexity easy: ")); // Ensure the method does not throw exceptions

    std::cin.rdbuf(originalCin);
}

// Testing the setupForGameMode method of AllBots
TEST(AllBotsTest, SetupForGameMode) {
    Game game;
    AllBots allBots(game);
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(allBots.setupForGameMode());  // Ensure the method does not throw exceptions
    
    std::cin.rdbuf(originalCin);
}

// Testing the OutputInfoPlayers method of AllBots
TEST(AllBotsTest, OutputInfoPlayers) {
    Game game;
    AllBots allBots(game);
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(allBots.OutputInfoPlayers());  // Ensure the method does not throw exceptions
    
    std::cin.rdbuf(originalCin);
}

// Testing the GameModePathGame method of AllBots
TEST(AllBotsTest, GameModePathGame) {
    Game game;
    AllBots allBots(game);
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(allBots.GameModePathGame(DataPass, ifActPlayerData, Allin, raund));  // Ensure the method does not throw exceptions
    
    std::cin.rdbuf(originalCin);
}

// ===== 2) Functional Testing

// Testing the interaction between AllBots and Game classes
TEST(AllBotsTest, InteractionWithGame) {
    Game game;
    AllBots allBots(game);
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    allBots.setupForGameMode();
    
    std::cin.rdbuf(originalCin);
    
    EXPECT_GT(game.getPlayer().size(), 0);  // Ensure that players are added to the game
}

// ===== 3) Performance Testing

// Testing the performance of the setupForGameMode method in AllBots
TEST(AllBotsTest, SetupForGameModePerformance) {
    Game game;
    AllBots allBots(game);

    auto start = std::chrono::high_resolution_clock::now();
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    allBots.setupForGameMode();
    
    std::cin.rdbuf(originalCin);
    
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 100);  // Ensure the method completes in less than 100 ms
}

// Testing the performance of the GameModePathGame method in AllBots
TEST(AllBotsTest, GameModePathGamePerformance) {
    Game game;
    AllBots allBots(game);
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;

    auto start = std::chrono::high_resolution_clock::now();
    allBots.GameModePathGame(DataPass, ifActPlayerData, Allin, raund);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 200);  // Ensure the method completes in less than 200 ms
}

// ===== 4) Load Testing

// Testing the setupForGameMode method with a large number of players
TEST(AllBotsTest, SetupForGameModeLoadTest) {
    Game game;
    AllBots allBots(game);

    for (int i = 0; i < 23; ++i) {
        game.setPlayer("Player " + std::to_string(i));
    }
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(allBots.setupForGameMode());  // Ensure the method handles a large number of players
    
    std::cin.rdbuf(originalCin);
}

// ===== 5) Edge Case Testing

// Testing the GameModePathGame method with all players passing
TEST(AllBotsTest, GameModePathGameEdgeCaseAllPass) {
    Game game;
    AllBots allBots(game);
    std::vector<bool> DataPass = {true, true};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(allBots.GameModePathGame(DataPass, ifActPlayerData, Allin, raund));  // Ensure the method handles all players passing
    
    std::cin.rdbuf(originalCin);
}


// ===========OneOnOne=============
// ===== 1) Unit Testing

// Testing the constructor and destructor of OneOnOne
TEST(OneOnOneTest, ConstructorDestructor) {
    Game game;
    OneOnOne oneOnOne(game);
    EXPECT_NO_THROW(oneOnOne.~OneOnOne());  // Ensure the destructor does not throw exceptions
}

// Testing the setupForGameMode method of OneOnOne
TEST(OneOnOneTest, SetupForGameMode) {
    Game game;
    OneOnOne oneOnOne(game);
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(oneOnOne.setupForGameMode());  // Ensure the method does not throw exceptions
    
    std::cin.rdbuf(originalCin);
}

// Testing the OutputInfoPlayers method of OneOnOne
TEST(OneOnOneTest, OutputInfoPlayers) {
    Game game;
    OneOnOne oneOnOne(game);
    EXPECT_NO_THROW(oneOnOne.OutputInfoPlayers());  // Ensure the method does not throw exceptions
}

// Testing the GameModePathGame method of OneOnOne
TEST(OneOnOneTest, GameModePathGame) {
    Game game;
    game.setPlayer("Alice");
    game.setPlayer("Bob");
    OneOnOne oneOnOne(game);

    std::stringstream combinedInput;
    combinedInput << "1\nqwe\npass\npass\n"; 
    
    std::streambuf* originalCin = std::cin.rdbuf();
    std::cin.rdbuf(combinedInput.rdbuf());

    oneOnOne.setupForGameMode();

    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;

    // Проверка что метод не упадёт
    EXPECT_NO_THROW({
        oneOnOne.GameModePathGame(DataPass, ifActPlayerData, Allin, raund);
    });

    // Восстанавливаем оригинальный std::cin
    std::cin.rdbuf(originalCin);
}



// ===== 2) Functional Testing

// Testing the interaction between OneOnOne and Game classes
TEST(OneOnOneTest, InteractionWithGame) {
    Game game;
    OneOnOne oneOnOne(game);
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    oneOnOne.setupForGameMode();
    
    std::cin.rdbuf(originalCin);
    
    EXPECT_GT(game.getPlayer().size(), 0);  // Ensure that players are added to the game
}


// Testing the GameModePathGame method with invalid input
TEST(OneOnOneTest, GameModePathGameInvalidInput) {
    Game game;
    OneOnOne oneOnOne(game);
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = -1;  // Invalid round number
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_THROW(oneOnOne.GameModePathGame(DataPass, ifActPlayerData, Allin, raund), std::invalid_argument);  // Expect an exception for invalid input
    
    std::cin.rdbuf(originalCin);
}

// ===== 3) Performance Testing

// Testing the performance of the setupForGameMode method in OneOnOne
TEST(OneOnOneTest, SetupForGameModePerformance) {
    Game game;
    OneOnOne oneOnOne(game);

    auto start = std::chrono::high_resolution_clock::now();
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    oneOnOne.setupForGameMode();
    
    std::cin.rdbuf(originalCin);
    
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 100);  // Ensure the method completes in less than 100 ms
}

// Testing the performance of the GameModePathGame method in OneOnOne
TEST(OneOnOneTest, GameModePathGamePerformance) {
    Game game;
    game.setPlayer("Player1");
    game.setPlayer("Player2");
    
    OneOnOne oneOnOne(game);
    std::vector<bool> DataPass = {false, false};
    std::vector<bool> ifActPlayerData = {false, false};
    bool Allin = false;
    int raund = 1;

    // Используем быстрые корректные действия
    std::istringstream input("pass\npass\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());

    auto start = std::chrono::high_resolution_clock::now();
    oneOnOne.GameModePathGame(DataPass, ifActPlayerData, Allin, raund);
    auto end = std::chrono::high_resolution_clock::now();

    std::cin.rdbuf(originalCin);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 200);
}


// ===== 4) Load Testing

// Testing the setupForGameMode method with a large number of players
TEST(OneOnOneTest, SetupForGameModeLoadTest) {
    Game game;
    OneOnOne oneOnOne(game);

    for (int i = 0; i < 25; ++i) {
        game.setPlayer("Player " + std::to_string(i));
    }
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(oneOnOne.setupForGameMode());  // Ensure the method handles a large number of players
    
    std::cin.rdbuf(originalCin);
}

// ===== 5) Edge Case Testing

// Testing the setupForGameMode method with maximum players
TEST(OneOnOneTest, SetupForGameModeEdgeCaseMaxPlayers) {
    Game game;
    OneOnOne oneOnOne(game);

    for (int i = 0; i < 24; ++i) {
        game.setPlayer("Player " + std::to_string(i));
    }
    
    std::istringstream input("1\nqwe\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    EXPECT_NO_THROW(oneOnOne.setupForGameMode());
    
    std::cin.rdbuf(originalCin);
}
