// -------------------------------------------------------------------------
//    @FileName         :    NFCTestActorModule.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/06/04
//    @Email			:    445267987@qq.com
//    @Module           :    NFTestPlugin
//
// -------------------------------------------------------------------------

#include "NFCTestActorModule.h"
#include "NFMessageDefine/NFMsgDefine.h"
#include <NFComm/NFPluginModule/NFIMysqlModule.h>
#include "NFComm/NFPluginModule/NFIHttpServerModule.h"
#include "NFComm/NFPluginModule/NFITaskModule.h"
#include "NFComm/NFPluginModule/NFTask.h"
#include "NFComm/NFPluginModule/NFLogMgr.h"
#include "NFComm/NFCore/NFCommon.h"


class NFLogTask : public NFTask
{
public:
	NFLogTask()
	{
		count = 0;
	}
	/**
	**  �첽�̴߳�������������һ���߳�������
	*/
	virtual bool ThreadProcess()
	{
		NFLogError("thread process........... pid:{}, thread_id:{}", NFGetPID(), ThreadId());
		count++;
		return true;
	}

	/**
	** ���̴߳������������̴߳�������ύ���������������ݷ��غ����Ƿ��������
	����ֵ�� thread::TPTask::TPTaskState�� ��ο�TPTaskState
	*/
	virtual TPTaskState MainThreadProcess()
	{
		if (count >= 10)
		{
			return NFTask::TPTASK_STATE_COMPLETED;
		}
		return TPTASK_STATE_CONTINUE_CHILDTHREAD;
	}

	std::atomic_int count;
};

NFCTestActorModule::NFCTestActorModule(NFIPluginManager* p)
{
	pPluginManager = p;
}

NFCTestActorModule::~NFCTestActorModule()
{
}

bool NFCTestActorModule::Init()
{
	//NFITaskModule* pTaskModule = pPluginManager->FindModule<NFITaskModule>();

	//for(int i = 0; i < 10000; i++)
	//	pTaskModule->AddTask(new NFLogTask());
	return true;
}

bool NFCTestActorModule::AfterInit()
{
	return true;
}

bool NFCTestActorModule::Execute()
{
	return true;
}

bool NFCTestActorModule::BeforeShut()
{
	return true;
}

bool NFCTestActorModule::Shut()
{
	return true;
}