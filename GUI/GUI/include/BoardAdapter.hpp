#include <RoboCatPCH.hpp>
#include "boardviewmodel.h"
#include "bishoppawnmodel.h"
#include "kingpawnmodel.h"
#include "queenpawnmodel.h"
#include "rookpawnmodel.h"
#include "knightpawnmodel.h"
#include "pawnpawnmodel.h"

class BoardAdapter : public BoardViewModel {

public:
    BoardAdapter();

    QList<BasePawnModel*> getBlackPawns() override;
    QList<BasePawnModel*> getWhitePawns() override;
    PlayerType getWhosTurn() override;
    PlayerType* getWinner() override;
    void setActivePawnForField(PawnField *pawn) override;
    //void setNewPositionForActivePawn(BoardPosition position) override;
    //BoardPosition getBoardPositionForMousePosition(QPoint position) override;
    //bool validatePawnPalcementForMousePosition(QPoint position) override;
    bool validatePawnMove(BoardPosition positionToMove, BasePawnModel *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr) override;
    //bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition) override;
    bool isKingInCheck(PlayerType owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer) override;
    bool didPromoteActivePawn() override;
    void switchRound() override;
private:
    bool isInPawnsList(QList<BasePawnModel*> inPawnsList, GameObjectPtr inGameObj);
    BasePawnModel* createPawnModel(GameObjectPtr obj);
};