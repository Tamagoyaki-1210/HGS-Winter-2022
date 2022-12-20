//=============================================================================
//
// score.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
// 前方宣言
//---------------------------
class CNumber;

//---------------------------
// クラス宣言
//---------------------------
class CScore
{
public:
	CScore();
	~CScore();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetScore();
	void AddScore(int nValue);
	static CScore *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
private:
	static const int Max_Digit = 8;			// スコアの桁数
	static const int Max_Score = 99999999;	// スコアの最大数

	int m_nScore;						// スコアの値
	CNumber *m_apNumber[Max_Digit];		// 数値のポインタ
};

#endif // !_SCORE_H_
