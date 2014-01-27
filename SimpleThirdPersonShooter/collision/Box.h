#pragma once
#include "../graphics/stdinc.h"

class Box
{
private:
	glm::vec3 m_center, m_extents;
public:
	Box();
	Box(glm::vec3 center, glm::vec3 extents);
};


struct BoundVolume
{
	Box m_parent;
	std::vector<Box> m_children;
};