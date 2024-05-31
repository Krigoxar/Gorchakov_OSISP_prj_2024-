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

    QApplication a(argc, argv);

    game = new GameView();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
