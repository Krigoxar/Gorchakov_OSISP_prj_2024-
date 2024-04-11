
#include "Board.h"

Board::Board()
{
    initializeBoard(false);
}

void Board::initializeBoard(bool isChess960)
{

    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            pieces[x][y] = nullptr;
        }
    }

    for (int x = 0; x < 8; ++x)
    {
        pieces[1][x] = new Piece(Color::BLACK, PieceType::PAWN);
        pieces[6][x] = new Piece(Color::WHITE, PieceType::PAWN);
    }

    if (isChess960)
    {
        // Здесь реализуйте инициализацию доски в режиме Chess960
        std::array<char, 8> positions{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        for (int i = 0; i < 8; i++)
        {
            switch (positions[i])
            {
            case 'R':
                pieces[0][i] = new Piece(Color::BLACK, PieceType::ROOK);
                pieces[7][i] = new Piece(Color::WHITE, PieceType::ROOK);
                break;
            case 'N':
                pieces[0][i] = new Piece(Color::BLACK, PieceType::KNIGHT);
                pieces[7][i] = new Piece(Color::WHITE, PieceType::KNIGHT);
                break;
            case 'B':
                pieces[0][i] = new Piece(Color::BLACK, PieceType::BISHOP);
                pieces[7][i] = new Piece(Color::WHITE, PieceType::BISHOP);
                break;
            case 'Q':
                pieces[0][i] = new Piece(Color::BLACK, PieceType::QUEEN);
                pieces[7][i] = new Piece(Color::WHITE, PieceType::QUEEN);
                break;
            case 'K':
                pieces[0][i] = new Piece(Color::BLACK, PieceType::KING);
                pieces[7][i] = new Piece(Color::WHITE, PieceType::KING);
                break;
            }
        }
    }
    else
    {
        pieces[0][0] = new Piece(Color::WHITE, PieceType::ROOK);
        pieces[7][0] = new Piece(Color::WHITE, PieceType::ROOK);
        pieces[0][7] = new Piece(Color::BLACK, PieceType::ROOK);
        pieces[7][7] = new Piece(Color::BLACK, PieceType::ROOK);

        pieces[1][0] = new Piece(Color::WHITE, PieceType::KNIGHT);
        pieces[6][0] = new Piece(Color::WHITE, PieceType::KNIGHT);
        pieces[1][7] = new Piece(Color::BLACK, PieceType::KNIGHT);
        pieces[6][7] = new Piece(Color::BLACK, PieceType::KNIGHT);

        pieces[2][0] = new Piece(Color::WHITE, PieceType::BISHOP);
        pieces[5][0] = new Piece(Color::WHITE, PieceType::BISHOP);
        pieces[2][7] = new Piece(Color::BLACK, PieceType::BISHOP);
        pieces[5][7] = new Piece(Color::BLACK, PieceType::BISHOP);

        pieces[3][0] = new Piece(Color::WHITE, PieceType::QUEEN);
        pieces[3][7] = new Piece(Color::BLACK, PieceType::QUEEN);

        pieces[4][0] = new Piece(Color::WHITE, PieceType::KING);
        pieces[4][7] = new Piece(Color::BLACK, PieceType::KING);
    }
}

void Board::makeMove(const Move &move, const Player &player)
{
    if (!isMoveValid(move))
    {
        return;
    }
    int startX = move.getStartX();
    int startY = move.getStartY();
    int endX = move.getEndX();
    int endY = move.getEndY();
    if (isEnemyPiece(endX, endY, player))
    {
        setPiece(nullptr, startX, startY);
        explodePieces(endX, endY);
    }
    else
    {
        setPiece(getPiece(startX, startY), endX, endY);
        setPiece(nullptr, startX, startY);
    }
    if (isGameOver())
    {
        // что будет происходить в конце
    }
}

