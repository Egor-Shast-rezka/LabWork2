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

AIPlayer_easy::AIPlayer_easy(std::string name, Game& game) : Player(name, game) {}

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
    
    if (currentBet < 0 || raund < 0) {
        throw std::invalid_argument("Invalid argument!");
    }
    
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
    if (chanceAllin(gen) == 1 || Allin || chips <= 0) {

        action[2] = 1; // Goes all-in
        return action;
    }

    // Protect against bets larger than available chips
    if (currentBet > chips) {
        action[1] = 1; // Pass
        return action;
    }

    std::vector<float> weights;
    float sumWeights = 0.0;

    // Calculate weights for raising or calling, with decreasing likelihood as the bet increases
    for (int i = currentBet; i <= chips; i++) {

        // Protect against division by zero
        int diff = std::max(1, i - currentBet);
        float weight = 1.0f / diff;

        weights.push_back(weight);
        sumWeights += weight;
    }

    // If no weights calculated, agree with current bet
    if (weights.empty() || sumWeights <= 0.0001f) {
        action[0] = 1;
        return action;
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
            action[3] = std::min(i, static_cast<size_t>(chips - currentBet)); // Ensure raise doesn't exceed chips
            return action;
        }
    }

    return action;
}


// ===========AIPlayer_normal=============

AIPlayer_normal::AIPlayer_normal(std::string name, Game& game) : Player(name, game) {}

// The bot is identified as a bot by returning true
bool AIPlayer_normal::isBot() {
    return true;
}

// Calculates the number of outs (possible cards that can improve the bot's hand)
int AIPlayer_normal::calculateOuts(std::vector<Card>& hand, std::vector<Card>& cardsOnTable, Dealler& dealler) {

    if (hand.empty() || cardsOnTable.empty()) {
        throw std::invalid_argument("Hand or cards on table are empty!");
    }

    int outs = 0;

    std::vector<Card> CurrentCards = hand;

    // Combine the bot's hand with the cards on the table
    CurrentCards.insert(CurrentCards.end(), cardsOnTable.begin(), cardsOnTable.end());
    
    // Not enough cards for evaluation
    if (CurrentCards.size() < 3) {
        return 0;
    }

    int handStrength = 0;
    try {
        handStrength = dealler.PowerHand(CurrentCards)[0];
    } catch (...) {
        return 0; // Safe default on error
    }

    std::vector<Card> remainingCards;
    try {
        remainingCards = dealler.getDeck().getAllCards();
    } catch (...) {
        return 0; // Safe default on error
    }
    
    if (remainingCards.empty()) {
        return 0;
    }

    std::sort(remainingCards.begin(), remainingCards.end());
    
    // Check how many cards can improve the current hand strength
    for (const auto& card : remainingCards) {

        std::vector<Card> possibleHand = hand;
        possibleHand.push_back(card);

        int newHandStrength = 0;
        try {
            newHandStrength = dealler.PowerHand(possibleHand)[0];
        } catch (...) {
            continue; // Skip problematic card
        }

        if (newHandStrength > handStrength) {
            outs++; // Count cards that improve the hand
        }
    }

    return std::min(outs, static_cast<int>(remainingCards.size()));
}

// Calculates the probability of winning based on the bot's current hand and cards on the table
float AIPlayer_normal::calculateWinningProbability(std::vector<Card> hand, std::vector<Card> cardsOnTable, Dealler& dealler) {

    std::vector<Card> CurrentCards = hand;

    // Combine the bot's hand with the cards on the table
    CurrentCards.insert(CurrentCards.end(), cardsOnTable.begin(), cardsOnTable.end());
    
    // Not enough cards for proper evaluation
    if (CurrentCards.size() < 3) {
        return 0.3f; // Base probability
    }

    int handStrength = 0;
    try {
        handStrength = dealler.PowerHand(CurrentCards)[0];
    } catch (...) {
        return 0.3f; // Base probability on error
    }

    int remainingCards = 0;
    try {
        remainingCards = static_cast<int>(dealler.getDeck().getAllCards().size());
    } catch (...) {
        remainingCards = 30; // Reasonable default
    }

    if (remainingCards <= 0) {
        return 0.0f;
    }

    float winProbability = 0.0f;

    // Set winning probability based on hand strength
    if (handStrength == 10) {
        winProbability = 0.99f; // Maximum hand strength, very high probability
    } else if (handStrength >= 8) {
        winProbability = 0.8f;  // Strong hand
    } else if (handStrength >= 5) {
        winProbability = 0.5f;  // Moderate hand
    } else {
        if (CurrentCards.size() < 5) return 0.5f; // Default for small hands
        int outs = calculateOuts(hand, cardsOnTable, dealler);
        winProbability = static_cast<float>(outs) / remainingCards;
    }

    // Ensure probability stays within valid range
    return std::max(0.0f, std::min(1.0f, winProbability));
}

