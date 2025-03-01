#Rus:
# План тестирования

## Цели тестирования
Тестирование направлено на проверку корректности работы всех компонентов системы, включая генерацию карт, взаимодействие игроков и дилера, логику ставок и правильное определение победителя.

## Области тестирования

1. Тестирование карт (Card)
   - Проверить, что карты правильно инициализируются с корректными номерами и мастями.
   - Проверить корректное отображение карты на экране.

2. Тестирование колоды (Deck)
   - Проверить генерацию полной колоды (52 карты).
   - Тестирование перемешивания колоды.
   - Проверить правильность удаления карты из колоды при раздаче.

3. Тестирование рук игрока (Hand)
   - Проверить добавление карт в руку игрока.
   - Убедиться, что карты корректно отображаются.
   - Проверить удаление карт из руки после завершения игры.

4. Тестирование игроков (Player и AIPlayer)
   - Проверить, что игроки могут делать ставки.
   - Убедиться, что боты принимают решения корректно в зависимости от уровня сложности.
   - Проверить корректность расчета фишек (ставок).

5. Тестирование дилера (Dealler)
   - Убедиться, что дилер правильно раздает карты.
   - Проверить корректное перемешивание колоды.
   - Убедиться, что дилер правильно определяет победителя.

6. Тестирование игрового процесса (Game)
   - Тестирование старта игры.
   - Проверить корректность цикла ставок и раздачи карт.
   - Убедиться, что игра корректно завершает раунд и определяет победителя.





#Eng:
# Test Plan

## Testing Objectives
Testing is aimed at checking the correct operation of all system components, including card generation, interaction between players and the dealer, betting logic, and correct determination of the winner.

## Testing Areas

1. Card Testing
- Check that the cards are correctly initialized with the correct numbers and suits.
- Check that the card is displayed correctly on the screen.

2. Deck Testing
- Check that a full deck (52 cards) is generated.
- Test the deck shuffling.
- Check that a card is removed from the deck correctly when dealing.

3. Hand Testing
- Check that cards are added to the player's hand.
- Make sure that the cards are displayed correctly.
- Check that cards are removed from the hand after the game is over.

4. Player and AIPlayer testing
- Check that players can place bets.
- Check that bots make decisions correctly depending on the difficulty level.
- Check that chips (bets) are calculated correctly.

5. Dealer testing
- Check that the dealer deals cards correctly.
- Check that the deck is shuffled correctly.
- Check that the dealer determines the winner correctly.

6. Game testing
- Test the game start.
- Check that the betting and card dealing cycle is correct.
- Check that the game correctly ends the round and determines the winner.
