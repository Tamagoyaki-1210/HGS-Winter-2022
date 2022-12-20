//=============================================================================
//
// inputKeyboard.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//***********************************************
//���C�u�����[�t�@�C���̃����N
//***********************************************
#pragma comment(lib,"dinput8.lib")	//���͏����Ɏg�p(�L�[�{�[�h)

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "input.h"

//---------------------------
// �N���X�錾
//---------------------------
class CInputKeyboard : public CInput
{
public:
	static const int NumMaxKey = 256;	//�L�[�̍ő吔(�L�[�{�[�h)

	CInputKeyboard();
	~CInputKeyboard() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	//�L�[�{�[�h
	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);

private:
	static BYTE m_aKeyState[NumMaxKey];			//�L�[�{�[�h�̃v���X���
	static BYTE m_aKeyStateTrigger[NumMaxKey];	//�L�[�{�[�h�̃g���K�[���

	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !_INPUT_KEYBOARD_H_
