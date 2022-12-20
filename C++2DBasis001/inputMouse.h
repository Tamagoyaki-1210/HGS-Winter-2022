//=============================================================================
//
// inputMouse.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include "input.h"

//---------------------------
// �N���X�錾
//---------------------------
class CInputMouse : public CInput
{
public:
	// �L�[���(�}�E�X)
	enum MOUSE
	{
		MOUSE_LEFT = 0,		// ���{�^��
		MOUSE_RIGHT,		// �E�{�^��
		MOUSE_CENTER,		// �����{�^��
		MOUSE_MAX
	};

	CInputMouse();
	~CInputMouse() override;
																				
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	static POINT GetPoint() { return m_Point; }
	static DIMOUSESTATE* GetMouseState() { return &m_CurrentMouseState; }

	static bool OnMouseDown(MOUSE button_type);	// �N���b�N�����u�Ԃ̔���
	static bool OnMouseUp(MOUSE button_type);	// �N���b�N����߂��u�Ԃ̔���

private:
	static POINT m_Point;						// �|�C���g�̏��
	static DIMOUSESTATE m_CurrentMouseState;	// ���݂̃}�E�X���
	static DIMOUSESTATE m_PrevMouseState;		// �O��̃}�E�X���

	HWND m_hWnd;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif // !INPUT_MOUSE_H