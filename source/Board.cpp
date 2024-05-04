#include <RoboCatPCH.hpp>

std::unique_ptr<Board> Board::sInstance = nullptr;

void Board::StaticInit()
{
	sInstance.reset(new Board());
}

Board::Board()
{
}

void Board::AddGameObject(GameObjectPtr inGameObject)
{
	mGameObjects.push_back(inGameObject);
	inGameObject->SetIndexInWorld(static_cast<int>(mGameObjects.size()) - 1);
}

void Board::RemoveGameObject(GameObjectPtr inGameObject)
{
	int index = inGameObject->GetIndexInWorld();

	int lastIndex = static_cast<int>(mGameObjects.size()) - 1;
	if (index != lastIndex)
	{
		mGameObjects[index] = mGameObjects[lastIndex];
		mGameObjects[index]->SetIndexInWorld(index);
	}

	inGameObject->SetIndexInWorld(-1);

	mGameObjects.pop_back();
}

void Board::Update(float inDeltaTime)
{
	// update all game objects- sometimes they want to die, so we need to tread carefully...

	for (int i = 0, c = static_cast<int>(mGameObjects.size()); i < c; ++i)
	{
		GameObjectPtr go = mGameObjects[i];

		if (!go->DoesWantToDie())
		{
			go->Update(inDeltaTime);
		}
		// you might suddenly want to die after your update, so check again
		if (go->DoesWantToDie())
		{
			RemoveGameObject(go);
			go->HandleDying();
			--i;
			--c;
		}
	}
}

uint32_t Board::TrySelectGameObject(const Vector2 &inSelectLoc)
{
	for (auto &g : mGameObjects)
	{
		if (g->TrySelect(inSelectLoc))
		{
			return g->GetNetworkId();
		}
	}

	return 0;
}
