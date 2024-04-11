#include "Game.h"

void Game::startNewGame(bool isChess960)
{
    board.initializeBoard(isChess960); // Передаем флаг игры в шахматы 960
    player1.initializePlayer();
    player2.initializePlayer();
    currentPlayer = &player1;
    gameOver = false;
    replayMode = false;
    chess960 = isChess960; // Устанавливаем флаг игры в шахматы 960
}

void Game::makeMove(const Move &move)
{
    if (!gameOver)
    {
        if (board.isMoveValid(move))
        {
            board.makeMove(move, *currentPlayer);
            checkWinner();
            currentPlayer->addMoveToHistory(move);
            switchPlayer();
        }
        else
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            makeMove(Move(x1, y1, x2, y2));
        }
    }
    else
    {
        // Обработка хода после окончания игры
        // Например, вывод сообщения о завершении игры и предложение начать новую игру
    }
}

void Game::checkWinner()
{

    if (board.isGameOver())
    {
        gameOver = true;
        Player *winner = currentPlayer;
        switchPlayer();
        Player *loser = currentPlayer;
    }
    else if (board.isStalemate(*currentPlayer))
    {
        gameOver = true;
    }
    
}

void Game::switchPlayer()
{
    currentPlayer = (*currentPlayer == player1) ? &player2 : &player1;
    board.toggleTurn();
}
bool Player::operator==(const Player &other) const
{
    return (name == other.name) && (color == other.color);
}