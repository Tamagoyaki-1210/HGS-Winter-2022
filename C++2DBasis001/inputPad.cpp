//=============================================================================
//
// inputPad.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// インクルードファイル
//---------------------------
#include "inputPad.h"

XINPUT_STATE CInputPad::m_JoyKeyState = {};				// ジョイパットのプレス情報
XINPUT_STATE CInputPad::m_JoyKeyStateTrigger = {};		// ジョイパットのトリガー情報
D3DXVECTOR3 CInputPad::m_JoyStickPos = {};				// ジョイスティックの傾き
int CInputPad::m_nTime = {};							// 振動持続時間
WORD CInputPad::m_nStrength = {};						// 振動の強さ (0 - 65535)

//=====================================
// デフォルトコンストラクタ
//=====================================
CInputPad::CInputPad() : m_pDevice(nullptr)
{
}

//=====================================
// デストラクタ
//=====================================
CInputPad::~CInputPad()
{

}

//=====================================
// 初期化
//=====================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// キーボードの初期化処理
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// 入力デバイス(キーボード)の生成
	if (FAILED(GetInput()->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// XInputのステートを設定（有効にする）
	XInputEnable(true);

	// メモリーのクリア
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// ジョイパッドの振動制御の０クリア
	ZeroMemory(&m_JoyMoter, sizeof(XINPUT_VIBRATION));

	// 振動制御用の初期化
	m_nStrength = 0;
	m_nTime = 0;

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CInputPad::Uninit()
{
	// XInputのステートを設定（無効にする）
	XInputEnable(false);

	// デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// 基本クラスの終了処理
	CInput::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CInputPad::Update()
{
	XINPUT_STATE JoyKeyState;		// ジョイパッド入力情報

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		m_JoyKeyStateTrigger.Gamepad.wButtons
			= ~m_JoyKeyState.Gamepad.wButtons
			& JoyKeyState.Gamepad.wButtons;	// トリガー情報を保存
		m_JoyKeyState = JoyKeyState;		// プレス処理
	}

	// ジョイパッドの振動
	m_JoyMoter.wLeftMotorSpeed = m_nStrength;
	m_JoyMoter.wRightMotorSpeed = m_nStrength;
	XInputSetState(0, &m_JoyMoter);

	if (m_nTime > 0)
	{
		m_nTime--;
	}
	else
	{
		m_nStrength = 0;
		m_nTime = 0;
	}
}

//=====================================
// ジョイパッドのプレス処理
//=====================================
bool CInputPad::GetJoypadPress(JOYKEY Key)
{
	return (m_JoyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=====================================
// ジョイパッドのトリガー処理
//=====================================
bool CInputPad::GetJoypadTrigger(JOYKEY Key)
{
	return (m_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=====================================
// ジョイパット（スティックプレス）処理
//=====================================
D3DXVECTOR3 CInputPad::GetJoypadStick(JOYKEY Key)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoyKeyState.Gamepad.sThumbLX / (float)0x7fff, -m_JoyKeyState.Gamepad.sThumbLY / (float)0x7fff, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoyKeyState.Gamepad.sThumbRX / (float)0x7fff, -m_JoyKeyState.Gamepad.sThumbRY / (float)0x7fff, 0.0f);
		break;
	}

	return m_JoyStickPos;
}

//=====================================
// ジョイパット（トリガーペダル）処理
//=====================================
int CInputPad::GetJoypadTriggerPedal(JOYKEY Key)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState.Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState.Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//=====================================
// コントローラーの振動制御
//=====================================
void CInputPad::JoypadVibration(int nTime, WORD nStrength)
{
	m_nTime = nTime;			// 振動持続時間
	m_nStrength = nStrength;	// 振動の強さ
}