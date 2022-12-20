//=============================================================================
//
// inputPad.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_PAD_H_
#define _INPUT_PAD_H_

//***********************************************
// ライブラリーファイルのリンク
//***********************************************
#pragma comment(lib,"xinput.lib")	//入力処理に使用(ジョイパッド)

//---------------------------
// インクルードファイル
//---------------------------
#include "input.h"
#include "XInput.h"

//---------------------------
// クラス宣言
//---------------------------
class CInputPad : public CInput
{
public:
	//キー種類(ジョイパッド)
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//十字ボタン上
		JOYKEY_DOWN,				//十字ボタン下
		JOYKEY_LEFT,				//十字ボタン左
		JOYKEY_RIGHT,				//十字ボタン右
		JOYKEY_START,				//スタートボタン
		JOYKEY_BACK,				//バックボタン
		JOYKEY_LEFT_THUMB,			//左スティック押込み
		JOYKEY_RIGHT_THUMB,			//右スティック押込み
		JOYKEY_LEFT_SHOULDER,		//L１ボタン
		JOYKEY_RIGHT_SHOULDER,		//R１ボタン
		JOYKEY_LEFT_TRIGGER,		//L２トリガー
		JOYKEY_RIGHT_TRIGGER,		//R２トリガー
		JOYKEY_A,					//Aボタン
		JOYKEY_B,					//Bボタン
		JOYKEY_X,					//Xボタン
		JOYKEY_Y,					//Yボタン
		JOYKEY_LEFT_STICK,			//左スティック
		JOYKEY_RIGHT_STICK,			//右スティック
		JOYKEY_MAX
	};

	CInputPad();
	~CInputPad() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	static bool GetJoypadPress(JOYKEY Key);					//ジョイパッドプレス処理
	static bool GetJoypadTrigger(JOYKEY Key);				//ジョイパッドトリガー処理
	static D3DXVECTOR3 GetJoypadStick(JOYKEY Key);			//ジョイパッドスティック処理
	static int GetJoypadTriggerPedal(JOYKEY Key);			//ジョイパッドトリガーペダル処理
	static void JoypadVibration(int nTime, WORD nStrength);	//ジョイパッド振動制御

private:

	static XINPUT_STATE m_JoyKeyState;						//ジョイパットのプレス情報
	static XINPUT_STATE m_JoyKeyStateTrigger;				//ジョイパットのトリガー情報
	static D3DXVECTOR3 m_JoyStickPos;						//ジョイスティックの傾き
	static int m_nTime;										//振動持続時間
	static WORD m_nStrength;								//振動の強さ (0 - 65535)
	
	XINPUT_VIBRATION m_JoyMoter;							//ジョイパッドのモーター
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !_INPUT_PAD_H_
