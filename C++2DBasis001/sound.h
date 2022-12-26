//=============================================================================
//
// sound.h
// Author : Tanimoto Kosuke
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>
#include "xaudio2.h"	// 音楽処理に必要

//---------------------------
// クラス宣言
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
	HRESULT Play(SOUND_LABEL label);	// 曲の再生処理
	void Stop(SOUND_LABEL label);		// 曲の停止処理
	void Stop();						// 曲の停止処理

	static CSound* Create(HWND hWnd);

private:

	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static SOUNDPARAM g_aParam[SOUND_LABEL_MAX];

	IXAudio2 *g_pXAudio2 = nullptr;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice = nullptr;		// マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif // !_SOUND_H