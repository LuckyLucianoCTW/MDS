class Render
{
	D3DPRESENT_PARAMETERS g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	LPD3DXSPRITE My_Pencil;
public:
	Render(LPDIRECT3DDEVICE9 device, D3DPRESENT_PARAMETERS g_pD3D);
	~Render();
	void Reset();
	void Begin(DWORD FLAGS) { My_Pencil->Begin(FLAGS); }
	void DrawImageAtPos(int pos_x, int pos_y, LPDIRECT3DTEXTURE9 tex, int size_x, int size_y);
	void End() { My_Pencil->End(); }
};