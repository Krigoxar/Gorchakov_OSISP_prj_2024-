#include <RoboCatPCH.hpp>

unique_ptr<Engine> Engine::sInstance;

bool Engine::StaticInit()
{
	RandGen::StaticInit();

	SocketUtil::StaticInit();

	GameObjectRegistry::StaticInit();


	Board::StaticInit();

	ScoreBoardManager::StaticInit();

	InputManager::StaticInit();



	sInstance.reset( new Engine() );

 	GameObjectRegistry::sInstance->RegisterCreationFunction( 'PIEC', Piece::StaticCreate );
 
 	string destination = StringUtils::GetCommandLineArg( 1 );
 	string name = StringUtils::GetCommandLineArg( 2 );

	if ( destination == "" || name == "" )
	{
		LOG( "ERROR: Missing command line arguments." );
		return false;
	}

	//assume no colon implies this is just the port, which implies that this is the master peer
	if( destination.find_first_of( ':' ) == string::npos )
	{
		Engine::CreateLobby(destination, name);
	}
	else
	{
		FindLobby(destination, name);
	}

	return true;
}

void Engine::FindLobby(const string& inAddress, const string & inName)
{
	LOG( "Started as a Slave." );
	SocketAddressPtr targetAddress = SocketAddressFactory::CreateIPv4FromString( inAddress );
	if( !targetAddress )
	{
		LOG( "ERROR: Unable to create target address from destination." );
		Engine::sInstance->SetShouldKeepRunning(false);
	}
	NetworkManager::StaticInitAsPeer( *targetAddress, inName );
}

void Engine::CreateLobby( const string& inPort, const string& inName ) 
{	
	LOG( "Started as a Master." );
	NetworkManager::StaticInitAsMasterPeer( stoi( inPort ), inName );
}

void Engine::UpdateStates()
{
	// Main work
	InputManager::sInstance->Update();

	Board::sInstance->Update();
	NetworkManager::sInstance->ProcessIncomingPackets();
	NetworkManager::sInstance->SendOutgoingPackets();
}

Engine::Engine() {}