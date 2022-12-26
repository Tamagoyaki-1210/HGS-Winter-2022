//=============================================================================
//
// block.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "block.h"
#include "application.h"
#include "texture.h"
#include "DirectInput.h"
#include "matrix.h"
#include "game.h"
#include "player.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CBlock::CBlock() : CObject_2D()
{

}

//=====================================
// コンストラクタ
//=====================================
CBlock::CBlock(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// デストラクタ
//=====================================
CBlock::~CBlock()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CBlock::Init()
{
	// 基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CBlock::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CBlock::Update()
{
	CObject_2D::Update();

	SetUV();

	// 位置取得
	D3DXVECTOR3 pos = CObject_2D::GetPos();

	CPlayer* pPlayer = CGame::GetPlayer();

	//// 使用例
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	if (PlayerPos.x == 640.0f|| PlayerPos.x == 100.f)
		
	{
		m_move.x = -pPlayer->GetMove().x;
	}
    else
    {
		m_move = D3DXVECTOR3(0.f, 0.f, 0.f);
    }

    switch (m_type)
    {
	case DOWNBLOCK:
		if (m_IsCollision)
		{
			m_move.y = 2.0f;
		}
		break;
	case UPBLOCK:
		if (m_IsCollision)
		{
			m_move.y = -2.0f;
		}
		break;
    }

	//位置更新
	pos += m_move;

	//位置設定処理
	CObject_2D::SetPos(pos);
}

//=====================================
// 描画処理
//=====================================
void CBlock::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// 生成処理
//=====================================
CBlock *CBlock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const BlockType type)
{
	CBlock* pBlock = new CBlock(PRIORITY_CENTER);

	if (FAILED(pBlock->Init()))
	{
		return nullptr;
	}

	pBlock->SetPos(pos);
	pBlock->SetSize(size);
	pBlock->m_type = type;

	switch (type)
	{
	case BlockType::BLOCK:
	{
		pBlock->SetTexture(CTexture::TEXTURE_BLOCK);
		break;
	}
	case BlockType::GOAL:
	{
		pBlock->SetTexture(CTexture::TEXTURE_GOAL);
		break;
	}
	case BlockType::THORN:
	{
		pBlock->SetTexture(CTexture::TEXTURE_THRON);
		break;
	}
	case BlockType::UPBLOCK:
	{
		pBlock->SetTexture(CTexture::TEXTURE_UPBLOCK);
		break;
	}
	case BlockType::DOWNBLOCK:
	{
		pBlock->SetTexture(CTexture::TEXTURE_DOWNBLOCK);
		break;
	}
	case BlockType::WOODCRATE:
	{
		pBlock->SetTexture(CTexture::TEXTURE_WOODCRATE);
		break;
	}
	default:
		break;
	}

	if (type != BlockType::NORMAL)
	{
		pBlock->SetCollision(true);
	}

	return pBlock;
}