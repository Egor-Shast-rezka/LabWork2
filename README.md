# Lab1.
Егор Шастин Олегович, gruppa b81-mm
Contact: st129457@student.spbu.ru,egor.shast0.0@gmail.com

# Poker Project

## Overview

This project is a C++ implementation of a poker game that simulates gameplay with human players and AI-controlled bots. The game follows basic poker rules, where players receive cards, place bets, and the dealer determines the winner based on the best hand.

## Table of Contents
- [Installation and Build](#installation-and-build)
- [Tests](#tests)
- [Document](#document)

## Installation and Build

### Required Libraries and Tools

Before building the project, make sure you have the following libraries and tools installed on your system:

| Package Name       | Description                            |
|--------------------|--------------------------------------|
| `make`             | Build automation tool                 |
| `cmake`            | Cross-platform build system          |
| `libasound2-dev`   | ALSA (Advanced Linux Sound Architecture) development files for audio support |
| `libgtest-dev`     | Google Test development files for unit testing framework |

### Installing on Ubuntu/Debian

```sh
sudo apt update
sudo apt install make cmake libgtest-dev libasound2-dev
```

### Building the Project

```sh
make
```

### Running the Game
To start the game, run the compiled executable:

```sh
make run
```

## Tests

#### Continuous Integration (CI)
This project uses GitHub Actions for automated builds and testing. All tests are run in the CI pipeline on every commit.

#### Running Tests Locally
To run tests locally, you can use the following commands:

```sh
make
make test          # Runs tests for all code
```

## Document
[Drawio to open UML diagramm](https://app.diagrams.net/)
