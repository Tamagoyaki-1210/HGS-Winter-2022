//=============================================================================
//
// title.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "title.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
#include "DirectInput.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CTitle::CTitle()
{

}

//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init()
{
	CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);

    CObject_2D* pObj2D = nullptr;

    pObj2D = CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100.0f, 100.0f));
    pObj2D->SetTexture((CTexture::Texture_Type)0);
    m_pvObj2D.push_back(pObj2D);

    CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80.0f, 80.0f), "タイトル");
    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CTitle::Uninit()
{

}

//=====================================
// 更新処理
//=====================================
void CTitle::Update()
{
    Input();
}

//=====================================
// 入力処理
//=====================================
void CTitle::Input()
{
    const auto p_Input = CApplication::GetInstance()->GetInput();

    // モード切り替え
    if (p_Input->KeyDown(DIK_RETURN, true) || p_Input->ControllerButtonDown(XINPUT_GAMEPAD_B, true))
    {
		CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
		CApplication::GetInstance()->SetMode(CApplication::Mode_Game);
    }
}

//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create()
{
    CTitle* pTitle = new CTitle;

    if (FAILED(pTitle->Init()))
    {
        return nullptr;
    }

    return pTitle;
}