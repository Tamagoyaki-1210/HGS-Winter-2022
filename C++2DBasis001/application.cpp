//=============================================================================
//
// application.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputPad.h"
#include "texture.h"
#include "fade.h"
#include "mode.h"
#include "object.h"
#include "debugProc.h"
#include "title.h"
#include "game.h"
#include "result.h"

CRenderer *CApplication::m_pRenderer = nullptr;	// レンダラーポインタ
CInput *CApplication::m_pInput[Input_Max] = {};	// 入力ポインタ
CTexture *CApplication::m_pTexture = nullptr;	// 画像ポインタ
CMode *CApplication::m_pMode = nullptr;			// モードポインタ
CSound *CApplication::m_pSound = nullptr;		// サウンドポインタ
CFade* CApplication::m_pFade = nullptr;			// フェードポインタ
CDebugProc* CApplication::m_pDebug = nullptr;	// デバッグポインタ

CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;			//モード
CApplication::Mode CApplication::m_modeNext = CApplication::Mode_Title;		//次のモード

//=====================================
// デフォルトコンストラクタ
//=====================================
CApplication::CApplication()
{

}

//=====================================
// デストラクタ
//=====================================
CApplication::~CApplication()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
	}

	// true : ウィンドウサイズ, false : 全画面
	if (FAILED(m_pRenderer->Init(hWnd, true)))
	{
		return -1;
	}

	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
		
		//全ての画像の読み込み処理
		m_pTexture->LoadAll();
	}

	if (m_pDebug == nullptr)
	{
		m_pDebug = CDebugProc::Create();
	}

	if (m_pSound == nullptr)
	{
		m_pSound = CSound::Create(hWnd);
	}

	if (m_pMode == nullptr)
	{
		// 最初のモード
		m_pMode = CTitle::Create();
		m_mode = Mode_Title;
		m_modeNext = Mode_Title;
	}

	if (m_pFade == nullptr)
	{
		// フェード生成
		m_pFade = CFade::Create();
		m_pFade->SetFade();
	}

	// インプットデバイスの生成
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] == nullptr)
		{
			// 種別毎の設定
			switch ((Input_type)nCnt)
			{
			case CApplication::Input_Keyboard:
				// キーボードインスタンスの生成
				m_pInput[nCnt] = new CInputKeyboard;
				break;

			case CApplication::Input_Pad:
				// パッドインスタンスの生成
				m_pInput[nCnt] = new CInputPad;
				break;

			case CApplication::Input_Mouse:
				// マウスインスタンスの生成
				m_pInput[nCnt] = new CInputMouse;
				break;

			default:
				break;
			}

			// インプットデバイスの初期化処理
			if (FAILED(m_pInput[nCnt]->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CApplication::Uninit()
{
	// レンダリングの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// モードの破棄
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// インプットデバイスの破棄
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	// サウンドの破棄
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//フェードの破棄
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// デバッグテキストの破棄
	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	// オブジェクト全体の終了
	CObject::ReleaseAll();

	// 画像の破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CApplication::Update()
{
	// インプットデバイスの更新処理
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// フェードの更新処理
	if (m_pFade != nullptr)
	{
		// フェードが読み込まれていない場合
		if (m_pFade->GetFade() != CFade::FADE_NONE)
		{
			m_pFade->Update();

			if (m_pFade->GetFade() == CFade::FADE_CHANGE)
			{// フェード切り替え状態の場合
				ChangeMode();
			}
		}
	}

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}
}

//=====================================
// 描画処理
//=====================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}


//=====================================
// モード設定処理
//=====================================
void CApplication::SetMode(Mode mode)
{
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		m_modeNext = mode;
		m_pFade->SetFade();
	}
}

//=====================================
// モード切り替え処理
//=====================================
void CApplication::ChangeMode()
{
	// 現在モードの終了
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	CObject::ReleaseAll();	// 全てのオブジェクトの終了

	if (m_pSound != nullptr)
	{// 使用中のサウンド停止
		m_pSound->Stop();
	}

	// モードを生成する
	switch (m_modeNext)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		break;

	case CApplication::Mode_Game:
		m_pMode = CGame::Create();
		break;

	case CApplication::Mode_Result:
		m_pMode = CResult::Create();
		break;

	default:
		break;
	}
	m_mode = m_modeNext;	// 次のモードに変更
}
