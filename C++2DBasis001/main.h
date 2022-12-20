//=========================================
// 
// main.h
// Author: Tanimoto Kosuke
// 
//=========================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>
#include <tchar.h> // _T

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define	DEBUG_NEW	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;

const D3DXVECTOR2 Vec2Null = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR3 Vec3Null = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXCOLOR ColorNull = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

int GetFPS();	// FPSの取得処理

#endif // !MAIN_H