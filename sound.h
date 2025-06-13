//==================================================================
//
//�T�E���h���� [sound.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SOUND_H_					//���̃}�N����`������ĂȂ�������
#define _SOUND_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "d3dx9.h"
#include "xaudio2.h"//�T�E���h�����ɕK�v

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//================================================
//�N���X
//================================================
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_LABEL_BGM01 = 0,
		SOUND_LABEL_BGM02,
		SOUND_LABEL_BGM03,
		SOUND_LABEL_BGM04,
		SOUND_LABEL_BGM05,
		SOUND_LABEL_BGM06,
		SOUND_LABEL_SE01,
		SOUND_LABEL_SE02,
		SOUND_LABEL_SE03,
		SOUND_LABEL_SE04,
		SOUND_LABEL_SE05,
		SOUND_LABEL_SE06,
		SOUND_LABEL_SE07,
		SOUND_LABEL_SE08,
		SOUND_LABEL_SE09,
		SOUND_LABEL_SE10,
		SOUND_LABEL_SE11,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/title002.wav", -1},      //BGM1
		{"data/BGM/result001.wav", -1},     //BGM2
		{"data/BGM/game000.wav", -1},       //BGM3
		{"data/BGM/CLEAR.wav", 0},			//BGM4
		{"data/BGM/GAMEOVER.wav", 0},       //BGM5
		{"data/BGM/tutorial.wav", 0},       //BGM6
		{"data/SE/Click.wav", 0},           //SE1
		{"data/SE/Error.wav", 0},           //SE2
		{"data/SE/Dong.wav", 0},            //SE3
		{"data/SE/PauseStart.wav", 0},      //SE4
		{"data/SE/PauseEnd.wav", 0},        //SE5
		{"data/SE/SelectUP.wav", 0},        //SE6
		{"data/SE/SelectDown.wav", 0},      //SE7
		{"data/SE/Boot.wav", 0},			//SE8
		{"data/SE/Error1.wav", 0},			//SE9
		{"data/SE/Denger.wav", 0},			//SE10
		{"data/SE/OUT.wav", 0},			//SE11
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y


};

#endif