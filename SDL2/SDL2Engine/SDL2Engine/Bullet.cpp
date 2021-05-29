#pragma region project include
#include "Bullet.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Player.h"
#include "MoveEnemy.h"
#include "Animation.h"

#pragma endregion

#include <iostream>

//Made by Ege, Iman
#pragma region public override function
// update every frame
void GBullet::Update(float _deltaSeconds)
{	
#pragma region Iman, Ege

	// if collision
	if (m_pColTarget)
	{
		//remove bullet
		CTM->RemoveObject(this);

		//if collides with enemy
		if(m_pColTarget->GetTag() == "Enemy")
		{
			
			GMoveEnemy* enemy = (GMoveEnemy*)m_pColTarget;
			SetHasHit(false);

			//if bullet was not hit
			if (!GetHasHit())
			{
				//damage enemy
				enemy->m_health -= 5;
				
				//set m_hasHit to true
				SetHasHit(true);

			}
		}
	
	}
#pragma endregion

	
	// update parent
	CMoveEntity::Update(_deltaSeconds);
}

// render every frame
void GBullet::Render()
{
	CMoveEntity::Render();
}
#pragma endregion