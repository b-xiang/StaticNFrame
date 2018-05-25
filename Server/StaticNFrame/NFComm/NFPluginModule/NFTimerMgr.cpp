// -------------------------------------------------------------------------
//    @FileName         :    NFTimerMgr.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#include "NFTimerMgr.h"

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
bool NFTimerMgr::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj* handler, uint32_t nCallCount/* = INFINITY_CALL */)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->SetFixTimer(nTimerID, nStartTime, nInterDays, handler, nCallCount);
	}
	return false;
}

//�رչ̶�ʱ�䶨ʱ��
bool NFTimerMgr::KillFixTimer(uint32_t nTimerID, NFTimerObj* handler)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->KillFixTimer(nTimerID, handler);
	}
	return false;
}

//�ر����й̶�ʱ�䶨ʱ��
bool NFTimerMgr::KillAllFixTimer(NFTimerObj* handler)
{
	if (m_pTimerModule)
	{
		return m_pTimerModule->KillAllFixTimer(handler);
	}
	return false;
}

