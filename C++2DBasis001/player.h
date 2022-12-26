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
	enum Player_Motion
	{
		MOTION_NONE,
		MOTION_WARK,
		MOTION_JUMP,
		MOTION_MAX
	};


	CPlayer();
	CPlayer(const int nPriority);
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Input();
	void PlayerCollision();
	void Motion();

	const D3DXVECTOR3& GetMove() const { return m_move; }

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
private:
	const float Fast_Player_Speed = 1.0f;
	const float Jump_Power = 40.0f;

	float m_gravity = 1.0f;
	bool m_IsGravityReversal = true;
	int m_nFrame;
	int m_nSave;
	D3DXVECTOR3 m_move;			// �ړ���
	float		m_fMoveSpeed;	// �ړ����x
	bool		m_bCollision;	// �ڐG����
	bool		m_bJump;		// �W�����v����
	Player_Motion m_motion;		// ���[�V����
};

#endif // !_PLAYER_H_
