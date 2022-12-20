//=============================================================================
//
// number.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "Object2D.h"

static const int Base_Number = 10;	//10�i��

//---------------------------
// �N���X�錾
//---------------------------
class CNumber : public CObject_2D
{
public:

	CNumber();
	CNumber(const int nPriority);
	~CNumber() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetNumber(int nScore);
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
private:
	
};

#endif // !_NUMBER_H_