bool Board::isMoveValid(const Move &move)
{
    int startX = move.getStartX();
    int startY = move.getStartY();
    int endX = move.getEndX();
    int endY = move.getEndY();
    Piece *movingPiece = getPiece(startX, startY);

    if (movingPiece == nullptr)
    {
        return false;
    }
    Color movingPieceColor = movingPiece->getColor();
    Color turnColor = getCurrentTurnColor();
    if (movingPieceColor != turnColor)
    {
        return false;
    }
    if (!isWithinBoard(startX, startY))
    {
        return false;
    }

    if (!isWithinBoard(endX, endY))
    {
        return false;
    }

    if (!isFreeOrEnemyPiece(endX, endY, (movingPieceColor == Color::WHITE) ? Color::BLACK : Color::WHITE))
    {
        return false;
    }

    PieceType pieceType = movingPiece->getType();
    bool isValidMove = false;

    switch (pieceType)
    {
    case PieceType::PAWN:
        // Проверяем ход пешкой
        isValidMove = isPawnMoveValid(startX, startY, endX, endY);
        break;
    case PieceType::ROOK:
        // Проверяем ход ладьей
        isValidMove = isRookMoveValid(startX, startY, endX, endY);
        break;
    case PieceType::KNIGHT:
        // Проверяем ход конем
        isValidMove = isKnightMoveValid(startX, startY, endX, endY);
        break;
    case PieceType::BISHOP:
        // Проверяем ход слоном
        isValidMove = isBishopMoveValid(startX, startY, endX, endY);
        break;
    case PieceType::QUEEN:
        // Проверяем ход ферзем
        isValidMove = isQueenMoveValid(startX, startY, endX, endY);
        break;
    case PieceType::KING:
        // Проверяем ход королем
        isValidMove = isKingMoveValid(startX, startY, endX, endY);
        break;
    }

    return isValidMove;
}

bool Board::isGameOver()
{
    bool WHITEKingPresent = false;
    bool BLACKKingPresent = false;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = getPiece(x, y);

            if (piece != nullptr && piece->getType() == PieceType::KING)
            {
                if (piece->getColor() == Color::WHITE)
                {
                    WHITEKingPresent = true;
                }
                else
                {
                    BLACKKingPresent = true;
                }
            }
        }
    }

    // Если короля одного из игроков нет, игра завершена
    if (!WHITEKingPresent || !BLACKKingPresent)
    {
        return true;
    }

    // Дополнительные проверки на возможность ходов

    // ...

    // Возвращаем false, если нет условий для завершения игры
    return false;
}

bool Board::isStalemate(const Player &player)
{

    // Проверяем, есть ли возможные ходы для игрока
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = getPiece(x, y);

            // Проверяем, что фигура принадлежит игроку и имеет ходы
            if (piece != nullptr && piece->getColor() == player.getColor() && hasValidMoves(player.getColor()))
            {
                return false; // У игрока есть возможные ходы, поэтому пат невозможен
            }
        }
    }

    return true;
}

bool Board::isEnemyPiece(int x, int y, const Player &player)
{
    Piece *piece = getPiece(x, y);

    if (piece != nullptr)
    {
        if (piece->getColor() != player.getColor())
        {
            return true;
        }
    }

    return false;
}

void Board::explodePieces(int x, int y)
{
    Piece *piece = getPiece(x, y);

    if (piece != nullptr)
    {
        delete piece;
        setPiece(nullptr, x, y);

        // Сбиваем соседние фигуры, исключая пешки
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                // Пропускаем позицию (x, y) и позиции за пределами доски
                if (dx == 0 && dy == 0 || !isWithinBoard(x + dx, y + dy))
                {
                    continue;
                }

                Piece *neighborPiece = getPiece(x + dx, y + dy);

                // Проверяем, что соседняя фигура существует и не является пешкой
                if (neighborPiece != nullptr && (neighborPiece->getType() != PieceType::PAWN))
                {
                    delete neighborPiece;
                    setPiece(nullptr, x + dx, y + dy);
                }
            }
        }
    }
}

bool Board::isWithinBoard(int x, int y)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return true;
    }
    return false;
}

bool Board::isFreeOrEnemyPiece(int x, int y, Color color)
{
    Piece *piece = getPiece(x, y);

    // Проверяем, что на заданной позиции нет фигуры или фигура противника
    if (piece == nullptr || piece->getColor() != color)
    {
        return true;
    }

    return false;
}

void Board::toggleTurn()
{
    isWhiteTurn = !isWhiteTurn;
}

Color Board::getCurrentTurnColor()
{
    if (isWhiteTurn)
    {
        return Color::WHITE;
    }
    else
    {
        return Color::BLACK;
    }
}

void Board::setPiece(Piece *piece, int x, int y)
{
    pieces[x][y] = piece;
}

Piece *Board::getPiece(int x, int y)
{
    if (isWithinBoard(x, y))
    {
        return pieces[x][y];
    }

    return nullptr;
}

