//=============================================================================
//
// texture.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "application.h"

LPDIRECT3DTEXTURE9 CTexture::m_pTextureType[TEXTURE_MAX] = {};

// �摜�̃p�X��ݒ�
char* CTexture::m_pTexturePass[TEXTURE_MAX] =
{
	" ",

	"data\\TEXTURE\\Font\\Japanese2000unicode.png",
	"data\\TEXTURE\\Number\\number000.png",

};

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CTexture::CTexture()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CTexture::~CTexture()
{

}

//=====================================
// �S�Ẳ摜�̉������
//=====================================
void CTexture::ReleaseAll()
{
	for (int nInd = 0; nInd < TEXTURE_MAX; nInd++)
	{
		if (m_pTextureType[nInd] != nullptr)
		{
			m_pTextureType[nInd]->Release();
			m_pTextureType[nInd] = nullptr;
		}
	}
}

//=====================================
// �S�Ẳ摜�̓ǂݍ��ݏ���
//=====================================
void CTexture::LoadAll()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int nInd = 0; nInd < TEXTURE_MAX; nInd++)
	{
		if (m_pTextureType[nInd] != nullptr)
		{
			m_pTextureType[nInd]->Release();
			m_pTextureType[nInd] = nullptr;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_pTexturePass[nInd],
			&m_pTextureType[nInd]);
	}
}

//=====================================
// �摜��ނ̎擾����
//=====================================
void CTexture::GetTextureType(Texture_Type textype)
{
	//�e�N�X�`���̐ݒ�
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, m_pTextureType[textype]);
}

//=====================================
// �摜�̉������
//=====================================
void CTexture::TextureClear()
{
	//�e�N�X�`���̐ݒ�
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, nullptr);
}