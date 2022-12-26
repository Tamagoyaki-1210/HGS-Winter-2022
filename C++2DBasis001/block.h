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

	enum BlockType
	{
		NORMAL,
		BLOCK,
		GOAL,
		THORN,
		UPBLOCK,
		DOWNBLOCK,
		WOODCRATE
	};

	CBlock();
	CBlock(const int nPriority);
	~CBlock() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CBlock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const BlockType type);
private:
	BlockType m_type;
	D3DXVECTOR3 m_move;			// 移動量
};

#endif // !_PLAYER_H_
