//=============================================================================
//
// application.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "fade.h"
#include "mode.h"
#include "object.h"
#include "debugProc.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "DirectInput.h"

CApplication* CApplication::m_pApplication = nullptr;

//=====================================
// デフォルトコンストラクタ
//=====================================
CApplication::CApplication() : m_pRenderer(nullptr), m_pTexture(nullptr), m_pSound(nullptr), m_pFade(nullptr),
m_pMode(nullptr),
m_pDebugProc(nullptr),
m_pInput(nullptr), m_mode(), m_modeNext()
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
    if (FAILED(m_pRenderer->Init(hWnd, false)))
    {
        return -1;
    }

    if (m_pTexture == nullptr)
    {
        m_pTexture = new CTexture;

        //全ての画像の読み込み処理
        m_pTexture->LoadAll();
    }

	if (m_pDebugProc == nullptr)
	{
		m_pDebugProc = CDebugProc::Create();
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

    if (!CreateDIInput(&m_pInput, hWnd, hInstance, false))
    {
        return -1;
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

    m_pInput->Shutdown();

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
    if (m_pDebugProc != nullptr)
    {
        delete m_pDebugProc;
        m_pDebugProc = nullptr;
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

	delete this;	// 自身のポインタの削除
}

//=====================================
// 更新処理
//=====================================
void CApplication::Update()
{
    //// インプットデバイスの更新処理
    //for (int nCnt = 0; nCnt < Input_Max; nCnt++)
    //{
    //	if (m_pInput[nCnt] != nullptr)
    //	{
    //		m_pInput[nCnt]->Update();
    //	}
    //}
    m_pInput->UpdateDevices();

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
