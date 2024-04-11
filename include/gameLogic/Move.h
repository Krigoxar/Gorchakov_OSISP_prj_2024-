class Move {
public:
    Move(int startX, int startY, int endX, int endY) :
        startX(startX), startY(startY), endX(endX), endY(endY) {}

    int getStartX() const {
        return startX;
    }

    int getStartY() const {
        return startY;
    }

    int getEndX() const {
        return endX;
    }

    int getEndY() const {
        return endY;
    }

private:
    int startX;
    int startY;
    int endX;
    int endY;
};