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
CBlock *CBlock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CBlock* pBlock = new CBlock(PRIORITY_CENTER);

	if (FAILED(pBlock->Init()))
	{
		return nullptr;
	}

	pBlock->SetPos(pos);
	pBlock->SetSize(size);

	pBlock->SetCollision(true);

	return pBlock;
}