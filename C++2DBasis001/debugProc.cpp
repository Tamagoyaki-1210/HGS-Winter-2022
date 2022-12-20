//=============================================================================
//
// debugProc.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "debugProc.h"
#include "application.h"
#include "renderer.h"
#include "main.h"

LPD3DXFONT CDebugProc::m_pFont = nullptr;
std::string CDebugProc::m_str = "";

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CDebugProc::CDebugProc()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CDebugProc::~CDebugProc()
{

}

//============================================================================
// ����������
//============================================================================
HRESULT CDebugProc::Init()
{
	//����������
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CDebugProc::Uninit()
{
	//�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		delete m_pFont;
		m_pFont = nullptr;
	}
}

//============================================================================
// �����̓��͏���
//============================================================================
void CDebugProc::Print(const char *pFormat, ...)
{
	va_list args;

	va_start(args, pFormat);

	// ������̍Ō�܂œǂݍ��ޏ���
	for (const char* pPointer = pFormat; *pPointer != '\0'; pPointer++)
	{
		// %�ł͖����ꍇ������ɒǉ�����
		if (*pPointer != '%')
		{
			m_str += *pPointer;
		}
		else
		{
			pPointer++;	// �|�C���^��i�߂�

			// ���̕����̎�ނŌ^�����߂鏈��
			switch (*pPointer)
			{

			case 'd':
			{
				m_str += std::to_string(va_arg(args, int));
			}
			break;

			case 'f':
			{
				m_str += std::to_string(va_arg(args, double));
			}
			break;

			case 'c':
			{
				m_str += std::to_string(va_arg(args, char));
			}
			break;

			case 's':
			{
				m_str += va_arg(args, char*);
			}
			break;

			default:
			{
				m_str += '%';
				m_str += *pPointer;
			}
			break;

			}
		}
	}

	va_end(args);
}

//============================================================================
// �`�揈��
//============================================================================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	TCHAR str[Str_Max];

	// �����񂪍ő啶������菭�Ȃ��ꍇ������
	if (m_str.length() < Str_Max)
	{
		sprintf(str, _T(m_str.c_str()));

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	m_str.clear();
}

//============================================================================
// ��������
//============================================================================
CDebugProc* CDebugProc::Create()
{
	CDebugProc* pDebug = new CDebugProc;

	// ����������
	if (FAILED(pDebug->Init()))
	{
		return nullptr;
	}

	return pDebug;
}