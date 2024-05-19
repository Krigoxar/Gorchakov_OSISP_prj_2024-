#include <RoboCatPCH.hpp>

#include <iostream>
#include <unistd.h>
using namespace std;


const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
	__argc = argc;
	__argv = argv;
	
	std::cout << "Starting Init" << std::endl;
	Engine::StaticInit();
	std::cout << "Init Succes" << std::endl;

	string input;
	while (true)
	{

		sleep(1);
		Engine::sInstance->UpdateStates();
	}

	return 0;
}