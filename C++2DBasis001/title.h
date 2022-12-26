//=============================================================================
//
// title.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mode.h"
#include <vector>

//---------------------------
// 前方宣言
//---------------------------
class CObject_2D;

//---------------------------
// クラス宣言
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void Input();

	static CTitle* Create();
private:
	int m_nScrool;
	std::vector<CObject_2D*> m_pvObj2D;
};

#endif // !_TITLE_H_