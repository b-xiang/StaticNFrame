// -------------------------------------------------------------------------
//    @FileName         :    NFTimerMgr.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#include "NFTimerMgr.h"
#include "NFComm/NFPluginModule/NFITimerModule.h"

NFTimerMgr::NFTimerMgr()
{
	m_pTimerModule = nullptr;
}

NFTimerMgr::~NFTimerMgr()
{
}

bool NFTimerMgr::Init(NFITimerModule* pTimerModule)
{
	m_pTimerModule = pTimerModule;
	return true;
}

void NFTimerMgr::UnInit()
{
	m_pTimerModule = nullptr;
}

//���ö�ʱ��
bool NFTimerMgr::SetTimer(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj* handler, uint32_t nCallCount /*= INFINITY_CALL*/)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->SetTimer(nTimerID, nInterVal, handler, nCallCount);
	}
	return false;
}

//�رն�ʱ��
bool NFTimerMgr::KillTimer(uint32_t nTimerID, NFTimerObj* handler)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->KillTimer(nTimerID, handler);
	}
	return false;
}

//�ر����ж�ʱ��
bool NFTimerMgr::KillAllTimer(NFTimerObj* handler)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->KillAllTimer(handler);
	}
	return false;
}

//���ù̶�ʱ��Ķ�ʱ��
bool NFTimerMgr::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterSec, NFTimerObj* handler, uint32_t nCallCount/* = INFINITY_CALL */)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->SetClocker(nTimerID, nStartTime, nInterSec, handler, nCallCount);
	}
	return false;
}

