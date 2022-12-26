//=============================================================================
//
// player.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "player.h"
#include "application.h"
#include "texture.h"
#include "DirectInput.h"
#include "matrix.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CPlayer::CPlayer() : CObject_2D()
{

}

//=====================================
// コンストラクタ
//=====================================
CPlayer::CPlayer(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// デストラクタ
//=====================================
CPlayer::~CPlayer()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CPlayer::Init()
{
	// 基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_fMoveSpeed = Fast_Player_Speed;

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CPlayer::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CPlayer::Update()
{
	CObject_2D::Update();

	SetUV();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 前回位置の取得
	m_posOld = pos;

	// 入力処理
	Input();

	//減衰
	m_move -= m_move * 0.15f;

	//位置更新
	pos += m_move * m_fMoveSpeed;

	//位置設定処理
	SetPos(pos);
}

//=====================================
// 描画処理
//=====================================
void CPlayer::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// 入力処理
//=====================================
void CPlayer::Input()
{
	CInputInterface* pInput = CApplication::GetInstance()->GetInput();

	//プレイヤー移動
	if (pInput->KeyDown(DIK_D))
	{//右移動
		if (pInput->KeyDown(DIK_S))
		{//下移動
			m_move += NormalizeLength(1.0f, 1.0f);
		}
		else if (pInput->KeyDown(DIK_W))
		{//上移動
			m_move += NormalizeLength(1.0f, -1.0f);
		}
		else
		{
			m_move.x += 1.0f;
		}
	}
	else if (pInput->KeyDown(DIK_A))
	{//左移動
		if (pInput->KeyDown(DIK_S))
		{//下移動
			m_move += NormalizeLength(-1.0f, 1.0f);
		}
		else if (pInput->KeyDown(DIK_W))
		{//上移動
			m_move += NormalizeLength(-1.0f, -1.0f);
		}
		else
		{
			m_move.x += -1.0f;
		}
	}
	else if(pInput->KeyDown(DIK_S))
	{//下移動
		m_move.y += 1.0f;
	}
	else if(pInput->KeyDown(DIK_W))
	{//上移動
		m_move.y += -1.0f;
	}
}

//=====================================
// 生成処理
//=====================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CPlayer* pPlayer = new CPlayer(PRIORITY_CENTER);

	if (FAILED(pPlayer->Init()))
	{
		return nullptr;
	}

	pPlayer->SetPos(pos);
	pPlayer->SetSize(size);

	return pPlayer;
}