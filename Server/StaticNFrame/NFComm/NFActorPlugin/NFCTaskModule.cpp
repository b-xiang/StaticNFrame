// -------------------------------------------------------------------------
//    @FileName         :    NFCTaskModule.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFActorPlugin
//
// -------------------------------------------------------------------------

#include "NFCTaskModule.h"
#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFPluginModule/NFTask.h"
#include "NFComm/NFPluginModule/NFLogMgr.h"

NFCTaskModule::NFCTaskModule(NFIPluginManager* p)
{
	pPluginManager = p;
	mnSuitIndex = 0;
	nRecvTaskCount = 0;
	nHandleTaskCount = 0;
	srand(static_cast<unsigned>(time(nullptr)));
	//首先初始化
	InitActorThread(std::thread::hardware_concurrency());
}

NFCTaskModule::~NFCTaskModule()
{

}

bool NFCTaskModule::Init()
{
	return true;
}

bool NFCTaskModule::AfterInit()
{
	return true;
}

bool NFCTaskModule::BeforeShut()
{
	return true;
}

bool NFCTaskModule::Shut()
{
	//等待异步处理完毕，然后再退出系统
	while (GetNumQueuedMessages() > 0 || m_mQueue.Count() > 0)
	{
		OnMainThreadTick();
		NFSLEEP(1);
	}
	return true;
}

bool NFCTaskModule::Finalize()
{
	CloseActorPool();
	return true;
}

bool NFCTaskModule::Execute()
{
	OnMainThreadTick();
	return true;
}

/**
* @brief 初始化actor系统, 配置线程个数
*
* @param thread_num	线程数目，至少为1
* @return < 0 : Failed
*/
int NFCTaskModule::InitActorThread(int thread_num)
{
	//根据物理硬件， 确定需要的线程数目
	if (thread_num <= 0) thread_num = 1;

	m_pFramework = new Theron::Framework(thread_num);

	m_pMainActor = new NFTaskActor(*m_pFramework, this);

	return 0;
}

/**
* @brief 向系统请求请求一个actor
*
* @return 返回actor的唯一索引
*/
int NFCTaskModule::RequireActor()
{
	NFTaskActor* pActor(new NFTaskActor(*m_pFramework, this));
	if (pActor)
	{
		m_mActorMap.emplace(pActor->GetAddress().AsInteger(), pActor);
		m_vecActorPool.push_back(pActor->GetAddress().AsInteger());
		return pActor->GetAddress().AsInteger();
	}
	return -1;
}

/**
* @brief 主线程通过自己保存的actorIndex将发送数据给actor线程
*
* @param nActorIndex	actor唯一索引
* @param pData			要发送的数据
* @return 是否成功
*/
bool NFCTaskModule::SendMsgToActor(const int nActorIndex, NFTask* pData)
{
	NFTaskActor* pActor = GetActor(nActorIndex);
	if (pActor != nullptr && m_pMainActor != nullptr && m_pFramework != nullptr)
	{
		NFTaskActorMessage xMessage;

		xMessage.nMsgType = NFTaskActorMessage::ACTOR_MSG_TYPE_COMPONENT;
		xMessage.pData = pData;
		xMessage.nFromActor = m_pMainActor->GetAddress().AsInteger();

		return m_pFramework->Send(xMessage, m_pMainActor->GetAddress(), pActor->GetAddress());
	}

	return false;
}

/**
* @brief 释放actor资源
*
* @return
*/
void NFCTaskModule::ReleaseActor()
{
	for (auto it = m_mActorMap.begin(); it != m_mActorMap.end(); it++)
	{
		NF_SAFE_DELETE(it->second);
	}
	m_mActorMap.clear();
	if (m_pMainActor)
	{
		NF_SAFE_DELETE(m_pMainActor);
	}
	m_pMainActor = nullptr;
	if (m_pFramework)
	{
		NF_SAFE_DELETE(m_pFramework);
	}
	m_pFramework = nullptr;
}

