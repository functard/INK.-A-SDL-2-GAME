#pragma once

#pragma region forward decleration
class SRect;
#pragma endregion

/// <summary>
/// class for physic function
/// </summary>
class CPhysic
{
public:
#pragma region public variable
	/// <summary>
	/// gravity value
	/// </summary>
	static float s_Gravity;
#pragma endregion

#pragma region public function
	/// <summary>
	/// check collision of two rects
	/// </summary>
	/// <param name="_rectOne">rect one</param>
	/// <param name="_rectTwo">rect two</param>
	/// <returns>return if collide</returns>
	static bool RectRectCollision(SRect _rectOne, SRect _rectTwo);
#pragma endregion
};