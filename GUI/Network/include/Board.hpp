/*
 * the world tracks all the live game objects. Failry inefficient for now, but not that much of a problem
 */
class Board
{
public:
	static void StaticInit();

	static std::unique_ptr<Board> sInstance;

	void AddGameObject(GameObjectPtr inGameObject);
	void RemoveGameObject(GameObjectPtr inGameObject);

	bool IsMovePosible(Vector2 inStartPosition, Vector2 inEndPosition);

	void Update();

	const std::vector<GameObjectPtr> &GetGameObjects() const { return mGameObjects; }

	uint32_t TrySelectGameObject(const Vector2 &inSelectLoc);

	void SetFirstPlayer();

	Color getCurrentTurnColor();
    bool isStalemate();
    bool isEnemyPiece(int x, int y);
    void toggleTurn();

private:
	Board();

	Piece* GetPieceAt(Vector2 inPosition);
	Piece* GetPieceAt(int x, int y);
	Color GetPlayerColor();

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

	bool isMoveValid(const Move &move);
    bool isGameOver();
    void explodePieces(int x, int y);
    bool isWithinBoard(int x, int y);
    bool isFreeOrEnemyPiece(int x, int y, Color color);
    bool isPawnMoveValid(int startX, int startY, int endX, int endY);
    bool isRookMoveValid(int startX, int startY, int endX, int endY);
    bool isKnightMoveValid(int startX, int startY, int endX, int endY);
    bool isBishopMoveValid(int startX, int startY, int endX, int endY);
    bool isQueenMoveValid(int startX, int startY, int endX, int endY);
    bool isKingMoveValid(int startX, int startY, int endX, int endY);
    bool hasValidMoves(Color currentPlayerColor);

	std::vector<GameObjectPtr> mGameObjects;
	uint32_t mCurentPlayer;
};