/**
* @brief 通过actorIndex获得一个actor
*
* @param nActorIndex	actor索引地址
* @return 返回获得的actor, 若没有，为NULL
*/
NFTaskActor* NFCTaskModule::GetActor(const int nActorIndex)
{
	auto iter = m_mActorMap.find(nActorIndex);
	if (iter != m_mActorMap.end())
	{
		return iter->second;
	}
	return nullptr;
}

int NFCTaskModule::GetNumQueuedMessages()
{
	int count = 0;
	if (m_pMainActor)
	{
		count += m_pMainActor->GetNumQueuedMessages();
	}

	for (auto it = m_mActorMap.begin(); it != m_mActorMap.end(); it++)
	{
		count += it->second->GetNumQueuedMessages();
	}

	return count;
}

bool NFCTaskModule::CloseActorPool()
{
	ReleaseActor();
	m_vecActorPool.clear();
	return true;
}

bool NFCTaskModule::HandlerEx(const NFTaskActorMessage& message, const int from)
{
	if (message.nMsgType != NFTaskActorMessage::ACTOR_MSG_TYPE_COMPONENT)
	{
		return m_mQueue.Push(message);
	}

	return false;
}

bool NFCTaskModule::AddTask(NFTask* pTask)
{
	int nActorId = GetBalanceActor(pTask->GetBalanceId());
	if (nActorId <= 0)
	{
		return false;
	}

	if (!SendMsgToActor(nActorId, pTask))
	{
		return false;
	}

	nRecvTaskCount++;
	return true;
}

bool NFCTaskModule::AddTask(int actorId, NFTask* pTask)
{
	if (actorId <= 0)
	{
		return false;
	}

	if (!SendMsgToActor(actorId, pTask))
	{
		return false;
	}

	nRecvTaskCount++;
	return true;
}

int NFCTaskModule::GetBalanceActor(uint64_t balanceId)
{
	if (balanceId == 0)
	{
		return GetRandActor();
	}
	else
	{
		if (m_vecActorPool.size() <= 0)
		{
			return -1;
		}
		mnSuitIndex = balanceId % m_vecActorPool.size();
		return m_vecActorPool[mnSuitIndex];
	}
}

int NFCTaskModule::GetRandActor()
{
	if (m_vecActorPool.size() <= 0)
	{
		return -1;
	}

	mnSuitIndex++;
	mnSuitIndex = mnSuitIndex % m_vecActorPool.size();

	return m_vecActorPool[mnSuitIndex];
}

void NFCTaskModule::OnMainThreadTick()
{
	std::vector<NFTaskActorMessage> listTask;
	bool ret = m_mQueue.Pop(listTask);
	if (ret)
	{
		uint64_t start = NFGetTime();
		for (auto it = listTask.begin(); it != listTask.end(); it++)
		{
			NFTaskActorMessage& xMsg = *it;
			if (xMsg.nMsgType != NFTaskActorMessage::ACTOR_MSG_TYPE_COMPONENT)
			{
				NFTask* pTask = static_cast<NFTask*>(xMsg.pData);
				if (pTask)
				{
					NFTask::TPTaskState state = pTask->MainThreadProcess();
					switch (state)
					{
					case NFTask::TPTASK_STATE_COMPLETED:
					{
						nHandleTaskCount++;
						NF_SAFE_DELETE(pTask);
					}
					break;
					case NFTask::TPTASK_STATE_CONTINUE_CHILDTHREAD:
					{
						AddTask(pTask);
					}
					break;
					case NFTask::TPTASK_STATE_CONTINUE_MAINTHREAD:
					{
						m_mQueue.Push(xMsg);
					}
					break;
					default:
					{
						//error
						nHandleTaskCount++;
						NF_SAFE_DELETE(pTask);
					}
					}
				}
			}
			else
			{
				//error
				NFTask* pTask = static_cast<NFTask*>(xMsg.pData);
				if (pTask)
				{
					NF_SAFE_DELETE(pTask);
				}
				else
				{
					//error
				}
				NFLogError("task actor module error................");
			}
		}

		if (listTask.size() > 0)
		{
			NFLogDebug("handle main thread tick task num:{}, use time:{}", listTask.size(), NFGetTime() - start);
		}
	}

	listTask.clear();
}