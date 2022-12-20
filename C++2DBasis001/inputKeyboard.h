//=============================================================================
//
// inputKeyboard.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//***********************************************
//ライブラリーファイルのリンク
//***********************************************
#pragma comment(lib,"dinput8.lib")	//入力処理に使用(キーボード)

//---------------------------
//インクルードファイル
//---------------------------
#include "input.h"

//---------------------------
// クラス宣言
//---------------------------
class CInputKeyboard : public CInput
{
public:
	static const int NumMaxKey = 256;	//キーの最大数(キーボード)

	CInputKeyboard();
	~CInputKeyboard() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	//キーボード
	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);

private:
	static BYTE m_aKeyState[NumMaxKey];			//キーボードのプレス情報
	static BYTE m_aKeyStateTrigger[NumMaxKey];	//キーボードのトリガー情報

	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !_INPUT_KEYBOARD_H_
