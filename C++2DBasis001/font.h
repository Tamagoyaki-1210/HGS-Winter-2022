//=============================================================================
//
// font.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _FONT_H
#define _FONT_H

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include <string>
#include <map>

//---------------------------
// �N���X�錾
//---------------------------
class CFont : public CObject_2D
{
public:
	CFont();
	CFont(const int nPriority);
	~CFont() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CFont* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* letter);

private:
	static const int FontAnimColumn = 20;	// ���{��t�H���g�摜�̉��敪
	static const int FontAnimLine = 10;		// ���{��t�H���g�摜�̏c�敪
};

#endif // !_FONT_H
