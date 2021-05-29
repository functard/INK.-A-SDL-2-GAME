#pragma region project include
#include "MainScene.h"
#include "Renderer.h"
#include "Player.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "World.h"
#include "Music.h"
#pragma endregion

//Made by Iman, Ege


class Player;
#pragma region public function
// load scene
void GMainScene::Load()
{

	// initialize mouse
	ENGINE->SetMouseVisible(false);
	
#pragma region Iman,Ege

	//set health bar
	m_UIHealth = new CTexturedEntity(SVector2(80, 300), SVector2(200, 80), "Texture/Environment/Background/T_Health.png");

	//add health bar as ui object
	CTM->AddUIObject(m_UIHealth);
	
	//set as ui element
	m_UIHealth->SetInWorld(false);

	// game background
	m_pMainBackground = new CTexturedEntity(SVector2(), SVector2(8100,900),  "Texture/Environment/Background/T_MainBackGround.png");
	
	// add background
	CTM->AddSceneObject(m_pMainBackground);
#pragma endregion


	

	// initialize world
	m_pWorld = new GWorld("Texture/World/T_WorldSide.png");
	m_pWorld->Init();

	// create music and start playing
	m_pMusic = new CMusic("Audio/M_Background.ogg");
	m_pMusic->Play(true);
}

// clean scene
void GMainScene::Clean()
{
	// delete music
	delete m_pMusic;

	// delete world
	delete m_pWorld;

	// delete all persistant objects
	CTM->CleanPersistantObjects();
}

// update every frame
void GMainScene::Update(float _deltaSeconds)
{
#pragma region Ege,Iman

	//if player is not dead
	if(GPlayer::Get()->m_playerHealth > 0)
		m_UIHealth->SetRectWidth(GPlayer::Get()->m_playerHealth); //scales the health bar according to player health
		
#pragma endregion
}

// render every frame
void GMainScene::Render()
{
	
}
#pragma endregion