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
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// サウンドの情報
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
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ


};

#endif