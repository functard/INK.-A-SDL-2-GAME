#pragma once
#pragma once

#pragma region project include
#include "MoveEntity.h"
#include "Animation.h"
#include "Player.h"
#pragma endregion

//Made by Iman

/// <summary>
/// move enemy class
/// </summary>
class GMoveBoss : public CMoveEntity
{
public:
#pragma region Iman
	bool m_pCanDie = false;

	float m_health = 35.0f;
#pragma endregion



#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GMoveBoss(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GMoveBoss(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMoveBoss() {}
#pragma endregion

#pragma region public override function
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

#pragma region public function
	/// <summary>
	/// initialize move enemy
	/// </summary>
	void Init();
private:

#pragma region Iman, Ege

	float m_shootTimer = 2.0f;
	
	bool m_startTimer = false;

	bool m_canShoot = true;

	CAnimation* m_pCurrentAnim = nullptr;

	CAnimation* m_pWalkAnim = nullptr;

	CAnimation* m_pAttackAnim = nullptr;

	CAnimation* m_pDeathAnim = nullptr;
#pragma endregion



#pragma endregion
};