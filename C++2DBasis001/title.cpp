//=============================================================================
//
// title.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "title.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "score.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CTitle::CTitle()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CTitle::~CTitle()
{

}

//=====================================
// ����������
//=====================================
HRESULT CTitle::Init()
{
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);
	
	CObject_2D* pObj2D = nullptr;

	pObj2D = CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100.0f, 100.0f));
	pObj2D->SetTexture((CTexture::Texture_Type)0);
	m_pvObj2D.push_back(pObj2D);

	pObj2D = CObject_2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100.0f, 100.0f));
	m_pvObj2D.push_back(pObj2D);

	CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80.0f, 80.0f), "�^�C�g��");

	CScore* pScore = CScore::Create(D3DXVECTOR3((float)SCREEN_WIDTH, SCREEN_HEIGHT / 12, 0.0f), D3DXVECTOR2(10.0f, 20.0f));
	pScore->AddScore(12345609);

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CTitle::Uninit()
{

}

//=====================================
// �X�V����
//=====================================
void CTitle::Update()
{
	Input();
}

//=====================================
// ���͏���
//=====================================
void CTitle::Input()
{
	// ���[�h�؂�ւ�
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
		CApplication::SetMode(CApplication::Mode_Game);
	}

	POINT pt = CInputMouse::GetPoint();

	D3DXVECTOR3 MousePos = Vec3Null;
	MousePos.x = (float)pt.x;
	MousePos.y = (float)pt.y;

	// �ʒu�v�Z�p�}�g���N�X
	D3DXVECTOR3 ObjPos;
	D3DXVECTOR2 ObjSize;

	float fLeft, fRight, fTop, fBottom;

	// 2D�I�u�W�F�N�g���̑傫�������߂鏈��
	for (int nCnt = 0; nCnt < (int)m_pvObj2D.size(); nCnt++)
	{
		ObjPos = m_pvObj2D[nCnt]->GetPos();
		ObjSize = m_pvObj2D[nCnt]->GetSize();

		fLeft = ObjPos.x - ObjSize.x;
		fRight = ObjPos.x + ObjSize.x;
		fTop = ObjPos.y - ObjSize.y;
		fBottom = ObjPos.y + ObjSize.y;

		// �I�u�W�F�N�g�ƃ}�E�X���d�Ȃ��Ă���ꍇ
		if (MousePos.x > fLeft && MousePos.x < fRight && MousePos.y > fTop&& MousePos.y < fBottom)
		{
			// ���{�^����b�������Ɉړ�
			if (CInputMouse::OnMouseUp(CInputMouse::MOUSE_LEFT))
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
				CApplication::SetMode(CApplication::Mode_Game);
			}
		}
	}
}

//=====================================
// ��������
//=====================================
CTitle* CTitle::Create()
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}