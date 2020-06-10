#include "main.h"

int offset = 60;
int imageSize = 50;

using namespace std;

 
const int jVecinPion[] = { 1,2,1,1 };
const int iVecinPion[] = { 0,0,1,-1 };
const int iVecinCal[] = { 1,1,-1,-1,2,2,-2,-2 };
const int jVecinCal[] = { 2,-2,2,-2,1,-1,1,-1 };
const int iVecinNebun[] = { 1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8 };
const int jVecinNebun[] = { 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,-1,-2,-3,-4,-5,-6,-7,-8 };
const int iVecinRegina[] = { 1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8 };
const int jVecinRegina[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,-1,-2,-3,-4,-5,-6,-7,-8 };
const int iVecinRege[] = { 1,1,1,-1,-1,-1,0,0 };
const int jVecinRege[] = { 1,0,-1,1,0,-1,1,-1 };
const int iVecinTura[] = { 1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const int jVecinTura[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8 };



LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Chess_Table->ChessWndProc(hWnd, msg, wParam, lParam))
		return true;
	return DefWindowProc(hWnd, msg, wParam, lParam);

}

float dist2d(float x, float y, float a, float b)
{
	return sqrt(pow((x - a), 2) + pow((y - b), 2));
}



std::string Visual::WhatPieceItIs(int j)
{

	int a = j;
	if (a > 4)
		a = 7 - a;
	switch (a)
	{
	case 0:
		return "tura";
	case 1:
		return "cal";
	case 2:
		return "nebun";
	case 3:
		return "rege";
	case 4:
		return "regina";
	default:
		return "pion";
	}
		

}
int* Visual::IsPositionOcuppied(int posX, int posY)
{ 
	int v[3];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 16; j++) {
			//	printf("IsOcuppied = %f %f | %f %f\n", pawnPos[i][j].x, pawnPos[i][j].y, posX, posY);
			if (pawnPos[i][j].x == posX && pawnPos[i][j].y == posY)
			{
				v[0] = 1;
				v[1] = i;
				v[2] = j;
				return v;
			}
		}
	}
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	return v;
}
bool Visual::isLineOfSightClear(int start_i, int start_j, int target_i, int target_j, std::string piesa)
{  
	if (piesa == "tura")
	{ 
		if (start_i == target_i)
		{ 
			if (start_j < target_j) {
				for (int j = start_j + offset; j < target_j; j += offset)
				{ 
					if (IsPositionOcuppied(start_i, j)[0])
						return false;
				}
				return true;
			}
			else
			{
				for (int j = target_j + offset; j < start_j; j += offset)
				{ 
					if (IsPositionOcuppied(start_i, j)[0])
						return false;
				}
				return true;
			}
			
		}
		else if (start_j == target_j)
		{ 
			if (start_i < target_i) {
				for (float j = start_i + offset; j < target_i; j += offset)
				{
					if (IsPositionOcuppied(j, start_j)[0])
						return false;
				}
				return true;
			}
			else
			{
				for (int j = target_i + offset; j < start_i; j += offset)
				{ 
					if (IsPositionOcuppied(j, start_j)[0])
						return false;
				}
				return true;
			}
		}
		else
			return false;
	}
	else if (piesa == "nebun")
	{ 
		if (abs(start_i - target_i) == abs(start_j - target_j))
		{
			if (start_i > target_i && start_j > target_j)
			{
				for (int i = target_i + offset,  j = target_j + offset; i < start_i && j < start_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i < target_i && start_j > target_j)
			{
				for (int i = start_i + offset, j = target_j + offset; i < target_i && j < start_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i < target_i && start_j < target_j)
			{
				for (int i = start_i + offset, j = start_j + offset; i < target_i && j < target_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i > target_i && start_j < target_j)
			{
				int i;
				int j;
				for (int i = target_i + offset, j = start_j + offset; i < start_i && j < target_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
		}
		else 
		{
			return false;
		}
	}
	else if (piesa == "regina")
	{
		if (abs(start_i - target_i) == abs(start_j - target_j))
		{
			if (start_i > target_i && start_j > target_j)
			{
				for (int i = target_i + offset, j = target_j + offset; i < start_i && j < start_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i < target_i && start_j > target_j)
			{
				for (int i = start_i + offset, j = target_j + offset; i < target_i && j < start_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i < target_i && start_j < target_j)
			{
				for (int i = start_i + offset, j = start_j + offset; i < target_i && j < target_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
			else if (start_i > target_i && start_j < target_j)
			{
				int i;
				int j;
				for (int i = target_i + offset, j = start_j + offset; i < start_i && j < target_j; i += offset, j += offset)
				{
					if (IsPositionOcuppied(i, j)[0])
						return false;
				}
				return true;
			}
		}
		if (start_i == target_i)
		{
			if (start_j < target_j) {
				for (int j = start_j + offset; j < target_j; j += offset)
				{
					if (IsPositionOcuppied(start_i, j)[0])
						return false;
				}
				return true;
			}
			else
			{
				for (int j = target_j + offset; j < start_j; j += offset)
				{
					if (IsPositionOcuppied(start_i, j)[0])
						return false;
				}
				return true;
			}

		}
		else if (start_j == target_j)
		{
			if (start_i < target_i) {
				for (float j = start_i + offset; j < target_i; j += offset)
				{
					if (IsPositionOcuppied(j, start_j)[0])
						return false;
				}
				return true;
			}
			else
			{
				for (int j = target_i + offset; j < start_i; j += offset)
				{
					if (IsPositionOcuppied(j, start_j)[0])
						return false;
				}
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if (piesa == "cal")
	{
	int size_vec = sizeof(jVecinCal) / sizeof(jVecinCal[0]);

	int target_pos_x = target_i / offset;
	int target_pos_y = target_j / offset;
	int start_pos_x = start_i / offset;
	int start_pos_y = start_j / offset;
	for (int i = 0; i < size_vec; i++) {
		printf("First = %d %d | Second = %d %d\n", start_pos_x + iVecinCal[i], start_pos_y + jVecinCal[i], target_i, target_j);
		if (start_pos_x + iVecinCal[i] == target_pos_x && start_pos_y + jVecinCal[i] == target_pos_y)
		{
			printf("Equals\n");
			int* vector_teams = IsPositionOcuppied(target_i, target_j);
			if (vector_teams[0] == 0)
				return true;
			else
			{
				if (vector_teams[1] != 1)
					return true;
				else
					return false;
			}
		}
	}
	return false;
	}
	else if (piesa == "pion")
	{
	int target_pos_x = target_i / offset;
	int target_pos_y = target_j / offset;
	int start_pos_x = start_i / offset;
	int start_pos_y = start_j / offset;
	int* getTargetTeam = IsPositionOcuppied(target_i, target_j);
	int* getMyTeam = IsPositionOcuppied(start_i, start_j);

	int size = sizeof(iVecinPion) / sizeof(iVecinPion[0]);
	printf("Start pos = %d %d || target = %d %d \n", start_pos_x, start_pos_y, target_pos_x, target_pos_y);
	if (start_pos_y == 6 && getMyTeam[1] == 1) 
	{ 
		for (int i = 0; i < size; i++)
		{
			printf("Inside for = %d %d | target = %d %d\n", start_pos_x + iVecinPion[i], start_pos_y + jVecinPion[i], target_pos_x, target_pos_y);
			if (start_pos_x - iVecinPion[i] == target_pos_x && start_pos_y - jVecinPion[i] == target_pos_y)
			{
				printf("Equals\n");
				if (getTargetTeam[0] == 0 && (i != 2 && i != 3))
				{
					return true;
				}
				else if (getTargetTeam[1] == 0 && getTargetTeam[0] == true)
				{
					if (i == 2 || i == 3)
						return true;
					else
						return false;
				}
				
			}
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 1)
				continue;
			if (start_pos_x - iVecinPion[i] == target_pos_x && start_pos_y - jVecinPion[i] == target_pos_y)
			{
				if (getTargetTeam[0] == 0 && (i != 2 && i != 3))
				{
					return true;
				}
				else if (getTargetTeam[1] == 0 && getTargetTeam[0] == true)
				{
					if (i == 2 || i == 3)
						return true;
					else
						return false;
				}

			}
		}
	}
	return false;
	}
	else if (piesa == "rege")
	{
	int target_pos_x = target_i / offset;
	int target_pos_y = target_j / offset;
	int start_pos_x = start_i / offset;
	int start_pos_y = start_j / offset;
	int size = sizeof(iVecinRege) / sizeof(iVecinRege[0]);
	for (int i = 0; i < size; i++)
	{
		if (start_pos_x + iVecinRege[i] == target_pos_x && start_pos_y + jVecinRege[i] == target_pos_y)
		{
			int* vector_teams = IsPositionOcuppied(target_i, target_j);
			if (vector_teams[0] == 0)
				return true;
			else
			{
				if (vector_teams[1] != 1)
					return true;
				else
					return false;
			}
			//if is not check

		}
	}
	return false;
	}
	return true;
}



bool Visual::IsAlrightToMoveToPos(int start_i,int start_j,int target_i, int target_j)
{  
	
	int posX = offset * target_i;
	int posY = offset * target_j; 
	string piece = WhatPieceItIs(start_j);
	bool lineofsight = isLineOfSightClear((int)pawnPos[start_i][start_j].x, (int)pawnPos[start_i][start_j].y, posX, posY, WhatPieceItIs(start_j));
	if (!lineofsight)
		return false; 
	int* vector_Pos;  
	if ((vector_Pos = IsPositionOcuppied(posX, posY))[0])
	{

		if (vector_Pos[1] == start_i)
			return false;
		printf("Target : %d %d ||| id = %d %d |vector_pos = %d %d | start_i_j = %d %d \n", posX, posY, target_i, target_j, vector_Pos[1], vector_Pos[2],start_i,start_j); 
		if ((!strcmp(piece.c_str(), "regina") || !strcmp(piece.c_str(), "nebun") || !strcmp(piece.c_str(), "tura") || !strcmp(piece.c_str(), "cal") || !strcmp(piece.c_str(), "pion") || !strcmp(piece.c_str(), "rege")))
		{
			printf("Am luat");
			pawnPos[vector_Pos[1]][vector_Pos[2]].x = -1;
			pawnPos[vector_Pos[1]][vector_Pos[2]].y = -1;
			return true;
		}  
	}  

	return true;
	//1,0 -> rege
	//1,1 -> regina
	//1,2 -> nebunu
	//1,3 -> cal
	//1,4 -> tura
	//1,5 -> pion
}

bool Visual::ChessWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case 0x201:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		int centerX = g_d3dpp.BackBufferWidth / 5;
		int centerY = g_d3dpp.BackBufferHeight / 5;
		if (!isActivated)
		{ 
		 
			if ((mouse.x >= centerX && mouse.y >= centerY) && (mouse.x <= centerX + (8 * offset)) && mouse.y <=centerY + (8 * offset))
			{ 
				i = -1; //my_i_pos
				j = -1; //my_j_pos
				float distX = 9999.0f;
				float distY = 9999.0f; 
				for (int k = 0; k < 16; k++)
				{
					float dist_x = dist2d(mouse.x, mouse.y , (offset / 2 + centerX + pawnPos[1][k].x), (offset / 2 + centerY + pawnPos[1][k].y));  
					if (distX > dist_x && dist_x < 30.0f)
					{ 
						i = 1;
						j = k;
						distX = dist_x;
					}
				} 
				if(i != -1 && j != -1)
				isActivated = true;
			}
		}
		else
		{
			if ((mouse.x >= centerX && mouse.y >= centerY) && (mouse.x <= centerX + (8 * offset)) && mouse.y <= centerY + (8 * offset))
			{
				int i_x; //target
				int j_y; //target
				float distX = 9999.0f;
				float distY = 9999.0f; 
				for (int k = 0; k < 8; k++)
				{
					float dist_x = abs(mouse.x - (offset / 2 + centerX + (k * offset)));
					float dist_y = abs(mouse.y - (offset / 2 + centerY + (k * offset)));
					if (distX > dist_x)
					{
						i_x = k;
						distX = dist_x;
					}
					if (distY > dist_y)
					{
						j_y = k;
						distY = dist_y;
					}
				}
				//verificarea
				if (IsAlrightToMoveToPos(i, j, i_x, j_y))
				{
					pawnPos[i][j].x = offset * i_x;
					pawnPos[i][j].y = offset * j_y;
					isActivated = false;
				}
				else
					isActivated = false;
			}
		}
		break;
	}
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
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//rege.png", &pawns[1][0])))	exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//regina.png", &pawns[1][1]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//nebun.png", &pawns[1][2]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//cal.png", &pawns[1][3]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//tura.png", &pawns[1][4]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "whites//pion.png", &pawns[1][5]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//rege.png", &pawns[0][0])))	exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//regina.png", &pawns[0][1]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//nebun.png", &pawns[0][2]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//cal.png", &pawns[0][3]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//tura.png", &pawns[0][4]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "blacks//pion.png", &pawns[0][5]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "background_border.png", &BackGround_Border))) exit(0); 
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "selected_white_square.png", &White_Square[0]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "white_square.png", &White_Square[1]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "selected_black_square.png", &Black_Square[0]))) exit(0);
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, "black_square.png", &Black_Square[1]))) exit(0);
	return true; 
}


void Visual::CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}


Visual::Visual()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 8; j++) {
			pawnPos[0][(8 * i) + j].x = (float)j * offset;
			pawnPos[0][(8 * i) + j].y = i * offset;
		}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 8; j++) 
	    {
				pawnPos[1][(8 * i) + j].x = (float)j * offset;
				pawnPos[1][(8 * i) + j].y = (offset * (7 - i));
		}
 
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Chess Window"), NULL };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, _T("Chess"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 800, NULL, NULL, wc.hInstance, NULL);

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
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,255,0,0), 1.0f, 0);
 
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
	int centerX = g_d3dpp.BackBufferWidth / 5;
	int centerY = g_d3dpp.BackBufferHeight / 5;
	for(int i = 0 ; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Rendering->DrawImageAtPos(centerX + (offset * i), centerY + (offset * j), (i + j) % 2 ? White_Square[0] : Black_Square[0], offset, offset);
	 
	int image_center = ((offset - imageSize) / 2);
	centerY += image_center;
	centerX += image_center;
 
	for (int j = 0; j < 16; j++)
	{
		 
	 
		if (j < 8) {
			int a = j;
			if (a > 4)
				a = 7 - a;
			switch (a)
			{
			case 0:
				if (pawnPos[0][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x , (int)pawnPos[0][j].y + centerY , pawns[0][4], imageSize, imageSize);
				break;
			case 1:
				if (pawnPos[0][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x , (int)pawnPos[0][j].y + centerY , pawns[0][3], imageSize, imageSize);
				break;
			case 2:
				if (pawnPos[0][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x , (int)pawnPos[0][j].y + centerY , pawns[0][2], imageSize, imageSize);
				break;
			case 3:
				if (pawnPos[0][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x , (int)pawnPos[0][j].y + centerY , pawns[0][1], imageSize, imageSize);
				break;
			case 4:
				if (pawnPos[0][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x , centerY + (int)pawnPos[0][j].y , pawns[0][0], imageSize, imageSize);
				break;
			}
		}
		else {
			if (pawnPos[0][j].x == -1)
				continue;
			Rendering->DrawImageAtPos(centerX + pawnPos[0][j].x, centerY + (int)pawnPos[0][j].y, pawns[0][5], imageSize, imageSize);
		}
		
	}
	for (int j = 0; j < 16; j++) 
	{
		
		if (j < 8) 
		{
			int a = j;
			if (a > 4)
				a = 7 - a;
			switch (a)
			{
			case 0:
				if (pawnPos[1][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX   + pawnPos[1][j].x , centerY + (int)pawnPos[1][j].y , pawns[1][4], imageSize, imageSize);
				break;
			case 1:
				if (pawnPos[1][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX   + pawnPos[1][j].x , centerY + (int)pawnPos[1][j].y , pawns[1][3], imageSize, imageSize);
				break;
			case 2:
				if (pawnPos[1][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX  + pawnPos[1][j].x , centerY + (int)pawnPos[1][j].y , pawns[1][2], imageSize, imageSize);
				break;
			case 3:
				if (pawnPos[1][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX   + pawnPos[1][j].x , centerY + (int)pawnPos[1][j].y , pawns[1][0], imageSize, imageSize);
				break;
			case 4:
				if (pawnPos[1][j].x == -1)
					continue;
				Rendering->DrawImageAtPos(centerX  + pawnPos[1][j].x , centerY+(int)pawnPos[1][j].y , pawns[1][1], imageSize, imageSize);
				break;
			}
		}
		else {
			if (pawnPos[1][j].x == -1)
				continue;
			Rendering->DrawImageAtPos(centerX + pawnPos[1][j].x, centerY + (int)pawnPos[1][j].y, pawns[1][5], imageSize, imageSize);
		}
	} 
 	Rendering->End();
}