//=============================================================================
//
// texture.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
// �N���X�錾
//---------------------------
class CTexture
{
public:
	enum Texture_Type
	{
		TEXTURE_NULL = 0,
		TEXTURE_JAPANESE,		//���{��t�H���g
		TEXTURE_NUMBER,			//�����t�H���g
		TEXTURE_PLAYER,			//�v���C���[
		TEXTURE_GOAL,			//�S�[��
		TEXTURE_BLOCK,			//�u���b�N
		TEXTURE_THRON,			//��
		TEXTURE_UPBLOCK,		//��u���b�N
		TEXTURE_DOWNBLOCK,		//���u���b�N
		TEXTURE_WOODCRATE,		//�ؔ�
		TEXTURE_SPACEBG,		//�F���̔w�i
		TEXTURE_BG,				//�Q�[���̔w�i
		TEXTURE_MAX
	};

	CTexture();
	~CTexture();

	static void ReleaseAll();								// �S�Ẳ摜�̉������
	static void LoadAll();									// �S�Ẳ摜�̓ǂݍ��ݏ���
	static void GetTextureType(Texture_Type textType);		// �摜�̎�ގ擾����
	static void TextureClear();								// �摜�̉������

private:
	static LPDIRECT3DTEXTURE9 m_pTextureType[TEXTURE_MAX];	// �摜�I�u�W�F�N�g�ւ̃|�C���^
	static char* m_pTexturePass[TEXTURE_MAX];				// �摜�̃p�X
};

#endif // !_TEXTURE_H_
