#pragma region project include
#include "Config.h"
#include "Helper.h"
#pragma endregion


// Made by Iman, Ege
#pragma region variables
int GConfig::s_BlockWidth = 64;
int GConfig::s_BlockHeight = 64;
int GConfig::s_BlockAtlasWidth = 26;
int GConfig::s_BlockAtlasHeight = 26;
float GConfig::s_Gravity = 9.81f;
float GConfig::s_PlayerJump = 1.0f;
int GConfig::s_PlayerSrcRectWidth = 36;
int GConfig::s_PlayerSrcRectHeight = 46;
int GConfig::s_FoxSrcRectWidth = 48;
int GConfig::s_FoxSrcRectHeight = 64;
int GConfig::s_BulletSpeed = 250.0f;
int GConfig::s_MoveEnemyWidth = 32;
int GConfig::s_MoveEnemyHeight = 32;
float GConfig::s_MoveEnemySpeed = 125.0f;
#pragma endregion

#pragma region public function
// load config from file
void GConfig::LoadConfig(const char* _pFile)
{
	// string from file
	string text = LoadStringFromFile(_pFile);

	// string for variable and value
	string variable;
	string value;

	// as long as there is a char in text
	while (text.length() > 0)
	{
		// reset variable and value
		variable = "";
		value = "";

		// as long as there is no :
		while (text[0] != ':')
		{
			// incraes variable char
			variable += text[0];

			// remove first char in text
			text.erase(0, 1);
		}

		// remove first char in text
		text.erase(0, 1);

		// as long as there is no new line
		while (text[0] != '\n')
		{
			// incraes value char
			value += text[0];

			// remove first char in text
			text.erase(0, 1);
		}

		// remove first char in text
		text.erase(0, 1);

		// if variable is block width set value
		if (variable == "BlockWidth")
			s_BlockWidth = stoi(value);

		// if variable is block height set value
		else if (variable == "BlockHeight")
			s_BlockHeight = stoi(value);

		// if variable is block atlas width set value
		else if (variable == "BlockAtlasWidth")
			s_BlockAtlasWidth = stoi(value);

		// if variable is block atlas height set value
		else if (variable == "BlockAtlasHeight")
			s_BlockAtlasHeight = stoi(value);

		// if variable is gravity set value
		else if (variable == "Gravity")
			s_Gravity = stoi(value) * 0.001f;

		// if variable is player jump set value
		else if (variable == "PlayerJump")
			s_PlayerJump = stoi(value) * 0.001f;

		// if variable is player source rect width set value
		else if (variable == "PlayerSrcRectWidth")
			s_PlayerSrcRectWidth = stoi(value);

		// if variable is player source rect height set value
		else if (variable == "PlayerSrcRectHeight")
			s_PlayerSrcRectHeight = stoi(value);

		// if variable is fox source rect width set value
		else if (variable == "FoxSrcRectWidth")
			s_FoxSrcRectWidth = stoi(value);

		// if variable is fox source rect height set value
		else if (variable == "FoxSrcRectHeight")
			s_FoxSrcRectHeight = stoi(value);

		// if variable is bullet speed set value
		else if (variable == "BulletSpeed")
			s_BulletSpeed = stoi(value) * 0.001f;

		// if variable is move enemy width set value
		else if (variable == "MoveEnemyWidth")
			s_MoveEnemyWidth = stoi(value);

		// if variable is move enemy height set value
		else if (variable == "MoveEnemyHeight")
			s_MoveEnemyHeight = stoi(value);

		// if variable is move enemy speed set value
		else if (variable == "MoveEnemySpeed")
			s_MoveEnemySpeed = stoi(value) * 0.001f;
	}
}
#pragma endregion