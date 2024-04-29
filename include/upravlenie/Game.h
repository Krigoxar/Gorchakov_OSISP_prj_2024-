#include "Player.h"
#include "Board.h"
#include "Move.h"
#include <fstream>
#include <chrono>

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
    int whiteTimeControl;
    int blackTimeControl;
    std::chrono::steady_clock::time_point moveStartTime;

public:
    void startNewGame(bool fischerMode);

    void makeMove(const Move &move);

    void checkWinner();

    void switchPlayer();

    void saveGame(const std::string &filename);

    void loadGame(const std::string &filename);

    void undoMove();

    void trackMoveTime();

    void updateStartTime();
};