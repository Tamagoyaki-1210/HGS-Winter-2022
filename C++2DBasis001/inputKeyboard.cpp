//=============================================================================
//
// inputKeyboard.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// インクルードファイル
//---------------------------
#include "inputKeyboard.h"

BYTE CInputKeyboard::m_aKeyState[NumMaxKey] = {};
BYTE CInputKeyboard::m_aKeyStateTrigger[NumMaxKey] = {};

//=====================================
// デフォルトコンストラクタ
//=====================================
CInputKeyboard::CInputKeyboard() : m_pDevice(nullptr)
{
}

//=====================================
// デストラクタ
//=====================================
CInputKeyboard::~CInputKeyboard()
{

}

//=====================================
// 初期化
//=====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// キーボードの初期化処理
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// 入力デバイス(キーボード)の生成
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NumMaxKey];		//キーボードの入力情報
										//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NumMaxKey; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = ~m_aKeyState[nCntKey] & aKeyState[nCntKey];	//キーボードのトリガー情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];									//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//=====================================
// キーボードのプレス情報を取得
//=====================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
// キーボードのトリガー情報を取得
//=====================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}