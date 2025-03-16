# System Description

## Introduction
This system is a simulation of a card game of poker with players (both real and virtual bots), a dealer, and gameplay with cards. The game is developed in C++ using object-oriented programming (OOP) to simulate various aspects of the game. The system implements such elements as a deck of cards, players, bets, and additional elements - characters with unique abilities that add variety to the gameplay.

## System Architecture
The game is based on the interaction of several key classes, each of which is responsible for a certain part of the gameplay. The system is organized as a set of objects (classes) that handle player actions, deck management, and game play.

## Main System Components
### Players (Player and descendants):
Represent real players and bots.
Players can place bets, receive cards, and interact with the game bank.
Descendants of the Player class include bots with different difficulty levels (AIPlayer_easy, AIPlayer_normal) and characters with special abilities (AllSeeingPlayer, CheaterPlayer, EngagedDeckPlayer, DeallersFrendPlayer, PhotographicMemoryPlayer, BettingManipulatorPlayer)

### Cards:
This class represents a single card that has a rank and a suit. It provides methods for displaying the card, setting the card's value, and getting the card's value.

### Deck:
This class manages a deck of 52 cards. It provides methods for shuffling the deck, dealing cards, and returning cards to the deck.

### Hand:
This class contains the set of cards that the player has in his hand. It provides methods for adding and removing cards, as well as displaying cards on the screen.

### Bank:
This class is responsible for managing the players' bets and the current bets of the game. It allows you to place and receive bets, as well as add money to the bank.

### Dealler:
The dealer manages the deck and is responsible for dealing cards to the players. The dealer also keeps order in the game and interacts with the bank and the players.
The dealer also finds the winner of the game.

### ContactWithPlayer:
This helper class is used to validate and transform data entered by the player. It handles user input.

### Characters:
Characters are special types of players with unique abilities.
1) AllSeeingPlayer - Player who can look at any one card of any player.
2) CheaterPlayer - Player who can replace one of his cards with the first card from the deck, his old card is sent back to the deck in a random place.
3) EngagedDeckPlayer - Player who can look at the top card of the deck.
4) DeallersFrendPlayer - Player who can replace the last card put on the table.
5) PhotographicMemoryPlayer - Player who can look at the remaining cards in the deck.
6) BettingManipulatorPlayer - Player who can steal platers money from bank.

### Bots (AIPlayer_easy, AIPlayer_normal):
Bots are controlled by the system and make decisions based on the game state. The difficulty level of the bot determines its behavior.
There are 2 types of bots: simple, normal. The maximum number of bots is 23 (excluding the player and with standard rules of the game with 2 cards for the player and 3 cards on the table).
1) A simple bot acts completely randomly, does not pass, and only goes all-in if the player does so.
2) A normal bot calculates the chance of winning based on the cards in hand and the remaining cards in the deck, can pass and go all-in.

### Timer:
The Timer class is used to manage the time aspect of the game. It ensures that each turn has a defined duration and adds time-based constraints to the gameplay. This helps to simulate a more realistic gaming environment, where players or bots have to make decisions within a certain timeframe.

## Rules:
The Rule class defines the set of rules for the game. This class is responsible for managing the guidelines under which the game operates and how the game state is determined based on actions made by players or bots. The rules help to maintain fairness and consistency in gameplay.

### Game:
The Game class is the core of the card game system, responsible for managing the game flow and the interactions between all the game components (players, cards, bank, dealer, etc.). It manages the setup of the game and oversees the state changes as the game progresses.

## Game Process

### Game Setup: 
The game begins with the selection of the mode and settings. The player is asked to choose whether he wants to play with a character, and if so, he can choose from the available options. The game mode is also selected: "AllBots" or "OneOnOne" with a bot. The initial number of chips for all participants in the game is set.

### Dealing the cards: 
After setting up, the dealer shuffles the deck and deals two cards to each player. Information about the players' cards is displayed only for the live player, and the bots' cards are hidden.

### Game Rounds: 
The game consists of three rounds, in each of which the dealer places one card on the table, starting with the first card. During each round, players and bots perform actions such as betting, folding, calling, or going into "all-in" mode. The specifics of the players' actions depend on the presence of the selected character, which can influence the game process with its unique abilities.

### Player Actions: 
During a round, each player and bot takes turns performing actions. Bots act based on algorithms, taking into account the current bets, the presence of All-in, and their strategy. A live player makes a choice manually by responding to requests. If a player plays with a character, he can use special abilities.

### Raising the bet: 
If a player or bot raises the bet, other participants must match the current bet or fold. Bots can also place bets, go All-in, or fold.

### Ending the Round: 
Each round ends after all participants have either matched the current bet or folded. The dealer then places a new card on the table and the next betting round begins.

### Continuing the Game: 
The game continues until the current match ends or players decide to stop playing.

### Game:
The main management class that controls the gameplay. It creates players, assigns them starting cards, manages the bank and dealer, and starts and controls game cycles.
The game also supports various modes, such as one-on-one play, bot play, etc.
The startGame method starts the game, initiating the distribution of cards, collecting bets, and choosing a winner.

## Game modes
1) One-on-one - play against a real player on one device.
2) Bot play - allows you to play with multiple bots controlled by the system.
