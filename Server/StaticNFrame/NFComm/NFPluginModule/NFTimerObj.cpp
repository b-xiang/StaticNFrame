// -------------------------------------------------------------------------
//    @FileName         :    NFTimerObj.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#include "NFTimerObj.h"
#include "NFTimerMgr.h"

NFTimerObj::NFTimerObj() : m_pTimerInfoPtr(nullptr), m_pFixTimerInfoPtr(nullptr)
{
}

NFTimerObj::~NFTimerObj()
{
	NFTimerMgr::Instance()->KillAllTimer(this);
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
bool NFTimerObj::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterSec, uint32_t nCallCount)
{
	return NFTimerMgr::Instance()->SetFixTimer(nTimerID, nStartTime, nInterSec, this, nCallCount);
}

