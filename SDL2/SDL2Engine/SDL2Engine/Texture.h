#pragma once

#pragma region forward decleration
class SDL_Texture;
#pragma endregion

/// <summary>
/// texture class
/// </summary>
class CTexture
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">file name in absolute path</param>
	CTexture(const char* _pFileName);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CTexture();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl texture
	/// </summary>
	/// <returns>sdl texture reference</returns>
	inline SDL_Texture* GetSDLTexture() { return m_pTexture; }

	/// <summary>
	/// set sdl texture
	/// </summary>
	/// <param name="_pSDLTexture">sdl texture</param>
	inline void SetSDLTexture(SDL_Texture* _pSDLTexture) { m_pTexture = _pSDLTexture; }
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// sdl texture reference
	/// </summary>
	SDL_Texture* m_pTexture = nullptr;
#pragma endregion
};