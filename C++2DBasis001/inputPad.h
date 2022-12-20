//=============================================================================
//
// inputPad.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_PAD_H_
#define _INPUT_PAD_H_

//***********************************************
// ���C�u�����[�t�@�C���̃����N
//***********************************************
#pragma comment(lib,"xinput.lib")	//���͏����Ɏg�p(�W���C�p�b�h)

//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "input.h"
#include "XInput.h"

//---------------------------
// �N���X�錾
//---------------------------
class CInputPad : public CInput
{
public:
	//�L�[���(�W���C�p�b�h)
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_LEFT_STICK,			//���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			//�E�X�e�B�b�N
		JOYKEY_MAX
	};

	CInputPad();
	~CInputPad() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	static bool GetJoypadPress(JOYKEY Key);					//�W���C�p�b�h�v���X����
	static bool GetJoypadTrigger(JOYKEY Key);				//�W���C�p�b�h�g���K�[����
	static D3DXVECTOR3 GetJoypadStick(JOYKEY Key);			//�W���C�p�b�h�X�e�B�b�N����
	static int GetJoypadTriggerPedal(JOYKEY Key);			//�W���C�p�b�h�g���K�[�y�_������
	static void JoypadVibration(int nTime, WORD nStrength);	//�W���C�p�b�h�U������

private:

	static XINPUT_STATE m_JoyKeyState;						//�W���C�p�b�g�̃v���X���
	static XINPUT_STATE m_JoyKeyStateTrigger;				//�W���C�p�b�g�̃g���K�[���
	static D3DXVECTOR3 m_JoyStickPos;						//�W���C�X�e�B�b�N�̌X��
	static int m_nTime;										//�U����������
	static WORD m_nStrength;								//�U���̋��� (0 - 65535)
	
	XINPUT_VIBRATION m_JoyMoter;							//�W���C�p�b�h�̃��[�^�[
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !_INPUT_PAD_H_
