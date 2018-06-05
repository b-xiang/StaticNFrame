// -------------------------------------------------------------------------
//    @FileName         :    NFTimerMgr.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#pragma once

#include "NFComm/NFPluginModule/NFITimerModule.h"
#include "NFComm/NFCore/NFSingleton.hpp"

class NFTimerMgr : public NFSingleton<NFTimerMgr>
{
public:
	NFTimerMgr();
	virtual ~NFTimerMgr();
public:
	virtual bool Init(NFITimerModule* pTimerModule);
	virtual void UnInit();
public:
	//���ö�ʱ��
	virtual bool SetTimer(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj* handler, uint32_t nCallCount = INFINITY_CALL);

	//�رն�ʱ��
	virtual bool KillTimer(uint32_t nTimerID, NFTimerObj* handler);

	//�ر����ж�ʱ��
	virtual bool KillAllTimer(NFTimerObj* handler);

	//���ù̶�ʱ��Ķ�ʱ��
	virtual bool SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj* handler, uint32_t nCallCount = INFINITY_CALL);

	//�رչ̶�ʱ�䶨ʱ��
	virtual bool KillFixTimer(uint32_t nTimerID, NFTimerObj* handler);

	//�ر����й̶�ʱ�䶨ʱ��
	virtual bool KillAllFixTimer(NFTimerObj* handler);
protected:
	NFITimerModule* m_pTimerModule;
};
