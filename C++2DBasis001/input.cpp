//=============================================================================
//
// input.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// インクルードファイル
//---------------------------
#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=====================================
// デフォルトコンストラクタ
//=====================================
CInput::CInput()
{

}

//=====================================
// デストラクタ
//=====================================
CInput::~CInput()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CInput::Uninit()
{
	// DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}