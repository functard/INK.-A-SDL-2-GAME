#pragma once

#pragma region project include
#include "MoveEntity.h" 
#pragma endregion

//Made by Ege, Iman
/// <summary>
/// bullet class
/// </summary>
class GBullet :	public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GBullet(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GBullet(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
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

#pragma region Iman, Ege

	//get m_hasHit
	inline bool GetHasHit() { return m_hasHit; }	

	//set m_hasHit
	inline void SetHasHit(bool _value) { m_hasHit = _value; }

protected:

	// is bullet hit
	bool m_hasHit = false;
#pragma endregion


};