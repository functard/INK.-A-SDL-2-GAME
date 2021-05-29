#pragma region system include
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#pragma endregion

#pragma region project include
#include "Macro.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Mouse.h"
#pragma endregion

#pragma region public function
// initialize sdl2
int CEngine::Init()
{
	// initialize sdl video
	LOG_SDL_ERROR(SDL_Init(SDL_INIT_VIDEO) < 0, 101)
	
	// create window
	m_pWindow = SDL_CreateWindow(
		"SDL2 Engine",			// name of window
		SDL_WINDOWPOS_CENTERED,	// position x
		SDL_WINDOWPOS_CENTERED,	// position y
		SCREEN_WIDTH,			// width
		SCREEN_HEIGHT,			// height
		SDL_WINDOW_SHOWN		// flag
	);

	// if window not created log error
	LOG_SDL_ERROR(!m_pWindow, 102);

	// get surface from window
	m_pSurface = SDL_GetWindowSurface(m_pWindow);

	// if surface not created log error
	LOG_SDL_ERROR(!m_pSurface, 103);

	// initialize renderer
	m_pRenderer = new CRenderer(m_pWindow);

	// error if renderer nullptr
	LOG_SDL_ERROR(!m_pRenderer->GetSDLRenderer(), 104);

	// initialize sdl font
	LOG_SDL_ERROR(TTF_Init() < 0, 105);

	// initialize audio
	LOG_SDL_ERROR(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096), 106);

	// create time
	m_pTime = new CTime();

	// error if time nullptr
	if (!m_pTime)
	{
		LOG_ERROR("Time not initialized", 201);
	}

	// initialize content management
	m_pCTM = new CContentManagement();

	// error if content management nullptr
	if (!m_pCTM)
	{
		LOG_ERROR("Content Management not initialized", 202);
	}

	// initialize texture management
	m_pTTM = new CTextureManagement();

	// error if texture management nullptr
	if (!m_pTTM)
	{
		LOG_ERROR("Texture Management not initialized", 203);
	}

	// initialize mouse
	m_pMouse = new CMouse(SVector2(32, 32));
	SDL_ShowCursor(SDL_DISABLE);

	// error if mouse nullptr
	if (!m_pMouse)
	{
		LOG_ERROR("Mouse not initialized", 204);
	}

	// return 0 if every module initialized
	return 0;
}

// load images
int CEngine::Load()
{
	// return 0 if scene loaded
	return 0;
}

// running program
void CEngine::Run()
{
	// loop if engine running
	while (m_isRunning)
	{
		// update
		Update();

		// render
		Render();
	}
}

// cleaning program
void CEngine::Clean()
{
	// change scene to nullptr
	ChangeScene(nullptr);

	// delete mouse
	delete m_pMouse;

	// delete time
	delete m_pTime;

	// delete ctm
	delete m_pCTM;

	// destroy renderer
	delete m_pRenderer;

	// close audio
	Mix_CloseAudio();

	// destroy surface
	SDL_FreeSurface(m_pSurface);

	// destroy window
	SDL_DestroyWindow(m_pWindow);

	// quit sdl
	SDL_Quit();
}

// set mouse visible
void CEngine::SetMouseVisible(bool _visible)
{
	m_pMouse->SetVisible(_visible);
}

// set position of mouse center
void CEngine::SetMouseCenter(float x, float y)
{
	m_pMouse->SetCenter(SVector2(x, y));
}

// set mouse texture
void CEngine::SetMouseTexture(CTexture* _pTexture)
{
	m_pMouse->SetTexture(_pTexture);
}

// change active scene
void CEngine::ChangeScene(CScene* _pScene)
{
	// if active scene valid
	if (m_pScene)
	{
		// clean scene objects
		m_pCTM->CleanSceneObjects();

		// clean scene
		m_pScene->Clean();

		// delete active scene
		delete m_pScene;
	}

	// set new scene
	m_pScene = _pScene;

	// if new scene valid load scene
	if (m_pScene)
		m_pScene->Load();
}
#pragma endregion

#pragma region private function
// update every frame
void CEngine::Update()
{
	//cout << m_pTime->GetFPS() << endl;

	// update time
	m_pTime->Update();

	// refresh state
	CInput::RefreshState();

	// create union sdl event
	SDL_Event e;

	// while getting event
	while (SDL_PollEvent(&e))
	{
		// if event quit set running false
		if (e.type == SDL_EventType::SDL_QUIT)
			m_isRunning = false;

		// parse event to input
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			CInput::ParseEvent(e);

		// parse mouse event to input
		else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			CInput::ParseMouseEvent(e);
	}

	// update mouse
	m_pMouse->Update(m_pTime->GetDeltaTime());

	// update content management
	m_pCTM->Update(m_pTime->GetDeltaTime());

	// update scene
	m_pScene->Update(m_pTime->GetDeltaTime());
}

// render every frame
void CEngine::Render()
{
	// clear screen
	m_pRenderer->ClearScreen();

	// render content management
	m_pCTM->Render();

	// render scene
	m_pScene->Render();

	// render mouse
	m_pMouse->Render();

	// present rendered screen
	m_pRenderer->Present();
}
#pragma endregion