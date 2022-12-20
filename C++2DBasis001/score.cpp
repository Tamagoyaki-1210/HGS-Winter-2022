//=============================================================================
//
// score.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "score.h"
#include "application.h"
#include "number.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CScore::CScore()
{
	
}

//=====================================
// デストラクタ
//=====================================
CScore::~CScore()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CScore::Init()
{
	m_nScore = 0;

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CScore::Uninit()
{
	m_nScore = 0;

	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// ポインタの中身が使用中の場合
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}
}

//=====================================
// 更新処理
//=====================================
void CScore::Update()
{
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// ポインタの中身が使用中の場合
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Update();
		}
	}
}

//=====================================
// 描画処理
//=====================================
void CScore::Draw()
{
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// ポインタの中身が使用中の場合
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//=====================================
// 点数の設定処理
//=====================================
void CScore::SetScore()
{
	// 指定の桁の数値を抽出
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		// 計算(スコア % 10のべき乗 / ひとつ下の10のべき乗)
		int A = (int)pow(10.0f, (Max_Digit - nCnt));
		int B = (int)pow(10.0f, (Max_Digit - nCnt - 1));
		m_apNumber[nCnt]->SetNumber(m_nScore % A / B);
	}
}

//=====================================
// 点数の加算処理
//=====================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	if (m_nScore > Max_Score)
	{
		m_nScore = Max_Score;
	}

	SetScore();
}

//=====================================
// 生成処理
//=====================================
CScore *CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CScore* pScore = new CScore;

	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR2 halfSize = size / 2;	// 文字サイズの半分の大きさ

	// 文字位置の調整
	for (int nCnt = 0; nCnt < Max_Digit; nCnt++)
	{
		pScore->m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x - ( Max_Digit / 2 * ((halfSize.x / 2) + (halfSize.x * (Max_Digit - nCnt))) ), pos.y, 0.0f), size);
	}
	pScore->SetScore();	// スコアを設定する

	return pScore;
}