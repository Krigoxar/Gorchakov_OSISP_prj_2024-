#include "RoboCatPCH.hpp"

GameObject::GameObject() :
	mIndexInWorld( -1 ),
	mDoesWantToDie( false ),
	mNetworkId( 0 ),
	mPlayerId( 0 ),
	mColor(Color::NONE),
	mLocation(-1, -1)
{
}

GameObject::~GameObject()
{
}

// void GameObject::Update( float inDeltaTime )
// {
// 	//object don't do anything by default...	
// }

void GameObject::HandleDying()
{
	NetworkManager::sInstance->UnregisterGameObject( this );
}

void GameObject::SetNetworkId( uint32_t inNetworkId )
{ 
	//this doesn't put you in the map or remove you from it
	mNetworkId = inNetworkId; 

}

bool GameObject::TrySelect( const Vector2& inLocation )
{
	return mLocation == inLocation;
}