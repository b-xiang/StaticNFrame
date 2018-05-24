#include "NFTimerObj.h"
#include "NFTimerMgr.h"

NFTimerObj::NFTimerObj() : m_pTimerInfoPtr(nullptr), m_pFixTimerInfoPtr(nullptr)
{
}

NFTimerObj::~NFTimerObj()
{
	NFTimerMgr::Instance()->KillAllTimer(this);
	NFTimerMgr::Instance()->KillAllFixTimer(this);
	m_pTimerInfoPtr = nullptr;
	m_pFixTimerInfoPtr = nullptr;
}

//���ö�ʱ��
bool NFTimerObj::SetTimer(uint32_t nTimerID, uint64_t nInterVal, uint32_t nCallCount)
{
	return NFTimerMgr::Instance()->SetTimer(nTimerID, nInterVal, this, nCallCount);
}

//�رն�ʱ��
bool NFTimerObj::KillTimer(uint32_t nTimerID)
{
	return NFTimerMgr::Instance()->KillTimer(nTimerID, this);
}

//�ر����ж�ʱ��
bool NFTimerObj::KillAllTimer()
{
	return NFTimerMgr::Instance()->KillAllTimer(this);
}

//���ù̶�ʱ��Ķ�ʱ��
bool NFTimerObj::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, uint32_t nCallCount)
{
	return NFTimerMgr::Instance()->SetFixTimer(nTimerID, nStartTime, nInterDays, this, nCallCount);
}

//�رչ̶�ʱ�䶨ʱ��
bool NFTimerObj::KillFixTimer(uint32_t nTimerID)
{
	return NFTimerMgr::Instance()->KillFixTimer(nTimerID, this);
}

//�ر����й̶�ʱ�䶨ʱ��
bool NFTimerObj::KillAllFixTimer()
{
	return NFTimerMgr::Instance()->KillAllFixTimer(this);
}

