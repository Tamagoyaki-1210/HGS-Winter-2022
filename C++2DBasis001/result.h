//=============================================================================
//
// result.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"

//---------------------------
// �N���X�錾
//---------------------------
class CResult : public CMode
{
public:
	CResult();
	~CResult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void Input();

	static CResult* Create();
private:

};

#endif // !_RESULT_H_