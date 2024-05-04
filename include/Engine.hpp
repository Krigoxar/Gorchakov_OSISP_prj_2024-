class Engine 
{

public:
	static bool StaticInit();
	virtual ~Engine();
	static std::unique_ptr< Engine >	sInstance;

	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
protected:

	Engine();

	virtual void	UpdateStates();

private:

			bool	mShouldKeepRunning;
};