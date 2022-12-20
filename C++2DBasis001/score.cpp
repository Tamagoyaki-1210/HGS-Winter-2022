//=============================================================================
//
// score.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "score.h"
#include "application.h"
#include "number.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CScore::CScore()
{
	
}

//=====================================
// �f�X�g���N�^
//=====================================
CScore::~CScore()
{

}

//=====================================
// ����������
//=====================================
HRESULT CScore::Init()
{
	m_nScore = 0;

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CScore::Uninit()
{
	m_nScore = 0;

	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// �|�C���^�̒��g���g�p���̏ꍇ
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}
}

//=====================================
// �X�V����
//=====================================
void CScore::Update()
{
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// �|�C���^�̒��g���g�p���̏ꍇ
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Update();
		}
	}
}

//=====================================
// �`�揈��
//=====================================
void CScore::Draw()
{
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// �|�C���^�̒��g���g�p���̏ꍇ
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//=====================================
// �_���̐ݒ菈��
//=====================================
void CScore::SetScore()
{
	// �w��̌��̐��l�𒊏o
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// �v�Z(�X�R�A % 10�ׂ̂��� / �ЂƂ���10�ׂ̂���)
		int A = (int)pow(10.0f, (Max_Digit - nCnt));
		int B = (int)pow(10.0f, (Max_Digit - nCnt - 1));
		m_apNumber[nCnt]->SetNumber(m_nScore % A / B);
	}
}

//=====================================
// �_���̉��Z����
//=====================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	if (m_nScore > Max_Score)
	{
		m_nScore = Max_Score;
	}

	SetScore();
}

//=====================================
// ��������
//=====================================
CScore *CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CScore* pScore = new CScore;

	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR2 halfSize = size / 2;	// �����T�C�Y�̔����̑傫��

	// �����ʒu�̒���
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		pScore->m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x - ( Max_Digit / 2 * ((halfSize.x / 2) + (halfSize.x * (Max_Digit - nCnt))) ), pos.y, 0.0f), size);
	}
	pScore->SetScore();	// �X�R�A��ݒ肷��

	return pScore;
}