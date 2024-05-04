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
    
    std::string toString() const {
        std::string moveString = "";
        moveString += static_cast<char>('a' + startX);
        moveString += std::to_string(startY + 1);
        moveString += "-";
        moveString += static_cast<char>('a' + endX);
        moveString += std::to_string(endY + 1);
        return moveString;
    }

private:
    int startX;
    int startY;
    int endX;
    int endY;
};