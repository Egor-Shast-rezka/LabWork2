#RUS:
# Описание системы

## Введение
Данная система представляет собой симуляцию карточной игры, состоящую из игроков (как людей, так и ботов), дилера, и набора карт. Игра разработана на языке C++ и реализует базовую логику карточных игр на основе ООП.

## Компоненты системы
1. Игроки (Player и AIPlayer) — базовый класс игрока и его наследники, представляющие игроков-ботов разного уровня сложности.
2. Карты (Card) — класс карты, которая содержит номер и масть.
3. Колода (Deck) — класс колоды, который генерирует и перемешивает 52 карты.
4. Рука игрока (Hand) — класс, содержащий карты, которые находятся у игрока на руках.
5. Дилер (Dealler) — класс дилера, который управляет колодой, раздает карты и отвечает за игровой процесс.
6. Меченная колода (EaggedDeck) — класс, добавляющий возможность игроку посмотреть верхнюю карту из колоды.
7. 6 Персонажей (...) — классы, добавляющие возможности игрокам, в корне изменяющие ход игры и игровые возможности участников.
8. Игра (Game) — класс, отвечающий за игровой цикл, включающий создание игроков, раздачу карт, подсчет ставок, определение победителей и т.д.

## Режимы игры.
Присуствует 4 режима игры.
1. Игра один на один с живым ироком на одном устройстве.
2. Игра с ограниченным количеством ботов.
3. Слепая игра: игра без знания своих карт.
4. Игра с изначально изменённым колличеством карт в руке.

## Взаимодействие компонентов
- В процессе игры дилер создает колоду, раздает карты игрокам и управляет процессом игры.
- Каждый игрок имеет свою руку (класс Hand), куда дилер добавляет карты.
- Игра (Game) обеспечивает взаимодействие игроков, карт и дилера, а также управляет игровым циклом (раздача карт, проверка ставок, определение победителя).




#Eng:
# System Description

## Introduction
This system is a simulation of a card game consisting of players (both humans and bots), a dealer, and a set of cards. The game is developed in C++ and implements the basic logic of card games based on OOP.

## System Components
1. Players (Player and AIPlayer) — the base player class and its descendants, representing bot players of different levels of complexity.
2. Cards (Card) — a class of a card that contains a number and a suit.
3. Deck (Deck) — a class of a deck that generates and shuffles 52 cards.
4. Hand (Hand) — a class containing cards that the player has in his hand.
5. Dealer (Dealler) — a class of a dealer that manages the deck, deals cards and is responsible for the game process.
6. EaggedDeck — a class that adds the ability for a player to look at the top card of the deck.
7. 6 Characters (...) — classes that add abilities to players, fundamentally changing the course of the game and the gaming capabilities of the participants.
8. Game — a class responsible for the game cycle, including creating players, dealing cards, counting bets, determining winners, etc.

## Game modes.
There are 4 game modes.
1. One-on-one play with a live player on one device.
2. Play with a limited number of bots.
3. Blind play: play without knowing your cards.
4. Play with an initially changed number of cards in hand.

## Interaction of components
- During the game, the dealer creates a deck, deals cards to players and controls the game process.
- Each player has his own hand (Hand class), where the dealer adds cards. - Game ensures interaction between players, cards and the dealer, and also controls the game cycle (dealing cards, checking bets, determining the winner).



