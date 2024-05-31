#include <RoboCatPCH.hpp>

#include <random>

const Vector2 Vector2::Zero( 0.0f, 0.0f);
const Vector2 Vector2::UnitX( 1.0f, 0.0f);
const Vector2 Vector2::UnitY( 0.0f, 1.0f);
const Vector2 Vector2::NegUnitX( -1.0f, 0.0f);
const Vector2 Vector2::NegUnitY( 0.0f, -1.0f);

float RoboMath::GetRandomFloatNonGame()
{
	static std::random_device rd;
	static std::mt19937 gen( rd() );
	static std::uniform_real_distribution< float > dis( 0.f, 1.f );
	return dis( gen );
}
