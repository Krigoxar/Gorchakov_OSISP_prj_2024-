#include <QApplication>
#include <gameview.h>
#include <RoboCatPCH.hpp>

#include <iostream>
#include <unistd.h>
GameView *game;
char** __argv;
int          __argc;
int main(int argc, char *argv[]) {

    __argc = argc;
    __argv = argv;

    std::cout << "Starting Init" << std::endl;
    if(!Engine::StaticInit()) return 1;
    std::cout << "Init Succes" << std::endl;

    while (NetworkManager::sInstance->GetState() != NetworkManager::NetworkManagerState::NMS_Playing)
    {
        Engine::sInstance->UpdateStates();
        if ((NetworkManager::sInstance->GetPlayerCount() == 2) && NetworkManager::sInstance->GetState() == NetworkManager::NetworkManagerState::NMS_Lobby)
        {
            NetworkManager::sInstance->TryStartGame();
        }
        sleep(1);
    }

    QApplication a(argc, argv);

    game = new GameView();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
