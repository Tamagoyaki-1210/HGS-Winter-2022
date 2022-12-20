//=============================================================================
//
// object.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "Application.h"

CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};

//=====================================
// デフォルトコンストラクタ
//=====================================
CObject::CObject() : m_bDeath(false)
{
	// 現在のオブジェクトが使用中の場合
	if (m_pCurrent[0] != nullptr)
	{
	 // 現在のオブジェクトが持つ次のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[0]->m_pNext = this;

		// 前のオブジェクトへのポインタに、現在のオブジェクトを設定する
		m_pPrev = m_pCurrent[0];

		// 現在のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[0] = this;
	}
	// 現在のオブジェクトが未使用の場合
	else
	{
	 // 先頭のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pTop[0] = this;

		// 現在のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[0] = this;

		// 前のオブジェクトへのポインタをnullにする
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;		// 次のオブジェクトへのポインタをnullにする
	m_nPriority = 0;		// 描画順を設定する
}

//=====================================
// コンストラクタ
//=====================================
CObject::CObject(int nPriority) : m_bDeath(false)
{
	// 現在のオブジェクトが使用中の場合
	if (m_pCurrent[nPriority] != nullptr)
	{
	 // 現在のオブジェクトが持つ次のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[nPriority]->m_pNext = this;

		// 前のオブジェクトへのポインタを設定する
		m_pPrev = m_pCurrent[nPriority];

		// 現在のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[nPriority] = this;
	}
	// 現在のオブジェクトが未使用の場合
	else
	{
	 // 先頭のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pTop[nPriority] = this;

		// 現在のオブジェクトへのポインタに、自身のアドレスを設定する
		m_pCurrent[nPriority] = this;

		// 前のオブジェクトへのポインタをnullにする
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;			// 次のオブジェクトへのポインタをnullにする
	m_nPriority = nPriority;	// 描画順を設定する
}

//=====================================
// デストラクタ
//=====================================
CObject::~CObject()
{
	
}

//=====================================
// 解放処理
//=====================================
void CObject::Release()
{
	m_bDeath = true;
}

//=====================================
// 全ての解放処理
//=====================================
void CObject::ReleaseAll()
{
	// 予め全てのオブジェクトを終了させる
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 先頭ポインタが使用中の場合
		if (m_pTop[nCnt] != nullptr)
		{
			// 現在位置ポインタに先頭ポインタを代入
			CObject *pCurrent = m_pTop[nCnt];

			// 現在位置ポインタが未使用になるまで
			while (pCurrent != nullptr)
			{
				pCurrent->Uninit();
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 先頭ポインタが使用中の場合
		if (m_pTop[nCnt] != nullptr)
		{
			// 現在位置ポインタに先頭ポインタを代入
			CObject *pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				// 現在のポインタが使用中の場合
				CObject *pNext = pCurrent->m_pNext;

				// 現在のポインタが持つ、前のポインタが使用中の場合
				if (pCurrent->m_pPrev != nullptr)
				{
					// 現在のポインタが持つ、次のポインタが使用中の場合
					if (pCurrent->m_pNext != nullptr)
					{
						pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
						pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
					}
					else
					{
						pCurrent->m_pPrev->m_pNext = nullptr;
						m_pCurrent[nCnt] = pCurrent->m_pPrev;
					}
				}
				else
				{
					// 現在のポインタが持つ、次のポインタが使用中の場合
					if (pCurrent->m_pNext != nullptr)
					{
						pCurrent->m_pNext->m_pPrev = nullptr;
						m_pTop[nCnt] = pCurrent->m_pNext;
					}
					else
					{
						m_pTop[nCnt] = nullptr;
						m_pCurrent[nCnt] = nullptr;
					}
				}
				delete pCurrent;		// メモリを解放する
				pCurrent = pNext;		// 現在のポインタに次のポインタを設定する
			}
		}
	}
}

//=====================================
// 全ての更新処理
//=====================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 先頭ポインタが使用中の場合
		if (m_pTop[nCnt] != nullptr)
		{
			// 現在位置ポインタに先頭ポインタを代入
			CObject *pCurrent = m_pTop[nCnt];

			// 現在位置ポインタが使用中の場合
			while (pCurrent != nullptr)
			{
				//死亡フラグが建っていない場合
				if (!pCurrent->m_bDeath)
				{
					pCurrent->Update();
				}
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 先頭ポインタが使用中の場合
		if (m_pTop[nCnt] != nullptr)
		{
			// 現在位置ポインタに先頭ポインタを代入
			CObject *pCurrent = m_pTop[nCnt];

			// 現在位置ポインタが使用中の場合
			while (pCurrent != nullptr)
			{
				CObject *pObjectNext = pCurrent->m_pNext;

				// 死亡フラグが建っている場合
				if (pCurrent->m_bDeath)
				{
					// 前回ポインタが使用中の場合
					if (pCurrent->m_pPrev != nullptr)
					{
						// 次回ポインタが使用中の場合
						if (pCurrent->m_pNext != nullptr)
						{
							pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
							pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
						}
						else
						{
							pCurrent->m_pPrev->m_pNext = nullptr;
							m_pCurrent[nCnt] = pCurrent->m_pPrev;
						}
					}
					else
					{
						// 次回ポインタが使用中の場合
						if (pCurrent->m_pNext != nullptr)
						{
							pCurrent->m_pNext->m_pPrev = nullptr;
							m_pTop[nCnt] = pCurrent->m_pNext;
						}
						else
						{
							m_pTop[nCnt] = nullptr;
							m_pCurrent[nCnt] = nullptr;
						}
					}
					delete pCurrent;
				}
				pCurrent = pObjectNext;
			}
		}
	}
}

//=====================================
// 全ての描画処理
//=====================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 先頭ポインタが使用中の場合
		if (m_pTop[nCnt] != nullptr)
		{
			// 現在位置ポインタに先頭ポインタを代入
			CObject *pCurrent = m_pTop[nCnt];

			// 現在位置ポインタが使用中の場合
			while (pCurrent != nullptr)
			{
				pCurrent->Draw();
				pCurrent = pCurrent->m_pNext;
			}
		}
	}
}

//=====================================
// 描画順の設定処理
//=====================================
void CObject::SetPriority(int nPriority)
{
	// 描画順が範囲外ではないように確認する
	if (nPriority < 0)
	{
		nPriority = 0;
	}
	else if (nPriority > PRIORITY_MAX)
	{
		nPriority = PRIORITY_MAX;
	}
}