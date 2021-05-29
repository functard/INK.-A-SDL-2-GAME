#pragma once

#pragma region project include
#include "Entity.h"
#include "Rect.h"
#include "Enum.h"
#pragma endregion

#pragma region forward decleration
class CRenderer;
class CTexture;
#pragma endregion

/// <summary>
/// textured object class
/// </summary>
class CTexturedEntity : public CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	CTexturedEntity(SVector2 _pos = SVector2(), SVector2 _size = SVector2());

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	CTexturedEntity(SVector2 _pos, SVector2 _size, const char* _pFileName);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CTexturedEntity() { }
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
	/// <param name="_pRenderer">renderer</param>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get angle
	/// </summary>
	/// <returns>angle</returns>
	inline float GetAngle() { return m_angle; }

	/// <summary>
	/// set angle
	/// </summary>
	/// <param name="_angle">angle to set</param>
	inline void SetAngle(float _angle) { m_angle = _angle; }

	/// <summary>
	/// set object is rendered with camera offset or screen
	/// </summary>
	/// <param name="_inWorld">camera offset rendered or screen</param>
	inline void SetInWorld(bool _inWorld) { m_inWorld = _inWorld; }

	/// <summary>
	/// get collision type
	/// </summary>
	/// <returns>collision type</returns>
	inline ECollisionType GetColType() { return m_colType; }

	/// <summary>
	/// set collision type
	/// </summary>
	/// <param name="_colType">collision type</param>
	inline void SetColType(ECollisionType _colType) { m_colType = _colType; }
	
	/// <summary>
	/// get rect
	/// </summary>
	/// <returns>rect</returns>
	inline SRect GetRect() { return m_rect; }

	/// <summary>
	/// set rect
	/// </summary>
	/// <param name="_rect">rect to set</param>
	inline void SetRect(SRect _rect) { m_rect = _rect; }

	inline void SetRectWidth(int _width) { m_rect.w = _width; }
	/// <summary>
	/// set source rect
	/// </summary>
	/// <param name="_rect">rect to set</param>
	inline void SetSrcRect(SRect _rect) { m_srcRect = _rect; }

	/// <summary>
	/// get mirror
	/// </summary>
	/// <returns>mirror</returns>
	inline SVector2 GetMirror() { return m_mirror; }

	/// <summary>
	/// set mirror
	/// </summary>
	/// <param name="_mirror">mirror to set</param>
	inline void SetMirror(SVector2 _mirror) { m_mirror = _mirror; }

	/// <summary>
	/// set texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	inline void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// render angle
	/// </summary>
	float m_angle = 0.0f;

	/// <summary>
	/// if object is rendered with camera offset or screen
	/// </summary>
	bool m_inWorld = true;

	/// <summary>
	/// collision type
	/// </summary>
	ECollisionType m_colType = ECollisionType::NONE;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// rect of object
	/// </summary>
	SRect m_rect = SRect();

	/// <summary>
	/// source rect for texture
	/// </summary>
	SRect m_srcRect = SRect();

	/// <summary>
	/// mirror horizontal and vertical
	/// x != 0 -> mirror horizontal
	/// y != 0 -> mirror vertical
	/// if x != 0 ignore y value
	/// </summary>
	SVector2 m_mirror = SVector2();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// texture of object
	/// </summary>
	CTexture* m_pTexture = nullptr;
	CTexture* m_pTexture2 = nullptr;
#pragma endregion
};