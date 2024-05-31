enum class PieceType
{
	NONE,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

class Piece: public GameObject
{
public:
	CLASS_IDENTIFICATION( 'PIEC', GameObject )

	static	GameObjectPtr StaticCreate() { return NetworkManager::sInstance->RegisterAndReturn( new Piece() ); }

	virtual	Piece*	GetAsPiece()	override { return this; }

	// returns true if the move is done
	virtual bool MoveToLocation( const Vector2& inLocation );
	virtual void HandleDying() override;

	Piece();

	const enum PieceType&	GetPieceType()				const				{ return mPieceType; }
	      	   void			SetPieceType( const enum PieceType& inPieceType )		{ mPieceType = inPieceType; }

	virtual void WriteForCRC( OutputMemoryBitStream& inStream ) override;
private:

	enum PieceType mPieceType;
};

typedef shared_ptr< Piece >	PiecePtr;
