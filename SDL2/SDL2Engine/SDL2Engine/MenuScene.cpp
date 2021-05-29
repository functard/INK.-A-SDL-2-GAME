#pragma region project include
#include "MenuScene.h"
#include "Engine.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Music.h"

#include "Text.h"
#include "MainScene.h"
#include "Input.h"
#pragma endregion

//Made by Iman

#pragma region public function
// load scene
void GMenuScene::Load()
{
	// initialize mouse
	ENGINE->SetMouseCenter(0.5f, 0.5f);
	ENGINE->SetMouseVisible(true);

	// background
	m_pBackground = new CTexturedEntity(SVector2(), SVector2(), "Texture/Environment/Background/T_Background.png");
	CTM->AddUIObject(m_pBackground);

	m_pMenu = new CMusic("Audio/M_Background2.mp3");
	m_pMenu->Play(true);

#pragma region Iman

	// start game button
	m_pStart = new CText("++++++++++++++", GAME->m_PArial, SRect(250, 100, 65, 487), SColor(0, 0, 0, 0));

	// quit game button
	m_pQuit = new CText("Quit Game", GAME->m_PArial, SRect(200, 50, 45, 630), SColor(255, 255, 255, 255));

#pragma endregion


}

// clean scene
void GMenuScene::Clean()
{
	// remove texts
	CTM->RemoveObject(m_pStart);
	CTM->RemoveObject(m_pQuit);
	CTM->RemoveObject(m_pBackground);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{

	// if mouse button left pressed and mouse position in start button load main scene
	if (CInput::GetMouseButtonDown(0) &&
		CInput::GetMousePosition().X >= m_pStart->GetRect().x &&
		CInput::GetMousePosition().X <= m_pStart->GetRect().x + m_pStart->GetRect().w &&
		CInput::GetMousePosition().Y >= m_pStart->GetRect().y &&
		CInput::GetMousePosition().Y <= m_pStart->GetRect().y + m_pStart->GetRect().h)
	{
		ENGINE->ChangeScene(new GMainScene());
	}
	else if (CInput::GetMouseButtonDown(0) &&
		CInput::GetMousePosition().X >= m_pQuit->GetRect().x &&
		CInput::GetMousePosition().X <= m_pQuit->GetRect().x + m_pQuit->GetRect().w &&
		CInput::GetMousePosition().Y >= m_pQuit->GetRect().y &&
		CInput::GetMousePosition().Y <= m_pQuit->GetRect().y + m_pQuit->GetRect().h)

	{
		GAME->QuitGame();
	}
}

// render every frame
void GMenuScene::Render()
{
	
}
#pragma endregion