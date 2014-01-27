#pragma once
#include "LiveUnit.h"

class Player : public LiveUnit
{
private:
	ModelAnimation m_animation;
	glm::vec3 m_offset;
	glm::mat4 m_offsetorient;

	int m_state; bool m_inTransition;
	/*bool m_running, m_shooting;
	bool m_inTransition;
	bool m_justShot;*/
	inline void ChangeState(int x);
public:
	Player();
	void Update(double deltaTime);
	void Draw();

	void Run(); void EndRun();
	void StrafeLeft(); void EndStrafeLeft();
	void StrafeRight(); void EndStrafeRight();
	void Shoot(); //void EndShoot();
};

