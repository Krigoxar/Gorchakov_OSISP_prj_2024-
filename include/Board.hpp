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

	void Update(float inDeltaTime);

	const std::vector<GameObjectPtr> &GetGameObjects() const { return mGameObjects; }

	uint32_t TrySelectGameObject(const Vector2 &inSelectLoc);

private:
	Board();

	std::vector<GameObjectPtr> mGameObjects;
};