#include "main.h"



int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Visual* render = new Visual;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		render->StartRendering();
	}
 
}