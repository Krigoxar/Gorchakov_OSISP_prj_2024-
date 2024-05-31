#include <RoboCatPCH.hpp>

std::unique_ptr<Board> Board::sInstance = nullptr;

void Board::StaticInit()
{
	sInstance.reset(new Board());
}

Board::Board() : 
mCurentPlayer(0),
mGameObjects()
{
	
}

void Board::AddGameObject(GameObjectPtr inGameObject)
{
	mGameObjects.push_back(inGameObject);
	inGameObject->SetIndexInWorld(static_cast<int>(mGameObjects.size()) - 1);
}

void Board::RemoveGameObject(GameObjectPtr inGameObject)
{
	int index = inGameObject->GetIndexInWorld();

	int lastIndex = static_cast<int>(mGameObjects.size()) - 1;
	if (index != lastIndex)
	{
		mGameObjects[index] = mGameObjects[lastIndex];
		mGameObjects[index]->SetIndexInWorld(index);
	}

	inGameObject->SetIndexInWorld(-1);

	mGameObjects.pop_back();
}

void Board::Update()
{
	// update all game objects- sometimes they want to die, so we need to tread carefully...

	for (int i = 0, c = static_cast<int>(mGameObjects.size()); i < c; ++i)
	{
		GameObjectPtr go = mGameObjects[i];

		if (!go->DoesWantToDie())
		{
			//go->Update(inDeltaTime);
		}
		// you might suddenly want to die after your update, so check again
		if (go->DoesWantToDie())
		{
			RemoveGameObject(go);
			go->HandleDying();
			--i;
			--c;
		}
	}
}

uint32_t Board::TrySelectGameObject(const Vector2 &inSelectLoc)
{
	for (auto &g : mGameObjects)
	{
		if (g->TrySelect(inSelectLoc))
		{
			return g->GetNetworkId();
		}
	}

	return 0;
}

bool Board::IsMovePosible(Vector2 inStartPosition, Vector2 inEndPosition) 
{
	return isMoveValid(Move(inStartPosition.mX, inStartPosition.mY, inEndPosition.mX, inEndPosition.mY));
}

Piece* Board::GetPieceAt(Vector2 inPosition)
{
	uint32_t networkID = TrySelectGameObject(inPosition);
    return NetworkManager::sInstance->GetGameObject(networkID)->GetAsPiece();
}

Piece* Board::GetPieceAt(int x, int y) 
{
    return GetPieceAt(Vector2(x, y)); 
}

bool Board::isMoveValid(const Move &move)
{
    int startX = move.getStartX();
    int startY = move.getStartY();
    int endX = move.getEndX();
    int endY = move.getEndY();
    Piece *movingPiece = GetPieceAt(Vector2(move.getStartX(), move.getStartY()));

    if(movingPiece == NULL) {return false;}

    if (movingPiece == nullptr)
    {
        return false;
    }
    Color movingPieceColor = movingPiece->GetColor();
    Color turnColor = ScoreBoardManager::sInstance->GetEntry(mCurentPlayer)->GetColor();
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

    PieceType pieceType = movingPiece->GetPieceType();
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
    case PieceType::NONE:
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
            Piece *piece = GetPieceAt(Vector2(x, y));

            if (piece != nullptr && piece->GetPieceType() == PieceType::KING)
            {
                if (piece->GetColor() == Color::WHITE)
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

bool Board::hasValidMoves(Color currentPlayerColor)
{
    // Iterate through all the pieces on the board
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = GetPieceAt(Vector2(x, y));
            if (piece != nullptr && piece->GetColor() == currentPlayerColor)
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

Color Board::GetPlayerColor() 
{ 
    return ScoreBoardManager::sInstance->GetEntry(mCurentPlayer)->GetColor(); 
}

bool Board::isStalemate()
{

    // Проверяем, есть ли возможные ходы для игрока
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = GetPieceAt(Vector2(x, y));

            // Проверяем, что фигура принадлежит игроку и имеет ходы
            if (piece != nullptr && piece->GetColor() == GetPlayerColor() && hasValidMoves(GetPlayerColor()))
            {
                return false; // У игрока есть возможные ходы, поэтому пат невозможен
            }
        }
    }

    return true;
}

bool Board::isEnemyPiece(int x, int y)
{
    Piece *piece = GetPieceAt(x, y);

    if (piece != nullptr)
    {
        if (piece->GetColor() != GetPlayerColor())
        {
            return true;
        }
    }

    return false;
}

void Board::explodePieces(int x, int y)
{
    Piece *piece = GetPieceAt(x, y);

    if (piece != nullptr)
    {
        piece->SetDoesWantToDie(true);

        // Сбиваем соседние фигуры, исключая пешки
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                // Пропускаем позицию (x, y) и позиции за пределами доски
                if ((dx == 0 && dy == 0) || !isWithinBoard(x + dx, y + dy))
                {
                    continue;
                }

                Piece *neighborPiece = GetPieceAt(x + dx, y + dy);

                // Проверяем, что соседняя фигура существует и не является пешкой
                if (neighborPiece != nullptr && (neighborPiece->GetPieceType() != PieceType::PAWN))
                {
                    delete neighborPiece;
                    GetPieceAt(x + dx, y + dy)->SetDoesWantToDie(true);
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
    Piece *piece = NetworkManager::sInstance->GetGameObject(TrySelectGameObject(Vector2(x,y)))->GetAsPiece();

    // Проверяем, что на заданной позиции нет фигуры или фигура противника
    if (piece == nullptr || piece->GetColor() != color)
    {
        return true;
    }

    return false;
}

void Board::toggleTurn()
{
	mCurentPlayer = ScoreBoardManager::sInstance->GetOtherEntry(mCurentPlayer)->GetPlayerId();
}

Color Board::getCurrentTurnColor()
{
    return ScoreBoardManager::sInstance->GetEntry(mCurentPlayer)->GetColor();
}

bool Board::isPawnMoveValid(int startX, int startY, int endX, int endY)
{
    Piece *startPiece = NetworkManager::sInstance->GetGameObject(TrySelectGameObject(Vector2(startX, startY)))->GetAsPiece();
    Piece *endPiece = NetworkManager::sInstance->GetGameObject(TrySelectGameObject(Vector2(endX, endY)))->GetAsPiece();
    if (startPiece->GetColor() == Color::WHITE)
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
            if (endPiece == nullptr && GetPieceAt(endX + 1, endY) == nullptr)
            {
                return true;
            }
        }
        // WHITE pawn can capture diagonally
        if (endX == startX - 1 && (endY == startY - 1 || endY == startY + 1))
        {
            if (endPiece != nullptr && endPiece->GetColor() == Color::BLACK)
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
            if (endPiece == nullptr && GetPieceAt(endX - 1, endY) == nullptr)
            {
                return true;
            }
        }
        // BLACK pawn can capture diagonally
        if (endX == startX + 1 && (endY == startY - 1 || endY == startY + 1))
        {
            if (endPiece != nullptr && endPiece->GetColor() == Color::WHITE)
            {
                return true;
            }
        }
    }
    return false;
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
        if (GetPieceAt(currentX, currentY) != nullptr)
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
            if (GetPieceAt(currentX, currentY) != nullptr)
            {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        // If there are no pieces in the path, the bishop move is considered valid
        return true;
    }
    return false;
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
            if (GetPieceAt(currentX, currentY) != nullptr)
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
