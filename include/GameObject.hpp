
#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; } \
static GameObject* CreateInstance() { return static_cast< GameObject* >( new inClass() ); } \

class GameObject
{
public:

	CLASS_IDENTIFICATION( 'GOBJ', GameObject )

	GameObject();
	virtual ~GameObject();

	virtual	Piece*		GetAsPiece()	{ return nullptr; }

	virtual void		Update( float inDeltaTime );

	virtual void		HandleDying();


	const   Vector2&	GetLocation()				const				{ return mLocation; }
			void		SetLocation( const Vector2& inLocation )		{ mLocation = inLocation; }

			void		SetColor( const Color& inColor )				{ mColor = inColor; }
	const   Color&		GetColor()					const				{ return mColor; }	
	
			void		SetIndexInWorld( int inIndex )					{ mIndexInWorld = inIndex; }
			int			GetIndexInWorld()			const				{ return mIndexInWorld; }

			bool		DoesWantToDie()				const				{ return mDoesWantToDie; }
			void		SetDoesWantToDie( bool inWants )				{ mDoesWantToDie = inWants; }

			uint32_t	GetNetworkId()				const				{ return mNetworkId; }
			void		SetNetworkId( uint32_t inNetworkId );

			void		SetPlayerId( uint32_t inPlayerId )				{ mPlayerId = inPlayerId; }
			uint32_t	GetPlayerId()				const 				{ return mPlayerId; }

	virtual bool		TrySelect( const Vector2& inLocation );

	//no default implementation because we don't know what's relevant for each object necessarily
	virtual void		WriteForCRC( OutputMemoryBitStream& inStream )	{ ( void )inStream; }
protected:

	Vector2				mLocation;
	Color				mColor;

	int					mIndexInWorld;

	uint32_t			mNetworkId;
	uint32_t			mPlayerId;

	bool				mDoesWantToDie;
};

typedef shared_ptr< GameObject >	GameObjectPtr;