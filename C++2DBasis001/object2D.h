//=============================================================================
//
// object2D.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"

//---------------------------
// �N���X�錾
//---------------------------
class CObject_2D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// �I�u�W�F�N�g2D�\����
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			// xyz���W
		float rhw;					// rhw
		D3DCOLOR col;				// �J�[���[
		D3DXVECTOR2 tex;			// �e�N�X�`�����W
	};

	CObject_2D();
	CObject_2D(const int nPriority);
	virtual ~CObject_2D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	
	D3DXVECTOR3 Collision(CObject* obj);

	void SetUV();
	void SetAnimAuto(int nSpeed);
	void SetAnimControl(int nAnimColumn, int nAnimLine);
	void SetAnimControl(int nAnimCounter);
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCollision(bool collision) { m_bCollision = collision; }
	void SetSize(const D3DXVECTOR2 size);
	void SetAnimDiv(int nDivX, int nDivY);

	void SetTexture(CTexture::Texture_Type textType) { m_textType = textType; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetPosOld() const { return m_posOld; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXVECTOR2& GetSize() const { return m_size; }
	const bool& GetCollision() const { return m_bCollision; }

	static CObject_2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// Buffer�I�u�W�F�N�g
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_posOld;				// �O��ʒu
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR2 m_size;					// �g���
	float m_fAngle;						// �p�x(�A�[�N�^���W�F���g)

	int m_nAnimColumn;					// �摜�A�j���[�V�����̗�
	int m_nAnimLine;					// �摜�A�j���[�V�����̍s��
	int m_nAnimControl;					// �摜�A�j���[�V�����̐���
	int m_nAnimColumnDiv;				// �摜�A�j���[�V�����̗�敪
	int m_nAnimLineDiv;					// �摜�A�j���[�V�����̍s�敪

	bool m_bCollision;					// �����蔻��

	CTexture::Texture_Type m_textType;	// �e�L�X�g�^�C�v
};

#endif // !_OBJECT_2D_H_