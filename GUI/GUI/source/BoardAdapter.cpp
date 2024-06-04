#include "BoardAdapter.hpp"

BoardAdapter::BoardAdapter() {}

BasePawnModel* BoardAdapter::createPawnModel(GameObjectPtr obj) 
{
    GameObject* gameObject = obj.get();

    if (gameObject == nullptr)
    {
        return nullptr;
    }
    
    Piece* PieceObj = gameObject->GetAsPiece();

    BoardPosition pos = BoardPosition();
    pos.x = PieceObj->GetLocation().mY;
    pos.y = PieceObj->GetLocation().mX;
    PlayerType playerType = (PlayerType)PieceObj->GetColor();
    PawnType pawnType = (PawnType)PieceObj->GetPieceType();
    QString imgPath = pawnViewModel.getImagePath((PawnType)PieceObj->GetPieceType(), (PlayerType)PieceObj->GetColor());

    switch (gameObject->GetAsPiece()->GetPieceType())
    {
        case PieceType::BISHOP:
            return new BishopPawnModel(pos, playerType, pawnType, imgPath);
            break;
        case PieceType::KING:
            return new KingPawnModel(pos, playerType, pawnType, imgPath);
            break;
        case PieceType::KNIGHT:
            return new KnightPawnModel(pos, playerType, pawnType, imgPath);
            break;
        case PieceType::PAWN:
            return new PawnPawnModel(pos, playerType, pawnType, imgPath);
            break;
        case PieceType::QUEEN:
            return new QueenPawnModel(pos, playerType, pawnType, imgPath);
            break;
        case PieceType::ROOK:
            return new RookPawnModel(pos, playerType, pawnType, imgPath);
            break;
    }
}

QList<BasePawnModel*> BoardAdapter::getBlackPawns()
{
    auto objs = Board::sInstance->GetGameObjects();
    for (auto pawn : blackPawns) 
    {
        delete pawn;
    }
    blackPawns.clear();
    for(auto obj : objs)
    {
        if(obj->GetColor() == Color::BLACK)
        {
            blackPawns.append(createPawnModel(obj));
        }
    }
    return blackPawns;
}

QList<BasePawnModel*> BoardAdapter::getWhitePawns()
{
    auto objs = Board::sInstance->GetGameObjects();
    for (auto pawn : whitePawns) 
    {
        delete pawn;
    }
    whitePawns.clear();
    for(auto obj : objs)
    {
        if(obj->GetColor() == Color::WHITE)
        {
            whitePawns.append(createPawnModel(obj));
        }
    }
    return whitePawns;
}

PlayerType BoardAdapter::getWhosTurn() 
{
    return (PlayerType)Board::sInstance->getTurnColor(); 
}

PlayerType* BoardAdapter::getWinner() 
{
    PlayerType* res = nullptr;
    if(blackPawns.end() == std::find_if(blackPawns.begin(), blackPawns.end(), [](BasePawnModel* pawn){return pawn->type == PawnType::king;}))
    {
        *res = PlayerType::white;
    }

    if(whitePawns.end() == std::find_if(whitePawns.begin(), whitePawns.end(), [](BasePawnModel* pawn){return pawn->type == PawnType::king;}))
    {
        *res = PlayerType::black;
    }

    return res;
}

void BoardAdapter::setActivePawnForField(PawnField* pawn) 
{
    BasePawnModel* pawnModel = getPawnOnBoardPosition(pawn->getPosition());

    if (pawnModel && pawnModel->owner == getWhosTurn()) {
        activePawn = pawnModel;
        pawn->setZValue(1);
    }
}

bool operator==(const BasePawnModel& left, const GameObjectPtr& right) {
    GameObject* objPtr = right.get();
    if (objPtr == nullptr)
    {
        return false;
    }
    
    return  left.position.x == objPtr->GetLocation().mX && 
            left.position.y == objPtr->GetLocation().mY &&
            (int)left.type == (int)objPtr->GetAsPiece()->GetPieceType() &&
            (int)left.owner == (int)objPtr->GetColor();
}

bool BoardAdapter::validatePawnMove(BoardPosition positionToMove,
                                      BasePawnModel *pawn,
                                      BoardPosition *requestedActivePawnPosition)
{
    BasePawnModel *pawnToValidate;
    if (pawn) {
        pawnToValidate = pawn;
    } else {
        pawnToValidate = activePawn;
    }
    
    BasePawnModel *pawnOnPositionToMove = getPawnOnBoardPosition(positionToMove);
    auto FromPawnLoc = pawnToValidate->position;
    Vector2 start = Vector2(FromPawnLoc.y, FromPawnLoc.x);
    Vector2 end = Vector2(positionToMove.y, positionToMove.x);
    return Board::sInstance->IsMovePosible(start, end);
}

bool BoardAdapter::isKingInCheck(PlayerType owner, bool isCheckingActivePlayer,
                                 BoardPosition positionToMoveActivePlayer)
{
    return false;
}

bool BoardAdapter::didPromoteActivePawn() { return false; }

void BoardAdapter::switchRound() 
{
    Board::sInstance->toggleTurn();
}

bool BoardAdapter::isInPawnsList(QList<BasePawnModel*> inPawnsList, GameObjectPtr inGameObj)
{
    for(auto pawn : inPawnsList)
    {
        if(*pawn == inGameObj)
        {
            return true;
        }
    }
    return false;
}
