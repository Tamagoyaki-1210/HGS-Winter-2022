//=============================================================================
//
// input.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CInput::CInput()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CInput::~CInput()
{

}

//=====================================
// ����������
//=====================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CInput::Uninit()
{
	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}