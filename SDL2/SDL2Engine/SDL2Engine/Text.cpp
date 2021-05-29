#pragma region project include
#include "Text.h"
#include "Engine.h"
#include "Renderer.h"
#include "Texture.h"
#include "Font.h"
#pragma endregion

#pragma region constructor
// constructor
CText::CText(const char* _pText, CFont* _pFont, SRect _rect, SColor _color)
	: CTexturedEntity(SVector2(), SVector2(), "")
{
	// variable
	m_pText = _pText;
	m_pFont = _pFont;
	m_rect = _rect;
	m_color = _color;

	// load text
	Load();
}
#pragma endregion

#pragma region destructor
// destructor
CText::~CText()
{
	// free surface
	SDL_FreeSurface(m_pSurface);
}
#pragma endregion

#pragma region public override function
// update every frame
void CText::Update(float _deltaTime)
{

}

// render every frame
void CText::Render()
{
	CTexturedEntity::Render();
}
#pragma endregion

#pragma region private function
// load text
void CText::Load()
{
	// text normally not in world
	m_inWorld = false;

	// update surface
	m_pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_pText, m_color);

	// if texture valid destroy old texture
	if(m_pTexture)
		SDL_DestroyTexture(m_pTexture->GetSDLTexture());

	// create texture
	m_pTexture->SetSDLTexture(SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), m_pSurface));

	// free surface
	SDL_FreeSurface(m_pSurface);
	m_pSurface = nullptr;
}
#pragma endregion