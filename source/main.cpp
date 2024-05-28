#include <RoboCatPCH.hpp>

#include <iostream>
#include <unistd.h>
using namespace std;

const char** __argv;
int          __argc;
int          main(int argc, const char** argv)
{
    __argc = argc;
    __argv = argv;

    std::cout << "Starting Init" << std::endl;
    if(!Engine::StaticInit()) return 1;
    std::cout << "Init Succes" << std::endl;

    string input;
    while (true)
    {
        Engine::sInstance->UpdateStates();
        if ((NetworkManager::sInstance->GetPlayerCount() == 2) && NetworkManager::sInstance->GetState() == NetworkManager::NetworkManagerState::NMS_Lobby)
        {
            NetworkManager::sInstance->TryStartGame();
        }
        //std::cout << NetworkManager::sInstance->GetState() << std::endl;
        sleep(1);
    }

    return 0;
}
