//=============================================================================
//
// inputMouse.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "inputMouse.h"
#include "debugProc.h"

POINT CInputMouse::m_Point = {};
DIMOUSESTATE CInputMouse::m_CurrentMouseState = {};
DIMOUSESTATE CInputMouse::m_PrevMouseState = {};

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CInputMouse::CInputMouse() : m_pDevice(nullptr)
{
	
}

//=====================================
// �f�X�g���N�^
//=====================================
CInputMouse::~CInputMouse()
{

}

//=====================================
// ����������
//=====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//��{�N���X�̏���������
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return -1;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(GetInput()->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return -1;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return -1;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	m_pDevice->Acquire();

	m_hWnd = hWnd;

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CInputMouse::Uninit()
{
	//�f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//��{�N���X�̏I������
	CInput::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CInputMouse::Update()
{
	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	m_PrevMouseState = m_CurrentMouseState;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{
		// �J�[�\���̈ʒu���擾
		GetCursorPos(&m_Point);
		ScreenToClient(m_hWnd, &m_Point);
	}
	else
	{
		m_pDevice->Acquire();
	}

	CDebugProc::Print("\n�J�[�\���ʒu : < X���W : %f Y���W : %f >\n", (float)m_Point.x, (float)m_Point.y);
}

//=====================================
// �N���b�N�����u�Ԃ̔���
//=====================================
bool CInputMouse::OnMouseDown(MOUSE button_type)
{
	if (!(m_PrevMouseState.rgbButtons[button_type] & 0x80) &&
		m_CurrentMouseState.rgbButtons[button_type] & 0x80)
	{
		return true;
	}

	return false;
}

//=====================================
// �N���b�N����߂��u�Ԃ̔���
//=====================================
bool CInputMouse::OnMouseUp(MOUSE button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(m_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}