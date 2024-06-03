#include <RoboCatPCH.hpp>

shared_ptr< Command > Command::StaticReadAndCreate( InputMemoryBitStream& inInputStream )
{
	CommandPtr retVal;
	
	int type = CM_INVALID;
	inInputStream.Read( type );
	uint32_t networkId = 0;
	inInputStream.Read( networkId );
	uint32_t playerId = 0;
	inInputStream.Read( playerId );

	switch ( type )
	{
	case CM_MOVE:
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;
	case CM_RESIGN:
		retVal = std::make_shared< ResignCommnad >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;
	default:
		LOG( "Read in an unknown command type??" );
		break;
	}

	return retVal;
}

void Command::Write( OutputMemoryBitStream& inOutputStream )
{
	inOutputStream.Write( mCommandType );
	inOutputStream.Write( mNetworkId );
	inOutputStream.Write( mPlayerId );
}

MoveCommandPtr MoveCommand::StaticCreate( uint32_t inNetworkId, const Vector2& inTarget )
{
	MoveCommandPtr retVal = nullptr;
	GameObjectPtr go = NetworkManager::sInstance->GetGameObject( inNetworkId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

	//can only issue commands to this unit if I own it, and it's a cat
	if ( go && go->GetClassId() == Piece::kClassId && 
		go->GetPlayerId() == playerId )
	{
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = inNetworkId;
		retVal->mPlayerId = playerId;
		retVal->mTarget = inTarget;
	}
	return retVal;
}

void MoveCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTarget );
}

void MoveCommand::ProcessCommand()
{
	GameObjectPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
	if ( obj && obj->GetClassId() == Piece::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		Piece* rc = obj->GetAsPiece();
		rc->MoveToLocation( mTarget );
    }
    Board::sInstance->toggleTurn();
    game->drawBoard();
}

void MoveCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTarget );
}

shared_ptr<ResignCommnad> ResignCommnad::StaticCreate() 
{
	ResignCommnadPtr retVal = nullptr;
	retVal = std::make_shared< ResignCommnad >();
	retVal->mPlayerId = NetworkManager::sInstance->GetMyPlayerId();
	retVal->mNetworkId = 0;
	return retVal;
}

void ResignCommnad::Write(OutputMemoryBitStream& inOutputStream) 
{
	Command::Write( inOutputStream );
}

void ResignCommnad::ProcessCommand() 
{
	//carbon blya sdelai resign
}

void ResignCommnad::Read(InputMemoryBitStream& inInputStream) 
{
	
}
