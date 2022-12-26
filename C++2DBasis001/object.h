//=============================================================================
//
// object.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//---------------------------
// クラス宣言
//---------------------------
class CObject
{
public:
	enum Priority_Type
	{
		PRIORITY_NULL = 0,
		PRIORITY_BACK,			// 背景
		PRIORITY_CENTER,		// 中央
		PRIORITY_FRONT,			// 前景
		PRIORITY_UI,			// UI
		PRIORITY_MAX
	};

	CObject();
	CObject(int priority);
	virtual ~CObject();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void Release();

	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetPriority(int nPriority);				// 描画順の設定処理

	virtual const D3DXVECTOR3& GetPos() const = 0;
	virtual const D3DXVECTOR3& GetPosOld() const = 0;
	virtual const D3DXVECTOR3& GetRot() const = 0;
	virtual const D3DXVECTOR2& GetSize() const = 0;
	virtual const bool& GetCollision() const = 0;

	CObject* GetNext() { return m_pNext; }
	CObject* GetTop() { return m_pTop[PRIORITY_CENTER]; }

	void SetIsCollision(bool IsCollision) { m_IsCollision = IsCollision; }

protected:
	bool m_IsCollision;

private:

	int m_nPriority;								// 描画順
	bool m_bDeath;									// 死亡フラグの判定
	static CObject* m_pTop[PRIORITY_MAX];			// 先頭オブジェクトへのポインタ
	static CObject* m_pCurrent[PRIORITY_MAX];		// 最後の(現在)オブジェクトへのポインタ
	CObject* m_pPrev;								// 前回のオブジェクトへのポインタ
	CObject* m_pNext;								// 次回のオブジェクトへのポインタ
};

#endif // !_OBJECT_H_