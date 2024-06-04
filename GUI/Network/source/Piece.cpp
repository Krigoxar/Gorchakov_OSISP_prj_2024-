#include <RoboCatPCH.hpp>
#include <zlib.h>

const float kMoveSpeed = 2.5f;
const float kAttackRangeSq = 1.5f * 1.5f;
const float kYarnCooldown = 1.0f;

Piece::Piece() :
	GameObject(),
	mPieceType(PieceType::NONE)
{
	// mSpriteComponent = std::make_shared<SpriteComponent>( this );
	// mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "cat" ) );
}

void Piece::WriteForCRC( OutputMemoryBitStream& inStream )
{
	inStream.Write( mPlayerId );
	inStream.Write( mNetworkId );
	inStream.Write( mLocation );
	inStream.Write( mColor );
	inStream.Write( mPieceType );
}

bool Piece::MoveToLocation(const Vector2& inDeltaLocation )
{
    if(Board::sInstance->TryBlow(GetLocation() +  inDeltaLocation ))
    {
        SetDoesWantToDie(true);
    }
    else
    {
        SetLocation(GetLocation() +  inDeltaLocation );
    }

    return true;
}

void Piece::HandleDying()
{
	GameObject::HandleDying();
	//ScoreBoardManager::sInstance->IncScore( mPlayerId, -1 );
}

