//=============================================================================
//
// result.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "result.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
#include "inputKeyboard.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CResult::CResult()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CResult::~CResult()
{

}

//=====================================
// ����������
//=====================================
HRESULT CResult::Init()
{
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);

	CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100, 100));

	CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80, 80), "���U���g");

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CResult::Uninit()
{

}

//=====================================
// �X�V����
//=====================================
void CResult::Update()
{
	Input();
}

//=====================================
// ���͏���
//=====================================
void CResult::Input()
{
	// ���[�h�؂�ւ�
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::Mode_Title);
	}
}

//=====================================
// ��������
//=====================================
CResult* CResult::Create()
{
	CResult* pResult = new CResult;

	if (FAILED(pResult->Init()))
	{
		return nullptr;
	}

	return pResult;
}