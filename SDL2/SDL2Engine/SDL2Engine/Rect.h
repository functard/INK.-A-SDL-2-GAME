#pragma once

#pragma region sdl include
#include <SDL_Rect.h>
#pragma endregion

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// rectangle struct
/// </summary>
struct SRect : public SDL_Rect
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	SRect()	{ x, y, w, h = 0; }

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_size">size (x = width)</param>
	/// <param name="_pos">position</param>
	SRect(SVector2 _size, SVector2 _pos = SVector2())
	{
		x = _pos.X;
		y = _pos.Y;
		w = _size.X;
		h = _size.Y;
	}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_w">width</param>
	/// <param name="_h">height</param>
	/// <param name="_x">position x</param>
	/// <param name="_y">position y</param>
	SRect(int _w, int _h, int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
#pragma endregion
};