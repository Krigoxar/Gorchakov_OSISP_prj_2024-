#include <RoboCatPCH.hpp>

#include <iostream>
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

	while (true)
	{
		
	}

	return 0;
}