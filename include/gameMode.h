/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <cstring>

#ifndef GAMEMODE_H
#define GAMEMODE_H


// -------------------------
class EaggedDeck : public Deck {
public:
    EaggedDeck();
    
    void viewNextCard();
};


// -------------------------
class AllBots : public Game {
public:
    void setup(Game& game);
};


// -------------------------
class MoreChances : public Game {
public:
    void setup(Game& game);


// -------------------------
class OneOnOne : public Game {
public:
    void setup(Game& game);
};


// -------------------------
class WithoutCards : public Game {
public:
    void setup(Game& game);
};

#endif
