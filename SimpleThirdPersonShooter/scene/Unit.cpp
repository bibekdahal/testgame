#include "Unit.h"

Unit::Unit() : m_model(NULL), m_dead(false)
{}

Unit::Unit(const glm::vec3 &position) : m_model(NULL), m_position(position), m_dead(false)
{}

void Unit::Update(double deltaTime) {}

void Unit::Draw()
{
	if (m_model)
	{
		m_model->SetTransform(glm::translate(glm::mat4(), m_position));
		m_model->Draw();
	}
}