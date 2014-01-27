#include "Zombie.h"

enum ZombieStates{
	ZOMBIE_IDLE,
	ZOMBIE_WALK,
	ZOMBIE_FLICH,
	ZOMBIE_ATTACK1,
	ZOMBIE_ATTACK2,
	ZOMBIE_DEATH,
};

Zombie::Zombie() : m_state(ZOMBIE_IDLE)
{}

void Zombie::Update(double deltaTime)
{
	m_model->Advance(m_animation, deltaTime);
}

static glm::mat4 g_globaltransform = glm::scale(glm::mat4(), glm::vec3(4.0f));
void Zombie::Draw()
{
	m_model->SetTransform(glm::translate(glm::mat4(), m_position)  * m_orient * g_globaltransform);
	m_model->Animate(m_animation);
	m_model->Draw();
}