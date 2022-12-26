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
#include"texture.h"

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

	m_bCollision = false;

	m_nFrame = 0;
	m_nSave = 0;

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
	D3DXVECTOR3 pos = CObject_2D::GetPos();

	if (!GetGround())
	{
		// 重力
		m_move.y += m_gravity;
	}

	// 入力処理
	Input();

	// モーション処理
	Motion();

	//減衰
	m_move -= m_move * 0.15f * m_fMoveSpeed;

	//位置更新
	pos += m_move;

	if (pos.x < 100.0f)
	{
		pos.x = 100.0f;
	}
	else if (pos.x > 640.0f)
	{
		pos.x = 640.0f;
	}

	// プレイヤー落下処理
	if (pos.y > SCREEN_HEIGHT + 200.0f)
	{
		CApplication::GetInstance()->SetMode(CApplication::Mode_Result);
	}

	//位置設定処理
	CObject_2D::SetPos(pos);

	// 当たり判定の処理
	PlayerCollision();
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
		m_move.x += 1.0f;
		if (m_motion != MOTION_WARK && GetGround())
		{
			m_motion = MOTION_WARK;
		}
	}
	else if (pInput->KeyDown(DIK_A))
	{//左移動
		m_move.x += -1.0f;
		if (m_motion != MOTION_WARK && GetGround())
		{
			m_motion = MOTION_WARK;
		}
	}
	else if (m_motion == MOTION_WARK && GetGround())
	{
		m_motion = MOTION_NONE;
	}

	if ((pInput->KeyDown(DIK_W, true) || pInput->KeyDown(DIK_SPACE, true)) && GetGround())
	{//上移動
		m_move.y -= Jump_Power;
		CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		SetGround(false);
		CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		if (m_motion != MOTION_JUMP)
		{
			m_motion = MOTION_JUMP;
		}
	}

    if (pInput->KeyDown(DIK_G, true) && GetGround())
	{//重力反転
		m_gravity = -m_gravity;
	}
}

//=====================================
// モーション処理
//=====================================
void CPlayer::Motion()
{
	switch (m_motion)
	{
	case CPlayer::MOTION_NONE:
	{
		SetAnimControl(0);
		if (m_nFrame != 0 || m_nSave != 0)
		{
			m_nFrame = 0;
			m_nSave = 0;
		}
		break;
	}
	case CPlayer::MOTION_WARK:
	{
		SetAnimControl(m_nFrame, 0);
		// フレームカウント処理
		if (m_nSave > 2)
		{
			if (m_nFrame < 4)
			{
				m_nFrame++;
			}
			else
			{
				m_nFrame = 0;
			}
			m_nSave = 0;
		}
		else
		{
			m_nSave++;
		}
		break;
	}
	case CPlayer::MOTION_JUMP:
	{
		SetAnimControl(m_nFrame, 1);
		if (m_nSave > 2)
		{
			// フレームカウント処理
			if (m_nFrame < 4)
			{
				m_nFrame++;
			}
			else
			{
				m_nFrame = 4;
			}
			m_nSave = 0;
		}
		else
		{
			m_nSave++;
		}
		break;
	}
	default:
		break;
	}


}

//=====================================
// 当たり判定処理
//=====================================
void CPlayer::PlayerCollision()
{
	CObject *pCenter = CObject::GetTop();	//オブジェクトの先頭ポインタ

	if (GetGround())
	{
		SetGround(false);
		if (m_motion == MOTION_JUMP)
		{
			m_motion = MOTION_NONE;
		}
	}

	if (pCenter != nullptr)
	{
		//現在位置ポインタに先頭ポインタを代入
		CObject *pObject = pCenter;

		//現在位置ポインタが使用中の場合
		while (pObject != nullptr)
		{
			if (pObject->GetCollision() == true && pObject != this)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR2 size = (GetSize() / 2);

				D3DXVECTOR3 posSub = pObject->GetPos();
				D3DXVECTOR2 sizeSub = (pObject->GetSize() / 2);

				float fLeft = pos.x - size.x;			//四角形左側
				float fRight = pos.x + size.x;			//四角形右側
				float fUpp = pos.y - size.y;			//四角形上側
				float fLow = pos.y + size.y;			//四角形下側

				float fLeftSub = posSub.x - sizeSub.x;	//四角形左側
				float fRightSub = posSub.x + sizeSub.x;	//四角形右側
				float fUppSub = posSub.y - sizeSub.y;	//四角形上側
				float fLowSub = posSub.y + sizeSub.y;	//四角形下側

				if (fLeft < fRightSub && fRight > fLeftSub
					&& fUpp < fLowSub && fLow > fUppSub)
				{
					SetPos(Collision(pObject));
					pObject->SetIsCollision(true);
				}
			}
			// 現在位置ポインタに次回ポインタを代入する(ポインタを進める処理)
			pObject = pObject->GetNext();
		}
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
	pPlayer->SetTexture(CTexture::TEXTURE_PLAYER);
	pPlayer->SetAnimDiv(4, 2);

	pPlayer->SetCollision(true);

	return pPlayer;
}