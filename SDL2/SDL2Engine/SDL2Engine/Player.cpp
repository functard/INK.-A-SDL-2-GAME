#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Config.h"
#include "Bullet.h"
#include "MenuScene.h"
#include "MainScene.h"
#include "Animation.h"
#include "Sound.h"
#include "Texture.h"
#include "Config.h"
#include "Time.h"
#include "MoveEnemy.h"
#include "Text.h"
#include "Game.h"

#pragma endregion

//Made by Ege, Iman

GPlayer* GPlayer::pPlayer = nullptr;

#pragma region public function
// initialize player
void GPlayer::Init()
{

	pPlayer = this;

#pragma region Ege, Iman

	//create take damage animation
	m_pTakaDamageAnim = new CAnimation(SVector2(GConfig::s_PlayerSrcRectWidth * 8, 0),
		SVector2(GConfig::s_PlayerSrcRectWidth, 165), 2);
	
	//set take damage animation time
	m_pTakaDamageAnim->SetAnimationTime(0.5f);

	// create idle animation
	m_pIdleAnim = new CAnimation(SVector2(0.0f, 0.0f),
		SVector2(GConfig::s_PlayerSrcRectWidth , 165), 1);

	//create shoot animation
	m_pShootAnim = new CAnimation(SVector2(0, 219),
		SVector2(GConfig::s_PlayerSrcRectWidth, 155), 5);

	//set shoot animation time
	m_pShootAnim->SetAnimationTime(0.5f);

	// create run animation
	m_pRunAnim = new CAnimation(SVector2(0,0),
		SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 8);

	//set run animation time
	m_pRunAnim->SetAnimationTime(0.5f);

	// set idle to current animation
	m_pCurrentAnim = m_pIdleAnim;

	// create shot sound
	m_pShot = new CSound("Audio/S_Shot.wav");

	//create fox attack sound
	m_pFoxAttack = new CSound("Audio/S_WolfAttack.wav");

	//create form changing sound
	m_Fox = new CSound("Audio/M_Fox.wav");
#pragma endregion



}
#pragma endregion

#pragma region public override function



