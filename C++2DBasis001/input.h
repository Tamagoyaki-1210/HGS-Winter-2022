//=============================================================================
//
// input.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***********************************************
// ライブラリーファイルのリンク
//***********************************************
#pragma comment(lib,"dxguid.lib")	//固有ID（GUID）が登録されているライブラリ

//---------------------------
// インクルードファイル
//---------------------------
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//---------------------------
// クラス
//---------------------------
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;

	static LPDIRECTINPUT8 GetInput() { return m_pInput; }
private:

	static LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_H_
