/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


// -------------
AIPlayer_easy::AIPlayer_easy(std::string name) : Player(name) {}

bool AIPlayer_easy::isBot() {
    return true;
}


//=================
std::vector<int> AIPlayer_easy::BotActions(std::unique_ptr<Player>& player, std::vector<Card> cardsOnTable, Deck& deck, int currentBet, bool Allin, bool ifReboot) {

    int chips = player->getChips();

    std::vector<int> action(3, 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> chanceReboot(1, 5);
    if (chanceReboot(gen) == 1 || ifReboot) {
        action[0] = 0;
        action[1] = 0;
        action[2] = 0;
        return action;
    }
    
    std::uniform_int_distribution<> chanceAllin(1, 20);
    if (chanceAllin(gen) == 1 || Allin) {
        action[0] = chips;
        action[1] = 0;
        action[2] = 1;
        return action;
    }

    std::vector<float> weights;
    float sumWeights = 0.0;

    for (int i = currentBet; i <= chips; i++) {
        float weight = 1.0f / (i - currentBet + 1);
        weights.push_back(weight);
        sumWeights += weight;
    }

    std::vector<float> probabilities;
    float cumulativeProbability = 0.0f;
    for (float weight : weights) {
        cumulativeProbability += weight / sumWeights;
        probabilities.push_back(cumulativeProbability);
    }

    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    for (std::size_t i = 0; i < probabilities.size(); i++) {
        if (randomValue < probabilities[i]) {
            action[0] = i + currentBet;
            action[1] = 0;
            action[2] = 0;
            return action;
        }
    }


    action[0] = 0;
    action[1] = 0;
    action[2] = 0;
    return action;
}


// -------------
AIPlayer_normal::AIPlayer_normal(std::string name) : Player(name) {}

bool AIPlayer_normal::isBot() {
    return true;
}

