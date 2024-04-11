#include "Player.h"
#include "Board.h"
#include "Move.h"

class Game
{
private:
    Board board;
    Player player1;
    Player player2;
    Player *currentPlayer;
    bool gameOver;
    bool replayMode;
    bool chess960;

public:
    void startNewGame(bool fischerMode);

    void makeMove(const Move &move);

    void checkWinner();

    void switchPlayer();
};