//=============================================================================
//
// texture.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
// クラス宣言
//---------------------------
class CTexture
{
public:
	enum Texture_Type
	{
		TEXTURE_NULL = 0,
		TEXTURE_JAPANESE,		//日本語フォント
		TEXTURE_NUMBER,			//数字フォント
		TEXTURE_PLAYER,			//プレイヤー
		TEXTURE_GOAL,			//ゴール
		TEXTURE_BLOCK,			//ブロック
		TEXTURE_THRON,			//棘
		TEXTURE_UPBLOCK,		//上ブロック
		TEXTURE_DOWNBLOCK,		//下ブロック
		TEXTURE_WOODCRATE,		//木箱
		TEXTURE_SPACEBG,		//宇宙の背景
		TEXTURE_BG,				//ゲームの背景
		TEXTURE_MAX
	};

	CTexture();
	~CTexture();

	static void ReleaseAll();								// 全ての画像の解放処理
	static void LoadAll();									// 全ての画像の読み込み処理
	static void GetTextureType(Texture_Type textType);		// 画像の種類取得処理
	static void TextureClear();								// 画像の解放処理

private:
	static LPDIRECT3DTEXTURE9 m_pTextureType[TEXTURE_MAX];	// 画像オブジェクトへのポインタ
	static char* m_pTexturePass[TEXTURE_MAX];				// 画像のパス
};

#endif // !_TEXTURE_H_