// update every frame
void GPlayer::Update(float _deltaSeconds)
{
#pragma region Ege
	// if cooldown start
	if (m_startCooldown)
	{
		// set invulnerability to true;
		m_invulnerability = true;

		// decrease invulnerability timer
		m_invulnerabilityTimer -= _deltaSeconds;

		//set current animation to take damage
		m_pCurrentAnim = m_pTakaDamageAnim;

	}
	// when timer hits zero
	if (m_invulnerabilityTimer <= 0)
	{
		//reset timer
		m_invulnerabilityTimer = 2.0f;

		//stop cooldown
		m_startCooldown = false;

		//set invulnerability to false
		m_invulnerability = false;

	}


	//when shoot animation finishes
	if (m_pShootAnim->GetAnimationPercentage() == 100)
	{
		//can idle
		m_canIdle = true;

		//can run
		m_canRun = true;

		//reset animation percantage
		m_pShootAnim->ResetAnimationPercentage();
	}


	//when shoot animation finishes
	if (m_pTakaDamageAnim->GetAnimationPercentage() == 100)
	{
		//reset animation percantage
		m_pTakaDamageAnim->ResetAnimationPercentage();

		//can idle
		m_canIdle = true;

		//can run
		m_canRun = true;


	}


	//if hit by boss bullet and not invulnerable
	if (m_pColTarget && m_pColTarget->GetTag() == "BossBullet" && !m_invulnerability)
	{
		//remove bullet
		CTM->RemoveObject(m_pColTarget);

		//player take damage
		m_playerHealth -= 50;

		//start invulnerability timer
		m_startCooldown = true;

		//player invulnerable
		m_invulnerability = true;

		//set animation to take damage animation
		m_pCurrentAnim = m_pTakaDamageAnim;
	}



	// if collides when falling
	if (m_pColFallTarget)
	{
		// if collides with fire and not invulnerable
		if (m_pColFallTarget->GetTag() == "Fire" && !m_invulnerability)
		{
			

			//delays for 2 sec
			SDL_Delay(2000);

			//change scene
			ENGINE->ChangeScene(new GMenuScene());

		}

	}



	// if key space is pressed down and is human form jump
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && m_grounded && m_isHumanForm)
	{
		//player jump
		SetFallTime(-GConfig::s_PlayerJump);
		canJump = false;
	}

	// if key space is pressed down and is fox form jump
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && m_grounded && !m_isHumanForm)
	{
		//fox currently jumping
		isJumping = true;

		//set current animation to jump animation
		m_pCurrentAnim = m_pJumpAnim;

		//fox jump
		SetFallTime(-GConfig::s_PlayerJump);

		//set can jump to false
		canJump = false;
	}

	// fox form double jump
	else if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && !m_grounded && !canJump && !m_isHumanForm)
	{
		//fox currently jumping
		isJumping = true;

		//set current animation to jump animation
		m_pCurrentAnim = m_pJumpAnim;

		//fox double jump
		SetFallTime(-GConfig::s_PlayerJump);

		//set can jump to true
		canJump = true;
	}

	// if key r pressed spawn ice bullet
	if (CInput::GetKeyDown(SDL_SCANCODE_R) && m_isHumanForm)
	{
		//can idle
		m_canIdle = false;

		//can run
		m_canRun = false;

		//sets current animation to shoot animation
		m_pCurrentAnim = m_pShootAnim;

		// create ice bullet
		GBullet* pBullet = new GBullet(SVector2(), SVector2(8, 8), "Texture/Bullet/T_IceBullet.png");

		// spawn left (-1) or right (1) from player
		int spawnSide = 1;

		// if mirror set spawn side left
		if (m_mirror.X)
			spawnSide = -1;

		// set values
		pBullet->SetPosition(SVector2(m_position.X + 20 + spawnSide * m_rect.w, m_position.Y + m_rect.h * 0.25f));
		pBullet->SetColType(ECollisionType::WALL);
		pBullet->SetSpeed(GConfig::s_BulletSpeed);
		pBullet->SetMovement(SVector2(spawnSide, 0.0f));
		pBullet->SetTag("Bullet");

		// add bullet to content management
		CTM->AddPersistantObject(pBullet);

		// play shot sound
		m_pShot->Play();
	}

	// if key space spawn ice bullet
	if (CInput::GetKeyDown(SDL_SCANCODE_RETURN) && m_isHumanForm)
	{
		//can idle
		m_canIdle = false;

		//can run
		m_canRun = false;

		//set current animation to run
		m_pCurrentAnim = m_pShootAnim;


		// create bullet
		GBullet* pBullet = new GBullet(SVector2(), SVector2(8, 8), "Texture/Bullet/T_Bullet.png");

		// spawn left (-1) or right (1) from player
		int spawnSide = 1;

		// if mirror set spawn side left
		if (m_mirror.X)
			spawnSide = -1;

		// set values
		pBullet->SetPosition(SVector2(m_position.X + 20 + spawnSide * m_rect.w, m_position.Y + m_rect.h * 0.25f));
		pBullet->SetColType(ECollisionType::WALL);
		pBullet->SetSpeed(GConfig::s_BulletSpeed);
		pBullet->SetMovement(SVector2(spawnSide, 0.0f));
		pBullet->SetTag("Bullet");

		// add bullet to content management
		CTM->AddPersistantObject(pBullet);

		// play shot sound
		m_pShot->Play();

		// if current animation finishes
		if (m_pCurrentAnim->GetAnimationPercentage() == 100)
			m_canIdle = true;  // can idle
	}
#pragma endregion

	
#pragma region Iman, Ege

	//if f pressed and is human
	if ((CInput::GetKeyUp(SDL_SCANCODE_F) && m_isHumanForm))
	{
		//fox texture	
		m_pTexture = new CTexture("Texture/Player/T_Fox.png");

		//not human
		m_isHumanForm = false;

		//play form change sound
		m_Fox->Play();

		// create idle animation 
		m_pIdleAnim = new CAnimation(SVector2(0, 0),
			SVector2(210, GConfig::s_FoxSrcRectHeight), 1);
	
		// set idle animation time 
		m_pIdleAnim->SetAnimationTime(2.0f);
	
		// create walk animation
		m_pRunAnim = new CAnimation(SVector2(0,145),
			SVector2(GConfig::s_FoxSrcRectWidth, GConfig::s_FoxSrcRectHeight), 6);
	
		// set walk animation time
		m_pRunAnim->SetAnimationTime(0.5f);

		// create wolf attack animation
		m_pAttackAnim = new CAnimation(SVector2(0, 451),
			SVector2(230,170), 5);
		
		// set attack animation time
		m_pAttackAnim->SetAnimationTime(1.0f);

		// create wolf jump animation
		m_pJumpAnim = new CAnimation(SVector2(0, 310),
			SVector2(230, 137),10);

		// set jump animation time
		m_pJumpAnim->SetAnimationTime(0.5f);
	}
#pragma endregion

#pragma region Iman

	//if f pressed and is fox
	else if ((CInput::GetKeyUp(SDL_SCANCODE_F) && !m_isHumanForm))
	{
		//can run
		m_canRun = true;

		//set player texture
		m_pTexture = new CTexture("Texture/Player/T_Player.png");

		//is human
		m_isHumanForm = true;
	
		// create idle animation 
		m_pIdleAnim = new CAnimation(SVector2(0.0f, 0),
			SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 1);
	
	
		// create walk animation
		m_pRunAnim = new CAnimation(SVector2(0.0f, 0.0f),
			SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 8);
	
		// set walk animation time 
		m_pRunAnim->SetAnimationTime(0.5f);


		// create shoot animation
		m_pShootAnim = new CAnimation(SVector2(0,219),
			SVector2(GConfig::s_PlayerSrcRectWidth, 155), 5);

		//set shoot animation time
		m_pShootAnim->SetAnimationTime(0.5f);
		

		// create jump animation
		m_pJumpAnim = new CAnimation(SVector2(0.0f, GConfig::s_PlayerSrcRectHeight * 2),
			SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 8);
	}
