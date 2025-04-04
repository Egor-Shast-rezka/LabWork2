# System Test Plan: Poker.

## Test Framework

### Description:
The baseGameRule module contains classes for managing the game: players, cards, decks, and game actions. It contains methods for working with cards, validating user input, and performing game mechanics such as shuffling cards, playing, and counting results.

### Test Types:
1) Unit Testing
2) Functional Testing
3) Error and Exception Testing
4) Performance Testing
5) Load Testing
6) Edge Case Testing

### Test Methods:
1) Automated testing using Google Test to check class methods and their correctness under different conditions.

2) Integration testing:
Checking interactions between objects.

## gtestВaseGameRule:

### Test scenarios:
1) Unit testing of methods:
Testing the classes ContactWithPlayer, Card, Deck, Hand, Player, Bank, Dealler for correct execution of basic operations.
Testing the methods for processing user input (answerUserCheckInt, answerUserCheckString) for correctness.

2) Functional testing:
Checking the process of creating a deck, dealing cards, shuffling and drawing.
Checking the correctness of processing players' bets.
Checking the correctness of the search for a winner (SearchWinner).

3) Testing for errors and exceptions:
Checking the operation of the program when there are no cards in the deck or in the player's hands (errors related to the lack of cards).
Checking the input of incorrect data in the methods of interaction with the user.

4) Performance testing:
Evaluation of the execution time of the shuffling and dealing operations.
Evaluation of performance with a large number of players and cards.

5) Load testing:
Simulation of work with a large number of cards and players.
Checking the stability of work under extreme loads.

6) Testing edge cases:
Dealing the maximum and minimum number of cards.
Inputting edge values (zero bets, negative values, etc.).
Checking the operation of methods with empty decks and hands

## gtestBots:

### Test scenarios:
1) Unit testing
Check that the isBot() method works correctly for AIPlayer_easy and AIPlayer_normal.
Check that the BotActions() method returns the correct result for AIPlayer_easy in different game situations (bets, cards on the table, number of chips).
2) Functional testing

Check that the bot correctly responds to the "reboot" function (ifReboot = true).
Check the bot's behavior in case of a forced "all-in" (Allin = true).

3) Testing for errors and exceptions
Handle incorrect data in the BotActions() method.
Check the behavior when passing an empty list of cards on the table or with an empty deck.

4) Performance testing
Measure the execution time of the BotActions() method for a large number of chips and cards to ensure its efficiency.

5) Load testing
Simulate a large number of bots performing actions simultaneously and check the stability and correctness of the game.

6) Edge case testing
Test the bot's behavior at minimum and maximum bets (0 chips and the maximum amount of chips).
Test how the bot behaves if it has 0 chips or too few to continue the game.

## gtestCharacter:

### Test scenarios:
1) Unit testing
Test the correctness of the isCharacter() method for all characters.
Test the correctness of the result of the CharacterActions() method for each character type under basic game conditions.

## gtestGameMode:

### Test scenarios:

1) Unit Testing
Testing the setAllBots() method: Ensure that the correct number of bots are added to the game at different difficulty levels.
Testing the setupForAllBots() method: Ensure that players and bots are set up correctly, and that characters are assigned correctly.
Testing the setupForAllPlayers() method: Ensure that all players are set up correctly in OneNoOne mode.

2) Functional Testing
Testing scenarios with bots of varying difficulty: Ensure that the game continues correctly when bots of all difficulty levels are added, and that the settings are applied.
Testing character assignment: Ensure that characters are assigned correctly when a player selects them.

3) Performance testing
Checking operation with a large number of players: Test the game performance with the maximum number of players and bots to identify possible lags and errors.

4) Load testing
Simulating the game with the maximum number of bots: Check that all methods work correctly when adding the maximum number of bots of different complexity to the game.

5) Testing edge cases
Adding the minimum and maximum number of bots: Make sure that everything works correctly when adding 0, 1 and 23 bots to the game.

## gtestPathGame:

### Test scenarios:

1) Unit testing
Testing the setPlayer() method: Make sure that the method correctly adds players to the game.
Testing the setBot() method: Make sure that the method correctly creates bots of varying difficulty and adds them to the game.
Testing the setPlayerCharacter() method: Make sure that when the method is called, characters are correctly assigned to players depending on the selection.
Testing the setDealler() method: Make sure that the method correctly creates the dealer and initializes it.
Testing the setChipsAllPlayer() method: Make sure that chips are installed correctly for all players.

2) Functional testing
Testing the functionality of creating players and bots: Make sure that players and bots are added to the game correctly and have the correct parameters.
Testing the functionality of selecting a character: Make sure that when a character is selected, its stats and abilities are correctly assigned to the player.
Game Mode Test: Make sure that the game mode setup and the corresponding actions with players and bots work correctly.

3) Performance Testing
Testing performance with a large number of players: Check how the game works when adding the maximum number of players and bots, whether lags or errors occur.
Check how the game works if all players' and bots' cards are on the table at the same time.

4) Load Testing
Testing the game with maximum number of bots: Simulate the game with the maximum number of bots of varying difficulty and ensure that all methods and game logic work correctly under these conditions.
Testing the game with maximum number of players: Test the game with the maximum number of players and bots to identify possible performance or game logic issues.
