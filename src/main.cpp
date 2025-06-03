/*
    Egor Shastin st129457@student.spbu.ru
    
    This code initializes a game by creating an instance of the Game class and setting the game mode using the setMode method. The necessary header files are included for the game’s rules, pathfinding, game mode configurations, bots, and character definitions. The program sets up the game environment and then exits.
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


#include <iostream>
#include <string>
#include <cstdio>

void setTerminalSize(int rows, int cols) {

    if (rows <= 0 || cols <= 0) {
        std::cerr << "Rows and columns must be positive values.\n";
        return;
    }
    std::string command = "\x1b[8;" + std::to_string(rows) + ";" + std::to_string(cols) + "t";
    std::cout << command;
    std::cout.flush();
}

int main() {

    freopen("/dev/null", "w", stderr);
    setTerminalSize(60, 64);
    
    Game game;
    
    game.setMode();
    
    return 0;
}
  
