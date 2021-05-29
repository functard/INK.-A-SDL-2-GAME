#pragma once

#pragma region system include
#include <SDL_mixer.h>  
#pragma endregion

#pragma region project include
#include "Helper.h"
#pragma endregion

/// <summary>
/// music class
/// </summary>
class CMusic
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">file name</param>
	CMusic(const char* _pFileName)
	{
		// load music
		m_pMusic = Mix_LoadMUS(GetAssetPath(_pFileName, 4).c_str());
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CMusic()
	{
		// free music
		Mix_FreeMusic(m_pMusic);
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get volume of music
	/// </summary>
	/// <returns>volume of music</returns>
	int GetVolume() 
	{
		return m_volume; 
	}

	/// <summary>
	/// set volume of music
	/// </summary>
	/// <param name="_volume">volume to set</param>
	void SetVolume(int _volume)
	{
		m_volume = _volume;
		Mix_VolumeMusic(_volume);
	}

	/// <summary>
	/// play music
	/// </summary>
	/// <param name="_loop">is looping</param>
	void Play(bool _loop)
	{
		// int for loop
		// 1 = 1 time
		// -1 = endless
		int loop = 1;

		// if loop
		if (_loop)
			loop = -1;

		// play music
		Mix_PlayMusic(m_pMusic, loop);
	}

	/// <summary>
	/// stop music
	/// </summary>
	void Stop()
	{
		// stop music
		Mix_HaltMusic();
	}
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// volume of music
	/// </summary>
	int m_volume = 100;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl music
	/// </summary>
	Mix_Music* m_pMusic = nullptr;
#pragma endregion
};