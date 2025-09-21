//==================================================================
//
//サウンド処理 [sound.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SOUND_H_					//このマクロ定義がされてなかったら
#define _SOUND_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "d3dx9.h"
#include "xaudio2.h"//サウンド処理に必要

//================================================
//ライブラリのリンク
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//================================================
//クラス
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
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/TITLE.wav", -1},      //BGM1
		{"data/BGM/TUTO.wav", -1},     //BGM2
		{"data/BGM/GAME.wav", -1},       //BGM3
		{"data/BGM/RESULT.wav", -1},			//BGM4
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	IXAudio2* m_pXAudio2;									//XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				//マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	//ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					//オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					//オーディオデータサイズ
};

#endif