#pragma region system include
#include <string>
#include <SDL_image.h>
#pragma endregion

#pragma region project include
#include "World.h"
#include "Engine.h"
#include "EndBoss.h"

#include "ContentManagement.h"
#include "Config.h"
#include "Texture.h"
#include "Player.h"
#include "MoveEnemy.h"
#include "Helper.h"	
#include "Collectable.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

//Made by Iman, Ege

#pragma region public function
// initlialize world
void GWorld::Init()
{
	// create world texture
	m_pTexture = new CTexture("Texture/World/T_WorldSide2.png");

	// string that defines world
	string world;

	// add lines to string
	// string is 100x20
	// 1 block is 64 x 64 pixel
	// screen has 20 (width) and 12 (height) blocks
	// X / red 128 = dirt (outside)
	// 0 / red 64 = black (free)
	// W / red 192 = way (walk on)
	// I / red 255 = lava (death)
	// E / blue = enemy
	// S / green = start
	
	// load world from txt file
	world = LoadStringFromFile("Save/World.txt");

	// load world from bmp file
	world = LoadWorldFromBmp("Save/World.png");

	// width and height of world
	int width = 0, height = 0;

	

	// through string
	for (int i = 0; i < world.length(); i++)
	{
		// create textured object
		CTexturedEntity* pObj = new CTexturedEntity(
			SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockWidth),	// position of block
			SVector2(GConfig::s_BlockWidth, 41)						// size of block
		);	

		

		// set texture of object
		pObj->SetTexture(m_pTexture);

		// x position of texture in atlas map
		int xPosOfTexture = 0;

		// switch char in world string
		switch (world[i])
		{
		// if dirt set position of second texture in atlas map
		case 'X':
			xPosOfTexture = 4* 112;
			pObj->SetColType(ECollisionType::WALL);
			break;

		// if way set position of third texture in atlas map
		case 'W':
			xPosOfTexture = 1* 15;
			pObj->SetColType(ECollisionType::WALL);
			pObj->SetTag("WALL");
			break;

		// if fire set position of fourth texture in atlas map
		case 'I':
			xPosOfTexture = 3* 78;
			pObj->SetColType(ECollisionType::MOVE);
			pObj->SetTag("Fire");
			break;

		// if player start position spawn player
		case 'S':
		{
			// initialize player
			GPlayer* pPlayer = new GPlayer(SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockHeight - 320),
				SVector2(120, 140), "Texture/Player/T_Player.png");
			pPlayer->Init();
			pPlayer->SetSpeed(GConfig::s_BlockWidth * 1.0f);
			pPlayer->ActivateGravity();
			pPlayer->SetCollisionList();
			pPlayer->SetTag("Player");

			// add player to persistant
			CTM->AddPersistantObject(pPlayer);
			break;
		}

		// if enemy spwawn enemy
		case 'E':
		{
			// create enemy
			GMoveEnemy* pEnemy = new GMoveEnemy(SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockHeight - 320),
				SVector2(GConfig::s_MoveEnemyWidth, GConfig::s_MoveEnemyHeight), "Texture/Enemy/T_MoveEnemy.png");

			// initialize enemy and add to persistant
			pEnemy->Init();
			pEnemy->SetCollisionList();
			CTM->AddPersistantObject(pEnemy);
			break;
		}
	


#pragma region Iman

		case 'D':
		
		 {
			// create boss
			
			GMoveBoss* pBoss = new GMoveBoss(SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockHeight - 320),
				SVector2(173, 218), "Texture/Enemy/T_MoveBoss.png");
		
			// initialize enemy and add to persistant
			pBoss->Init();
			//set collision list
			pBoss->SetCollisionList();

			//add to persistant list
			CTM->AddPersistantObject(pBoss);
			break;
		}
#pragma endregion



		default:
			// if new line increase height and reset width
			if (world[i] == '\n')
			{
				height++;
				width = 0;
			}

			width++;
			continue;
		}

		// set source rect of object
		pObj->SetSrcRect(SRect(GConfig::s_BlockAtlasWidth, GConfig::s_BlockAtlasHeight, xPosOfTexture, 0));

		// add object to scene list
		CTM->AddSceneObject(pObj);

		// increase width
		width++;

		
	}
}
#pragma endregion

#pragma region private function
// load world as string from bmp file
string GWorld::LoadWorldFromBmp(const char* _pFile)
{
	// string to return
	string text = "";

	// create sdl surface from file
	SDL_Surface* pWorld = IMG_Load(GetAssetPath(_pFile, 4).c_str());

	// load pixels in char*
	char* pPixels = (char*)pWorld->pixels;

	// check all pixels
	for (int i = 0; i < pWorld->w * pWorld->h; i++)
	{
		// get pixel colors
		uint8_t r = pPixels[0];
		uint8_t g = pPixels[1];
		uint8_t b = pPixels[2];

		// if pixel is blue
		if (r == 64)
			text.append("0");

		// if pixel is b
		else if (r == 128)
			text.append("X");

		// if pixel is green
		else if (r == 192)
			text.append("W");

		// if pixel is red
		else if (r == 255)
			text.append("I");

		// if pixel is white
		else if (b == 255)
			text.append("E");

		// if pixel is yellow
		else if (g == 255)
			text.append("S");
		else if (g == 155)
			text.append("Z");

#pragma region Iman
		else if (b == 100)
			text.append("D");

#pragma endregion

		// if nothing hit add 0
		else
			text.append("0");

		// increase pixel pointer of bytes per pixel
		pPixels += pWorld->format->BytesPerPixel;

		// if i is modulo width of world add new line
		if ((i + 1) % pWorld->w == 0)
			text.append("\n");
	}

	// return string
	return text;
}
#pragma endregion