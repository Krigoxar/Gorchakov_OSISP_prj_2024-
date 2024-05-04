#include "RoboCatPCH.hpp"
#include <ctime>

std::unique_ptr< RandGen > RandGen::sInstance = nullptr;

RandGen::RandGen() :
	mt(0)
{

}

void RandGen::StaticInit()
{
	sInstance = std::make_unique< RandGen >();
	//just use a default random seed, we'll reseed later
    std::time_t currentTime = std::time(nullptr);

	sInstance->mt = RandGen::MersenneTwister( currentTime );
}

void RandGen::Seed( uint32_t inSeed )
{
	mt = RandGen::MersenneTwister( inSeed );
}

uint32_t RandGen::GetRandomUInt32( uint32_t inMin, uint32_t inMax )
{
	return ((uint32_t)mt.extractNumber() % (inMax - inMin)) + inMin;
}

int32_t RandGen::GetRandomInt( int32_t inMin, int32_t inMax )
{
	return ((int32_t)mt.extractNumber() % (inMax - inMin)) + inMin;
}
