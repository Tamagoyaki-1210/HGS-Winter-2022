//=============================================================================
//
// debugProc.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <d3dx9.h>
#include <stdarg.h>
#include <string>

//---------------------------
// �N���X�錾
//---------------------------
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
														
	HRESULT Init();
	void Uninit();
														
	void Print(const char *pFormat, ...);		// �����̓��͏���
	void Draw();

	static CDebugProc* Create();

private:
	static const int Str_Max = 2048;	// �����̍ő吔

	LPD3DXFONT m_pFont;			// �t�H���g
	std::string m_str;			// ������
};

#endif	// _DEBUG_PROC_H_