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
#include <vector>

class CPlayer;
class CLevel;
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

	static CPlayer* GetPlayer() { return m_pPlayer; }

	static CGame* Create();
private:
	CLevel* m_pLevel;
	static CPlayer* m_pPlayer;
};

#endif // !_GAME_H_
