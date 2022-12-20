//=============================================================================
//
// input.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***********************************************
// ���C�u�����[�t�@�C���̃����N
//***********************************************
#pragma comment(lib,"dxguid.lib")	//�ŗLID�iGUID�j���o�^����Ă��郉�C�u����

//---------------------------
// �C���N���[�h�t�@�C��
//---------------------------
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//---------------------------
// �N���X
//---------------------------
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;

	static LPDIRECTINPUT8 GetInput() { return m_pInput; }
private:

	static LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_H_
