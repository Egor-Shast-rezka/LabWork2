#Description of system requirements

##1) General requirements:
The system must support multiplayer gameplay, where players can interact with virtual opponents (bots) or with each other, depending on the selected game mode.
Each game match must involve at least one player and one bot.
Support for both a text interface for user interaction and automatic execution of actions by bots.
All game actions must be performed sequentially in turn, ensuring fairness of the move for each participant.

##2) Player requirements:
A player can be either a live user or a bot controlled by artificial intelligence.
The game must provide for different types of bots, with different difficulty levels: "easy" and "normal".
Players can choose a character with unique abilities that can be used during the game. The choice of character must affect the actions available to the player during the game.

##3) Game modes:
Two game modes are supported:
All vs. bots (AllBots): in this mode, all players except one are bots.
One-on-One (OneOnOne): In this mode, one live player plays against one bot.

##4) Dealer:
The dealer is responsible for creating a new deck of cards at the start of each new game, shuffling it, and dealing the cards to the players.
The dealer also monitors the current state of the deck and places one card on the table for each round of play, as well as choosing the winner.

##5) Banking:
The game must support a banking function that stores the total bet for the current round (the pot), as well as the player's current bet.
Players can place bets, increase the current bet, or go All-in.
The pot is reset at the start of a new game.

##6) Characters:
Players can choose from six characters, each with a unique ability. An ability can be used once per round.
Characters affect the gameplay by providing the player with additional actions.

##7) End of game:
Players should be able to continue or end the game after each match is completed. The choice is made through a query interface with a yes or no answer.


#Usage Scenarios

##Scenario 1: Game Setup
The system asks the player if he wants to select a character (y/n).
The player selects a character or declines to select.
The system prompts the player to select a game mode (1 - AllBots, 2 - OneOnOne).
The player selects a game mode.
The system asks the player for the number of chips for all participants.
The player enters the number of chips.
The game starts dealing cards.

##Scenario 2: Gameplay (Round)
The dealer shuffles the deck and deals two cards to each player.
The system displays card information for the live player and hides the bot cards.
The dealer places one card on the table.
Players and bots take turns performing actions: placing bets, passing, or switching to All-in mode.
If the player is alive, he enters his actions through the interface (possible commands: pass, call, allin, act).
Bots automatically make decisions based on the current game situation.
The round ends when all players have completed their actions.

## Scenario 3: Using a character's ability
If a player has selected a character, they are given the opportunity to activate their ability (act).
The system checks whether the player has used the ability in the current round, if not, the ability is activated.
The character performs an action that changes the gameplay.

##Scenario 4: Ending a round and starting a new one
After the third round is completed, the system asks the player if they want to continue the game (y/n).
If the player chooses "yes", the game continues with a new deal of cards.
If the player chooses "no", the game ends the current session.

##Scenario 5: Managing bets
At the beginning of the round, the system asks the player for the amount of their bet (unless the player has decided to fold or go all-in).
The player enters a bet.
The system checks whether the bet exceeds the current pot and places it in the pot.
Bots make similar decisions based on their difficulty level.

##Scenario 6: Reset the game
If the number of cards in the deck is not enough to continue the game, the system automatically resets the game.
The dealer creates a new deck and shuffles it.
All bets and players' cards are reset.
