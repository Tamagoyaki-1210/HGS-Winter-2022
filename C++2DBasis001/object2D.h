//=============================================================================
//
// object2D.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "texture.h"

//---------------------------
// クラス宣言
//---------------------------
class CObject_2D : public CObject
{
public:
	// 頂点フォーマット
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// オブジェクト2D構造体
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			// xyz座標
		float rhw;					// rhw
		D3DCOLOR col;				// カーラー
		D3DXVECTOR2 tex;			// テクスチャ座標
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

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// Bufferオブジェクト
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_posOld;				// 前回位置
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR2 m_size;					// 拡大量
	float m_fAngle;						// 角度(アークタンジェント)

	int m_nAnimColumn;					// 画像アニメーションの列数
	int m_nAnimLine;					// 画像アニメーションの行数
	int m_nAnimControl;					// 画像アニメーションの制御
	int m_nAnimColumnDiv;				// 画像アニメーションの列区分
	int m_nAnimLineDiv;					// 画像アニメーションの行区分

	bool m_bCollision;					// 当たり判定

	CTexture::Texture_Type m_textType;	// テキストタイプ
};

#endif // !_OBJECT_2D_H_