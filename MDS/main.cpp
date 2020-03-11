#include "main.h"
Visual* Chess_Table;
Render* Rendering;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
   	AllocConsole();
   	freopen("CON", "w", stdout);
   	SetConsoleTitle("[DEBUG] CHEATS.TW");
   	printf("Starting debugger...\n\n");
	Chess_Table = new Visual;
	Rendering = new Render(Chess_Table->GetDevice(),Chess_Table->getd3dpp());
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	Chess_Table->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Chess_Table->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
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