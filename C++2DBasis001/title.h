//=============================================================================
//
// title.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"
#include <vector>

//---------------------------
// �O���錾
//---------------------------
class CObject_2D;

//---------------------------
// �N���X�錾
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