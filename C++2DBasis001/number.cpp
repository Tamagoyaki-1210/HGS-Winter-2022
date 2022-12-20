//=============================================================================
//
// number.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "number.h"
#include "application.h"
#include "texture.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CNumber::CNumber() : CObject_2D()
{

}

//=====================================
// コンストラクタ
//=====================================
CNumber::CNumber(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// デストラクタ
//=====================================
CNumber::~CNumber()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CNumber::Init()
{
	// 基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CNumber::Uninit()
{
	CObject_2D::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CNumber::Update()
{
	CObject_2D::Update();
}

//=====================================
// 描画処理
//=====================================
void CNumber::Draw()
{
	CObject_2D::Draw();
}

//=====================================
// 点数の設定処理
//=====================================
void CNumber::SetNumber(int nScore)
{
	SetAnimControl(nScore);
}

//=====================================
// スコア生成処理
//=====================================
CNumber *CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CNumber* pNumber = new CNumber(PRIORITY_UI);

	if (FAILED(pNumber->Init()))
	{
		return nullptr;
	}

	pNumber->SetPos(pos);
	pNumber->SetSize(size);

	pNumber->SetTexture(CTexture::TEXTURE_NUMBER);		//テクスチャの設定
	pNumber->SetAnimDiv(Base_Number, 1);
	pNumber->SetAnimControl(0);

	return pNumber;
}