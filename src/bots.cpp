/*
    Egor Shastin st129457@student.spbu.ru
    
    The code implements two classes for bots: AIPlayer_easy and AIPlayer_normal.

    > AIPlayer_easy chooses actions randomly with the probability of accepting the bet, all-in or raise based on the current bet and the player's chips.
    >AIPlayer_normal makes decisions based on the probability of winning, calculated from the strength of the hand. The bot either folds, calls, raises or goes all-in depending on the chances of winning.
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// ===========AIPlayer_easy=============

AIPlayer_easy::AIPlayer_easy(std::string name) : Player(name) {}

// The bot is identified as a bot by returning true
bool AIPlayer_easy::isBot() {
    return true;
}

/*
    Returns an array of 5 numbers:
    1 - 0 or 1 - the bot agrees with the current bet or not,
    2 - 0 or 1 - the bot passes or not,
    3 - 0 or 1 - goes all-in or not,
    4 - the bot raises the current bet by some number of coins, (raise)
    5 - the bot changes the bet (call)
*/
std::vector<int> AIPlayer_easy::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot) {

    int chips = player->getChips();

    std::vector<int> action(5, 0);

    std::random_device rd;
    std::mt19937 gen(rd());

    // Random chance for bot to reboot, or reboot if condition is met
    std::uniform_int_distribution<> chanceReboot(1, 5);
    if (chanceReboot(gen) == 1 || ifReboot) {

        action[0] = 1; // The bot agrees with the current bet or not
        return action;
    }

    // Random chance for bot to go all-in, or if all-in condition is met
    std::uniform_int_distribution<> chanceAllin(1, 20);
    if (chanceAllin(gen) == 1 || Allin) {

        action[2] = 1; // Goes all-in
        return action;
    }

    std::vector<float> weights;
    float sumWeights = 0.0;

    // Calculate weights for raising or calling, with decreasing likelihood as the bet increases
    for (int i = currentBet; i <= chips; i++) {

        float weight = 1.0f / (i - currentBet + 1);

        weights.push_back(weight);

        sumWeights += weight;
    }

    std::vector<float> probabilities;
    float cumulativeProbability = 0.0f;
    
    // Calculate cumulative probabilities for each possible action
    for (float weight : weights) {

        cumulativeProbability += weight / sumWeights;

        probabilities.push_back(cumulativeProbability);
    }

    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    // Choose action based on random value and calculated probabilities
    for (std::size_t i = 0; i < probabilities.size(); i++) {

        if (randomValue < probabilities[i]) {
            if (raund == 1) {

                action[4] = i + currentBet; // In the first round, the bot calls

            } else {

                action[3] = i; // In other rounds, the bot raises
            }

            return action;
        }
    }

    return action;
}


// ===========AIPlayer_normal=============

AIPlayer_normal::AIPlayer_normal(std::string name) : Player(name) {}

// The bot is identified as a bot by returning true
bool AIPlayer_normal::isBot() {
    return true;
}

// Calculates the number of outs (possible cards that can improve the bot's hand)
int AIPlayer_normal::calculateOuts(std::vector<Card>& hand, std::vector<Card>& cardsOnTable, Dealler& dealler) {

    int outs = 0;

    std::vector<Card> CurrentCards = hand;

    // Combine the bot's hand with the cards on the table
    CurrentCards.insert(CurrentCards.end(), cardsOnTable.begin(), cardsOnTable.end());

    int handStrength = dealler.PowerHand(CurrentCards)[0];

    std::vector<Card> remainingCards = dealler.getDeck().getAllCards();

    // Check how many cards can improve the current hand strength
    for (const auto& card : remainingCards) {

        std::vector<Card> possibleHand = hand;
        possibleHand.push_back(card);

        std::vector<Card> CurrentCardsInPossibleHand = possibleHand;

        CurrentCardsInPossibleHand.insert(CurrentCardsInPossibleHand.end(), cardsOnTable.begin(), cardsOnTable.end());

        int newHandStrength = dealler.PowerHand(CurrentCardsInPossibleHand)[0];

        if (newHandStrength > handStrength) {
            outs++; // Count cards that improve the hand
        }
    }

    return outs;
}

// Calculates the probability of winning based on the bot's current hand and cards on the table
float AIPlayer_normal::calculateWinningProbability(std::vector<Card> hand, std::vector<Card> cardsOnTable, Dealler& dealler) {

    std::vector<Card> CurrentCards = hand;

    // Combine the bot's hand with the cards on the table
    CurrentCards.insert(CurrentCards.end(), cardsOnTable.begin(), cardsOnTable.end());

    int handStrength = dealler.PowerHand(CurrentCards)[0];

    int remainingCards = static_cast<int>(dealler.getDeck().getAllCards().size());

    float winProbability = 0.0f;

    // Set winning probability based on hand strength
    if (handStrength == 10) {
        winProbability = 0.99f; // Maximum hand strength, very high probability
    } else if (handStrength >= 8) {
        winProbability = 0.8f;  // Strong hand
    } else if (handStrength >= 5) {
        winProbability = 0.5f;  // Moderate hand
    } else {

        int outs = calculateOuts(hand, cardsOnTable, dealler);
        winProbability = static_cast<float>(outs) / remainingCards;  // Calculate probability based on outs
    }

    return winProbability;
}

// Determines the bot's actions based on its hand, available chips, and game state
std::vector<int> AIPlayer_normal::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int round, bool ifReboot) {
    int playerChips = player->getChips();
    std::vector<Card> playerHand = player->getAllCards();
    int remainingChips = playerChips - currentBet;

    // If already all-in or not enough chips to continue betting
    if (Allin || playerChips <= currentBet) {
        return {0, 0, 1, 0, 0};  // Agree with current bet and go all-in
    }

    // Calculate the probability of winning based on the bot's hand
    float winProbability = calculateWinningProbability(playerHand, cardsOnTable, dealler);

    int agreeWithBet = 0;
    int fold = 0;
    int allIn = 0;
    int raiseAmount = 0;
    int callAmount = 0;

    // Decision-making logic based on winning probability
    if (winProbability < 0.2f) {
        fold = 1;  // Fold if the win probability is too low
    } else if (winProbability >= 0.2f && winProbability < 0.5f) {
        // If the win probability is moderate
        if (round == 1) {
            callAmount = currentBet;  // In the first round, the bot calls
        } else {
            raiseAmount = currentBet + remainingChips * 0.1;  // In later rounds, the bot raises a small amount
        }
    } else if (winProbability >= 0.5f && winProbability < 0.8f) {
        // If the win probability is good
        if (round == 1) {
            callAmount = currentBet;  // In the first round, the bot calls
        } else {
            raiseAmount = currentBet + remainingChips * 0.3;  // In later rounds, the bot raises a larger amount
        }
    } else {
        // If the win probability is very high
        allIn = 1;
        raiseAmount = playerChips;  // The bot goes all-in
    }

    // If the win probability is over 50% and the bot isn't going all-in, there's a 20% chance of all-in
    if (winProbability >= 0.5f && allIn == 0 && (rand() % 5 == 0)) {
        allIn = 1;
        raiseAmount = playerChips;
    }

    // Return the bot's actions:
    // 1 - agree with current bet
    // 2 - fold
    // 3 - all-in
    // 4 - raise
    // 5 - call
    return {agreeWithBet, fold, allIn, raiseAmount, callAmount};
}
