//=============================================================================
//
// result.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mode.h"

//---------------------------
// クラス宣言
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