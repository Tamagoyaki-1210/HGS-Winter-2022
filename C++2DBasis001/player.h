//=============================================================================
//
// player.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "Object2D.h"

//---------------------------
// �N���X�錾
//---------------------------
class CPlayer : public CObject_2D
{
public:

	CPlayer();
	CPlayer(const int nPriority);
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Input();
	void PlayerCollision();

	const D3DXVECTOR3& GetMove() const { return m_move; }

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
private:
	const float Fast_Player_Speed = 1.0f;

	D3DXVECTOR3 m_move;			// �ړ���
	float		m_fMoveSpeed;	// �ړ����x
	bool		m_bCollision;	// �ڐG����
	bool		m_bJump;		// �W�����v����
};

#endif // !_PLAYER_H_
