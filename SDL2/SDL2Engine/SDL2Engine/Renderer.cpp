#pragma region sdl include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Renderer.h"
#include "Rect.h"
#include "Texture.h"
#include "Macro.h"
#pragma endregion

#pragma region constructor
// constructor
CRenderer::CRenderer(SDL_Window * _pWindow)
{
	// initialize renderer nullptr
	m_pRenderer = nullptr;

	// create renderer
	m_pRenderer = SDL_CreateRenderer(
		_pWindow,						// window reference
		-1,								// index
		SDL_RENDERER_ACCELERATED |		// flags
		SDL_RENDERER_PRESENTVSYNC
	);
}
#pragma endregion

#pragma region destructor
// destructor
CRenderer::~CRenderer()
{
	// if renderer valid destroy renderer
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
}
#pragma endregion

#pragma region public function
// clear screen
void CRenderer::ClearScreen()
{
	SDL_RenderClear(m_pRenderer);
}

// render texture
void CRenderer::RenderTexture(CTexture* _pTexture, SRect* _dstRect, SRect* _srcRect, 
	float _angle, SVector2 _mirror, bool _inWorld)
{
	// if texture not valid return
	if (!_pTexture)
		return;

	// if destination rect has no width or height set to nullptr
	if (_dstRect && (!_dstRect->w || !_dstRect->h))
		_dstRect = nullptr;

	// if source rect has no width or height set to nullptr
	if (_srcRect && (!_srcRect->w || !_srcRect->h))
		_srcRect = nullptr;

	// rotation point
	SDL_Point rotationPoint;

	// if destination rect valid
	if (_dstRect)
	{
		// set rotation point to center
		rotationPoint.x = _dstRect->w / 2;
		rotationPoint.y = _dstRect->h / 2;

		// if object is rendered in world
		if (_inWorld)
		{
			// add camera offset to destination rect
			_dstRect->x -= m_camera.X - SCREEN_WIDTH / 16;
			_dstRect->y -= m_camera.Y - SCREEN_HEIGHT / 2;
		}
	}

	// flip enum default none
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

	// if mirror x not 0 flip texture horizontal
	if (_mirror.X != 0 && _mirror.Y == 0)
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	// if mirror y not 0 flip texture vertical
	else if (_mirror.X == 0 && _mirror.Y != 0)
		flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

	// render texture with angle
	SDL_RenderCopyEx(
		m_pRenderer,					// sdl renderer reference
		_pTexture->GetSDLTexture(),		// sdl texture reference
		_srcRect,						// source rect
		_dstRect,						// destination rect
		_angle,							// angle
		&rotationPoint,					// position of
		flip							// flip flags
	);
}

// present rendered screen
void CRenderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}
#pragma endregion