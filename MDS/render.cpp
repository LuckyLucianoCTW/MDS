#include "main.h"


Render::Render(LPDIRECT3DDEVICE9 device, D3DPRESENT_PARAMETERS g_pD3D)
{
	D3DXCreateSprite(device, &My_Pencil);
	this->g_pd3dDevice = device;
	this->g_pD3D = g_pD3D;
}

Render::~Render()
{
	My_Pencil->Release();
}


void Render::Reset()
{
	My_Pencil->OnResetDevice();
}

void Render::DrawImageAtPos(int pos_x, int pos_y, LPDIRECT3DTEXTURE9 tex, int size_x, int size_y)
{
	D3DXVECTOR2 trans = D3DXVECTOR2((float)pos_x, (float)pos_y);
	float rotation = 0.0f;
	D3DXMATRIX mat;
	static D3DSURFACE_DESC x;
	tex->GetLevelDesc(0, &x);
	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)x.Width, (float)x.Height);
	float scaleW = size_x / (float)x.Width;
	float scaleH = size_y / (float)x.Height;
	D3DXVECTOR2 scaling(scaleW, scaleH);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
	My_Pencil->SetTransform(&mat);
	My_Pencil->Draw(tex, NULL, NULL, &D3DXVECTOR3((float)pos_x, (float)pos_y,0), 0xFFFFFFFF);
}