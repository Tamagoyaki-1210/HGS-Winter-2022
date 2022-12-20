//=============================================================================
//
// inputMouse.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// インクルードファイル
//---------------------------
#include "inputMouse.h"
#include "debugProc.h"

POINT CInputMouse::m_Point = {};
DIMOUSESTATE CInputMouse::m_CurrentMouseState = {};
DIMOUSESTATE CInputMouse::m_PrevMouseState = {};

//=====================================
// デフォルトコンストラクタ
//=====================================
CInputMouse::CInputMouse() : m_pDevice(nullptr)
{
	
}

//=====================================
// デストラクタ
//=====================================
CInputMouse::~CInputMouse()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//基本クラスの初期化処理
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return -1;
	}

	// 入力デバイス(キーボード)の生成
	if (FAILED(GetInput()->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//デバイスフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return -1;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return -1;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	m_pDevice->Acquire();

	m_hWnd = hWnd;

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CInputMouse::Uninit()
{
	//デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//基本クラスの終了処理
	CInput::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CInputMouse::Update()
{
	// 更新前に最新マウス情報を保存する
	m_PrevMouseState = m_CurrentMouseState;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{
		// カーソルの位置を取得
		GetCursorPos(&m_Point);
		ScreenToClient(m_hWnd, &m_Point);
	}
	else
	{
		m_pDevice->Acquire();
	}

	CDebugProc::Print("\nカーソル位置 : < X座標 : %f Y座標 : %f >\n", (float)m_Point.x, (float)m_Point.y);
}

//=====================================
// クリックした瞬間の判定
//=====================================
bool CInputMouse::OnMouseDown(MOUSE button_type)
{
	if (!(m_PrevMouseState.rgbButtons[button_type] & 0x80) &&
		m_CurrentMouseState.rgbButtons[button_type] & 0x80)
	{
		return true;
	}

	return false;
}

//=====================================
// クリックをやめた瞬間の判定
//=====================================
bool CInputMouse::OnMouseUp(MOUSE button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(m_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}