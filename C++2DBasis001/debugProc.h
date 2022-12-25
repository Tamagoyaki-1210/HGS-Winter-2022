//=============================================================================
//
// debugProc.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include <d3dx9.h>
#include <stdarg.h>
#include <string>

//---------------------------
// クラス宣言
//---------------------------
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
														
	HRESULT Init();
	void Uninit();
														
	void Print(const char *pFormat, ...);		// 文字の入力処理
	void Draw();

	static CDebugProc* Create();

private:
	static const int Str_Max = 2048;	// 文字の最大数

	LPD3DXFONT m_pFont;			// フォント
	std::string m_str;			// 文字列
};

#endif	// _DEBUG_PROC_H_