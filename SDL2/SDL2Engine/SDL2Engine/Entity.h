#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// base object class
/// </summary>
class CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEntity() {}
#pragma endregion

#pragma region inline function
	/// <summary>
	/// get tag
	/// </summary>
	/// <returns>tag</returns>
	inline const char* GetTag() { return m_pTag; }

	/// <summary>
	/// set tag
	/// </summary>
	/// <param name="_pTag">tag to set</param>
	void SetTag(const char* _pTag) { m_pTag = _pTag; }

	/// <summary>
	/// get position of object
	/// </summary>
	/// <returns>position of object</returns>
	inline SVector2 GetPosition() { return m_position; }

	/// <summary>
	/// set position of object
	/// </summary>
	/// <param name="_pos">position to set</param>
	inline void SetPosition(SVector2 _pos) { m_position = _pos; }

	/// <summary>
	/// add vector2 to position
	/// </summary>
	/// <param name="_vec2"></param>
	inline void AddPosition(SVector2 _vec2) { m_position = m_position + _vec2; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) = 0;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() = 0;
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// tag of object
	/// </summary>
	const char* m_pTag = nullptr;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// position of object
	/// </summary>
	SVector2 m_position = SVector2();
#pragma endregion
};