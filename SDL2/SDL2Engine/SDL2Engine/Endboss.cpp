#pragma region project include
#include "EndBoss.h"
#include "Config.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Animation.h"
#include "Input.h"
#include "Bullet.h"
#include "Sound.h"
#include "Text.h"
#include "Font.h"
#include "Game.h"
#include "MenuScene.h"

#pragma endregion

// Made by Iman, Ege
#pragma region public override function
// update every frame
void GMoveBoss::Update(float _deltaSeconds)
{
#pragma region Iman, Ege

	
		//if not moveable and is not colliding with bullet
	if (!m_moveable && m_pColTarget && m_pColTarget->GetTag() != "Bullet")
	{
		//set boss movement
		m_movement.X *= -1;
		m_position.X += m_movement.X;
	}

	//if looking right
	if (m_movement.X > 0)
	{
		//change direction to right
		m_mirror = 1.0f;
	}
	//if looking left
	else if (m_movement.X < 0)
	{
		//change direction to left
		m_mirror = 0;
	}

	//if boss is in range attack range and boss can shoot
	if ((!(GetPosition().X < GPlayer::Get()->GetPosition().X + 250 || GetPosition().X < GPlayer::Get()->GetPosition().X - 250) && 
	GetPosition().X < GPlayer::Get()->GetPosition().X + 700 || GetPosition().X < GPlayer::Get()->GetPosition().X - 700) && m_canShoot)
	{
		//can shoot
		m_canShoot = false;

		//set and start timer
		m_startTimer = true;
		m_shootTimer = 2.0f;
		

		// create bullet
		GBullet* pBullet = new GBullet(SVector2(), SVector2(20, 20), "Texture/Bullet/T_Bullet.png");

		// spawn left (-1) or right (1) from player
		int spawnSide = -1;

		// if mirror set spawn side left
		if (m_mirror.X)
			spawnSide = 1;
		

		// set values
		pBullet->SetPosition(SVector2(m_position.X + 20 + spawnSide * m_rect.w, m_position.Y + m_rect.h  * 0.25 + 70 ));
		pBullet->SetColType(ECollisionType::MOVE);
		pBullet->SetSpeed(GConfig::s_BulletSpeed);
		pBullet->SetMovement(SVector2(spawnSide, 0.0f));
		pBullet->SetTag("BossBullet");

		// add bullet to content management
		CTM->AddPersistantObject(pBullet);

		
	}

	// if shoot timer is 0
	if (m_shootTimer <= 0)
	{
		//can shoot
		m_canShoot = true;
	}
	else
	{
		//start timer
		m_shootTimer -= _deltaSeconds;
	}

	
	
	
	//if collides with bullet
	if (m_pColTarget &&m_pColTarget->GetTag() == "Bullet")
		m_health -= 30; // damage boss

	//if boos is dead
	if (m_health <= 0)

	{
			//set current animation to death animation
			m_pCurrentAnim = m_pDeathAnim;

			//create you win text
			CText* pText = new CText("YOU WIN", GAME->m_PArial, SRect(150, 150, 580, 100), SColor(0, 255, 0));

			//set as ui element
			pText->SetInWorld(false);

			// ad to CTM as ui object
			CTM->AddUIObject(pText);

			//delays for 2 sec
			SDL_Delay(2000);
			ENGINE->ChangeScene(new GMenuScene());


			//if death animation finishes
		if (m_pDeathAnim->GetAnimationPercentage() == 100)
		{
			//Delete boss
			CTM->RemoveObject(this);

			
			
		}

	}

	// if player is near
	if (GetPosition().X < GPlayer::Get()->GetPosition().X + 250 || GetPosition().X < GPlayer::Get()->GetPosition().X - 250)
	{
		//enemy attack
		m_pCurrentAnim = m_pAttackAnim;
	}

	//if current animation is not death animation
	else if (m_pCurrentAnim != m_pDeathAnim)
	{
		//set current animation to run animation
		m_pCurrentAnim = m_pWalkAnim;
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
void GMoveBoss::Render()
{
	// render parent
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize move enemy
void GMoveBoss::Init()
{
#pragma region Iman, Ege

	// set boss walk animation
	m_pWalkAnim = new CAnimation(SVector2(0, 0),
		SVector2(173, 218), 9);

	//set boss walk animation time
	m_pWalkAnim->SetAnimationTime(1.0f);


	// set boss attack animation
	m_pAttackAnim = new CAnimation(SVector2(0, 260),
		SVector2(178, 210), 5);

	//set boss attack animation time
	m_pAttackAnim->SetAnimationTime(1.0f);

	// set boss death animation
	m_pDeathAnim = new CAnimation(SVector2(0, 480),
		SVector2(180, 190), 6);

	//set boss death animation time
	m_pDeathAnim->SetAnimationTime(1.0f);

	// set current animation to run animation
	m_pCurrentAnim = m_pWalkAnim;

	// set tag
	m_pTag = "Boss";

	// set gravity and speed
	m_gravity = true;
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