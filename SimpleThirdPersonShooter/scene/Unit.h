#pragma once
#include "../graphics/graphics.h"

class Unit
{
protected:
	Model * m_model;
	glm::vec3 m_position;
	bool m_dead;

public:
	Unit();
	Unit(const glm::vec3 &position);
	virtual ~Unit() = 0 {}

	virtual void Initialize(Model * model, glm::vec3 position = glm::vec3()) { m_model = model; m_position = position; }
	virtual void CleanUp() {}

	void SetDead(bool die) { m_dead = die; }
	bool GetDead() { return m_dead; }

	virtual void Update(double deltaTime);
	virtual void Draw();
};