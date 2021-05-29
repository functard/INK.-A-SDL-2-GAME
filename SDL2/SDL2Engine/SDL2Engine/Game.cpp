#pragma region project include
#include "Game.h"
#include "Font.h"
#include "Engine.h"
#include "Config.h"
#include "Physic.h"
#include "MenuScene.h"
#include "Texture.h"
#pragma endregion

#pragma region public function
// initialize game
void GGame::Init()
{
	// create arial font
	m_PArial = new CFont("Font/F_Arial.ttf");

	// load config from file
	GConfig::LoadConfig("Save/Config.txt");

	// load mouse
	ENGINE->SetMouseTexture(new CTexture("Texture/Mouse/T_Mouse.png"));

	// set gravity
	CPhysic::s_Gravity = GConfig::s_Gravity * GConfig::s_BlockHeight;

	// create new main scene
	ENGINE->ChangeScene(new GMenuScene());
}

// clean game
void GGame::Clean()
{
	// delete arial font
	delete m_PArial;
}
#pragma endregion