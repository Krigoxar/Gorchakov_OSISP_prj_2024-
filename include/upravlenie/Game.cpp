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

void Game::saveGame(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (outFile.is_open())
    {
        // Сохраняем состояние игры
        outFile << (gameOver ? "1" : "0") << std::endl;
        outFile << (replayMode ? "1" : "0") << std::endl;
        outFile << (chess960 ? "1" : "0") << std::endl;

        // Сохраняем состояние текущего игрока
        outFile<<currentPlayer->getColor()<<std::endl;

        // Сохраняем историю ходов для каждого игрока
        for (const auto &move : player1.getMoveHistory())
        {
            outFile << move.toString() << std::endl;
        }
        for (const auto &move : player2.getMoveHistory())
        {
            outFile << move.toString() << std::endl;
        }

        // Сохраняем состояние поля
        std::string encodedState;
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                Piece* piece = board.getPiece(x, y);
                if (piece==nullptr)
                {
                    encodedState += "0"; // пустая клетка
                }
                else
                {
                    encodedState += std::to_string(piece->getType());
                    encodedState += std::to_string(piece->getColor());
                }
            }
        }
        outFile<<encodedState<<std::endl;

        outFile.close();
        
    }
}

void Game::loadGame(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        std::string line;

        // Загружаем состояние игры
        std::getline(inFile, line);
        gameOver = (line == "1");
        std::getline(inFile, line);
        replayMode = (line == "1");
        std::getline(inFile, line);
        chess960 = (line == "1");

        // Загружаем состояние текущего игрока
        std::getline(inFile, line);
        int currentPlayerColor = std::stoi(line);
        currentPlayer = (currentPlayerColor == 1) ? &player1 : &player2;

        // Загружаем историю ходов для каждого игрока
        std::vector<Move> player1Moves;
        std::vector<Move> player2Moves;

        while (std::getline(inFile, line))
        {
            Move move;
            // Парсим строку хода и добавляем его в соответствующий список ходов игрока
            // Например, если line = "b2-b4", то move будет содержать координаты (1, 1) и (1, 3)

            int startX = line[0] - 'a';
            int startY = line[1] - '1';
            int endX = line[3] - 'a';
            int endY = line[4] - '1';

            move = Move(startX, startY, endX, endY);
            if (currentPlayer == &player1)
            {
                player1Moves.push_back(move);
            }
            else
            {
                player2Moves.push_back(move);
            }
        }

        player1.setMoveHistory(player1Moves);
        player2.setMoveHistory(player2Moves);

        // Загружаем состояние поля
        std::getline(inFile, line);
        for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            char pieceChar = line[x * 8 + y];
            Piece *piece = nullptr;

            if (pieceChar != '0')
            {
                int type = pieceChar - '0';
                int color = (line[x * 8 + y + 1] - '0') ? 1 : 0;
                piece = Piece(color, type);
                y++; // Пропускаем следующий символ, который представляет цвет фигуры
            }

            board.setPiece(piece, x, y);
        }
    }
        inFile.close();
    }
}

void Game::undoMove()
{

    Move lastMove = currentPlayer->getMoveHistory().back();
    currentPlayer->getMoveHistory().pop_back();

    // Возвращаем фигуру на исходную клетку
    board.makeMove(Move(lastMove.endX, lastMove.endY, lastMove.startX, lastMove.startY), *currentPlayer);
}

void Game::trackMoveTime()
{
    int timeControl = (currentPlayer->getColor() == 0) ? whiteTimeControl : blackTimeControl;

    // Вычисляем время, прошедшее с начала хода
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - moveStartTime).count();

    // Проверяем, превышено ли время на ход
    if (elapsedMilliseconds >= timeControl)
    {
        // Время на ход истекло, принимаем соответствующие меры
    }
}

void Game::updateStartTime() {
    moveStartTime = std::chrono::steady_clock::now();
}
