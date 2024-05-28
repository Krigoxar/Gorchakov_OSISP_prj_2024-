
class InputManager
{
public:


	static void StaticInit();
	static unique_ptr< InputManager >	sInstance;

	//void HandleInput( EInputAction inInputAction, int inKeyCode );
	void HandleMouseClick( Vector2 inBoardPos );

	CommandList&	GetCommandList()		{ return mCommandList; }
	void			ClearCommandList()		{ mCommandList.Clear(); }
	
	void			Update();
	uint32_t		GetSelectedNetId()	{ return mSelectedNetId; }

	void GenerateMoveComand(const Vector2 inStartPosition, const Vector2 inEndPosition);
	void GenerateResignComand();

private:
	//void			GenerateRightClickCommand( const Vector2& inWorldPos );
	InputManager();

	
	CommandList		mCommandList;
	uint32_t		mSelectedNetId;
};