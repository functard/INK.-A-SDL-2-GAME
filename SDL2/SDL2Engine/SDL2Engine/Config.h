#pragma once

/// <summary>
/// static config class
/// </summary>
static class GConfig
{
public:
#pragma region public static primitive variable
	static int s_BlockWidth;
	static int s_BlockHeight;
	static int s_BlockAtlasWidth;
	static int s_BlockAtlasHeight;
	static float s_Gravity;
	static float s_PlayerJump;
	static int s_PlayerSrcRectWidth;
	static int s_PlayerSrcRectHeight;
	static int s_FoxSrcRectWidth;
	static int s_FoxSrcRectHeight;
	static int s_BulletSpeed;
	static int s_MoveEnemyWidth;
	static int s_MoveEnemyHeight;
	static float s_MoveEnemySpeed;

#pragma endregion

#pragma region public static function
	/// <summary>
	/// load config from file
	/// </summary>
	/// <param name="_pFile">file name</param>
	static void LoadConfig(const char* _pFile);
#pragma endregion
};