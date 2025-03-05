/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/

#include <gtest/gtest.h>
#include "baseGameRule.h"


// Test for Card
TEST(CardTest, TestCardConstructor) {
    Card card(11, 1);
    EXPECT_EQ(card.getNumber(), 11);
    EXPECT_EQ(card.getSuit(), 1);
}

TEST(CardTest, TestCardSetters) {
    Card card(10, 2);
    card.setNumber(14);
    card.setSuit(3);
    EXPECT_EQ(card.getNumber(), 14);
    EXPECT_EQ(card.getSuit(), 3);
}


// Test for Deck
TEST(DeckTest, TestDeckInitialization) {
    Deck deck;
    EXPECT_EQ(deck.deal().getNumber(), 14);
}

TEST(DeckTest, TestShuffle) {
    Deck deck1;
    Deck deck2;
    deck1.shuffle();
    deck2.shuffle();
    EXPECT_NE(deck1.deal().getNumber(), deck2.deal().getNumber());
}


// Test for Hand
TEST(HandTest, TestHandAddCard) {
    Hand hand;
    Card card(10, 1);
    hand.setCards(card);
    EXPECT_EQ(hand.getCountCards(), 1);
}

TEST(HandTest, TestHandRemoveCard) {
    Hand hand;
    Card card(10, 1);
    hand.setCards(card);
    hand.delLastCard();
    EXPECT_EQ(hand.getCountCards(), 0);
}

TEST(HandTest, TestHandEmpty) {
    Hand hand;
    EXPECT_THROW(hand.delLastCard(), std::out_of_range);
}


// Test for Player
TEST(PlayerTest, TestPlayerNameAndChips) {
    Player player("Vova");
    player.setChips(100);
    
    testing::internal::CaptureStdout();
    player.getChipsOnDisplay();
    std::string output_1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output_1, "Chips count: 100.\n");
    
    testing::internal::CaptureStdout();
    player.getNameOnDisplay();
    std::string output_2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output_2, "Player name: Vova.\n");
}

TEST(PlayerTest, TestPlayerCards) {
    Player player("Vova");
    Card card(10, 1);
    player.setCard(card);
    EXPECT_EQ(player.getCountCards(), 1);
    player.delAllCards();
    EXPECT_EQ(player.getCountCards(), 0);
}


// Test for Dealler
TEST(DeallerTest, TestDealCards) {
    Player player("Vova");
    Dealler dealer;
    dealer.dealCards(2, player);
    EXPECT_EQ(player.getCountCards(), 2);
}

TEST(DeallerTest, TestShuffleDeck) {
    Dealler dealer1;
    Dealler dealer2;
    dealer1.shuffleDeck();
    dealer2.shuffleDeck();
    Card CardDealer1 = dealer1.getOneCard();
    Card CardDealer2 = dealer2.getOneCard();
    EXPECT_NE(CardDealer1.getNumber(), CardDealer2.getNumber());
}

TEST(DeallerTest, TestSearchWinner) {
    Player player1("Vova");
    Player player2("Dima");
    std::vector<Player> players = {player1, player2};
    Dealler dealer;
    std::vector<Card> tableCards = {Card(10, 1), Card(11, 1), Card(12, 1)};
    dealer.dealCards(2, player1);
    dealer.dealCards(2, player2);
    std::vector<int> DataPass = {0, 0};
    std::vector<int> winners = dealer.SearchWinner(players, tableCards, DataPass);
    EXPECT_TRUE(winners.size() > 0);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
