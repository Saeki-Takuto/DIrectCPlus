#include "motion.h"

CMotion::CMotion()
{
	m_nType = MOTION_TYPE_NEUTRAL;
	m_nNumKey = 0;
	m_bLoop = false;
	m_nNumAll = 0;
	m_nType = 0;
	m_bLoop = false;
	m_nNumKey = 0;
	m_nKey = 0;
	m_nCounter = 0;
	m_bFinish = false;
	m_nNumModel = 0;

}

CMotion::~CMotion()
{
}

void CMotion::Set(int nType)
{
}

void CMotion::Update(void)
{
}

int CMotion::GetType(void)
{
	return 0;
}

bool CMotion::IsFinish(void)
{
	return false;
}

void CMotion::SetInfo(INFO info)
{
}

void CMotion::SetModel(CModel** ppModel, int nNumModel)
{
}
