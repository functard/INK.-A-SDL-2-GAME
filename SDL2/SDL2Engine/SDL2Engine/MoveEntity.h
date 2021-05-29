#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "TexturedEntity.h" 
#pragma endregion

/// <summary>
/// moveable object class
/// </summary>
class CMoveEntity : public CTexturedEntity
{
public:
	bool isDead = false; // Ege
	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	CMoveEntity(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CTexturedEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	CMoveEntity(SVector2 _pos, SVector2 _size, const char* _pFileName) : CTexturedEntity(_pos, _size, _pFileName){}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMoveEntity() {}
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

#pragma region public inline function
	/// <summary>
	/// activate gravity
	/// </summary>
	inline void ActivateGravity() { m_gravity = true; }

	/// <summary>
	/// deactivate gravity
	/// </summary>
	inline void DeactivateGravity() { m_gravity = false; }

	/// <summary>
	/// get movement speed
	/// </summary>
	/// <returns>movement speed</returns>
	inline float GetSpeed() { return m_speed; }

	/// <summary>
	/// set movement speed
	/// </summary>
	/// <param name="_speed">movement speed to set</param>
	inline void SetSpeed(float _speed) { m_speed = _speed; }

	/// <summary>
	/// get movement values
	/// </summary>
	/// <returns>movement values</returns>
	inline SVector2 GetMovement() { return m_movement; }

	/// <summary>
	/// set movement values
	/// </summary>
	/// <param name="_movement">movement values</param>
	inline void SetMovement(SVector2 _movement) { m_movement = _movement; }

	/// <summary>
	/// set falle time
	/// </summary>
	/// <param name="_fallTime">fall time to set</param>
	inline void SetFallTime(float _fallTime) { m_fallTime = _fallTime; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// fill collision list with near collidable objects
	/// </summary>
	void SetCollisionList();
#pragma endregion

protected:
#pragma region protected primitive variable


	/// <summary>
	/// object moveable
	/// </summary>
	bool m_moveable = false;

	/// <summary>
	/// object jumpable
	/// </summary>
	bool canJump = false; // ege

	/// <summary>
	/// object jumping
	/// </summary>
	bool isJumping = false; // ege

	/// <summary>
	/// if gravity is active
	/// </summary>
	bool m_gravity = false;

	/// <summary>
	/// if object falls not
	/// </summary>
	bool m_grounded = false;

	/// <summary>
	/// movement speed
	/// </summary>
	float m_speed = 0.0f;

	/// <summary>
	/// timer until collision list update
	/// </summary>
	float m_colTimer = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// movement values
	/// </summary>
	SVector2 m_movement = SVector2();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// collision target
	/// </summary>
	CTexturedEntity* m_pColTarget;

	/// <summary>
/// collision target while falling
	CTexturedEntity* m_pColFallTarget; // ege


	/// <summary>
	/// list with all collision objects in range
	/// </summary>
	std::list<CTexturedEntity*> m_pCol;
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time that object is in air
	/// </summary>
	float m_fallTime = 0.0f;
#pragma endregion

#pragma region private function
	/// <summary>
	/// check collision with collidable objects list
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	/// <param name="_movement">movmenet to move to</param>
	/// <param name="_speed">movement speed</param>
	/// <param name="_useGravity">if gravity movement</param>
	void CheckCollision(float _deltaSeconds, SVector2 _movement, float _speed, bool _useGravity);
#pragma endregion
};