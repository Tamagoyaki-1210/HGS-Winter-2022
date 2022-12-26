//=============================================================================
//
// game.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "game.h"
#include "application.h"
#include "player.h"
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

    CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(60, 60));

    CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80, 80), "ゲーム");



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