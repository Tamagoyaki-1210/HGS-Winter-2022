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
class CInputInterface;
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


    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit();
    void Update();
    void Draw();

    CRenderer* GetRenderer() const { return m_pRenderer; }	// レンダラーの取得処理
    CTexture* GetTexture() const { return m_pTexture; }		// 画像の取得処理
    CSound* GetSound() const { return m_pSound; }			// サウンドの取得処理
    CFade* GetFade() const { return m_pFade; }				// フェードの取得処理
    CInputInterface* GetInput() const { return m_pInput; }
	CDebugProc* GetDebugProc() const { return m_pDebugProc; }

    Mode GetMode() const { return m_mode; }					// モードの取得処理
    void SetMode(Mode mode);								// モードの設定処理
    void ChangeMode();										// モードの変更処理

	// applicationのシングルトン
	static CApplication* GetInstance()
	{ 
		// ポインタが未使用の場合
		if (!m_pApplication) m_pApplication = new CApplication;
		return m_pApplication;
	}

private:
    CApplication();
    ~CApplication();

    CRenderer* m_pRenderer;
    CTexture* m_pTexture;
    CSound* m_pSound;
    CFade* m_pFade;
    CMode* m_pMode;
    CDebugProc* m_pDebugProc;
    CInputInterface* m_pInput;

    Mode	m_mode;		//現在モード
    Mode m_modeNext;	//次のモード

	static CApplication* m_pApplication;
};

#endif // !_APPLICATION_H_
