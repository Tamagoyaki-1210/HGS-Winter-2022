//=============================================================================
//
// number.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "number.h"
#include "application.h"
#include "texture.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CNumber::CNumber() : CObject_2D()
{

}

//=====================================
// �R���X�g���N�^
//=====================================
CNumber::CNumber(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CNumber::~CNumber()
{

}

//=====================================
// ����������
//=====================================
HRESULT CNumber::Init()
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
void CNumber::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CNumber::Update()
{
	CObject_2D::Update();
}

//=====================================
// �`�揈��
//=====================================
void CNumber::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// �_���̐ݒ菈��
//=====================================
void CNumber::SetNumber(int nScore)
{
	SetAnimControl(nScore);
}

//=====================================
// �X�R�A��������
//=====================================
CNumber *CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CNumber* pNumber = new CNumber(PRIORITY_UI);

	if (FAILED(pNumber->Init()))
	{
		return nullptr;
	}

	pNumber->SetPos(pos);
	pNumber->SetSize(size);

	pNumber->SetTexture(CTexture::TEXTURE_NUMBER);		//�e�N�X�`���̐ݒ�
	pNumber->SetAnimDiv(Base_Number, 1);
	pNumber->SetAnimControl(0);

	return pNumber;
}