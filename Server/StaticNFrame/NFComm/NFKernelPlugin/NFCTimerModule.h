// -------------------------------------------------------------------------
//    @FileName         :    {Filename}
//    @Author           :    GaoYi
//    @Date             :    2017-09-27
//    @Module           :   {Filename}
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFITimerModule.h"
#include "NFComm/NFPluginModule/NFTimerAxis.h"

class NFCTimerModule : public NFITimerModule
{
public:
    explicit NFCTimerModule(NFIPluginManager* p);
	virtual ~NFCTimerModule() { }
public:
    virtual bool Init();

    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();

    virtual bool Shut();
public:
	//���ö�ʱ��
	virtual bool SetTimer(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj *handler, uint32_t nCallCount = INFINITY_CALL);

	//�رն�ʱ��
	virtual bool KillTimer(uint32_t nTimerID, NFTimerObj *handler);

	//�ر����ж�ʱ��
	virtual bool KillAllTimer(NFTimerObj *handler);

	//���ù̶�ʱ��Ķ�ʱ��
	virtual bool SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj *handler, uint32_t nCallCount = INFINITY_CALL);

	//�رչ̶�ʱ�䶨ʱ��
	virtual bool KillFixTimer(uint32_t nTimerID, NFTimerObj *handler);

	//�ر����й̶�ʱ�䶨ʱ��
	virtual bool KillAllFixTimer(NFTimerObj *handler);
protected:
	NFTimerAxis mTimerAxis;
};
