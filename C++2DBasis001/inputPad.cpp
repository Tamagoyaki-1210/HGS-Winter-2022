//=============================================================================
//
// inputPad.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "inputPad.h"

XINPUT_STATE CInputPad::m_JoyKeyState = {};				// �W���C�p�b�g�̃v���X���
XINPUT_STATE CInputPad::m_JoyKeyStateTrigger = {};		// �W���C�p�b�g�̃g���K�[���
D3DXVECTOR3 CInputPad::m_JoyStickPos = {};				// �W���C�X�e�B�b�N�̌X��
int CInputPad::m_nTime = {};							// �U����������
WORD CInputPad::m_nStrength = {};						// �U���̋��� (0 - 65535)

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CInputPad::CInputPad() : m_pDevice(nullptr)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
CInputPad::~CInputPad()
{

}

//=====================================
// ������
//=====================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̏���������
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(GetInput()->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	// �������[�̃N���A
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// �W���C�p�b�h�̐U������̂O�N���A
	ZeroMemory(&m_JoyMoter, sizeof(XINPUT_VIBRATION));

	// �U������p�̏�����
	m_nStrength = 0;
	m_nTime = 0;

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CInputPad::Uninit()
{
	// XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);

	// �f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// ��{�N���X�̏I������
	CInput::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CInputPad::Update()
{
	XINPUT_STATE JoyKeyState;		// �W���C�p�b�h���͏��

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		m_JoyKeyStateTrigger.Gamepad.wButtons
			= ~m_JoyKeyState.Gamepad.wButtons
			& JoyKeyState.Gamepad.wButtons;	// �g���K�[����ۑ�
		m_JoyKeyState = JoyKeyState;		// �v���X����
	}

	// �W���C�p�b�h�̐U��
	m_JoyMoter.wLeftMotorSpeed = m_nStrength;
	m_JoyMoter.wRightMotorSpeed = m_nStrength;
	XInputSetState(0, &m_JoyMoter);

	if (m_nTime > 0)
	{
		m_nTime--;
	}
	else
	{
		m_nStrength = 0;
		m_nTime = 0;
	}
}

//=====================================
// �W���C�p�b�h�̃v���X����
//=====================================
bool CInputPad::GetJoypadPress(JOYKEY Key)
{
	return (m_JoyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=====================================
// �W���C�p�b�h�̃g���K�[����
//=====================================
bool CInputPad::GetJoypadTrigger(JOYKEY Key)
{
	return (m_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=====================================
// �W���C�p�b�g�i�X�e�B�b�N�v���X�j����
//=====================================
D3DXVECTOR3 CInputPad::GetJoypadStick(JOYKEY Key)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoyKeyState.Gamepad.sThumbLX / (float)0x7fff, -m_JoyKeyState.Gamepad.sThumbLY / (float)0x7fff, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoyKeyState.Gamepad.sThumbRX / (float)0x7fff, -m_JoyKeyState.Gamepad.sThumbRY / (float)0x7fff, 0.0f);
		break;
	}

	return m_JoyStickPos;
}

//=====================================
// �W���C�p�b�g�i�g���K�[�y�_���j����
//=====================================
int CInputPad::GetJoypadTriggerPedal(JOYKEY Key)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState.Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState.Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//=====================================
// �R���g���[���[�̐U������
//=====================================
void CInputPad::JoypadVibration(int nTime, WORD nStrength)
{
	m_nTime = nTime;			// �U����������
	m_nStrength = nStrength;	// �U���̋���
}