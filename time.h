//==================================================================
//
//敵処理 [time.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _TIME_H_					//このマクロ定義がされてなかったら
#define _TIME_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "number.h"

//================================================
//マクロ定義
//================================================
#define TIME_PRIORITY (7)		//敵の優先度

//================================================
//クラス
//================================================
class CTime :public CNumber
{
public:
    CTime(int nPriority);
    ~CTime();

    typedef enum
    {
        TIME_TYPE_NONE = 0,
        TIME_TYPE_NORMAL_01,
        TIME_TYPE_NORMAL_02,
        TIME_TYPE_MAX
    }TIME_TYPE;

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

	static CTime* Create(
		TIME_TYPE timeType,
		int digit,          // 桁数
		int value,
		const D3DXVECTOR3& center,
		float width = 30.0f,      // 桁の幅
		float height = 50.0f,     // 桁の高さ
		float spacing = 4.0f       // 桁間のスペース
	);

    static HRESULT Load(void);
    static void Unload(void);

	//int GetValue() const { return m_value; }
	//void SetValue(int value) { m_value = value; }
    void AddTime(int value);

    TIME_TYPE GetTimeType() const { return m_timeType; }
    void SetTimeType(TIME_TYPE type) { m_timeType = type; }

    typedef struct
    {
    }Time;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture[TIME_TYPE_MAX];
    TIME_TYPE m_timeType;
	//int m_value;
    Time m_Time;
	int m_nCntTime;
};

#endif