/*
    Returns an array of 5 numbers: 
    1 - 0 or 1 - the bot agrees with the current bet or not, 
    2 - 0 or 1 - the bot passes or not, 
    3 - 0 or 1 - goes all-in or not, 
    4 - the bot raises the current bet by some number of coins, (raise)
    5 - the bot changes the bet (call)
*/   
std::vector<int> AIPlayer_normal::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Dealler& dealler, int currentBet, bool Allin, int raund, bool ifReboot) {
    
    if (currentBet < 0 || (raund < 0 || raund > 6)) {
        throw std::invalid_argument("Invalid argument!");
    }

    // Correct negative bets
    currentBet = std::max(0, currentBet);
    
    int playerChips = player->getChips();
    
    if (playerChips <= 0) return { 0, 1, 0, 0, 0 };
    
    std::vector<Card> playerHand = player->getAllCards();

    if (playerHand.empty()) {
        throw std::invalid_argument("Player hand is empty!");
    }

    int remainingChips = playerChips - currentBet;

    // If already all-in or not enough chips to continue betting
    if (Allin || playerChips <= currentBet) {
        return {0, 0, 1, 0, 0};  // Agree with current bet and go all-in
    }
    if (ifReboot == true) {
        return {1, 0, 0, 0, 0};
    }

    // Calculate the probability of winning based on the bot's hand
    float winProbability = 0.0f;
    try {
        winProbability = calculateWinningProbability(playerHand, cardsOnTable, dealler);
    } catch (...) {
        winProbability = 0.3f; // Default probability on error
    }

    int agreeWithBet = 0;
    int pass = 0;
    int allIn = 0;
    int raiseAmount = 0;
    int callAmount = 0;


    // Decision-making logic based on winning probability
    if (winProbability < 0.2f) {
    
        pass = 1;  // Fold if the win probability is too low
        
    } else if (winProbability >= 0.2f && winProbability < 0.5f) {
        // If the win probability is moderate
        if (raund == 1) {

            int proposedCall = currentBet + static_cast<int>(remainingChips * 0.1);
            callAmount = (proposedCall < currentBet) ? currentBet : proposedCall;
            callAmount = std::min(callAmount, playerChips); // Ensure doesn't exceed chips

        }
        else {

            raiseAmount = std::max(0, static_cast<int>(remainingChips * 0.2));
            raiseAmount = std::min(raiseAmount, playerChips - currentBet); // Ensure doesn't exceed chips

        }
    } else if (winProbability >= 0.5f && winProbability < 0.8f) {
        // If the win probability is good
        if (raund == 1) {
        
            if (currentBet + remainingChips * 0.2 >= remainingChips) {
            
                agreeWithBet = 1;
                
            } else {
            
                callAmount = currentBet + static_cast<int>(remainingChips * 0.2);
                callAmount = std::min(callAmount, playerChips); // Ensure doesn't exceed chips
                
            }
        } else {
        
            raiseAmount = static_cast<int>(remainingChips * 0.4);
            raiseAmount = std::min(raiseAmount, playerChips - currentBet); // Ensure doesn't exceed chips
        }
    } else {
        // If the win probability is very high
        allIn = 1;

    }
    
    // Ensure all values are non-negative
    raiseAmount = std::max(0, raiseAmount);
    callAmount = std::max(0, callAmount);
    
    return {agreeWithBet, pass, allIn, raiseAmount, callAmount};
}
