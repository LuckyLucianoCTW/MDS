#include "main.h"
Visual* Chess_Table;
Render* Rendering;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Chess_Table = new Visual;
	Rendering = new Render(Chess_Table->GetDevice(),Chess_Table->getd3dpp());
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		Chess_Table->StartRendering();
	}
   
	delete Chess_Table;
	 
	return 0;
}