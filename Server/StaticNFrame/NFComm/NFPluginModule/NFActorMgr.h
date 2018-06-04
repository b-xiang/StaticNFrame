// -------------------------------------------------------------------------
//    @FileName         :    JyActorMgr.h
//    @Author           :    GaoYi
//    @Date             :    2018-05-19
//    @Email			:    445267987@qq.com
//    @Module           :    
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFXActor.h"

class NFTask;

/**
* @brief actor�첽�������
*
*/
class NFXActorMgr
{
public:
	/**
	* @brief ���캯��
	*/
	NFXActorMgr()
	{
		nMainThreadRuning = true;
		nIsInit = false;
	}

	/**
	* @brief ��������
	*/
	virtual ~NFXActorMgr()
	{

	}

	/**
	* @brief �Ƿ��ʼ��
	*
	* @return �Ƿ��ʼ��
	*/
	virtual bool IsInit()
	{
		return nIsInit;
	}

	/**
	* @brief ��ʼ��actorϵͳ, �����̸߳���
	*
	* @param thread_num	�߳���Ŀ������Ϊ1
	* @return < 0 : Failed
	*/
	virtual int InitActor(int thread_num) = 0;

	/**
	* @brief ��ϵͳ��������һ��actor
	*
	* @return ����actor��Ψһ����
	*/
	virtual int RequireActor() = 0;

	/**
	* @brief �ͷ�actor��Դ
	*
	* @return
	*/
	virtual void ReleaseActor() = 0;

	/**
	* @brief ��Ϣ���ݴ����������б�Ҫ�����ݷ��ظ����̣߳�
	*		 ��������������Ϣ�������͸����̣߳����������actor�߳���ִ��
	*
	* @param messag	��Ϣ����
	* @param from	������Ϣ��actor��ַ
	* @return �Ƿ�ɹ�
	*/
	virtual bool HandlerEx(const NFXActorMessage& message, const int from) = 0;

	/**
	* @brief ���߳�ͨ���Լ������actorIndex���������ݸ�actor�߳�
	*
	* @param nActorIndex	actorΨһ����
	* @param pData			Ҫ���͵�����
	* @return �Ƿ�ɹ�
	*/
	virtual bool SendMsgToActor(const int nActorIndex, void* pData) = 0;

	/**
	* @brief ���߳�ͨ���Լ������actorIndex���������ݸ�actor�߳�
	*
	* @param nActorIndex	actorΨһ����
	* @param strData		Ҫ���͵�����
	* @return �Ƿ�ɹ�
	*/
	virtual bool SendMsgToActor(const int nActorIndex, const std::string& strData) = 0;
    
	/**
	* @brief ͨ��actorIndex���һ��actor
	*
	* @param nActorIndex	actor������ַ
	* @return ���ػ�õ�actor, ��û�У�ΪNULL
	*/
	virtual NFXActor* GetActor(const int nActorIndex) = 0;

	/**
	* @brief ��ϵͳ����actorNum��actor, ��ʼ��actor��
	*
	* @param actorNum	actor��Ŀ
	* @return �Ƿ�ɹ�
	*/
	virtual bool StartActorPool(int actorNum) = 0;

	/**
	* @brief �ͷ������actor���ݣ��ر�actor��
	*
	* @return �Ƿ�ɹ�
	*/
	virtual bool CloseActorPool() = 0;

	/**
	* @brief ���ϵͳ��û�д������������Ŀ
	*
	* @return δ��ɵ�������Ŀ
	*/
	virtual int GetNumQueuedMessages() = 0;

	/**
	* @brief ���Ҫ�첽�����task
	*
	* @param pTask Ҫ�첽�����task
	* @return
	*/
	virtual bool AddTask(NFTask* pTask) = 0;

	/**
	* @brief ���Ҫ�첽��������ݣ� ���ݷ����ַ�����
	*
	* @param strData Ҫ�첽���������
	* @return
	*/
	virtual bool AddStrData(const std::string& strData) = 0;

	/**
	* @brief ���̴߳���actor���ص�����
	*
	* @return
	*/
	virtual void OnMainThreadTick() = 0;

	/**
	* @brief �����������Ҫ, �������˳���ʱ��
	*        �����ж��첽�������Ƿ�ȫ�����, �첽����ȫ����ɺ�
	*        �����������˳�
	*
	* @return
	*/
	virtual bool IsSaveDone()
	{
		if (nIsInit == false) return true;

		if (GetNumQueuedMessages() > 0)
		{
			return false;
		}
		return true;
	}

	/**
	* @brief ���÷��������߳��Ƿ���ִ��
	*
	* @return
	*/
	void		SetMainThreadRunning(bool running) { nMainThreadRuning = running; }
protected:
	/**
	* @brief ���������߳��Ƿ���ִ�У�
	*        �������˳���ʱ������Ϊfalse���������µ���������첽ϵͳ
	*/
	bool nMainThreadRuning;
	/**
	* @brief actormgr�Ƿ�����˳�ʼ��
	*/
	bool nIsInit;
};

/**
* @brief actor�첽����ģ��, ActorType��actor�����actor����
*
*/
template<class ActorType>
class NFActorMgr : public NFXActorMgr
{
public:
	/**
	* @brief ���캯��
	*/
	NFActorMgr()
	{
		m_pFramework = nullptr;
		m_pMainActor = nullptr;
	}

