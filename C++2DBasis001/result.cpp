﻿//=============================================================================
//
// result.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "result.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
#include "DirectInput.h"
//=====================================
// デフォルトコンストラクタ
//=====================================
CResult::CResult()
{

}

//=====================================
// デストラクタ
//=====================================
CResult::~CResult()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CResult::Init()
{
    g_pApplication->GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);

    CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100, 100));

    CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80, 80), "リザルト");

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CResult::Uninit()
{

}

//=====================================
// 更新処理
//=====================================
void CResult::Update()
{
    Input();
}

//=====================================
// 入力処理
//=====================================
void CResult::Input()
{
    // モード切り替え

    if (g_pApplication->GetInput()->KeyDown(DIK_RETURN, true))
    {
        g_pApplication->SetMode(g_pApplication->Mode_Title);
    }
}

//=====================================
// 生成処理
//=====================================
CResult* CResult::Create()
{
    CResult* pResult = new CResult;

    if (FAILED(pResult->Init()))
    {
        return nullptr;
    }

    return pResult;
}