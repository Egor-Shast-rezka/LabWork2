/*
    Egor Shastin st129457@student.spbu.ru
    
    This code initializes the timer for the game. The program infinitely reads all lines from the temporary file.
    
*/


#include <iostream>
#include <cstdlib>


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
    setTerminalSize(40, 36);
    std::cout << "============Start Timer============\n";
    std::cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡟⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡀⠀⠀⢠⣶⣶⣶⣶⣶⣶⣶⣶⡄⠀⠀⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⣄⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣠⣾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠈⠻⣷⣌⣙⣿⣿⣿⣿⣿⣿⣋⣡⣾⠟⠁⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀
⠀⠀⠀⣠⣴⣿⣿⣷⠀⠀⠀⠀⠈⠙⠻⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⣾⣿⣿⣦⣄⠀⠀⠀
⠀⠀⠀⠘⣿⣿⣿⣿⣆⠀⣀⣠⣤⣶⣾⣿⣿⣿⣿⣿⣿⣷⣶⣤⣄⣀⠀⣰⣿⣿⣿⣿⠃⠀⠀⠀
⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⠿⠟⠛⠉⠉⠉⠉⠉⠉⠛⠻⠿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣾⣿⡿⠟⠉⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠉⠻⢿⣿⣷⣄⠀⠀⠀⠀⠀
⠀⠀⠀⢠⣾⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣷⡄⠀⠀⠀
⠀⠀⣰⣿⣿⠏⠀⠀⠻⣦⡀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⢠⣴⠟⠀⠀⠻⣿⣿⣆⠀⠀
⠀⣰⣿⣿⠃⠀⠀⠀⠀⠈⠻⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠟⠁⠀⠀⠀⠀⠘⣿⣿⣆⠀
⢀⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⡀
⣸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣇
⣿⣿⡇⠀⢀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣶⣶⣶⣶⣶⣦⡀⠀⣀⣀⣀⣀⡀⠀⢹⣿⣿)" << "\n\n";
    while (true) {
        system("cat /tmp/timerData");
    }

    return 0;
}
