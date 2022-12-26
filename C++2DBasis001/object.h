//=============================================================================
//
// object.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
// �N���X�錾
//---------------------------
class CObject
{
public:
	enum Priority_Type
	{
		PRIORITY_NULL = 0,
		PRIORITY_BACK,			// �w�i
		PRIORITY_CENTER,		// ����
		PRIORITY_FRONT,			// �O�i
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

	void SetPriority(int nPriority);				// �`�揇�̐ݒ菈��

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

	int m_nPriority;								// �`�揇
	bool m_bDeath;									// ���S�t���O�̔���
	static CObject* m_pTop[PRIORITY_MAX];			// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_pCurrent[PRIORITY_MAX];		// �Ō��(����)�I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pPrev;								// �O��̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;								// ����̃I�u�W�F�N�g�ւ̃|�C���^
};

#endif // !_OBJECT_H_