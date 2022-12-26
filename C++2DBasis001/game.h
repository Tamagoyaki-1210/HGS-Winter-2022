//=============================================================================
//
// game.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"

class CLevel;

//---------------------------
// �N���X�錾
//---------------------------
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void Input();

	static CGame* Create();
private:
	CLevel* m_pLevel;

};

#endif // !_GAME_H_
