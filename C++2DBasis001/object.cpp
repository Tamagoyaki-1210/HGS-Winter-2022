//=============================================================================
//
// object.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "Application.h"

CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CObject::CObject() : m_bDeath(false)
{
	// ���݂̃I�u�W�F�N�g���g�p���̏ꍇ
	if (m_pCurrent[0] != nullptr)
	{
	 // ���݂̃I�u�W�F�N�g�������̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[0]->m_pNext = this;

		// �O�̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���݂̃I�u�W�F�N�g��ݒ肷��
		m_pPrev = m_pCurrent[0];

		// ���݂̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[0] = this;
	}
	// ���݂̃I�u�W�F�N�g�����g�p�̏ꍇ
	else
	{
	 // �擪�̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pTop[0] = this;

		// ���݂̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[0] = this;

		// �O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;		// ���̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���
	m_nPriority = 0;		// �`�揇��ݒ肷��
}

//=====================================
// �R���X�g���N�^
//=====================================
CObject::CObject(int nPriority) : m_bDeath(false)
{
	// ���݂̃I�u�W�F�N�g���g�p���̏ꍇ
	if (m_pCurrent[nPriority] != nullptr)
	{
	 // ���݂̃I�u�W�F�N�g�������̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[nPriority]->m_pNext = this;

		// �O�̃I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��
		m_pPrev = m_pCurrent[nPriority];

		// ���݂̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[nPriority] = this;
	}
	// ���݂̃I�u�W�F�N�g�����g�p�̏ꍇ
	else
	{
	 // �擪�̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pTop[nPriority] = this;

		// ���݂̃I�u�W�F�N�g�ւ̃|�C���^�ɁA���g�̃A�h���X��ݒ肷��
		m_pCurrent[nPriority] = this;

		// �O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;			// ���̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���
	m_nPriority = nPriority;	// �`�揇��ݒ肷��
}

//=====================================
// �f�X�g���N�^
//=====================================
CObject::~CObject()
{
	
}

//=====================================
// �������
//=====================================
void CObject::Release()
{
	m_bDeath = true;
}

//=====================================
// �S�Ẳ������
//=====================================
void CObject::ReleaseAll()
{
	// �\�ߑS�ẴI�u�W�F�N�g���I��������
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[nCnt] != nullptr)
		{
			// ���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pCurrent = m_pTop[nCnt];

			// ���݈ʒu�|�C���^�����g�p�ɂȂ�܂�
			while (pCurrent != nullptr)
			{
				pCurrent->Uninit();
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[nCnt] != nullptr)
		{
			// ���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				// ���݂̃|�C���^���g�p���̏ꍇ
				CObject *pNext = pCurrent->m_pNext;

				// ���݂̃|�C���^�����A�O�̃|�C���^���g�p���̏ꍇ
				if (pCurrent->m_pPrev != nullptr)
				{
					// ���݂̃|�C���^�����A���̃|�C���^���g�p���̏ꍇ
					if (pCurrent->m_pNext != nullptr)
					{
						pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
						pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
					}
					else
					{
						pCurrent->m_pPrev->m_pNext = nullptr;
						m_pCurrent[nCnt] = pCurrent->m_pPrev;
					}
				}
				else
				{
					// ���݂̃|�C���^�����A���̃|�C���^���g�p���̏ꍇ
					if (pCurrent->m_pNext != nullptr)
					{
						pCurrent->m_pNext->m_pPrev = nullptr;
						m_pTop[nCnt] = pCurrent->m_pNext;
					}
					else
					{
						m_pTop[nCnt] = nullptr;
						m_pCurrent[nCnt] = nullptr;
					}
				}
				delete pCurrent;		// ���������������
				pCurrent = pNext;		// ���݂̃|�C���^�Ɏ��̃|�C���^��ݒ肷��
			}
		}
	}
}

//=====================================
// �S�Ă̍X�V����
//=====================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[nCnt] != nullptr)
		{
			// ���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pCurrent = m_pTop[nCnt];

			// ���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pCurrent != nullptr)
			{
				//���S�t���O�������Ă��Ȃ��ꍇ
				if (!pCurrent->m_bDeath)
				{
					pCurrent->Update();
				}
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[nCnt] != nullptr)
		{
			// ���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pCurrent = m_pTop[nCnt];

			// ���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pCurrent != nullptr)
			{
				CObject *pObjectNext = pCurrent->m_pNext;

				// ���S�t���O�������Ă���ꍇ
				if (pCurrent->m_bDeath)
				{
					// �O��|�C���^���g�p���̏ꍇ
					if (pCurrent->m_pPrev != nullptr)
					{
						// ����|�C���^���g�p���̏ꍇ
						if (pCurrent->m_pNext != nullptr)
						{
							pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
							pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
						}
						else
						{
							pCurrent->m_pPrev->m_pNext = nullptr;
							m_pCurrent[nCnt] = pCurrent->m_pPrev;
						}
					}
					else
					{
						// ����|�C���^���g�p���̏ꍇ
						if (pCurrent->m_pNext != nullptr)
						{
							pCurrent->m_pNext->m_pPrev = nullptr;
							m_pTop[nCnt] = pCurrent->m_pNext;
						}
						else
						{
							m_pTop[nCnt] = nullptr;
							m_pCurrent[nCnt] = nullptr;
						}
					}
					delete pCurrent;
				}
				pCurrent = pObjectNext;
			}
		}
	}
}

//=====================================
// �S�Ă̕`�揈��
//=====================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[nCnt] != nullptr)
		{
			// ���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pCurrent = m_pTop[nCnt];

			// ���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pCurrent != nullptr)
			{
				pCurrent->Draw();
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
}

//=====================================
// �`�揇�̐ݒ菈��
//=====================================
void CObject::SetPriority(int nPriority)
{
	// �`�揇���͈͊O�ł͂Ȃ��悤�Ɋm�F����
	if (nPriority < 0)
	{
		nPriority = 0;
	}
	else if (nPriority > PRIORITY_MAX)
	{
		nPriority = PRIORITY_MAX;
	}
}