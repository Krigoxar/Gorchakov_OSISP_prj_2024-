class Command
{
public:
	enum ECommandType
	{
		CM_INVALID,
		CM_MOVE,
		CM_RESIGN,
	};

	Command() :
	mCommandType( CM_INVALID ),
	mNetworkId( 0 ),
	mPlayerId( 0 )
	{}

	//given a buffer, will construct the appropriate command subclass
	static shared_ptr< Command > StaticReadAndCreate( InputMemoryBitStream& inInputStream );

	void SetNetworkId( uint32_t inId ) { mNetworkId = inId; }
	int GetNetworkId() const { return mNetworkId; }

	void SetPlayerId( uint32_t inId ) { mPlayerId = inId; }
	uint32_t GetPlayerId() const { return mPlayerId; }

	virtual void Write( OutputMemoryBitStream& inOutputStream );
	virtual void ProcessCommand() = 0;
protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) = 0;

	ECommandType mCommandType;
	uint32_t mNetworkId;
	uint32_t mPlayerId;
};

typedef shared_ptr< Command >	CommandPtr;


class MoveCommand : public Command
{
public:
	MoveCommand()
	{
		mCommandType = CM_MOVE;
	}

	static shared_ptr< MoveCommand > StaticCreate( uint32_t inNetworkId, const Vector2& inTarget );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	Vector2 mTarget;
};
typedef shared_ptr< MoveCommand > MoveCommandPtr;

class ResignCommnad : public Command
{
public:
	ResignCommnad()
	{
		mCommandType = CM_RESIGN;
	}

	static shared_ptr< ResignCommnad > StaticCreate();

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;
};
typedef shared_ptr< ResignCommnad > ResignCommnadPtr;