	/**
	* @brief ��������
	*/
	virtual ~NFActorMgr()
	{
		NFActorMgr<ActorType>::ReleaseActor();
	}
public:
	/**
	* @brief ��ʼ��actorϵͳ, �����̸߳���
	*
	* @param thread_num	�߳���Ŀ������Ϊ1
	* @return < 0 : Failed
	*/
	virtual int InitActor(int thread_num) override
	{
		//��������Ӳ���� ȷ����Ҫ���߳���Ŀ
		if (thread_num <= 0) thread_num = 1;

		m_pFramework = new Theron::Framework(thread_num);
		
		m_pMainActor = new ActorType(*m_pFramework, this);

		return 0;
	}

	/**
	* @brief ��ϵͳ��������һ��actor
	*
	* @return ����actor��Ψһ����
	*/
	virtual int RequireActor() override
	{
		NFXActor* pActor(new ActorType(*m_pFramework, this));
		if (pActor)
		{
			m_mActorMap.emplace(pActor->GetAddress().AsInteger(), pActor);
			return pActor->GetAddress().AsInteger();
		}
		return -1;
	}

	/**
	* @brief ���߳�ͨ���Լ������actorIndex���������ݸ�actor�߳�
	*
	* @param nActorIndex	actorΨһ����
	* @param pData			Ҫ���͵�����
	* @return �Ƿ�ɹ�
	*/
	virtual bool SendMsgToActor(const int nActorIndex, void* pData) override
	{
		NFXActor* pActor = GetActor(nActorIndex);
		if (pActor != nullptr && m_pMainActor != nullptr && m_pFramework != nullptr)
		{
			NFXActorMessage xMessage;

			xMessage.nMsgType = NFXActorMessage::ACTOR_MSG_TYPE_COMPONENT;
			xMessage.pData = pData;
			xMessage.nFromActor = m_pMainActor->GetAddress().AsInteger();

			return m_pFramework->Send(xMessage, m_pMainActor->GetAddress(), pActor->GetAddress());
		}

		return false;
	}

	/**
	* @brief ���߳�ͨ���Լ������actorIndex���������ݸ�actor�߳�
	*
	* @param nActorIndex	actorΨһ����
	* @param strData		Ҫ���͵�����
	* @return �Ƿ�ɹ�
	*/
	virtual bool SendMsgToActor(const int nActorIndex, const std::string& strData) override
	{
		NFXActor* pActor = GetActor(nActorIndex);
		if (pActor != nullptr && m_pMainActor != nullptr && m_pFramework != nullptr)
		{
			NFXActorMessage xMessage;

			xMessage.nMsgType = NFXActorMessage::ACTOR_MSG_TYPE_COMPONENT;
			xMessage.strData = strData;
			xMessage.nFromActor = m_pMainActor->GetAddress().AsInteger();

			return m_pFramework->Send(xMessage, m_pMainActor->GetAddress(), pActor->GetAddress());
		}

		return false;
	}
    
	/**
	* @brief �ͷ�actor��Դ
	*
	* @return
	*/
	virtual void ReleaseActor() override
	{
		for (auto it = m_mActorMap.begin(); it != m_mActorMap.end(); it++)
		{
			NFSafeDelete(it->second);
		}
		m_mActorMap.clear();
		if (m_pMainActor)
		{
			NFSafeDelete(m_pMainActor);
		}
		m_pMainActor = nullptr;
		if (m_pFramework)
		{
			NFSafeDelete(m_pFramework);
		}
		m_pFramework = nullptr;
	}

	/**
	* @brief ͨ��actorIndex���һ��actor
	*
	* @param nActorIndex	actor������ַ
	* @return ���ػ�õ�actor, ��û�У�ΪNULL
	*/
	virtual NFXActor* GetActor(const int nActorIndex) override
	{
		auto iter = m_mActorMap.find(nActorIndex);
		if (iter != m_mActorMap.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	/**
	* @brief ���ϵͳ��û�д������������Ŀ
	*
	* @return δ��ɵ�������Ŀ
	*/
	virtual int GetNumQueuedMessages() override
	{
		if (nIsInit == false) return 0;

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

	/**
	* @brief ���Ҫ�첽�����task
	*
	* @param pTask Ҫ�첽�����task
	* @return
	*/
	virtual bool AddTask(NFTask* pTask) override
	{
		return true;
	}

	/**
	* @brief ���Ҫ�첽��������ݣ� ���ݷ����ַ�����
	*
	* @param strData Ҫ�첽���������
	* @return
	*/
	virtual bool AddStrData(const std::string& strData) override
	{
		return true;
	}

	/**
	* @brief ��Ϣ���ݴ����������б�Ҫ�����ݷ��ظ����̣߳�
	*		 ��������������Ϣ�������͸����̣߳����������actor�߳���ִ��
	*
	* @param messag	��Ϣ����
	* @param from	������Ϣ��actor��ַ
	* @return �Ƿ�ɹ�
	*/
	virtual bool HandlerEx(const NFXActorMessage& message, const int from) override
	{
		return true;
	}

	/**
	* @brief ���̴߳���actor���ص�����
	*
	* @return
	*/
	virtual void OnMainThreadTick() override
	{

	}
protected:
	Theron::Framework*			m_pFramework;
	NFXActor*					m_pMainActor;
	std::map<int, NFXActor*>	m_mActorMap;
};
