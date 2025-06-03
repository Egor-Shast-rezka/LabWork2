/*
    Egor Shastin st129457@student.spbu.ru
    
    This code defines the structure of a card game, incorporating multiple components such as game modes, timers, players, bots, and characters. The game can be customized with timers and various player types, including special characters with unique abilities. The game logic involves dealing cards, making moves, and determining winners.
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "gameMode.h"
#include "bots.h"
#include "characters.h"
#include "music.h"


#include <iostream>
#include <string>
#include <vector>


// =========== printAsciiArt =============

void printAsciiArt(const std::string& text) {

    std::vector<std::string> P = {
        "#### ",
        "#   #",
        "#### ",
        "#    ",
        "#    "
    };

    std::vector<std::string> O = {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    };

    std::vector<std::string> K = {
        "#  # ",
        "# #  ",
        "##   ",
        "# #  ",
        "#  # "
    };

    std::vector<std::string> E = {
        "#####",
        "#    ",
        "###  ",
        "#    ",
        "#####"
    };

    std::vector<std::string> R = {
        "#### ",
        "#   #",
        "#### ",
        "# #  ",
        "#  # "
    };

    std::vector<std::string> S = {
        " ####",
        "#    ",
        " ### ",
        "    #",
        "#### "
    };
    
    std::vector<std::string> T = {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    };

    std::vector<std::string> A = {
        "  #  ",
        " # # ",
        "#####",
        "#   #",
        "#   #"
    };

    std::vector<std::string> space = {
        " ",
        " ",
        " ",
        " ",
        " "
    };
    
    std::vector<std::string> G = {
        " ####",
        "#    ",
        "# ###",
        "#   #",
        " ####"
    };

    std::vector<std::string> M = {
        "#   #",
        "## ##",
        "# # #",
        "#   #",
        "#   #"
    };
    
    std::vector<std::string> V = {
        "#   #",
        "#   #",
        "#   #",
        " # # ",
        "  #  "
    };

    std::map<char, std::vector<std::string>> ascii_map;
    ascii_map['P'] = P;
    ascii_map['O'] = O;
    ascii_map['K'] = K;
    ascii_map['E'] = E;
    ascii_map['R'] = R;
    ascii_map['S'] = S;
    ascii_map['T'] = T;
    ascii_map['A'] = A;
    ascii_map['G'] = G;
    ascii_map['M'] = M;
    ascii_map['V'] = V;
    ascii_map[' '] = space;

    int height = P.size();

    for (int i = 0; i < height; ++i) {

        for (char c : text) {

            auto it = ascii_map.find(c);
            if (it != ascii_map.end()) {
                std::cout << it->second[i] << " ";
            } else {
                std::cout << "      ";
            }
        }
        std::cout << std::endl;
    }
}

// =========== printAsciiArt =============

void printAsciiArt(int index) {
    switch(index) {
    case 1:
        std::cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣤⣤⣤⣴⣶⣿⣿⣿⣶⣶⣤⣤⣤⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣾⣿⣿⣿⣿⡿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⣿⣿⡿⠋⠁⠀⠀⠀⠉⠙⠛⠻⠿⢿⣿⣿⣿⣿⣿⣿⣷⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⠟⠋⠁⢸⣿⣿⠁⠀⠀⠀⢸⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⢿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡏⠀⠀⠀⢸⣿⣿⠀⠀⠀⢀⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⡇⠀⠀⠀⢸⣿⣿⠀⠀⠀⣸⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⠀⠀⠀⢸⣿⣿⠀⠀⢀⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⡆⠀⠀⢸⣿⣿⠀⠀⣸⣿⡟⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⠀⠀⢸⣿⣿⠀⢠⣿⣿⠃⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⢠⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀)" << "\n";
        break;
    case 2:
        std::cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣤⣤⣶⣶⣶⣶⡶⣴⣿⡿⢹⣿⣿⣿⣿⣿⣿⡖⣴⣶⣷⣶⣤⣀⡢⠤⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠏⢿⣿⣿⣿⣿⣿⡇⢸⣿⢃⡘⣿⣿⣿⣿⣿⣿⢑⣿⡿⠃⣿⣿⣿⣿⣿⣶⣯⣵⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⣄⣤⣴⣶⣿⣯⢸⣿⠰⠘⣿⣿⣿⣿⣿⣧⣼⣏⣤⡄⣿⣿⣿⣿⣿⠇⣼⡿⠁⠃⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣤⣆⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢰⣾⡿⢿⣿⣿⣿⣿⣿⣿⣸⣿⣰⣦⣹⣿⣿⣿⣿⠀⣿⠿⠉⢿⣿⣿⣿⣿⣟⢰⣿⣷⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠘⣿⣷⢀⢻⣿⣿⣿⣿⣿⠉⣟⠉⠁⠈⣿⣿⣿⡿⣄⣿⣦⣠⣤⣿⣿⣿⡿⢌⣿⣏⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢹⣿⠈⣤⣻⣿⣿⣿⣿⡀⣿⣶⣤⣾⣿⠏⠁⠀⢹⣿⣿⣿⣿⣿⣿⣿⡓⣼⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢿⣿⠟⠻⢿⣿⣿⣿⡇⢻⣿⣿⣿⡏⠀⠀⠀⢸⣿⣿⣿⣿⣿⡿⠏⢱⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠸⣿⣀⣠⣼⣿⣿⣿⡇⢸⣿⣿⣿⣷⡀⠀⠈⣿⣿⣿⣿⣿⡏⠀⢀⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)" << "\n";
        break;
    case 3:
        std::cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠀⠠⠀⢀⣀⠠⠄⠐⠒⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠄⣒⠍⠀⠀⠒⠒⠛⠓⠖⢉⣁⢀⣒⠛⠛⠋⡍⠛⠋⠠⢀⣑⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⠄⠒⠋⠉⠉⡇⢀⡞⠉⢳⠀⠀⢰⠀⢠⣧⡜⠁⠀⠀⡸⠀⠀⡐⡇⠀⠈⠉⠛⠩⠍⣁⠐⠒⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⠠⠐⠚⠁⠀⠈⢻⠀⠀⠀⡇⠈⣧⠤⡸⡀⠀⡸⠀⣸⡁⣳⡀⠀⢀⠁⢠⡞⠂⡇⠀⠀⠀⠀⠀⠀⠀⠉⠀⠂⠤⢀⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠠⠐⠈⢀⠠⡀⠀⠆⠀⢀⡘⡆⠀⠀⠁⠀⠈⢁⠙⠃⠀⡇⠀⢀⣠⠀⠀⠀⡆⠀⠀⣀⠘⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠒⠠⠀⠀⠀
⠀⠀⠇⠐⣆⢸⡀⠸⡄⢰⠀⠈⠉⡁⠀⠀⢸⠀⣠⣿⣷⣄⢀⠃⢰⣿⣿⣷⠀⠘⠀⣴⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀
⠀⠀⠘⡄⠘⣆⠑⠀⠁⠀⠇⠀⣰⣿⣷⡄⢸⠀⠙⠻⠟⠃⢸⠀⠀⠉⠋⠉⢠⠁⠀⠈⠟⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⠀
⠀⠀⠀⠘⡈⠁⢀⣶⣤⣄⠰⠀⠙⠛⠏⠁⢸⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠎⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀
⠀⠀⠀⠀⠰⡀⠸⣿⢿⠋⠀⡆⠀⠀⠀⠀⠘⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀)" << "\n";
        break;
    case 4:
        std::cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠠⠀⠀⠲⣶⠶⠶⠶⠶⠶⢶⡶⠀⠀⠄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣥⣤⠄⣠⣵⣶⣿⠛⠿⢹⢉⣛⢻⣷⣶⣥⡀⢤⣤⣵⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡧⡘⢿⣿⣿⣿⠲⢤⢠⢠⡀⢈⣿⣿⡿⠟⠸⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣶⣤⣀⣀⠘⢉⣭⣿⣿⣾⣾⣿⣯⣍⠓⢀⣀⣠⡴⣾⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⡄⢸⠉⣿⣿⢹⣿⣿⣿⣿⣿⡏⠉⢹⡇⠀⢸⡇⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣷⡼⢤⣿⣿⣸⣿⣿⣿⣿⣿⣇⣀⣸⣧⣤⣼⠷⠟⣋⣥⣶⣶⡤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⡇⢸⡇⣿⣿⠉⣿⣿⣿⣿⣿⡏⠉⠉⡇⠀⣴⣿⣿⡟⢿⣿⢿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡿⢿⣿⣾⣧⣿⣿⣄⣿⣿⣿⣿⣿⣇⣀⠤⠧⡄⡿⠿⠛⡇⠈⢡⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⡇⢸⡆⣿⣿⠈⣿⣿⣿⣿⣿⡇⠀⠀⡇⠀⠀⡇⡧⠶⢚⣧⠀⢸⣿⣿⣿⣆⢾⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣷⠻⡿⢤⣿⣿⣿⣿⣿⣧⣤⣴⠧⠶⡿⠇⢱⣾⣿⢿⣦⡜⡿⢻⠉⢹⣮⢿⡄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⠀⡇⢸⣿⡇⣿⣿⣿⣿⣿⡇⠀⠀⡇⠀⠈⣏⣤⣶⣿⣷⢻⠸⡂⠨⠜⣎⣿⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⡏⢻⠛⣿⣾⢿⣷⣿⣿⣿⣿⡿⠷⢶⡖⠓⢹⡇⠸⣿⣿⣿⣿⣧⢯⣥⠀⠇⣻⣸⣧⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣇⣸⠀⣿⣿⢸⣿⣿⣿⣿⣿⡇⠀⢸⡇⠀⣸⣧⣇⢻⣿⣿⣿⣿⣮⢳⣤⣾⣿⡇⠈⠄⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⠉⣿⠛⣿⡶⢿⣿⣿⣿⣿⣷⠶⠚⢻⠛⠉⢹⠀⠆⢻⠉⠀⠈⣟⠀⠹⢿⣿⡇⠄⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠄⣡⢈⣿⡇⢸⣿⣿⠿⠟⢛⣀⣠⣤⣤⣴⠶⠶⠂⠀⠁⠀⠛⠉⣧⡀⠀⣭⣴⣦⠰⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⢉⠩⠀⢀⠠⣙⣯⡽⣖⢒⢘⣛⢻⣿⣷⣶⡄⢻⣿⣿⣿⣦⣹⣿⣿⠇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣥⣤⢊⣶⣿⣿⣯⣀⣈⢈⡀⣀⢈⣿⣿⠟⠁⠚⢋⣹⣿⡿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡿⠌⠛⠿⠿⠿⠤⠬⢤⣂⣛⣯⣥⣀⣀⠤⠒⣿⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⣦⠤⣤⢤⣤⣾⢿⣿⣿⣿⣿⣿⠉⠁⢻⠀⠀⢹⠤⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⡀⢻⠈⣿⣷⠘⣿⣿⣿⣿⣿⣆⠠⠼⠒⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠚⠒⠛⠛⠒⠛⠋⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)" << "\n";
        break;
    }
}


// ===========Timer=============

Timer::Timer(Game& game) : game(game) {};

void Timer::SetExist(bool ex) {
    
    exist = ex;
}

void Timer::setSecondForTimer(int second) {
    
    seconds = second;
    SetExist(true);
}
    
bool Timer::IsExist() {
    
    return exist;
}
    
void Timer::TimerStart() { 

    if (seconds <= 0) return;
    
    system("rm -f /tmp/timerData");
    system("mkfifo /tmp/timerData");
    
    system("gnome-terminal -- bash -c \"g++ -o bin/start_timer TimerData/main_timer.cpp && ./bin/start_timer bash\"");

    auto start = std::chrono::steady_clock::now();
    std::string line;

    // Loop until the specified number of seconds have passed
    while (true) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start;

        // If the specified amount of time has passed, exit the loop
        if (elapsed.count() >= seconds) {
            system("echo \"Timer finished!\" > /tmp/timerData");
            game.timeIsUp = true;
            break;
        }

        // Pause for 1 second so that the timer does not load the processor
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Print the remaining time
        std::string command = "echo \"Time left: " + std::to_string(seconds - static_cast<int>(elapsed.count())) + " seconds\" > /tmp/timerData";

        system(command.c_str());
        
    }
    std::cout << "--\nTimer finised, game over.\n";
    game.timeIsUp = true;
}


// ===========Game=============

Game::Game() : contact(*this) {
    timer = std::make_unique<Timer>(*this);
}
Game::~Game() {
    if (musicThread.joinable()) {
        if (melody) melody->stop();
        musicThread.join();
    }
}

// Creating players
void Game::setPlayer(std::string name) {
    players.push_back(std::make_unique<Player>(name, *this));
}

std::vector<std::unique_ptr<Player>>& Game::getPlayer() {
    return players;
}

void Game::setDealler() { // Creating a dealer.
    Dealler diller;
    dealler = diller;
}

Dealler& Game::getDealler() {
    return dealler;
}

std::vector<Card>& Game::getAllCardsForTable() {
    return cards;
}

// Function for adding bots
void Game::setBot(std::string name, int index) {
    
    switch(index) {
        case 1:
        
            players.push_back(std::make_unique<AIPlayer_easy>(name, *this));
            break;
    
        case 2:
        
            players.push_back(std::make_unique<AIPlayer_normal>(name, *this));
            break;
            
    }
}

void Game::setPlayerCharacter(std::string name, int index) {
    
    switch(index) {
        case 1:
        
            players.push_back(std::make_unique<AllSeeingPlayer>(name, *this));
            break;
            
        case 2:
        
            players.push_back(std::make_unique<CheaterPlayer>(name, *this));
            break;
            
        case 3:
        
            players.push_back(std::make_unique<EngagedDeckPlayer>(name, *this));
            break;
            
        case 4:
        
            players.push_back(std::make_unique<DeallersFrendPlayer>(name, *this));
            break;
            
        case 5:
        
            players.push_back(std::make_unique<PhotographicMemoryPlayer>(name, *this));
            break;
            
        case 6:
        
            players.push_back(std::make_unique<BettingManipulatorPlayer>(name, *this));
            break;
    }

}

Bank& Game::getBank() {

    return bank;
    
}

bool Game::getCharacter() {

    return Character;
    
}

void Game::resetGame() {
    
    if ((static_cast<int>(players.size()) * 2 + 3) * (CountGame + 2) > 52) {
    
        CountGame = 0;
        dealler.newDeck();
        dealler.shuffleDeck();
        
        std::cout << "> The cards are out. Get new colode!\n";
    }
    
    CountGame++;
    
    cards.clear();
    bank.setCurrentBet(0);
    bank.setCountBetEachPlayer(static_cast<int>(getPlayer().size()));
    
    // Remove all player's cards
    for (auto& player : players) {
        player->delAllCards();
    }
}

bool Game::checkContinueGame() {

    std::string act = contact.answerUserCheckString("Do you want to continue the game? (y/n): ");
    
    while (!(act == "y" || act == "n")){
    
        std::cerr << "ERROR: Write 'y' or 'n'!\n";
        
        act = contact.answerUserCheckString("Do you want to continue the game? (y/n): ");
        
    }

    return act == "y";
}

void Game::setChipsAllPlayer(int count) {
    for (auto& player : players) {
        player->setChips(count);
    }
}

std::string Game::getValidAction(std::vector<std::string> actions, std::string prompt, std::vector<bool> ifActPlayerData, int index) {
            
    std::string action;
                
    while (true) {
                
        action = contact.answerUserCheckString(prompt);
                    
        if (std::find(actions.begin(), actions.end(), action) != actions.end()) {
                    
            if (action == "act" && ifActPlayerData[index]) {
                        
                std::cerr << "ERROR: Player can only use the ability once per round.\n";
                            
            } else {
                        
                return action;
                            
            }
        } else {
                    
            std::cerr << "ERROR: Available actions: ";
                        
            for (const auto& act : actions) {
                        
                std::cerr << act << " ";
                            
            }
                        
            std::cerr << "\n";
        }
    }
}

// Main function to start the game
int Game::startGame() {
    
    if (players.empty()) {
        throw std::runtime_error("No players in the game!");
    }

    // Path game
    try {
        do {
            std::cout << "\n";
            
            bool Allin = false; // True if somebody make an Allin
            dealler.shuffleDeck(); // The dealer shuffles the deck

            // Create vector for allin and pass
            std::vector<bool> DataPass(players.size(), false);

            // Array for storing player character actions 
            std::vector<bool> ifActPlayerData(players.size(), false);

            // Distribute cards to the players
            for (auto& player : players) {
                dealler.dealCards(2, *player);
            }

            // Output information about players
            gamemode[0]->OutputInfoPlayers();

            // Array with number
            std::vector<std::string> Numbers = { "First", "Second", "Third" };

            for (int raund = 1; raund <= 3; raund++) {
                Card card = dealler.getOneCard(); // Get card from deck
                cards.push_back(card);
                printAsciiArt(raund);
                std::cout << "\n-> " << Numbers[raund - 1] << " card: ";
                card.display();
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                gamemode[0]->GameModePathGame(DataPass, ifActPlayerData, Allin, raund);

            }

            std::vector<Player> player_refs;
            for (const auto& player : players) {
                player_refs.push_back(*player);
            }

            std::vector<int> answer = dealler.SearchWinner(player_refs, cards, DataPass);

            for (std::size_t count = 0; count < answer.size(); count++) {

                if (answer[count] == 123456) {
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    std::cout << "-> All players make a pass!\n";
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                }
                else if (answer[count] == -2) {
                    std::cout << "Player: " << count + 1 << " - " << players[count]->getName() << " make a pass!\n";
                }
                else if (answer[count] == -3) {
                    std::cout << "Player: " << count + 1 << " - " << players[count]->getName() << " fool!\n";
                }
                else {
                    std::cout << "Player: " << count + 1 << " - " << players[count]->getName() << " win!\n";
                    players[count]->setChips(players[count]->getChips() + bank.getPlayerMoney());
                }

            }
            printAsciiArt(4);
            resetGame();
            
        } while (checkContinueGame() && !timeIsUp);

    } catch (const std::runtime_error& e) {
        std::cout << "\n----------\n" << e.what() << "\nGame over!\n";
    }

    std::cout << "\n";
    std::cout << "\n================================================================\n\n";
    printAsciiArt("    GAME OVER");
    std::cout << "\n================================================================\n";
    return 0;
}


void Game::setMode() {
    std::cout << "> To open rules, write 'rule'.\n";

    std::string setMusic = contact.answerUserCheckString("> Do you want to play with Music? (y/n): ");
    while (!(setMusic == "y" || setMusic == "n")) {
        std::cerr << "ERROR: Write 'y' or 'n'!\n";
        setMusic = contact.answerUserCheckString("> Do you want to play with Music? (y/n): ");
    }

    if (setMusic == "y") {
        int type = contact.answerUserCheckInt("> Write the music type (1-random note, 2-parts, 3-grasshopper): ");

        while (!(type >= 1 && type <= 3)) {
            std::cerr << "ERROR: Write 1 or 2 or 3!\n";
            type = contact.answerUserCheckInt("> Write the music type (1-random note, 2-parts, 3-grasshopper): ");
        }

        // Create Generator and engine
        auto melodyGenerator = std::make_unique<RandomMelodyGenerator>();
        auto engine = std::make_unique<AudioEngine>();

        melody = std::make_unique<InfiniteMelodyPlayer>(*engine, *melodyGenerator);

        this->engine = std::move(engine);
        this->melodyGenerator = std::move(melodyGenerator);

        // Generations sound
        std::vector<std::unique_ptr<SoundGenerator>> generators;
        generators.push_back(std::make_unique<SquareWaveGenerator>());
        generators.push_back(std::make_unique<TriangleWaveGenerator>());
        generators.push_back(std::make_unique<SawWaveGenerator>());
        generators.push_back(std::make_unique<SineWaveGenerator>());

        melody->setGenerators(std::move(generators));

        musicThread = std::thread([this, type]() {
            switch (type) {

            case 1:

                melody->startInfinite_Lite();
                break;

            case 2: {

                std::vector<std::vector<double>> parts = {
                    {440.0, 440.0, 493.88, 523.25, 523.25, 493.88, 440.0, 392.0},
                    {440.0, 440.0, 392.0, 392.0, 440.0, 440.0, 392.0},
                    {440.0, 440.0, 493.88, 523.25, 523.25, 493.88, 440.0, 392.0},
                    {440.0, 392.0, 440.0, 493.88, 440.0, 392.0, 349.23, 329.63},
                    {329.63, 349.23, 392.0, 440.0, 392.0, 349.23, 349.23},
                    {440.0, 440.0, 493.88, 523.25, 440.0, 392.0, 392.0},
                };
                melody->setMelodyParts(parts);
                melody->startInfinite_Part();
                break;
            }
            case 3:

                melody->startInfinite_Melody_1();
                break;
            }
        });
    }

    
    // Set Timer
    std::string setTimer = contact.answerUserCheckString("> Do you want to play with Timer? (y/n): ");
    while (!(setTimer == "y" || setTimer == "n")){
    
        std::cerr << "ERROR: Write 'y' or 'n'!\n";
        
        setTimer = contact.answerUserCheckString("> Do you want to play with Timer? (y/n): ");

    }
    
    if (setTimer == "y") {
        
        int second = contact.answerUserCheckInt("> Write the game time (at second): ");
        timer->setSecondForTimer(second);
        
    }
    
    // Set Character for Player
    std::string setCharacter = contact.answerUserCheckString("> Do you want to play with character? (y/n): ");
    while (!(setCharacter == "y" || setCharacter == "n")){
    
        std::cerr << "ERROR: Write integer 'y' or 'n'!\n";
        
        setCharacter = contact.answerUserCheckString("> Do you want to play with character? (y/n): ");

    }
        
    if (setCharacter == "y") {
        Character = true;
    }
    
    // Set game mode
    int modeChoice = contact.answerUserCheckInt("Choose game mode: 1 - AllBots, 2 - OneOnOne.\n> Write name game mode: ");

    while (!(modeChoice == 1 || modeChoice == 2)){
        
        std::cerr << "ERROR: Write integer 1 or 2!\n";
    
        modeChoice = contact.answerUserCheckInt("Choose game mode: 1 - AllBots, 2 - OneOnOne.\n> Write name game mode: ");
        
    } 
    switch(modeChoice) {
        case 1:
        
            gamemode.push_back(std::make_unique<AllBots>(*this));
            break;
            
        case 2:
        
            gamemode.push_back(std::make_unique<OneOnOne>(*this));
            break;
    }
    
    gamemode[0]->setupForGameMode();
    
    // Set count chips
    int answerPlayer = contact.answerUserCheckInt("> Write chips for all player: ");
    
    setChipsAllPlayer(answerPlayer);
    
    bank.setCountBetEachPlayer(static_cast<int>(getPlayer().size()));
    
    bank.setCurrentBet(0);

    system("clear");

    std::cout << "\n";
    std::cout << "\n================================================================\n\n";
    printAsciiArt(" POKER START");
    std::cout << "\n================================================================\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~Write 'rule' to see rules~~~~~~~~~~~~~~~~~~~\n\n";
    
    // Set Game
    if (timer->IsExist()) {
        
        std::thread timerThread(&Timer::TimerStart, timer.get());
        timerThread.detach();
        
        startGame();
        
    } else {
    
        startGame();
    }
}


// ===========Rule=============

bool Rule::resetGetRule(ContactWithPlayer& contact) {
    std::string answer = contact.answerUserCheckString("> Do you want to know any other rules?(y, n)");
    while (!(answer == "y" || answer == "n")) {
        std::cout << "ERROR: Write 'y' or 'n'\n";
        
        answer = contact.answerUserCheckInt("> Do you want to know any other rules? (y, n)");
    }
    return answer == "y";
}

void Rule::getRuleOnDisplay(ContactWithPlayer& contact) {

    std::cout << "\n\n===============Game Rule===============\n";
    
    do {
    
        int act = contact.answerUserCheckInt("> Select the rules you want to know (1-Game Rule, 2-Player Rule, 3-Character Rule, 4-Bot Rule, 5-Mode Rule, 6-Timer Rule): ");
        
        while (!(act == 1 || act == 2 || act == 3 || act == 4 || act == 5 || act == 6)) {
            std::cout << "ERROR: Please choose an integer in the range 1 - 6\n";
            act = contact.answerUserCheckInt("> Select the rules you want to know (1-Game Rule, 2-Player Rule, 3-Character Rule, 4-Bot Rule, 5-Mode Rule, 6-Timer Rule): ");
        }
    
        if (act == 1) {

            std::cout << "1) The game is a card game where players can call, raise, pass, and go all-in based on their hand.\n";
            std::cout << "2) Players can choose between multiple game modes, including All Bots and One-on-One mode.\n";
            std::cout << "3) The game includes both human players and bots, with various actions available depending on the game mode.\n";
            std::cout << "4) Players can interact with each other and the game through various characters with unique abilities.\n";
            std::cout << "\n-> To accept the current rate, enter the current rate if 'call' is selected or enter 0 if 'raise' is selected.\n";
        }
        else if (act == 2) {

            std::cout << "1) In the All Bots game mode, there is one player who can be one of six characters. The player can perform the following actions:\n";
            std::cout << "   - Call: Set new bid.\n";
            std::cout << "   - Raise: Add to current bid.\n";
            std::cout << "   - All-In: Bet all of their remaining chips.\n";
            std::cout << "   - Act: Perform an action if the player is a character (based on their special abilities).\n";
            std::cout << "   - Pass: Decline to act and move on to the next round.\n";
            std::cout << "2) In the One-on-One game mode, you can have up to 24 players. Each player can be assigned one of the six available characters.\n";
            std::cout << "   Players in this mode also have the ability to call, raise, all-in, act (if a character), and pass.\n";
        }
        else if (act == 3) {

            std::cout << "1) AllSeeingPlayer: This player can inspect the cards of other players.\n";
            std::cout << "2) CheaterPlayer: Allows a player to replace one of their cards with a new one from the deck.\n";
            std::cout << "3) EngagedDeckPlayer: his player can see the last card in the deck.\n";
            std::cout << "4) DeallersFrendPlayer: Allows a player to manipulate the cards on the table by replacing the last card with a new one from the deck.\n";
            std::cout << "5) PhotographicMemoryPlayer: This player can remember and display the remaining cards in the deck.\n";
            std::cout << "6) BettingManipulatorPlayer: Allows a player to steal chips from another player.\n";
        }
        else if (act == 4) {
 
            std::cout << "There are 2 types of bots in the game:\n";
            std::cout << "1) Easy Bot: Acts completely randomly. They do not fold and will only go all-in if the player does so.\n";
            std::cout << "2) Normal Bot: Calculates the chances of winning based on their hand, the cards on the table, and the remaining cards in the deck. This bot can fold and go all-in if necessary.\n";
            std::cout << "3) The maximum number of bots allowed is 23 (excluding the human player), with the standard setup of 2 cards for the player and 3 cards on the table.\n";
            std::cout << "4) Bots cannot be assigned characters, and their difficulty cannot be changed during gameplay.\n";
        }
        else if (act == 5) {

            std::cout << "1) All Bots Mode: In this mode, all players are bots (less to 23), except for one player who can choose one of the 6 characters. The bot players act based on predefined behaviors (easy or normal). \n";
            std::cout << "2) One-on-One Mode: This mode allows you to add up to 24 players. Each player can be given one of the 6 characters and can take part in the game accordingly.\n";
            std::cout << "3) Game Progression: In both modes, players take turns making bets, raising, calling, folding, and going all-in. The game continues until there is a winner or players decide to stop.\n";
        }
        else if (act == 6) {

            std::cout << "1) Timer Settings: Each player has a timer for their actions. The timer duration can be set before the game starts.\n";
            std::cout << "2) If the timer runs out, the game over.\n";
            std::cout << "3) You can enable or disable the timer depending on the game mode and player preferences.\n";
        }

    } while (resetGetRule(contact));
    
    std::cout << "=============Exit Game Rule===========\n\n";
}



