//=============================================================================
//
// game.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mode.h"

//---------------------------
// クラス宣言
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

};

#endif // !_GAME_H_
