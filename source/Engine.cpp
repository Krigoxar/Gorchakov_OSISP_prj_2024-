#include <RoboCatPCH.hpp>

void Engine::UpdateStates()
{
	// Main work
	InputManager::sInstance->Update();

	Board::sInstance->Update();
	NetworkManager::sInstance->ProcessIncomingPackets();
	NetworkManager::sInstance->SendOutgoingPackets();
}