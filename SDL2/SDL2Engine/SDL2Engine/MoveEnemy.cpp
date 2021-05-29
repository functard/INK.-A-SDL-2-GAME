#pragma region project include
#include "MoveEnemy.h"
#include "Config.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Animation.h"
#include "Bullet.h"
#pragma endregion

// Made by Ege
GMoveEnemy* GMoveEnemy::pEnemy = nullptr;

#pragma region Ege

#pragma region public override function
// update every frame
void GMoveEnemy::Update(float _deltaSeconds)
{
	// if death animation finishes
	if (m_pDeathAnim->GetAnimationPercentage() == 100)
	{
		//can die
		m_pCanDie = true;

		//set current animation to death animation
		m_pDeathAnim->ResetAnimationPercentage();
	}

	//if player is dead
	if (m_health <= 0)
	{
		//set current animation to death animation
		m_pCurrentAnim = m_pDeathAnim;

		// is dead
		isDead = true;

		//if can die 
		if (m_pCanDie)
		{
			//delete enemy
			CTM->RemoveObject(this);
		}

	}


	
	// if enemy is near player
	if ((GetPosition().X < GPlayer::Get()->GetPosition().X + 250 || GetPosition().X < GPlayer::Get()->GetPosition().X - 250) && m_pCurrentAnim != m_pDeathAnim)
	{
		//enemy attack
		m_pCurrentAnim = m_pAttackAnim;
	}

	//else
	else if(m_pCurrentAnim != m_pDeathAnim && m_pCurrentAnim != m_pDeathAnim)
	{
		//play enemy walk animation
		m_pCurrentAnim = m_pWalkAnim;
	}


	//if enemy collides 
	if (!m_moveable && m_pColTarget && m_pColTarget->GetTag() != "Bullet")
	{
		//change direction
		m_movement.X *= -1;
		m_position.X += m_movement.X;
	}

	//if moving right
	if (m_movement.X > 0)
	{
		//set direction right
		m_mirror = 1.0f;
	}

	//if moving left
	else if(m_movement.X < 0)
	{
		//set direction left
		m_mirror = 0;
	}
#pragma endregion

	
	// update animation
	m_pCurrentAnim->Update(_deltaSeconds);

	// set source from animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y,
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y
	);


	// update parent
	CMoveEntity::Update(_deltaSeconds);
}

// render every frame
void GMoveEnemy::Render()
{
	// render parent
	CMoveEntity::Render();
}
#pragma endregion


#pragma region Ege

#pragma region public function
// initialize move enemy
void GMoveEnemy::Init()
{
		//set enemy to this
		pEnemy = this;

		// set enemy walk animation
		m_pWalkAnim = new CAnimation(SVector2(0,260),
		SVector2(170, GConfig::s_MoveEnemyHeight), 5);

		//set enemy walk animation time
		m_pWalkAnim->SetAnimationTime(0.5f);

		//set enemy attack animation time
		m_pAttackAnim = new CAnimation(SVector2(0, 0),
			SVector2(170, 210), 7);

		//set enemy attack animation time
		m_pAttackAnim->SetAnimationTime(0.5f);

		// set enemy death animation
		m_pDeathAnim = new CAnimation(SVector2(0, 480),
			SVector2(180,190), 6);

		//set enemy death animation time
		m_pDeathAnim->SetAnimationTime(1.0f);

		// sets current animation to walk animation
		m_pCurrentAnim = m_pWalkAnim;

	// set tag
	m_pTag = "Enemy";

	// set health
	m_health = 20;

	// set gravity 
	m_gravity = true;

	// set speed
	m_speed = GConfig::s_MoveEnemySpeed;

	// set col type
	m_colType = ECollisionType::MOVE;
	
	// random movement x
	if (rand() % 2)
		m_movement.X = 1.0f;
	else
		m_movement.X = -1.0f;
#pragma endregion

}
#pragma endregion