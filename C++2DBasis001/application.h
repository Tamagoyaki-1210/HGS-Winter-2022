//=============================================================================
//
// application.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>
#include "sound.h"

//---------------------------
// 前方宣言
//---------------------------
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
class CSound;
class CDebugProc;

//---------------------------
// クラス宣言
//---------------------------
class CApplication
{
public:
	enum Mode
	{
		Mode_Title = 0,		// タイトル
		Mode_Game,			// ゲーム
		Mode_Result,		// リザルト

		Mode_Max
	};

	enum Input_type
	{
		Input_Keyboard = 0,	// キーボード
		Input_Pad,			// パッド
		Input_Mouse,		// マウス

		Input_Max
	};

	CApplication();
	~CApplication();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer* GetRenderer() { return m_pRenderer; }	// レンダラーの取得処理
	static CTexture* GetTexture() { return m_pTexture; }	// 画像の取得処理
	static CSound* GetSound() { return m_pSound; }			// サウンドの取得処理
	static CFade* GetFade() { return m_pFade; }				// フェードの取得処理

	static Mode GetMode() { return m_mode; }				// モードの取得処理
	static void SetMode(Mode mode);							// モードの設定処理
	void ChangeMode();										// モードの変更処理

private:
	static CRenderer*		m_pRenderer;
	static CInput*			m_pInput[Input_Max];
	static CTexture*		m_pTexture;
	static CSound*			m_pSound;
	static CFade*			m_pFade;
	static CMode*			m_pMode;
	static CDebugProc*		m_pDebug;

	static Mode	m_mode;		//現在モード
	static Mode m_modeNext;	//次のモード
};

#endif // !_APPLICATION_H_
