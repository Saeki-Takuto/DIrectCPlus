//==================================================================
//
//敵処理 [score.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SCORE_H_					//このマクロ定義がされてなかったら
#define _SCORE_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "number.h"

//================================================
//マクロ定義
//================================================
#define SCORE_PRIORITY (7)		//敵の優先度

//================================================
//クラス
//================================================
class CScore :public CNumber
{
public:
    CScore(int nPriority);
    ~CScore();

    typedef enum
    {
        SCORE_TYPE_NONE = 0,
        SCORE_TYPE_NORMAL_01,
        SCORE_TYPE_NORMAL_02,
        SCORE_TYPE_MAX
    }SCORE_TYPE;

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

	static CScore* Create(
		SCORE_TYPE scoreType,
		int digit,          // 桁数
		int value,
		const D3DXVECTOR2& center,
		float width = 30.0f,      // 桁の幅
		float height = 50.0f,     // 桁の高さ
		float spacing = 4.0f       // 桁間のスペース
	);

    static HRESULT Load(void);
    static void Unload(void);

	int GetValue() const { return m_value; }
	void SetValue(int value) { m_value = value; }
    void AddScore(int value);

    SCORE_TYPE GetScoreType() const { return m_scoreType; }
    void SetScoreType(SCORE_TYPE type) { m_scoreType = type; }

    typedef struct
    {
    }Score;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture[SCORE_TYPE_MAX];
    SCORE_TYPE m_scoreType;
	int m_value;
    Score m_Score;
};

#endif