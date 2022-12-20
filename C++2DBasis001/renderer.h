//=============================================================================
//
// renderer.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
// クラス宣言
//---------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }	// デバイスの取得処理

private:
	void DrawFPS();

	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト
	LPD3DXFONT m_pFont;
};

#endif // !_RENDERER_H_
