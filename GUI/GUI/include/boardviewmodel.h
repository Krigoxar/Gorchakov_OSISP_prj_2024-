#ifndef BOARDVIEWMODEL_H
#define BOARDVIEWMODEL_H

#include <QPoint>
#include "boardposition.h"
#include "pawnfield.h"
#include "basepawnmodel.h"
#include "pawnviewmodel.h"

class BoardViewModel {

public:
    BoardViewModel();

    bool isEnPassantAvailable;

    virtual QList<BasePawnModel*> getBlackPawns();
    virtual QList<BasePawnModel*> getWhitePawns();
    BasePawnModel* getActivePawn();
    virtual PlayerType getWhosTurn();
    virtual PlayerType* getWinner();
    virtual void setActivePawnForField(PawnField *pawn);
    virtual void setNewPositionForActivePawn(BoardPosition position);
    virtual void discardActivePawn();
    virtual BoardPosition getBoardPositionForMousePosition(QPoint position);
    virtual bool validatePawnPalcementForMousePosition(QPoint position);
    virtual bool validatePawnMove(BoardPosition positionToMove, BasePawnModel *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);
    virtual bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);
    virtual bool isKingInCheck(PlayerType owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer);
    virtual bool didPromoteActivePawn();
    virtual void switchRound();

protected:
    BasePawnModel *activePawn;
    PlayerType whosTurn;
    QList<BasePawnModel*> blackPawns;
    QList<BasePawnModel*> whitePawns;
    PawnViewModel pawnViewModel;
    PlayerType *winner;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, PlayerType owner);
    BasePawnModel* getPawnOnBoardPosition(BoardPosition baordPosition);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove, BasePawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateKingsCheckForPawns(QList<BasePawnModel*> pawns, bool isCheckingActivePlayer, BasePawnModel *king, BoardPosition positionToMoveActivePlayer);
};

#endif // BOARDVIEWMODEL_H
