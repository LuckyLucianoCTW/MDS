class Render
{
	LPDIRECT3DVERTEXBUFFER9 g_pVB;  
	LPDIRECT3DINDEXBUFFER9  g_pIB;   
	D3DPRESENT_PARAMETERS g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	LPD3DXSPRITE My_Pencil;
public:
	Render(LPDIRECT3DDEVICE9 device, D3DPRESENT_PARAMETERS g_pD3D);
	~Render();
	void Reset();
	void Begin(DWORD FLAGS) { My_Pencil->Begin(FLAGS); }
	void D3DBox(float x, float y, float w, float h, D3DCOLOR color);
	void DrawImageAtPos(int pos_x, int pos_y, LPDIRECT3DTEXTURE9 tex, int size_x, int size_y, D3DCOLOR color = 0xFFFFFFFF);
	void End() { My_Pencil->End(); }
	void Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT* pSrcRect, CONST D3DXVECTOR3* pCenter, CONST D3DXVECTOR3* pPosition, D3DCOLOR Color) { My_Pencil->Draw(pTexture, pSrcRect, pCenter, pPosition, Color); }
};

struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};