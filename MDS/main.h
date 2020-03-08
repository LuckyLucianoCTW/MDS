#include <Windows.h>
#include <d3d9.h>
#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)            assert(_EXPR)
#endif


class Visual
{
	
	WNDCLASSEX wc;
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	D3DPRESENT_PARAMETERS g_d3dpp;
	HWND hwnd;
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
public:
	bool ChessWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	Visual();
	~Visual();
	void StartRendering();
	LPDIRECT3DDEVICE9 GetDevice() { return g_pd3dDevice; }
	D3DPRESENT_PARAMETERS getd3dpp() { return g_d3dpp; }
};

extern Visual* render;