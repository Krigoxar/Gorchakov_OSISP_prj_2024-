#include <string>
#include <vector>
#include <iostream>
#include "Color.h"
#include "Move.h"
using namespace std;
class Player
{
public:
    Player(const string& name, Color color);

    string getName() const;
    Color getColor() const;
    vector<Move> getMoveHistory() const;
    void addMoveToHistory(const Move& move);
    bool operator==(const Player& other) const;
    void initializePlayer();

private:
    string name;
    Color color;
    vector<Move> moveHistory;
};