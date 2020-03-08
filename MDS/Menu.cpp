#include "main.h"


 

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Chess_Table->ChessWndProc(hWnd, msg, wParam, lParam))
		return true;
	return DefWindowProc(hWnd, msg, wParam, lParam);

}


bool Visual::ChessWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
 
	case WM_DESTROY:
		PostQuitMessage(0);
		return 1;
	}
	return 0;
}


bool Visual::CreateDeviceD3D(HWND hWnd)
{

	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;
 
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "rege.png", &pawns[0])))	exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "regina.png", &pawns[1]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "nebun.png", &pawns[2]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "cal.png", &pawns[3]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "tura.png", &pawns[4]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "pion.png", &pawns[5]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "background_border.png", &BackGround_Border))) exit(0); 
	return true; 
}


void Visual::CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}


Visual::Visual()
{
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Chess Window"), NULL };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, _T("Chess"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 1280, NULL, NULL, wc.hInstance, NULL);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		exit(0);
	}
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
}


Visual::~Visual()
{
	CleanupDeviceD3D();
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}


void Visual::StartRendering()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,0,0,0), 1.0f, 0);
	g_pd3dDevice->BeginScene();
	this->DrawTable();
	g_pd3dDevice->EndScene();
	HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	    g_pd3dDevice->Reset(&g_d3dpp);
}


void Visual::DrawTable()
{ 
	Rendering->Begin(D3DXSPRITE_ALPHABLEND);
	Rendering->DrawImageAtPos(0, 0, BackGround_Border, g_d3dpp.BackBufferWidth, g_d3dpp.BackBufferHeight);
	//Rendering->DrawImageAtPos(50, 50, pawns[0], 150, 150);
	Rendering->End();
}