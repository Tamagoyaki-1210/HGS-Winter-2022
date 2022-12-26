//=============================================================================
//
// game.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "game.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
//#include "inputKeyboard.h"
#include "DirectInput.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CGame::CGame()
{

}

//=====================================
// デストラクタ
//=====================================
CGame::~CGame()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CGame::Init()
{
	CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

    CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100, 100));

    CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80, 80), "ゲーム");

	CScore* pScore = CScore::Create(D3DXVECTOR3((float)SCREEN_WIDTH, SCREEN_HEIGHT / 12, 0.0f), D3DXVECTOR2(10.0f, 20.0f));
	pScore->AddScore(12345609);

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGame::Uninit()
{

}

//=====================================
// 更新処理
//=====================================
void CGame::Update()
{
    Input();
}

//=====================================
// 入力処理
//=====================================
void CGame::Input()
{
    //// Pでポーズ切り替え
    //if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
    //{
    //    g_pApplication->SetMode(g_pApplication->Mode_Result);
    //}

    if (CApplication::GetInstance()->GetInput()->KeyDown(DIK_RETURN, true))
    {
		CApplication::GetInstance()->SetMode(CApplication::Mode_Result);
    }
}

//=====================================
// 生成処理
//=====================================
CGame* CGame::Create()
{
    CGame* pGame = new CGame;

    if (FAILED(pGame->Init()))
    {
        return nullptr;
    }

    return pGame;
}