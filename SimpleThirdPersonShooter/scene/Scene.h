#pragma once
#include "Unit.h"
#include "Camera.h"

class Scene
{
private:
	Renderer * m_renderer;
	std::vector<Unit*> m_units;
	Camera * m_camera;

public:
	Scene(Renderer * renderer = NULL);
	void SetRenderer(Renderer * renderer) { m_renderer = renderer; }
	Renderer* GetRenderer() { return m_renderer; }

	void Initialize();
	void Resize(float width, float height);
	void Update(double deltaTime);
	void Draw();
	void CleanUp();
	
	void SetCamera(Camera * camera) { m_camera = camera; }
	void AddUnit(Unit * unit) { m_units.push_back(unit); }
};