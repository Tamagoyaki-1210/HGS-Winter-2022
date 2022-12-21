﻿//=============================================================================
//
// texture.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "application.h"

LPDIRECT3DTEXTURE9 CTexture::m_pTextureType[TEXTURE_MAX] = {};

// 画像のパスを設定
char* CTexture::m_pTexturePass[TEXTURE_MAX] =
{
    " ",

    "data\\TEXTURE\\Font\\Japanese2000unicode.png",
    "data\\TEXTURE\\Number\\number000.png",

};

//=====================================
// デフォルトコンストラクタ
//=====================================
CTexture::CTexture()
{

}

//=====================================
// デストラクタ
//=====================================
CTexture::~CTexture()
{

}

//=====================================
// 全ての画像の解放処理
//=====================================
void CTexture::ReleaseAll()
{
    for (int nInd = 0; nInd < TEXTURE_MAX; nInd++)
    {
        if (m_pTextureType[nInd] != nullptr)
        {
            m_pTextureType[nInd]->Release();
            m_pTextureType[nInd] = nullptr;
        }
    }
}

//=====================================
// 全ての画像の読み込み処理
//=====================================
void CTexture::LoadAll()
{
    LPDIRECT3DDEVICE9 pDevice = g_pApplication->GetRenderer()->GetDevice();

    for (int nInd = 0; nInd < TEXTURE_MAX; nInd++)
    {
        if (m_pTextureType[nInd] != nullptr)
        {
            m_pTextureType[nInd]->Release();
            m_pTextureType[nInd] = nullptr;
        }

        // テクスチャの読み込み
        D3DXCreateTextureFromFile(pDevice,
            m_pTexturePass[nInd],
            &m_pTextureType[nInd]);
    }
}

//=====================================
// 画像種類の取得処理
//=====================================
void CTexture::GetTextureType(Texture_Type textype)
{
    //テクスチャの設定
    g_pApplication->GetRenderer()->GetDevice()->SetTexture(0, m_pTextureType[textype]);
}

//=====================================
// 画像の解放処理
//=====================================
void CTexture::TextureClear()
{
    //テクスチャの設定
    g_pApplication->GetRenderer()->GetDevice()->SetTexture(0, nullptr);
}