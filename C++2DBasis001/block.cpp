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
// �f�t�H���g�R���X�g���N�^
//=====================================
CBlock::CBlock() : CObject_2D()
{

}

//=====================================
// �R���X�g���N�^
//=====================================
CBlock::CBlock(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CBlock::~CBlock()
{

}

//=====================================
// ����������
//=====================================
HRESULT CBlock::Init()
{
	// ��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CBlock::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CBlock::Update()
{
	CObject_2D::Update();

	SetUV();

	// �ʒu�擾
	D3DXVECTOR3 pos = CObject_2D::GetPos();

	CPlayer* pPlayer = CGame::GetPlayer();

	//// �g�p��
	//pos = pPlayer->GetPos();
	//m_move = pPlayer->GetMove();

	//�ʒu�X�V
	pos += m_move;

	//�ʒu�ݒ菈��
	CObject_2D::SetPos(pos);
}

//=====================================
// �`�揈��
//=====================================
void CBlock::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// ��������
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