#pragma once

#pragma region project include
#include "Scene.h"  
#include "TexturedEntity.h"
#pragma endregion

#pragma region forward decleration
class CText;
class CMusic;

#pragma endregion

//Made by Iman

/// <summary>
/// menu game scene
/// </summary>
class GMenuScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GMenuScene() : CScene() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMenuScene() { Clean(); }
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
	/// start text
	/// </summary>
	//variables
	CText* m_pStart = nullptr;
	CText* m_pQuit = nullptr;
	CMusic* m_pMenu = nullptr;
	CTexturedEntity* m_pBackground = nullptr;
};