/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"


// -------------
AIPlayer_easy::AIPlayer_easy(std::string name) : Player(name) {}

bool AIPlayer_easy::isBot() {
    return true;
}
    
int AIPlayer_easy::chipRandom(int count, int Allin) {
    
    if (Allin == 1) {
        return count;
    }
    std::vector<float> weights;
    float summ = 0;
    int answer = 0;

    for (int i = 1; i <= count; i++) {
        summ += i;
    }

    float cumulativeWeight = 0.0f;
    for (int i = count; i > 0; i--) {
        cumulativeWeight += static_cast<float>(i) / summ;
        weights.push_back(cumulativeWeight);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double randomValue = dis(gen);

    for (int i = 0; i < count; i++) {
        if (randomValue < weights[i]) {
            return answer;
        }
        answer++;
    }
    return 0;
}

int AIPlayer_easy::BotActions(int countChips, int currentBet, int Bank, int Allin) {
    return chipRandom(countChips, Allin);
}


// -------------
AIPlayer_normal::AIPlayer_normal(std::string name) : Player(name) {}

bool AIPlayer_normal::isBot() {
    return true;
}


// -------------
AIPlayer_hard::AIPlayer_hard(std::string name) : Player(name) {}

bool AIPlayer_hard::isBot() {
    return true;
}


