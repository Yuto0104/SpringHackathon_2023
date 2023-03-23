//=============================================================================
//
// sound.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SOUND_H
#define SOUND_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xaudio2.h"					// 音楽処理に必要

//音クラス
class CSound
{
public:

	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_BGM000 = 0,
		SOUND_LABEL_BGM_BGM001,
		SOUND_LABEL_BGM_BGM002,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_SE_ATTACK,
		SOUND_LABEL_SE_ENTER,
		SOUND_LABEL_SE_EXPLOSION,
		SOUND_LABEL_SE_HIT,
		SOUND_LABEL_MAX
	};

	CSound();								//コンストラクタ
	~CSound();								//デストラクタ

	HRESULT Init(HWND hWnd);				//初期化処理
	void Uninit(void);						//終了処理
	HRESULT Play(SOUND_LABEL label);		//再生処理
	void Stop(SOUND_LABEL label);			//停止処理
	void Stop(void);						//停止処理

	static CSound* Create(HWND hWnd);		//生成処理

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
#endif