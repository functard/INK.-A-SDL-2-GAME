#pragma once

#pragma region sdl include
#include <SDL_mixer.h>
#pragma endregion

#pragma region project include
#include "Helper.h"
#pragma endregion

/// <summary>
/// sound class
/// </summary>
class CSound
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">file name</param>
	CSound(const char* _pFileName)
	{
		// load sound
		m_pSound = Mix_LoadWAV(GetAssetPath(_pFileName, 4).c_str());
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CSound()
	{
		// free sound
		Mix_FreeChunk(m_pSound);
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get volume of sound
	/// </summary>
	/// <returns>volume of sound</returns>
	int GetVolume()
	{
		return m_volume;
	}

	/// <summary>
	/// set volume of sound
	/// </summary>
	/// <param name="_volume">volume to set</param>
	void SetVolume(int _volume)
	{
		m_volume = _volume;
		Mix_VolumeChunk(m_pSound, _volume);
	}

	/// <summary>
	/// play sound
	/// </summary>
	void Play()
	{
		// play sound
		Mix_PlayChannel(-1, m_pSound, 0);
	}

	/// <summary>
	/// stop sound
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
	/// volume of sound
	/// </summary>
	int m_volume = 100;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl sound
	/// </summary>
	Mix_Chunk* m_pSound = nullptr;
#pragma endregion
};