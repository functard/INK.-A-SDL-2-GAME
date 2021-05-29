#pragma once

/// <summary>
/// 2D vector class
/// </summary>
struct SVector2
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_x">x value</param>
	/// <param name="_y">y value</param>
	SVector2(float _x = 0.0f, float _y = 0.0f)
	{
		X = _x;
		Y = _y;
	}
#pragma endregion

#pragma region public primitive variable
	/// <summary>
	/// x value
	/// </summary>
	float X = 0.0f;

	/// <summary>
	/// y value
	/// </summary>
	float Y = 0.0f;
#pragma endregion

#pragma region operator
	/// <summary>
	/// vector2 + vector2
	/// </summary>
	/// <param name="_vec">other 2D vector</param>
	/// <returns>new 2D vector</returns>
	SVector2 operator + (SVector2 _vec)
	{
		// returns new 2D vector
		return SVector2(X + _vec.X, Y + _vec.Y);
	}

	/// <summary>
	/// vector2 * float
	/// </summary>
	/// <param name="_value">float value</param>
	/// <returns>new vector2</returns>
	SVector2 operator*(float _value)
	{
		// return new vector2
		return SVector2(X * _value, Y * _value);
	}
#pragma endregion
};