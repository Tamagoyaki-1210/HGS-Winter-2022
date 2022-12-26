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

    pObj2D = CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR2(12800.0f, 720.0f));
    pObj2D->SetTexture((CTexture::TEXTURE_SPACEBG));
    m_pvObj2D.push_back(pObj2D);

    pObj2D = CObject_2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100.0f, 100.0f));
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

    const POINT pt = p_Input->GetMousePos();

    D3DXVECTOR3 MousePos = Vec3Null;
    MousePos.x = (float)pt.x;
    MousePos.y = (float)pt.y;

    // 位置計算用マトリクス
    D3DXVECTOR3 ObjPos;
    D3DXVECTOR2 ObjSize;

    float fLeft, fRight, fTop, fBottom;

    // 2Dオブジェクト毎の大きさを求める処理
    for (int nCnt = 0; nCnt < (int)m_pvObj2D.size(); nCnt++)
    {
        ObjPos = m_pvObj2D[nCnt]->GetPos();
        ObjSize = m_pvObj2D[nCnt]->GetSize();

        fLeft = ObjPos.x - ObjSize.x;
        fRight = ObjPos.x + ObjSize.x;
        fTop = ObjPos.y - ObjSize.y;
        fBottom = ObjPos.y + ObjSize.y;

        // オブジェクトとマウスが重なっている場合
        if (MousePos.x > fLeft && MousePos.x < fRight && MousePos.y > fTop && MousePos.y < fBottom)
        {
            // 左ボタンを話した時に移動
            if (p_Input->MouseButtonDown(MOUSE_LEFT_BUTTON, true))
            {
				CApplication::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
				CApplication::GetInstance()->SetMode(CApplication::Mode_Game);
            }
        }
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