#pragma endregion

#pragma region Ege


	//if fox form and enter pressed
	if (CInput::GetKeyDown(SDL_SCANCODE_RETURN) && !m_isHumanForm)
	{
		//can run
		m_canRun = false;

		//starts attack
		m_isAttacking = true;

		//if facing right
		if(m_mirror.X == 0)
			m_movement = 3.0f; // move right
		else
			m_movement = -3.0f; // move left

		//play fox attack sound
		m_pFoxAttack->Play();
	}

	// if jump animation finishes
	if (m_pJumpAnim && m_pJumpAnim->GetAnimationPercentage() == 100)
	{
			//is jumping
			isJumping = false;

			//reset animation percentage
			m_pJumpAnim->ResetAnimationPercentage();
	}


	// if key a is pressed and not attacking
	if (CInput::GetKey(SDL_SCANCODE_A) && m_isAttacking == false && m_canRun)
	{
		// set negative x movement and mirror horizontal
		m_movement.X = -10.0f;
		m_mirror.X = 1.0f;

		// set current animation to run 
		if(!isJumping )//c)
			m_pCurrentAnim = m_pRunAnim;

		//can idle
		m_canIdle = true;
		

	}
	

	// if key d is pressed and not attacking
	else if (CInput::GetKey(SDL_SCANCODE_D) && m_isAttacking == false && m_canRun)
	{
		// set positive x movement and mirror none
		
		
		//set movement
		m_movement.X = 10.0f;

		//set direction
		m_mirror.X = 0.0f;

		//if is jumping
		if (!isJumping)
		m_pCurrentAnim = m_pRunAnim;  // set current animation to run 
		

		//can idle
		m_canIdle = true;
		

	}


	// if fox attack
	else if (m_isAttacking)
	{
		// set attack animation
		m_pCurrentAnim = m_pAttackAnim;

		//if animation finishes
		if (m_pCurrentAnim->GetAnimationPercentage() == 100)
		{
			//reset animation percentage
			m_pCurrentAnim->ResetAnimationPercentage();

			//is attacking
			m_isAttacking = false;

			//can run
			m_canRun = true;
			
		}
		
	}
	// else no x movement
	else
	{
		m_movement.X = 0.0f;

		if (!isJumping && m_canIdle)
			{
				//reset shoot animation
				m_pShootAnim->ResetAnimationPercentage();

				// set current animation to idle
				m_pCurrentAnim = m_pIdleAnim;  

		}
	}


	// update animation
	m_pCurrentAnim->Update(_deltaSeconds);

	// set source from animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y,
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y
	);

	// if collision target valid and is enemy and not attacking destroy all and back to menu
	if (m_pColTarget && m_pColTarget->GetTag() == "Enemy"  && !m_isAttacking)
	{
		if (!m_invulnerability)
			m_playerHealth -= 50;

		//can idle
		m_canIdle = false;

		//can run
		m_canRun = false;

		//invulnerable
		m_invulnerability = true;

		//start invulnerability timer
		m_startCooldown = true;
	}

	// if collision target valid and is enemy and not attacking destroy all and back to menu
	if (m_pColTarget && m_pColTarget->GetTag() == "Boss" && !m_isAttacking)
	{
		// if not invulnerable
		if (!m_invulnerability)
			m_playerHealth -= 50; // player get damage

		//can idle
		m_canIdle = false;

		//can run
		m_canRun = false;

		//is invulnerable
		m_invulnerability = true;

		//start invulnerability timer
		m_startCooldown = true;
	}

		//if player dies
	if (m_playerHealth <= 0)
	{
		
		//delays for 2 sec
		SDL_Delay(2000);

		//change scene
		ENGINE->ChangeScene(new GMenuScene());



	}
		
	
	// if collision target valid and is enemy and is attacking 
	else if (m_pColTarget && (m_pColTarget->GetTag() == "Enemy" || m_pColTarget->GetTag() == "Boss") && m_isAttacking)
	{
		//damage enemy
		GMoveEnemy::Get()->m_health -= 20;
	}

	// update parent
	CMoveEntity::Update(_deltaSeconds);

	

	// parent camera to player
	RENDERER->SetCamera(m_position);
}
#pragma endregion


// render every frame
void GPlayer::Render()
{
	CMoveEntity::Render();
}
#pragma endregion

