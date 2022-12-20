//=============================================================================
//
// application.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputPad.h"
#include "texture.h"
#include "fade.h"
#include "mode.h"
#include "object.h"
#include "debugProc.h"
#include "title.h"
#include "game.h"
#include "result.h"

CRenderer *CApplication::m_pRenderer = nullptr;	// �����_���[�|�C���^
CInput *CApplication::m_pInput[Input_Max] = {};	// ���̓|�C���^
CTexture *CApplication::m_pTexture = nullptr;	// �摜�|�C���^
CMode *CApplication::m_pMode = nullptr;			// ���[�h�|�C���^
CSound *CApplication::m_pSound = nullptr;		// �T�E���h�|�C���^
CFade* CApplication::m_pFade = nullptr;			// �t�F�[�h�|�C���^
CDebugProc* CApplication::m_pDebug = nullptr;	// �f�o�b�O�|�C���^

CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;			//���[�h
CApplication::Mode CApplication::m_modeNext = CApplication::Mode_Title;		//���̃��[�h

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CApplication::CApplication()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CApplication::~CApplication()
{

}

//=====================================
// ����������
//=====================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
	}

	// true : �E�B���h�E�T�C�Y, false : �S���
	if (FAILED(m_pRenderer->Init(hWnd, true)))
	{
		return -1;
	}

	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
		
		//�S�Ẳ摜�̓ǂݍ��ݏ���
		m_pTexture->LoadAll();
	}

	if (m_pDebug == nullptr)
	{
		m_pDebug = CDebugProc::Create();
	}

	if (m_pSound == nullptr)
	{
		m_pSound = CSound::Create(hWnd);
	}

	if (m_pMode == nullptr)
	{
		// �ŏ��̃��[�h
		m_pMode = CTitle::Create();
		m_mode = Mode_Title;
		m_modeNext = Mode_Title;
	}

	if (m_pFade == nullptr)
	{
		// �t�F�[�h����
		m_pFade = CFade::Create();
		m_pFade->SetFade();
	}

	// �C���v�b�g�f�o�C�X�̐���
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] == nullptr)
		{
			// ��ʖ��̐ݒ�
			switch ((Input_type)nCnt)
			{
			case CApplication::Input_Keyboard:
				// �L�[�{�[�h�C���X�^���X�̐���
				m_pInput[nCnt] = new CInputKeyboard;
				break;

			case CApplication::Input_Pad:
				// �p�b�h�C���X�^���X�̐���
				m_pInput[nCnt] = new CInputPad;
				break;

			case CApplication::Input_Mouse:
				// �}�E�X�C���X�^���X�̐���
				m_pInput[nCnt] = new CInputMouse;
				break;

			default:
				break;
			}

			// �C���v�b�g�f�o�C�X�̏���������
			if (FAILED(m_pInput[nCnt]->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CApplication::Uninit()
{
	// �����_�����O�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// ���[�h�̔j��
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// �C���v�b�g�f�o�C�X�̔j��
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//�t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// �f�o�b�O�e�L�X�g�̔j��
	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	// �I�u�W�F�N�g�S�̂̏I��
	CObject::ReleaseAll();

	// �摜�̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CApplication::Update()
{
	// �C���v�b�g�f�o�C�X�̍X�V����
	for (int nCnt = 0; nCnt < Input_Max; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// �t�F�[�h�̍X�V����
	if (m_pFade != nullptr)
	{
		// �t�F�[�h���ǂݍ��܂�Ă��Ȃ��ꍇ
		if (m_pFade->GetFade() != CFade::FADE_NONE)
		{
			m_pFade->Update();

			if (m_pFade->GetFade() == CFade::FADE_CHANGE)
			{// �t�F�[�h�؂�ւ���Ԃ̏ꍇ
				ChangeMode();
			}
		}
	}

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}
}

//=====================================
// �`�揈��
//=====================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}


//=====================================
// ���[�h�ݒ菈��
//=====================================
void CApplication::SetMode(Mode mode)
{
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		m_modeNext = mode;
		m_pFade->SetFade();
	}
}

//=====================================
// ���[�h�؂�ւ�����
//=====================================
void CApplication::ChangeMode()
{
	// ���݃��[�h�̏I��
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	CObject::ReleaseAll();	// �S�ẴI�u�W�F�N�g�̏I��

	if (m_pSound != nullptr)
	{// �g�p���̃T�E���h��~
		m_pSound->Stop();
	}

	// ���[�h�𐶐�����
	switch (m_modeNext)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		break;

	case CApplication::Mode_Game:
		m_pMode = CGame::Create();
		break;

	case CApplication::Mode_Result:
		m_pMode = CResult::Create();
		break;

	default:
		break;
	}
	m_mode = m_modeNext;	// ���̃��[�h�ɕύX
}
