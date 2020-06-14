#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <d3dx9.h>
#include "render.h"
#include <vector>
#include <iostream>  
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "SocketClient.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")

#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)            assert(_EXPR)
#endif


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"

struct INTVEC2
{
	INTVEC2(int xx, int yy) {
		this->x = xx;
		this->y = yy;
	}
	int x;
	int y;
};
 

class Visual
{
	bool gameOver;
	int i, j;
	bool isActivated;
	//120x120 8x8
	POINT mouse;
	LPDIRECT3DTEXTURE9 pawns[2][6];
	LPDIRECT3DTEXTURE9 BackGround_Border;
	LPDIRECT3DTEXTURE9 White_Square[2];
	LPDIRECT3DTEXTURE9 Black_Square[2];
	LPDIRECT3DTEXTURE9 Selected_Square;
	D3DXVECTOR2 pawnPos[2][16];
	WNDCLASSEX wc;
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	D3DPRESENT_PARAMETERS g_d3dpp;
	HWND hwnd; 
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void DrawTable(); 
private:
	std::vector<INTVEC2> Selected_Squares;
	bool IsAlrightToMoveToPos(int start_i, int start_j, int target_i, int target_j, bool changeValue = true);
	std::string WhatPieceItIs(int i, int j);
	int* IsPositionOcuppied(int posX, int posY);
	bool isLineOfSightClear(int start_i, int start_j, int target_i, int target_j,std::string piesa);
	std::vector<INTVEC2> pionToRegina;
	void RevertTable();
public:
	bool ChessWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	Visual();
	~Visual();
	void StartRendering();
	bool KingIsAttacked(int pos_x, int pos_y);
	LPDIRECT3DDEVICE9 GetDevice() { return g_pd3dDevice; }
	D3DPRESENT_PARAMETERS getd3dpp() { return g_d3dpp; }
	void LoadSelectedSquares();
	bool isCheck(int pos_x, int pos_y); 
	bool isCheckMate(int i, int j, int team_type);
};

extern Visual* Chess_Table;
extern Render* Rendering;
