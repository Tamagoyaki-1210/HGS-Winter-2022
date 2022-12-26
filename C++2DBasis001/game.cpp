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
#include "DirectInput.h"
#include "block.h"
#include "score.h"
#include "CLevel.h"
#include"object2D.h"
CPlayer* CGame::m_pPlayer = nullptr;
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

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(40, 60));
	
	CScore* pScore = CScore::Create(D3DXVECTOR3((float)SCREEN_WIDTH, SCREEN_HEIGHT / 12, 0.0f), D3DXVECTOR2(10.0f, 20.0f));
	pScore->AddScore(12345609);

	CObject_2D* pObj2D = CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	pObj2D->CObject_2D::SetTexture(CTexture::TEXTURE_SPACEBG);
	pObj2D->SetAnimDiv(10, 1);

	pObj2D = CObject_2D::Create(D3DXVECTOR3(120.0f, 120.0f, 0.0f), D3DXVECTOR2(200.0f,180.0f));
	pObj2D->CObject_2D::SetTexture(CTexture::TEXTURE_TUTORIAL);

	m_pLevel = new CLevel;
	m_pLevel->LoadMapFile("data\\MAP\\map.txt");

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGame::Uninit()
{
	delete m_pLevel;
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