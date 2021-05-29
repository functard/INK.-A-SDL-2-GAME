#pragma region project include
#include "MoveEntity.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Macro.h"
#include "Player.h"
#pragma endregion

// Made by Ege
#pragma region public override function
// update every frame
void CMoveEntity::Update(float _deltaSeconds)
{
	// check gravity movement down
	CheckCollision(_deltaSeconds, SVector2(0.0f, 1.0f), CPhysic::s_Gravity, true);

	// check collision with collision list
	CheckCollision(_deltaSeconds, m_movement, m_speed, false);

	// update parent
	CTexturedEntity::Update(_deltaSeconds);
	

}

// render every frame
void CMoveEntity::Render()
{
	CTexturedEntity::Render();
}
#pragma endregion

#pragma region public function
// fill collision list with near collidable objects
void CMoveEntity::SetCollisionList()
{
	// if camera too far away return
	if (RENDERER->GetCamera().X > m_position.X + SCREEN_WIDTH ||
		RENDERER->GetCamera().X < m_position.X - SCREEN_WIDTH ||
		RENDERER->GetCamera().Y > m_position.Y + SCREEN_HEIGHT ||
		RENDERER->GetCamera().Y < m_position.Y - SCREEN_HEIGHT)
	{
		return;
	}

	// clear list of collision objects in range
	m_pCol.clear();

	// set range check rect
	SRect rangeRect = m_rect;
	rangeRect.x -= COLLISION_RANGE;
	rangeRect.y -= COLLISION_RANGE;
	rangeRect.w += 2 * COLLISION_RANGE;
	rangeRect.h += 2 * COLLISION_RANGE;

	// through all scene objects
	for (CEntity* pObj : CTM->GetSceneObjects())
	{
		if (!pObj)
			continue;
		
		// if current object is textured object min and not self
		if ((CTexturedEntity*)pObj && pObj != this)
		{
			// if collision type is none continue
			if (((CTexturedEntity*)pObj)->GetColType() == ECollisionType::NONE)
				continue;
			
			// if current object collides (is in range) with this
			if (CPhysic::RectRectCollision(rangeRect, ((CTexturedEntity*)pObj)->GetRect()))
				// add current object to collision list
				m_pCol.push_front((CTexturedEntity*)pObj);
		}
	}

	// through all persistant objects
	for (CEntity* pObj : CTM->GetPersistantObjects())
	{
		if (!pObj)
			continue;
		// if current object is textured object min and not self
		if ((CTexturedEntity*)pObj && pObj != this)
		{
			// if collision type is none continue
			if (((CTexturedEntity*)pObj)->GetColType() == ECollisionType::NONE)
				continue;

			// if current object collides (is in range) with this
			if (CPhysic::RectRectCollision(rangeRect, ((CTexturedEntity*)pObj)->GetRect()) && !GPlayer::Get()->m_invulnerability) // Ege
				// add current object to collision list
				m_pCol.push_front((CTexturedEntity*)pObj);
		}
	}
}
#pragma endregion

#pragma region private function
// check collision with collidable objects list
void CMoveEntity::CheckCollision(float _deltaSeconds, SVector2 _movement, float _speed, bool _useGravity)
{
	// if camera too far away return
	if (RENDERER->GetCamera().X > m_position.X + SCREEN_WIDTH ||
		RENDERER->GetCamera().X < m_position.X - SCREEN_WIDTH ||
		RENDERER->GetCamera().Y > m_position.Y + SCREEN_HEIGHT ||
		RENDERER->GetCamera().Y < m_position.Y - SCREEN_HEIGHT)
	{
		return;
	}

	// if gravity used but gravity false return
	if (_useGravity && !m_gravity)
		return;

	// moveable default true
	bool moveable = true;

	// if gravity used grounded default true
	if(_useGravity)
		m_grounded = true;

	// reset collision target
	m_pColTarget = nullptr;

	// reset collision target
	m_pColTarget = nullptr;

	// calculate position to move to
	SVector2 nextPos = m_position + _movement * _speed * _deltaSeconds;

	// if gravity used
	if (_useGravity)
	{

		// increase fall time
		m_fallTime += _deltaSeconds;

		// calculate position to move to
		nextPos = m_position + _movement * _speed * m_fallTime * _deltaSeconds;


	}

	// calculate rect to move to
	SRect rect = m_rect;
	rect.x = nextPos.X;
	rect.y = nextPos.Y;

	// through all collision objects in range
	for (CTexturedEntity* pObj : m_pCol)
	{
		// if current object is textured object min
		if (pObj != this)
		{
			// get rect from object
			SRect objRect = ((CTexturedEntity*)pObj)->GetRect();
			objRect.x = pObj->GetPosition().X;
			objRect.y = pObj->GetPosition().Y;

			// if collision type is none continue
			if (pObj->GetColType() == ECollisionType::NONE)
				continue;

			// set moveable by checking collision
			moveable = !CPhysic::RectRectCollision(rect, objRect);

			// if not moveable cancel collision check
			if (!moveable)
			{
				
				// set collision target
				m_pColTarget = (CTexturedEntity*)pObj;
				m_pColFallTarget = (CTexturedEntity*)pObj;

				break;
			}
			


		}
	}

	// if gravity used and moveable set grounded false
	if (_useGravity && moveable)
	{
		m_grounded = false;
	}

	// if still moveable set new position
	if (moveable)
		// set next position
		m_position = nextPos;
	
#pragma region Ege

	// if not moveable and gravity true reset fall time
	else if (_useGravity)
	{
		
		m_fallTime = 0;
		canJump = true;
		isJumping = false;
		
	}
#pragma endregion
		
}
#pragma endregion