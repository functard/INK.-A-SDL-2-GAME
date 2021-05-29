#pragma region sdl inlude
#include <SDL_image.h>
#pragma endregion

#pragma region project include
#include "Texture.h"
#include "Engine.h"
#include "Renderer.h"
#include "Helper.h"
#pragma endregion

#pragma region constructor
// constructor
CTexture::CTexture(const char * _pFileName)
{
	// initialize renderer nullptr
	m_pTexture = nullptr;

	// if file name valid load texture
	if(_pFileName)
		m_pTexture = IMG_LoadTexture(RENDERER->GetSDLRenderer(),
			GetAssetPath(_pFileName, 4).c_str());
}
#pragma endregion

#pragma region destructor
// destructor
CTexture::~CTexture()
{
	// if texture valid destroy texture
	if (m_pTexture)
		SDL_DestroyTexture(m_pTexture);
}
#pragma endregion