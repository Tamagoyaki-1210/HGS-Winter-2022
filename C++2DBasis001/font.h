//=============================================================================
//
// font.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _FONT_H
#define _FONT_H

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object2D.h"
#include <string>
#include <map>

//---------------------------
// クラス宣言
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
	static const int FontAnimColumn = 20;	// 日本語フォント画像の横区分
	static const int FontAnimLine = 10;		// 日本語フォント画像の縦区分
};

#endif // !_FONT_H
