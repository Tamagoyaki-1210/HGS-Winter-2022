//=============================================================================
//
// sound.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>
#include "xaudio2.h"	// ���y�����ɕK�v

//---------------------------
// �N���X�錾
//---------------------------
class CSound
{
public:

	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_RESULT,

		SOUND_LABEL_SE_SELECT,
		SOUND_LABEL_SE_YES,
		SOUND_LABEL_SE_JUMP,

		SOUND_LABEL_MAX
	};

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(SOUND_LABEL label);	// �Ȃ̍Đ�����
	void Stop(SOUND_LABEL label);		// �Ȃ̒�~����
	void Stop();						// �Ȃ̒�~����

	static CSound* Create(HWND hWnd);

private:

	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static SOUNDPARAM g_aParam[SOUND_LABEL_MAX];

	IXAudio2 *g_pXAudio2 = nullptr;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *g_pMasteringVoice = nullptr;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};

#endif // !_SOUND_H