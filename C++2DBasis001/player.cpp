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

	m_bCollision = false;
	m_bJump = false;

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
	D3DXVECTOR3 pos = CObject_2D::GetPos();

	if (!GetGround())
	{
		// �d��
		m_move.y += 1.0f;
	}

	// ���͏���
	Input();

	//����
	m_move -= m_move * 0.15f * m_fMoveSpeed;

	//�ʒu�X�V
	pos += m_move;

	if (pos.x <= 100.0f)
	{
		pos.x = 100.0f;
	}
	else if (pos.x >= 700.0f)
	{
		pos.x = 700.0f;
	}

	//�ʒu�ݒ菈��
	CObject_2D::SetPos(pos);

	// �����蔻��̏���
	PlayerCollision();
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
		if (pInput->KeyDown(DIK_SPACE, true) && GetGround())
		{//��ړ�
			m_move += NormalizeLength(1.0f, -1);
			m_move.y -= Jump_Power;
			SetGround(false);
		}
		m_move.x += 1.0f;
	}
	else if (pInput->KeyDown(DIK_A))
	{//���ړ�
		if (pInput->KeyDown(DIK_SPACE, true) && GetGround())
		{//��ړ�
			m_move += NormalizeLength(-1.0f, -1);
			m_move.y -= Jump_Power;
			SetGround(false);
		}
		m_move.x += -1.0f;
	}
	else if (pInput->KeyDown(DIK_SPACE, true) && GetGround())
	{//��ړ�
		m_move += NormalizeLength(0.0f, -1);
		m_move.y -= Jump_Power;
		SetGround(false);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
void CPlayer::PlayerCollision()
{
	CObject *pCenter = CObject::GetTop();	//�I�u�W�F�N�g�̐擪�|�C���^

	SetGround(false);

	if (pCenter != nullptr)
	{
		//���݈ʒu�|�C���^�ɐ擪�|�C���^����
		CObject *pObject = pCenter;

		//���݈ʒu�|�C���^���g�p���̏ꍇ
		while (pObject != nullptr)
		{
			if (pObject->GetCollision() == true && pObject != this)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR2 size = (GetSize() / 2);

				D3DXVECTOR3 posSub = pObject->GetPos();
				D3DXVECTOR2 sizeSub = (pObject->GetSize() / 2);

				float fLeft = pos.x - size.x;			//�l�p�`����
				float fRight = pos.x + size.x;			//�l�p�`�E��
				float fUpp = pos.y - size.y;			//�l�p�`�㑤
				float fLow = pos.y + size.y;			//�l�p�`����

				float fLeftSub = posSub.x - sizeSub.x;	//�l�p�`����
				float fRightSub = posSub.x + sizeSub.x;	//�l�p�`�E��
				float fUppSub = posSub.y - sizeSub.y;	//�l�p�`�㑤
				float fLowSub = posSub.y + sizeSub.y;	//�l�p�`����

				if (fLeft < fRightSub && fRight > fLeftSub
					&& fUpp < fLowSub && fLow > fUppSub)
				{
					SetPos(Collision(pObject));
				}
			}
			// ���݈ʒu�|�C���^�Ɏ���|�C���^��������(�|�C���^��i�߂鏈��)
			pObject = pObject->GetNext();
		}
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

	pPlayer->SetCollision(true);

	return pPlayer;
}