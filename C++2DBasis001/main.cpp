﻿//=============================================================================
//
// main.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include <Windows.h>
#include "application.h"
#include "debugProc.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace
{
    // ウインドウのクラス名
    LPCTSTR CLASS_NAME = _T("AppClass");
    // ウインドウのキャプション名
    LPCTSTR WINDOW_NAME = _T("2Dゲーム制作中");
}

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
#ifdef _DEBUG
// FPSカウンタ
int g_nCountFPS;
#endif // _DEBUG

//--------------------------------
// 静的変数
//--------------------------------
static bool s_bExit;

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE/* hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        CLASS_NAME,
        NULL
    };

    // ウィンドウクラスの登録
    RegisterClassEx(&wcex);

    RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    // 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    // ウィンドウの作成
    HWND hWnd = CreateWindow(CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (rect.right - rect.left),
        (rect.bottom - rect.top),
        NULL,
        NULL,
        hInstance,
        NULL);

    // アプリケーションの生成
    CApplication* pApplication = CApplication::GetInstance();

    if (FAILED(pApplication->Init(hInstance, hWnd)))
    {
        return -1;
    }

    // 分解能を設定
    timeBeginPeriod(1);

    // フレームカウント初期化
    DWORD dwCurrentTime = 0;
    DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
    DWORD dwFrameCount = 0;
    DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

    // ウインドウの表示
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    // メッセージループ
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            { // PostQuitMessage()が呼ばれたらループ終了
                break;
            }
            else
            {
                // メッセージの翻訳とディスパッチ
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            dwCurrentTime = timeGetTime();	// 現在の時間を取得
#ifdef _DEBUG
            if ((dwCurrentTime - dwFPSLastTime) >= 500)
            {// 0.5秒ごとに実行
             // FPSを算出
                g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
                dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
                dwFrameCount = 0;
            }
#endif // _DEBUG

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
            { // 1/60秒経過
              // 現在の時間を保存
                dwExecLastTime = dwCurrentTime;

                if (pApplication != nullptr)
                {
                    // 更新処理
					pApplication->Update();

                    // 描画処理
					pApplication->Draw();
                }

#ifdef _DEBUG
                dwFrameCount++;
#endif // _DEBUG
                if (s_bExit)
                {
                    break;	//ウインドウを破棄する
                }
            }
        }
    }

    if (pApplication != nullptr)
    {
		pApplication->Uninit();
		pApplication = nullptr;
    }

    // ウィンドウクラスの登録を解除
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    // 分解能を戻す
    timeEndPeriod(1);

    return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (s_bExit)
    {
        // ウィンドウを破棄する
        DestroyWindow(hWnd);
    }

    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE: // [ESC]キーが押された
            // ウィンドウを破棄
            DestroyWindow(hWnd);
            break;
        }
        break;

    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=====================================
// Windowの終了処理
//=====================================
void ExitExe()
{
    s_bExit = true;
}

#ifdef _DEBUG

//=====================================
// FPSの取得処理
//=====================================
int GetFPS()
{
    return g_nCountFPS;
}
#endif // _DEBUG