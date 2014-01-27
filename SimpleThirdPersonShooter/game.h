
Window g_window;
Renderer g_renderer(&g_window);

int g_width = 900;
int g_height = 650;


Scene g_scene(&g_renderer);
Camera g_camera;
Model g_humanmodel(&g_renderer), g_zombiemodel(&g_renderer);
Player g_player;
Zombie g_zombie;

Model g_testmodel(&g_renderer);
Ground g_ground;

void Initialize()
{
	g_renderer.Initialize();
	g_scene.Initialize();
	g_scene.SetCamera(&g_camera);

	g_humanmodel.LoadModel("human.mdl");
	g_player.Initialize(&g_humanmodel, glm::vec3(-20.0f, -150.0f, -160.0f));

	g_zombiemodel.LoadModel("zombie.mdl");
	g_zombie.Initialize(&g_zombiemodel, glm::vec3(50.0f, -150.0f, -400.0f));

	Mesh mesh(&g_renderer);
	Mesh::CreateBox(&mesh, glm::vec3(10000.0f, 0.5f, 10000.0f));
	g_testmodel.AddMesh(mesh);
	g_testmodel.SetTexture(0, "diffuse_1.jpg");
	g_ground.Initialize(&g_testmodel, glm::vec3(0.0f, -150.0f - 0.25f, -500.0f));

	g_scene.AddUnit(&g_player);
	g_scene.AddUnit(&g_zombie);
	g_scene.AddUnit(&g_ground);
}

void CleanUp()
{
	g_humanmodel.CleanUp();
	g_zombiemodel.CleanUp();
	g_testmodel.CleanUp();

	g_player.CleanUp();
	g_zombie.CleanUp();
	g_ground.CleanUp();

	g_renderer.CleanUp();
	g_scene.CleanUp();
}

bool g_justDown = false;
void Update(double totalTime, double deltaTime)
{
	if (g_window.GetMouseState(MOUSE_LEFT))
	{
		if (!g_justDown)
		{
			g_justDown = true;
			g_player.Shoot();
		}
	}
	else
		g_justDown = false;

	if (g_window.CheckKey('a')) g_player.StrafeLeft();
	else g_player.EndStrafeLeft();

	if (g_window.CheckKey('d')) g_player.StrafeRight();
	else g_player.EndStrafeRight();

	if (g_window.CheckKey('w')) g_player.Run();
	else g_player.EndRun();

	g_scene.Update(deltaTime);
}

void Render()
{
	g_scene.Draw();
}

void Resize(int width, int height)
{
	g_width = width; g_height = height;
	g_scene.Resize(static_cast<float>(width), static_cast<float>(height));
}