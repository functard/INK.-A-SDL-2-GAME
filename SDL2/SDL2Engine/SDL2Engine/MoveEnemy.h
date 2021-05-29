#pragma once

#pragma region project include
#include "MoveEntity.h"
#include "Animation.h"
#include "Player.h"
#pragma endregion

//Made by Ege

/// <summary>
/// move enemy class
/// </summary>
class GMoveEnemy : public CMoveEntity
{
public:


#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GMoveEnemy(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GMoveEnemy(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMoveEnemy() {}
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

#pragma region Ege, Iman

	//enemy reference
	static GMoveEnemy* pEnemy;

	//static function to acces enemy outside class
	inline static GMoveEnemy* Get()
	{		
		return pEnemy;
	}


	//enemy health
	float m_health;

	//enemy can die
	bool m_pCanDie = false;

private:

	//enemy is dead
	bool m_isDead = false;

	// enemies currently playing animation
	CAnimation* m_pCurrentAnim = nullptr;
	
	//enemy walk animation
	CAnimation* m_pWalkAnim = nullptr;

	//enemy death animation
	CAnimation* m_pDeathAnim = nullptr;

	//enemy attack animation
	CAnimation* m_pAttackAnim = nullptr;
#pragma endregion





#pragma endregion
};