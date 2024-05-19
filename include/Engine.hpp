class Engine 
{

public:
	static bool StaticInit();
	Engine();
	static std::unique_ptr< Engine >	sInstance;

	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
	
	static void FindLobby(const string& inAddress, const string & inName);
	static void CreateLobby( const string& inPort, const string& inName);

	virtual void	UpdateStates();
protected:


private:


			bool	mShouldKeepRunning;
};