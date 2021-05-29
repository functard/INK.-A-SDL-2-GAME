#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

#pragma region forward decleration
class SRect;
class CTexture;
class SDL_Window;
class SDL_Renderer;
#pragma endregion

/// <summary>
/// class to render images
/// </summary>
class CRenderer
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pWindow">sdl window reference</param>
	CRenderer(SDL_Window* _pWindow);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CRenderer();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl renderer
	/// </summary>
	/// <returns>sdl renderer reference</returns>
	inline SDL_Renderer* GetSDLRenderer() { return m_pRenderer; }

	/// <summary>
	/// get camera position
	/// </summary>
	/// <returns>camera position</returns>
	inline SVector2 GetCamera() { return m_camera; }

	/// <summary>
	/// set position of camera
	/// </summary>
	/// <param name="_pos">position to set</param>
	inline void SetCamera(SVector2 _pos) { m_camera = _pos; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// clear screen
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture to render</param>
	/// <param name="_dstRect">destination rect reference</param>
	/// <param name="_srcRect">source rect reference</param>
	/// <param name="_angle">angle</param>
	/// <param name="_mirror">mirror (x != 0 horizontal, y != 0 vertical)</param>
	/// <param name="_inWorld">object is rendered with camera offset or screen</param>
	void RenderTexture(CTexture* _pTexture, SRect* _dstRect = nullptr, SRect* _srcRect = nullptr, 
		float _angle = 0, SVector2 _mirror = SVector2(), bool _inWorld = true);

	/// <summary>
	/// present rendered screen
	/// </summary>
	void Present();
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// camera position
	/// </summary>
	SVector2 m_camera = SVector2();
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl renderer reference
	/// </summary>
	SDL_Renderer* m_pRenderer = nullptr;
#pragma endregion
};