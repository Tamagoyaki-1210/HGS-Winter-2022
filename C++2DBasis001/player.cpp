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
// �f�t�H���g�R���X�g���N�^
//=====================================
CPlayer::CPlayer() : CObject_2D()
{

}

//=====================================
// �R���X�g���N�^
//=====================================
CPlayer::CPlayer(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CPlayer::~CPlayer()
{

}

//=====================================
// ����������
//=====================================
HRESULT CPlayer::Init()
{
	// ��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_fMoveSpeed = Fast_Player_Speed;

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CPlayer::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CPlayer::Update()
{
	CObject_2D::Update();

	SetUV();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �O��ʒu�̎擾
	m_posOld = pos;

	// ���͏���
	Input();

	//����
	m_move -= m_move * 0.15f;

	//�ʒu�X�V
	pos += m_move * m_fMoveSpeed;

	//�ʒu�ݒ菈��
	SetPos(pos);
}

//=====================================
// �`�揈��
//=====================================
void CPlayer::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// ���͏���
//=====================================
void CPlayer::Input()
{
	CInputInterface* pInput = CApplication::GetInstance()->GetInput();

	//�v���C���[�ړ�
	if (pInput->KeyDown(DIK_D))
	{//�E�ړ�
		if (pInput->KeyDown(DIK_S))
		{//���ړ�
			m_move += NormalizeLength(1.0f, 1.0f);
		}
		else if (pInput->KeyDown(DIK_W))
		{//��ړ�
			m_move += NormalizeLength(1.0f, -1.0f);
		}
		else
		{
			m_move.x += 1.0f;
		}
	}
	else if (pInput->KeyDown(DIK_A))
	{//���ړ�
		if (pInput->KeyDown(DIK_S))
		{//���ړ�
			m_move += NormalizeLength(-1.0f, 1.0f);
		}
		else if (pInput->KeyDown(DIK_W))
		{//��ړ�
			m_move += NormalizeLength(-1.0f, -1.0f);
		}
		else
		{
			m_move.x += -1.0f;
		}
	}
	else if(pInput->KeyDown(DIK_S))
	{//���ړ�
		m_move.y += 1.0f;
	}
	else if(pInput->KeyDown(DIK_W))
	{//��ړ�
		m_move.y += -1.0f;
	}
}

//=====================================
// ��������
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

	return pPlayer;
}