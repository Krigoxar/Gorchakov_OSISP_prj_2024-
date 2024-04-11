#include "Color.h"

enum class PieceType
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

class Piece
{
public:
    Piece(Color color, PieceType type) : color(color), type(type) {}

    Color getColor()
    {
        return color;
    }

    PieceType getType()
    {
        return type;
    }

private:
    Color color;
    PieceType type;
};
