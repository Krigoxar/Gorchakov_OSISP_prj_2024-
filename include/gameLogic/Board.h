
#include <array>
#include <iostream>
#include <algorithm>
#include <random>
#include "Player.h"
#include "Move.h"
#include "Piece.h"

class Board
{
public:
    Board();

    void initializeBoard(bool isChess960);
    void makeMove(const Move &move, const Player &player);
    bool isMoveValid(const Move &move);
    bool isGameOver();
    bool isStalemate(const Player &player);
    bool isEnemyPiece(int x, int y, const Player &player);
    void explodePieces(int x, int y);
    bool isWithinBoard(int x, int y);
    bool isFreeOrEnemyPiece(int x, int y, Color color);
    bool isPawnMoveValid(int startX, int startY, int endX, int endY);
    bool isRookMoveValid(int startX, int startY, int endX, int endY);
    bool isKnightMoveValid(int startX, int startY, int endX, int endY);
    bool isBishopMoveValid(int startX, int startY, int endX, int endY);
    bool isQueenMoveValid(int startX, int startY, int endX, int endY);
    bool isKingMoveValid(int startX, int startY, int endX, int endY);
    Piece* getPiece(int x, int y);
    void setPiece(Piece* piece, int x, int y);
    Color getCurrentTurnColor();
    void toggleTurn();
    bool hasValidMoves(Color currentPlayerColor);

private:
    bool isWhiteTurn;
    Piece* pieces[8][8];
};
