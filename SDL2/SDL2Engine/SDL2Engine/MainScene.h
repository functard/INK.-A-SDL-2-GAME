#pragma once


#pragma region project include
#include "Scene.h"
#pragma endregion

#pragma region forward decleration
class GWorld;
class CMusic;
class CTexturedEntity;
#pragma endregion

//Made by Iman, Ege

/// <summary>
/// main game scene
/// </summary>
class GMainScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GMainScene() : CScene() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMainScene() { Clean(); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// load scene
	/// </summary>
	virtual void Load() override;

	/// <summary>
	/// clean scene
	/// </summary>
	virtual void Clean() override;

	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// world
	/// </summary>
	GWorld* m_pWorld = nullptr;

	/// <summary>
	/// background music
	/// </summary>
	CMusic* m_pMusic = nullptr;

	// background
	CTexturedEntity* m_pMainBackground = nullptr;

	//health bar 
	CTexturedEntity* m_UIHealth = nullptr;

#pragma endregion
};