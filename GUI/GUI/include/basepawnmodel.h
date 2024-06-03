#ifndef PAWNMODEL_H
#define PAWNMODEL_H

#include <QString>
#include "boardposition.h"

enum class PawnType {
    none,
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king,
};

enum class PlayerType {
    none,
    white,
    black,
};

class BasePawnModel {

public:
    BasePawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath);

    BoardPosition position;
    PlayerType owner;
    PawnType type;
    QString imagePath;
    bool didTakeFirstMove;

    virtual bool validateMove(BoardPosition positionToMove,
                              BasePawnModel *pawnOnPositionToMove,
                              BoardPosition *requestedActivePawnPosition) = 0;
    virtual ~BasePawnModel() = default;

protected:
    bool pawnWantsToMoveByOneField(BoardPosition positionToMove);
    bool validateDiagonalMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove);
    bool validateVerticalOrHorizontalMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove);
};

#endif // PAWNMODEL_H
