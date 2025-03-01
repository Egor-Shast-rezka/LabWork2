# Lab1.
Егор Шастин Олегович, gruppa b81-mm
Contact: st129457@student.spbu.ru,egor.shast0.0@gmail.com

# Poker Project

## Overview

This project is a C++ implementation of a poker game that simulates gameplay with human players and AI-controlled bots. The game follows basic poker rules, where players receive cards, place bets, and the dealer determines the winner based on the best hand.

## Table of Contents
- [Installation and Build](#installation-and-build)
- [Tests](#tests)

## Installation and Build

### Building the Project

```sh
make
```

### Running the Game
To start the game, run the compiled executable:

```sh
./bin/Poker
```

## Tests

#### Continuous Integration (CI)
This project uses GitHub Actions for automated builds and testing. All tests are run in the CI pipeline on every commit.

#### Running Tests Locally
To run tests locally, you can use the following commands:

```sh
make test_base    # Runs tests for base game components
make test_bot     # Runs tests for bot behavior
make test_game    # Runs full integration tests for the game logic
```

### Contact
- Author: Egor Shastin
- Email: egor.shast0.0@gmail.com