bool Board::isPawnMoveValid(int startX, int startY, int endX, int endY)
{
    Piece *startPiece = getPiece(startX, startY);
    Piece *endPiece = getPiece(endX, endY);
    if (startPiece->getColor() == Color::WHITE)
    {
        // WHITE pawn can move forward by one square
        if (endX == startX - 1 && endY == startY)
        {
            if (endPiece == nullptr)
            {
                return true;
            }
        }
        // WHITE pawn can move forward by two squares from the starting position
        if (startX == 6 && endX == startX - 2 && endY == startY)
        {
            if (endPiece == nullptr && getPiece(endX + 1, endY) == nullptr)
            {
                return true;
            }
        }
        // WHITE pawn can capture diagonally
        if (endX == startX - 1 && (endY == startY - 1 || endY == startY + 1))
        {
            if (endPiece != nullptr && endPiece->getColor() == Color::BLACK)
            {
                return true;
            }
        }
    }
    else
    {
        // BLACK pawn can move forward by one square
        if (endX == startX + 1 && endY == startY)
        {
            if (endPiece == nullptr)
            {
                return true;
            }
        }
        // BLACK pawn can move forward by two squares from the starting position
        if (startX == 1 && endX == startX + 2 && endY == startY)
        {
            if (endPiece == nullptr && getPiece(endX - 1, endY) == nullptr)
            {
                return true;
            }
        }
        // BLACK pawn can capture diagonally
        if (endX == startX + 1 && (endY == startY - 1 || endY == startY + 1))
        {
            if (endPiece != nullptr && endPiece->getColor() == Color::WHITE)
            {
                return true;
            }
        }
    }
}
bool Board::isRookMoveValid(int startX, int startY, int endX, int endY)
{
    if (startX != endX && startY != endY)
    {
        return false;
    }

    // Check if there are any pieces in the path of the rook's movement
    int deltaX = (endX > startX) ? 1 : (endX < startX) ? -1
                                                       : 0;
    int deltaY = (endY > startY) ? 1 : (endY < startY) ? -1
                                                       : 0;

    int currentX = startX + deltaX;
    int currentY = startY + deltaY;

    while (currentX != endX || currentY != endY)
    {
        if (getPiece(currentX, currentY) != nullptr)
        {
            return false;
        }

        currentX += deltaX;
        currentY += deltaY;
    }
    return true;
}
bool Board::isKnightMoveValid(int startX, int startY, int endX, int endY)
{
    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);

    // Check if the move is a valid knight move
    if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1))
    {
        return true;
    }

    // If none of the conditions are met, the knight move is considered invalidint deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);

    // Check if the move is a valid knight move
    if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1))
    {
        return true;
    }

    // If none of the conditions are met, the knight move is considered invalid
    return false;
}
bool Board::isBishopMoveValid(int startX, int startY, int endX, int endY)
{
    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);

    // Check if the move is a valid bishop move
    if (deltaX == deltaY)
    {
        // Check if there are any pieces in the path of the bishop's movement
        int stepX = (endX > startX) ? 1 : -1;
        int stepY = (endY > startY) ? 1 : -1;

        int currentX = startX + stepX;
        int currentY = startY + stepY;

        while (currentX != endX || currentY != endY)
        {
            if (getPiece(currentX, currentY) != nullptr)
            {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        // If there are no pieces in the path, the bishop move is considered valid
        return true;
    }
}
bool Board::isQueenMoveValid(int startX, int startY, int endX, int endY)
{
    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    if (deltaX == 0 || deltaY == 0 || deltaX == deltaY)
    {
        // Check if there are any pieces in the path of the queen's movement
        int stepX = (endX > startX) ? 1 : (endX < startX) ? -1
                                                          : 0;
        int stepY = (endY > startY) ? 1 : (endY < startY) ? -1
                                                          : 0;

        int currentX = startX + stepX;
        int currentY = startY + stepY;

        while (currentX != endX || currentY != endY)
        {
            if (getPiece(currentX, currentY) != nullptr)
            {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        // If there are no pieces in the path, the queen move is considered valid
        return true;
    }

    // If the move is neither horizontal, vertical, nor diagonal, it is invalid
    return false;
}
bool Board::isKingMoveValid(int startX, int startY, int endX, int endY)
{
    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);

    // Check if the move is a valid king move
    if (deltaX <= 1 && deltaY <= 1)
    {
        return true;
    }
    return false;
}

bool Board::hasValidMoves(Color currentPlayerColor)
{
    // Iterate through all the pieces on the board
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = getPiece(x, y);
            if (piece != nullptr && piece->getColor() == currentPlayerColor)
            {
                // Check if the piece has any valid moves
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (isMoveValid(Move(x, y, i, j)))
                        {

                            return true;
                        }
                    }
                }
            }
        }
    }

    // If no piece of the current player's color has any valid moves, return false
    return false;
}