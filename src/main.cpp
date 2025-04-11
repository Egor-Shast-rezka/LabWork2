/*
    Egor Shastin st129457@student.spbu.ru
    
    This code initializes a game by creating an instance of the Game class and setting the game mode using the setMode method. The necessary header files are included for the game’s rules, pathfinding, game mode configurations, bots, and character definitions. The program sets up the game environment and then exits.
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"


int main() {

    Game game;
    
    game.setMode();
    
    return 0;
}
  
