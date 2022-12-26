//=============================================================================
//
// block.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Object2D.h"

//---------------------------
// クラス宣言
//---------------------------
class CBlock : public CObject_2D
{
public:

	CBlock();
	CBlock(const int nPriority);
	~CBlock() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Input();

	static CBlock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
private:

};

#endif // !_PLAYER_H_
