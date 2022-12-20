//=============================================================================
//
// score.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
// �O���錾
//---------------------------
class CNumber;

//---------------------------
// �N���X�錾
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
	static const int Max_Digit = 8;			// �X�R�A�̌���
	static const int Max_Score = 99999999;	// �X�R�A�̍ő吔

	int m_nScore;						// �X�R�A�̒l
	CNumber *m_apNumber[Max_Digit];		// ���l�̃|�C���^
};

#endif // !_SCORE_H_
