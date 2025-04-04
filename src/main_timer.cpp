/*
    Egor Shastin st129457@student.spbu.ru
    
    This code initializes the timer for the game. The program infinitely reads all lines from the temporary file.
    
*/


#include <iostream>
#include <cstdlib>


int main() {
    std::cout << "==========Start Timer==========\n";

    while (true) {
        system("cat /tmp/timerData");
    }

    return 0;
}
