//=============================================================================
//
// sound.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SOUND_H
#define SOUND_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xaudio2.h"					// ���y�����ɕK�v

//���N���X
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

	CSound();								//�R���X�g���N�^
	~CSound();								//�f�X�g���N�^

	HRESULT Init(HWND hWnd);				//����������
	void Uninit(void);						//�I������
	HRESULT Play(SOUND_LABEL label);		//�Đ�����
	void Stop(SOUND_LABEL label);			//��~����
	void Stop(void);						//��~����

	static CSound* Create(HWND hWnd);		//��������

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
#endif