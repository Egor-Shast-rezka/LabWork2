/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>
#include <cmath>


#ifndef CHARACTERS_H
#define CHARACTERS_H


// -------------------------
class PlayerDecorator : public Player {
protected:
    Player* player;

public:
    PlayerDecorator(Player* p);
    virtual ~PlayerDecorator();

    virtual void setName(std::string name) override;
    virtual std::string getName() const override;
    virtual void getNameOnDisplay() const override;

    virtual void setChips(int num) override;
    virtual void getChipsOnDisplay() const override;
    virtual int getChips() const override;

    virtual void PlaceBid(int num) override;

    virtual void setCard(Card elem) override;
    virtual std::vector<Card> getAllCards() const override;

    virtual void getCardsOnDisplay() const override;
    virtual int getCountCards() const override;

    virtual void delAllCards() override;

    virtual bool isBot() override;
    virtual int BotActions(int countChips, int currentBet, int Bank, int Allin) override;
};


// -------------------------
class AllSeeingPlayer : public PlayerDecorator, public Game {
public:
    
    AllSeeingPlayer(Player* p);
    
    Card CheckCardEnemy(Game& game, int player, int card);
    
    Card CharacterActions(Game& game, int player, int card);
};

/*
// -------------------------
class CheaterPlayer : public PlayerDecorator, public Game {
public:
    
    CheaterPlayer(Player* p);
    
    bool isCharacter() override;
    
    void ReplaceCardInHand(Game& game, Dealler& dealler, int card);
    
    int CharacterActions();
};

*/
#endif
