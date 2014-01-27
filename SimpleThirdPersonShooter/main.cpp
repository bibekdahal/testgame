#include "graphics/graphics.h"
#include "scene/Scene.h"
#include "scene/Player.h"
#include "scene/Zombie.h"
#include "scene/Ground.h"
#include "game.h"

int main(int argc, char* argv[])
{
	int ret;
	ret = g_window.InitWindow("Simple Third Person Shooter", g_width, g_height, argv, SW_SHOWMAXIMIZED);
	if (ret == -1)
	{
		MessageBox(0, "Window Initialization - Failed", "Error", MB_OK);
		return 0;
	}
	
	g_window.SetupOpengl();	
	Initialize();

	g_window.RenderFunc(Render);
	g_window.UpdateFunc(Update);
	g_window.ResizeFunc(Resize);
	Resize(g_width, g_height);
	
	ret = g_window.MainLoop();

	CleanUp();

	return (int)ret;
}
