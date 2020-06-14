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

void Render::DrawImageAtPos(int pos_x, int pos_y, LPDIRECT3DTEXTURE9 tex, int size_x, int size_y, D3DCOLOR color)
{
	D3DXVECTOR2 trans = D3DXVECTOR2(pos_x, pos_y);
	float rotation = 0.0f;
	D3DXMATRIX mat;
	static D3DSURFACE_DESC x;
	tex->GetLevelDesc(NULL, &x);
	D3DXVECTOR2 spriteCentre = D3DXVECTOR2(size_x /2, size_y / 2);
	float scaleW =  (float)size_x / (float)x.Width;
	float scaleH =  (float)size_y / (float)x.Height;
	D3DXVECTOR2 scaling(scaleW, scaleH);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, NULL, &trans);
	My_Pencil->SetTransform(&mat);
	My_Pencil->Draw(tex, NULL, NULL, NULL, color);
}

void Render::D3DBox(float x, float y, float w, float h, D3DCOLOR color)
{
	vertex V[4];

	V[0].color = V[1].color = V[2].color = V[3].color = color;

	V[0].z = V[1].z = V[2].z = V[3].z = 0;
	V[0].rhw = V[1].rhw = V[2].rhw = V[3].rhw = 0;

	V[0].x = x;
	V[0].y = y;
	V[1].x = x + w;
	V[1].y = y;
	V[2].x = x + w;
	V[2].y = y + h;
	V[3].x = x;
	V[3].y = y + h;

	unsigned short indexes[] = { 0, 1, 3, 1, 2, 3 };

	g_pd3dDevice->CreateVertexBuffer(4 * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
	g_pd3dDevice->CreateIndexBuffer(2 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, sizeof(V), (void**)& pVertices, 0);
	memcpy(pVertices, V, sizeof(V));
	g_pVB->Unlock();

	VOID* pIndex;
	g_pIB->Lock(0, sizeof(indexes), (void**)& pIndex, 0);
	memcpy(pIndex, indexes, sizeof(indexes));
	g_pIB->Unlock();

	g_pd3dDevice->SetTexture(0, NULL);
	g_pd3dDevice->SetPixelShader(NULL);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	g_pd3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pd3dDevice->SetIndices(g_pIB);

	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	g_pVB->Release();
	g_pIB->Release();
}