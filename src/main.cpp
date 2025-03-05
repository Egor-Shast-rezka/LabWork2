/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"


int main() {

    Game game;
    // Timer timer;
    
    // std::thread timerThread(&Timer::setTimerForGame, &timer, 20);
    
    game.startGame();
    
    //if (timerThread.joinable()) {
    //    timerThread.join();
    //}

    // std::cout << "Game and timer processes finished." << std::endl;
    
    return 0;
}
    
    
    
    
