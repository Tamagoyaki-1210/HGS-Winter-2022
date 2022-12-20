//=============================================================================
//
// application.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>
#include "sound.h"

//---------------------------
// �O���錾
//---------------------------
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
class CSound;
class CDebugProc;

//---------------------------
// �N���X�錾
//---------------------------
class CApplication
{
public:
	enum Mode
	{
		Mode_Title = 0,		// �^�C�g��
		Mode_Game,			// �Q�[��
		Mode_Result,		// ���U���g

		Mode_Max
	};

	enum Input_type
	{
		Input_Keyboard = 0,	// �L�[�{�[�h
		Input_Pad,			// �p�b�h
		Input_Mouse,		// �}�E�X

		Input_Max
	};

	CApplication();
	~CApplication();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer* GetRenderer() { return m_pRenderer; }	// �����_���[�̎擾����
	static CTexture* GetTexture() { return m_pTexture; }	// �摜�̎擾����
	static CSound* GetSound() { return m_pSound; }			// �T�E���h�̎擾����
	static CFade* GetFade() { return m_pFade; }				// �t�F�[�h�̎擾����

	static Mode GetMode() { return m_mode; }				// ���[�h�̎擾����
	static void SetMode(Mode mode);							// ���[�h�̐ݒ菈��
	void ChangeMode();										// ���[�h�̕ύX����

private:
	static CRenderer*		m_pRenderer;
	static CInput*			m_pInput[Input_Max];
	static CTexture*		m_pTexture;
	static CSound*			m_pSound;
	static CFade*			m_pFade;
	static CMode*			m_pMode;
	static CDebugProc*		m_pDebug;

	static Mode	m_mode;		//���݃��[�h
	static Mode m_modeNext;	//���̃��[�h
};

#endif // !_APPLICATION_H_
