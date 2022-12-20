//=============================================================================
//
// game.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "game.h"
#include "application.h"
#include "object2D.h"
#include "fontString.h"
#include "inputKeyboard.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CGame::CGame()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGame::~CGame()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGame::Init()
{
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

	CObject_2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(100,100));

	CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), D3DXVECTOR2(80, 80), "�Q�[��");

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CGame::Uninit()
{

}

//=====================================
// �X�V����
//=====================================
void CGame::Update()
{
	Input();
}

//=====================================
// ���͏���
//=====================================
void CGame::Input()
{
	// P�Ń|�[�Y�؂�ւ�
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::Mode_Result);
	}
}

//=====================================
// ��������
//=====================================
CGame* CGame::Create()
{
	CGame* pGame = new CGame;

	if (FAILED(pGame->Init()))
	{
		return nullptr;
	}

	return pGame;
}