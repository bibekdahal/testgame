#include "Player.h"

// These are animation states for palyer, arranged according to respective animation index in the model file
enum PlayerStates { 
	PLAYER_IDLE = 0, PLAYER_RUN, PLAYER_SHOOT, 
	PLAYER_AIM, 
	PLAYER_STRAFELEFT, PLAYER_STRAFERIGHT,
	PLAYER_AIMIDLE, PLAYER_IDLEAIM, 
	PLAYER_GUNRELOAD, 
	PLAYER_IDLERUN, PLAYER_RUNIDLE, 
	PLAYER_RUNSHOOTING, PLAYER_RUNAIMING,
	PLAYER_SLEFTSHOOTING, PLAYER_SRIGHTSHOOTING, 
	PLAYER_SLEFTAIMING, PLAYER_SRIGHTAIMING,
};

inline void Player::ChangeState(int x)
{
	m_state = x;
	switch (x)
	{
	// These animations are slighty tilted, so "offset-rotate" and "offset-position" them 
	case PLAYER_RUNSHOOTING:
	case PLAYER_RUNAIMING:
	case PLAYER_SLEFTSHOOTING:
	case PLAYER_SRIGHTSHOOTING:
	case PLAYER_SLEFTAIMING:
	case PLAYER_SRIGHTAIMING:
		m_offsetorient = glm::rotate(glm::mat4(), -1.5f, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(), 18.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		m_offset = glm::vec3(0.0f, 0.0f, -25.0f);
		break;
	// for other use identity offset transformation
	default:
		m_offsetorient = glm::mat4();	m_offset = glm::vec3();
	}

	m_model->Transition(m_animation, x, 0.0);

	// These "transition" animations are better animated quickly (see Update function)
	if (x == PLAYER_RUNIDLE || x == PLAYER_IDLERUN || x == PLAYER_AIMIDLE || x == PLAYER_IDLEAIM)
		m_inTransition = true;
	else
		m_inTransition = false;
}

Player::Player() : m_state(PLAYER_IDLE), m_inTransition(false)
{
	m_orient = glm::rotate(glm::mat4(), 175.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Player::Run()
{
	if (m_state == PLAYER_IDLE || m_state == PLAYER_AIM)
		ChangeState(PLAYER_IDLERUN);
}

void Player::EndRun()
{
	if (m_state == PLAYER_RUN || m_state == PLAYER_RUNSHOOTING || m_state == PLAYER_RUNAIMING)
		ChangeState(PLAYER_RUNIDLE);
}

void Player::StrafeLeft()
{
	if (m_state == PLAYER_RUN || m_state == PLAYER_RUNSHOOTING || m_state == PLAYER_RUNAIMING)
		ChangeState(PLAYER_STRAFELEFT);
	else if (m_state == PLAYER_IDLE || m_state == PLAYER_AIM)
		ChangeState(PLAYER_IDLERUN);
}
void Player::EndStrafeLeft()
{
	if (m_state == PLAYER_STRAFELEFT) ChangeState(PLAYER_RUN);
	else if (m_state == PLAYER_SLEFTSHOOTING) ChangeState(PLAYER_RUNSHOOTING);
	else if (m_state == PLAYER_SLEFTAIMING) ChangeState(PLAYER_RUNAIMING);
}
void Player::StrafeRight()
{
	if (m_state == PLAYER_RUN || m_state == PLAYER_RUNSHOOTING || m_state == PLAYER_RUNAIMING)
		ChangeState(PLAYER_STRAFERIGHT);
	else if (m_state == PLAYER_IDLE || m_state == PLAYER_AIM)
		ChangeState(PLAYER_IDLERUN);
}
void Player::EndStrafeRight()
{
	if (m_state == PLAYER_STRAFERIGHT) ChangeState(PLAYER_RUN);
	else if (m_state == PLAYER_SRIGHTSHOOTING) ChangeState(PLAYER_RUNSHOOTING);
	else if (m_state == PLAYER_SRIGHTAIMING) ChangeState(PLAYER_RUNAIMING);
}

void Player::Shoot()
{
	switch (m_state)
	{
	case PLAYER_IDLE:
	case PLAYER_AIM:
		ChangeState(PLAYER_SHOOT);
		break;
		break;
	case PLAYER_RUN:
	case PLAYER_RUNAIMING:
		ChangeState(PLAYER_RUNSHOOTING);
		break;
	case PLAYER_STRAFELEFT:
	case PLAYER_SLEFTAIMING:
		ChangeState(PLAYER_SLEFTSHOOTING);
		break;
	case PLAYER_STRAFERIGHT:
	case PLAYER_SRIGHTAIMING:
		ChangeState(PLAYER_SRIGHTSHOOTING);
		break;
	}
}

void Player::Update(double deltaTime)
{
	bool g_end = false;
	if (m_inTransition)
		m_model->Advance(m_animation, deltaTime * 3, &g_end);		// quickly end the transition animations
	else
		m_model->Advance(m_animation, deltaTime, &g_end);

	// if animation is at end, change to appropriate animation
	if (g_end)
	{	
		switch (m_state)
		{
		case PLAYER_RUNIDLE:
		case PLAYER_AIMIDLE:
			ChangeState(PLAYER_IDLE);			break; 
		case PLAYER_IDLERUN:
		case PLAYER_RUNAIMING:
			ChangeState(PLAYER_RUN);			break;
		case PLAYER_AIM:
			ChangeState(PLAYER_AIMIDLE);		break;
		case PLAYER_IDLEAIM:
		case PLAYER_SHOOT:
			ChangeState(PLAYER_AIM);			break;
		
		case PLAYER_RUNSHOOTING:
			ChangeState(PLAYER_RUNAIMING);		break;
		case PLAYER_SLEFTSHOOTING:
			ChangeState(PLAYER_SLEFTAIMING);	break;
		case PLAYER_SRIGHTSHOOTING:
			ChangeState(PLAYER_SRIGHTAIMING);	break;

		case PLAYER_SLEFTAIMING:
			ChangeState(PLAYER_STRAFELEFT);		break;
		case PLAYER_SRIGHTAIMING:
			ChangeState(PLAYER_STRAFERIGHT);	break;
		}
		g_end = false;
	}
}

void Player::Draw()
{
	// transform the model, animate and draw it
	m_model->SetTransform(glm::translate(glm::mat4(), m_position)  * m_orient * glm::translate(glm::mat4(), m_offset) * m_offsetorient);
	m_model->Animate(m_animation);
	m_model->Draw();	
}
