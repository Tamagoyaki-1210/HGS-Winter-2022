//=============================================================================
//
// inputMouse.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

//---------------------------
// インクルードファイル
//---------------------------
#include "input.h"

//---------------------------
// クラス宣言
//---------------------------
class CInputMouse : public CInput
{
public:
	// キー種類(マウス)
	enum MOUSE
	{
		MOUSE_LEFT = 0,		// 左ボタン
		MOUSE_RIGHT,		// 右ボタン
		MOUSE_CENTER,		// 中央ボタン
		MOUSE_MAX
	};

	CInputMouse();
	~CInputMouse() override;
																				
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	static POINT GetPoint() { return m_Point; }
	static DIMOUSESTATE* GetMouseState() { return &m_CurrentMouseState; }

	static bool OnMouseDown(MOUSE button_type);	// クリックした瞬間の判定
	static bool OnMouseUp(MOUSE button_type);	// クリックをやめた瞬間の判定

private:
	static POINT m_Point;						// ポイントの情報
	static DIMOUSESTATE m_CurrentMouseState;	// 現在のマウス状態
	static DIMOUSESTATE m_PrevMouseState;		// 前回のマウス状態

	HWND m_hWnd;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !INPUT_MOUSE_H