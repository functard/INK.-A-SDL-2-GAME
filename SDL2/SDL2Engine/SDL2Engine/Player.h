#pragma once

#pragma region project include
#include "MoveEntity.h"
#pragma endregion

#pragma region forward decleration
class CAnimation;
class CSound;
#pragma endregion

//Made by Iman, Ege
/// <summary>
/// player class
/// </summary>
class GPlayer :	public CMoveEntity
{
public:
#pragma region Ege

	//player invulnerability
	bool m_invulnerability = false;

	//player health
	float m_playerHealth = 200.0f;
#pragma endregion


#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GPlayer(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GPlayer(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		// delete animations
		delete m_pIdleAnim;
		delete m_pRunAnim;
		delete m_pShootAnim;
		delete m_pAttackAnim;
		delete m_pJumpAnim;
		delete m_pTakaDamageAnim;
	}
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
	/// initialize player
	/// </summary>
	void Init();
#pragma endregion

#pragma region Ege

	//static function to acces player outside class
	inline static GPlayer* Get()
	{
		// return player
		return pPlayer;
	}
#pragma endregion


private:
#pragma region Ege
	// Keeps track of player form
	bool m_isHumanForm = true;

	//is attacking
	bool m_isAttacking = false;

	//starts invulnerability timer
	bool m_startCooldown = false;

	//can idle
	bool m_canIdle = true;

	//can run
	bool m_canRun = true;

	//player invulnerabiltiy time
	float m_invulnerabilityTimer = 2.0f;

	//player reference
	static GPlayer* pPlayer;






	/// <summary>
	/// current animation
	/// </summary>
	CAnimation* m_pCurrentAnim = nullptr;

	/// <summary>
	/// idle animation
	/// </summary>
	CAnimation* m_pIdleAnim = nullptr;

	/// <summary>
	/// shoot animation
	/// </summary>
	CAnimation* m_pShootAnim = nullptr;


	/// <summary>
	/// run animation
	/// </summary>
	CAnimation* m_pRunAnim = nullptr;

	/// <summary>
	/// take damage animation
	/// </summary>
	CAnimation* m_pTakaDamageAnim = nullptr;


	/// <summary>
	/// wolf attack animation
	/// </summary>
	CAnimation* m_pAttackAnim = nullptr;

	/// <summary>
	/// jump animation
	/// </summary>
	CAnimation* m_pJumpAnim = nullptr;


	/// <summary>
	/// shot sound
	/// </summary>
	CSound* m_pShot = nullptr;

	// wolf attack sound
	CSound* m_pFoxAttack = nullptr;

	// form change sound
	CSound*m_Fox = nullptr;


	

#pragma endregion
};