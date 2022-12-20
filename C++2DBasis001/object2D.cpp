//=============================================================================
//
// object2D.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CObject_2D::CObject_2D() : CObject(), m_pVtxBuff(nullptr)
{

}

//=====================================
// �R���X�g���N�^
//=====================================
CObject_2D::CObject_2D(const int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CObject_2D::~CObject_2D()
{

}

//=====================================
// ����������
//=====================================
HRESULT CObject_2D::Init()
{
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;

	m_fAngle = 0.0f;
	m_nAnimColumn = 0;
	m_nAnimLine = 0;
	m_nAnimControl = 0;

	// �A�j���[�V�����̋敪�̏�����(1 * 1)
	m_nAnimColumnDiv = 1;
	m_nAnimLineDiv = 1;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �e�N�X�`���̏�����
	SetTexture(CTexture::TEXTURE_NULL);

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CObject_2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=====================================
// �X�V����
//=====================================
void CObject_2D::Update()
{

}

//=====================================
// �`�揈��
//=====================================
void CObject_2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	CTexture::GetTextureType(m_textType);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`���̉������
	CTexture::TextureClear();
}

//=====================================
// UV�ݒ菈��
//=====================================
void CObject_2D::SetUV()
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fLength = sqrtf((powf(m_size.x, 2) + powf(m_size.y, 2)) / 2);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle + m_rot.y) * fLength;
	pVtx[0].pos.z = m_pos.z;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.y) * fLength;
	pVtx[1].pos.z = m_pos.z;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.y) * fLength;
	pVtx[2].pos.z = m_pos.z;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.y) * fLength;
	pVtx[3].pos.z = m_pos.z;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================
// �����I�Ȓ��_�e�N�X�`���ݒ菈���@(�摜���x)
//=========================================================
void CObject_2D::SetAnimAuto(int nSpeed)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn,		(1.0f / m_nAnimLineDiv) * m_nAnimLine);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * m_nAnimLine);
	pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn,		(1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));
	
	// �A�j���[�V�����̕b���𐔂���
	m_nAnimControl++;

	// �w��̕b���ŃA�j���[�V�������鏈��
	if (nSpeed <= m_nAnimControl)
	{
		// �P�񉡂ɃA�j���[�V��������
		m_nAnimColumn++;

		// �A�j���[�V�����b���̏�����
		m_nAnimControl = 0;

		// �񂪉��̍ő吔�𒴂����ꍇ
		if (m_nAnimColumnDiv <= m_nAnimColumn)
		{
			// ���[�ɖ߂�
			m_nAnimColumn = 0;

			// �P�s�c�ɃA�j���[�V��������
			m_nAnimLine++;

			// �s���c�̍ő吔�𒴂����ꍇ
			if (m_nAnimLineDiv <= m_nAnimLine)
			{
				// ��ԏ�ɖ߂�
				m_nAnimLine = 0;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================
// �蓮�p�̒��_�e�N�X�`���ݒ菈���@(�摜��, �摜�s)
//=========================================================
void CObject_2D::SetAnimControl(int nAnimColumn, int nAnimLine)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * nAnimColumn,			(1.0f / m_nAnimLineDiv) * nAnimLine);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * nAnimLine);
	pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * nAnimColumn,			(1.0f / m_nAnimLineDiv) * (nAnimLine + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * (nAnimLine + 1));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=========================================================
// �蓮�p�̒��_�e�N�X�`���ݒ菈���@(�摜�ԍ�)
//=========================================================
void CObject_2D::SetAnimControl(int nAnimCounter)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �w�肳�ꂽ�A�j���ԍ���ϐ��Ɋi�[����
	int nCounter = nAnimCounter;

	// ���̍ő吔���w�肳�ꂽ�l���傫���ꍇ���[�v����
	while (m_nAnimColumnDiv <= nCounter)
	{
		// �l���敪���������炷
		nCounter -= m_nAnimColumnDiv;

		// �P�s�c�ɃA�j���[�V��������
		m_nAnimLine++;

		// �c�̍ő吔���w�肳�ꂽ�l���傫���ꍇ
		if (m_nAnimLine >= m_nAnimLineDiv)
		{
			// �c�A�j���[�V�����̏�����
			m_nAnimLine = 0;
		}
	}

	// ��A�j���[�V�����̑��
	m_nAnimColumn = nCounter;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn,		(1.0f / m_nAnimLineDiv) * m_nAnimLine);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * m_nAnimLine);
	pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn,		(1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1),	(1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
// �F�ݒ菈��(���_��)
//=====================================
void CObject_2D::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col0;
	pVtx[1].col = col1;
	pVtx[2].col = col2;
	pVtx[3].col = col3;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
// �F�ݒ菈��(�S��)
//=====================================
void CObject_2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
// �g��ʂ̐ݒ菈��
//=====================================
void CObject_2D::SetSize(const D3DXVECTOR2 size)
{
	m_size = size;
	m_fAngle = atan2f(m_size.x, m_size.y);

	SetUV();			// UV�̐ݒ菈��
}

//=====================================
// �摜�A�j���[�V�����̋敪�ݒ菈��
//=====================================
void CObject_2D::SetAnimDiv(int nDivX, int nDivY)
{
	m_nAnimColumnDiv = nDivX;
	m_nAnimLineDiv = nDivY;
}

//=====================================
// �I�u�W�F�N�g2D��������
//=====================================
CObject_2D* CObject_2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CObject_2D* pObject2D = new CObject_2D;

	if (FAILED(pObject2D->Init()))
	{
		return nullptr;
	}

	pObject2D->SetPos(pos);
	pObject2D->SetSize(size);

	return pObject2D;
}