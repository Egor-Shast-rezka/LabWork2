/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/


#include <gtest/gtest.h>
#include "baseGameRule.h"
#include "pathGame.h"
#include "characters.h"


// ===========AllSeeingPlayer=============
// ===== 1) Unit Testing

// Testing the constructor of AllSeeingPlayer
TEST(AllSeeingPlayerTest, Constructor) {
    Game game; // Added Game object
    AllSeeingPlayer player("AllSeeingPlayer", game); // Pass game object
    EXPECT_EQ(player.getName(), "AllSeeingPlayer");  // Ensure the name is set correctly
}

// Testing the isCharacter method of AllSeeingPlayer
TEST(AllSeeingPlayerTest, IsCharacter) {
    Game game; // Added Game object
    AllSeeingPlayer player("AllSeeingPlayer", game); // Pass game object
    EXPECT_TRUE(player.isCharacter());  // Ensure the method returns true for a character
}


// ===========CheaterPlayer=============
// ===== 1) Unit Testing

// Testing the constructor of CheaterPlayer
TEST(CheaterPlayerTest, Constructor) {
    Game game; // Added Game object
    CheaterPlayer player("CheaterPlayer", game); // Pass game object
    EXPECT_EQ(player.getName(), "CheaterPlayer");  // Ensure the name is set correctly
}

// Testing the isCharacter method of CheaterPlayer
TEST(CheaterPlayerTest, IsCharacter) {
    Game game; // Added Game object
    CheaterPlayer player("CheaterPlayer", game); // Pass game object
    EXPECT_TRUE(player.isCharacter());  // Ensure the method returns true for a character
}


// ===========EngagedDeckPlayer=============
// ===== 1) Unit Testing

// Testing the constructor of EngagedDeckPlayer
TEST(EngagedDeckPlayerTest, Constructor) {
    Game game; // Added Game object
    EngagedDeckPlayer player("EngagedDeckPlayer", game); // Pass game object
    EXPECT_EQ(player.getName(), "EngagedDeckPlayer");  // Ensure the name is set correctly
}

// Testing the isCharacter method of EngagedDeckPlayer
TEST(EngagedDeckPlayerTest, IsCharacter) {
    Game game; // Added Game object
    EngagedDeckPlayer player("EngagedDeckPlayer", game); // Pass game object
    EXPECT_TRUE(player.isCharacter());  // Ensure the method returns true for a character
}


// ===========DeallersFrendPlayer=============
// ===== 1) Unit Testing

// Testing the constructor of DeallersFrendPlayer
TEST(DeallersFrendPlayerTest, Constructor) {
    Game game; // Added Game object
    DeallersFrendPlayer player("DeallersFrendPlayer", game); // Pass game object
    EXPECT_EQ(player.getName(), "DeallersFrendPlayer");  // Ensure the name is set correctly
}

// Testing the isCharacter method of DeallersFrendPlayer
TEST(DeallersFrendPlayerTest, IsCharacter) {
    Game game; // Added Game object
    DeallersFrendPlayer player("DeallersFrendPlayer", game); // Pass game object
    EXPECT_TRUE(player.isCharacter());  // Ensure the method returns true for a character
}
