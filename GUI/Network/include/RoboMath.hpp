class Vector2
{
public:

	int	mX, mY;

	Vector2( float x, float y) :
		mX( x ),
		mY( y )
	{}

	Vector2() :
		mX( 0.0f ),
		mY( 0.0f )
	{}

	void Set( float x, float y)
	{
		mX = x;
		mY = y;
	}

	friend Vector2 operator+( const Vector2& inLeft, const Vector2& inRight )
	{
		return Vector2( inLeft.mX + inRight.mX, inLeft.mY + inRight.mY);
	}

	friend Vector2 operator-( const Vector2& inLeft, const Vector2& inRight )
	{
		return Vector2( inLeft.mX - inRight.mX, inLeft.mY - inRight.mY);
	}


	Vector2& operator+=( const Vector2& inRight )
	{
		mX += inRight.mX;
		mY += inRight.mY;
		return *this;
	}

	Vector2& operator-=( const Vector2& inRight )
	{
		mX -= inRight.mX;
		mY -= inRight.mY;
		return *this;
	}

	bool operator==( const Vector2& inRight )
	{
		return (inRight.mX == mX) && (inRight.mY == mY);
	}

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 UnitZ;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
	static const Vector2 NegUnitZ;
};

namespace RoboMath
{
	const float PI = 3.1415926535f;
	float GetRandomFloatNonGame();
}

enum class Color
{
	NONE,
    WHITE,
    BLACK
};