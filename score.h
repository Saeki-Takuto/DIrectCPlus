//==================================================================
//
//�G���� [score.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SCORE_H_					//���̃}�N����`������ĂȂ�������
#define _SCORE_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "number.h"

//================================================
//�}�N����`
//================================================
#define SCORE_PRIORITY (7)		//�G�̗D��x

//================================================
//�N���X
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
		int digit,          // ����
		int value,
		const D3DXVECTOR2& center,
		float width = 30.0f,      // ���̕�
		float height = 50.0f,     // ���̍���
		float spacing = 4.0f       // ���Ԃ̃X�y�[�X
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