//=============================================================================
//
// inputKeyboard.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "inputKeyboard.h"

BYTE CInputKeyboard::m_aKeyState[NumMaxKey] = {};
BYTE CInputKeyboard::m_aKeyStateTrigger[NumMaxKey] = {};

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CInputKeyboard::CInputKeyboard() : m_pDevice(nullptr)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
CInputKeyboard::~CInputKeyboard()
{

}

//=====================================
// ������
//=====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̏���������
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NumMaxKey];		//�L�[�{�[�h�̓��͏��
										//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NumMaxKey; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = ~m_aKeyState[nCntKey] & aKeyState[nCntKey];	//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];									//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=====================================
// �L�[�{�[�h�̃v���X�����擾
//=====================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
// �L�[�{�[�h�̃g���K�[�����擾
//=====================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}