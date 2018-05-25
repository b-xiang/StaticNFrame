// -------------------------------------------------------------------------
//    @FileName         :    NFITimerModule.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#pragma once

#include "NFIModule.h"
#include "NFComm/NFPluginModule/NFTimerAxis.h"

class NFITimerModule : public NFIModule
{
public:
	//���ö�ʱ��
	virtual bool SetTimer(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj* handler, uint32_t nCallCount = INFINITY_CALL) = 0;

	//�رն�ʱ��
	virtual bool KillTimer(uint32_t nTimerID, NFTimerObj* handler) = 0;

	//�ر����ж�ʱ��
	virtual bool KillAllTimer(NFTimerObj* handler) = 0;

	//���ù̶�ʱ��Ķ�ʱ��
	virtual bool SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj* handler, uint32_t nCallCount = INFINITY_CALL) = 0;

	//�رչ̶�ʱ�䶨ʱ��
	virtual bool KillFixTimer(uint32_t nTimerID, NFTimerObj* handler) = 0;

	//�ر����й̶�ʱ�䶨ʱ��
	virtual bool KillAllFixTimer(NFTimerObj* handler) = 0;
};

