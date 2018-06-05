#pragma once

#define THERON_USE_STD_THREADS 1

#include <map>
#include <Theron/Theron.h>

class NFXActorMgr;

/**
* @brief actor��Ϣ����
*
*/
class NFXActorMessage
{
public:
	/**
	* @brief ��Ϣ����
	*
	*/
	enum MessageType
	{
		/**
		* @brief Ҫ�������Ϣ
		*
		*/
		ACTOR_MSG_TYPE_COMPONENT,
		/**
		* @brief �Ѿ����������Ϣ���ȴ��������̴߳���
		*
		*/
		ACTOR_MSG_TYPE_END_FUNC,
	};

	/**
	* @brief ���캯��
	*
	*/
	NFXActorMessage()
	{
		nFromActor = 0;
		pData = nullptr;
		nMsgType = ACTOR_MSG_TYPE_COMPONENT;
	}
public:
	/**
	* @brief ��Ϣ����
	*
	*/
	int nMsgType;

	/**
	* @brief ������Ϣ��actor����
	*
	*/
	int nFromActor;

	/**
	* @brief ��Ϣ����
	*
	*/
	void* pData;

	/**
	* @brief �ַ���Я����Ϣ����
	*
	*/
	std::string strData;
};

/**
* @brief actor����
*
*/
class NFXActor : public Theron::Actor
{
public:
	/**
	* @brief ���캯��
	*        �������RegisterHandler��ע���첽��������������ĺ���
	*/
	NFXActor(Theron::Framework& framework, NFXActorMgr* pActorMgr) : Theron::Actor(framework)
	{
		RegisterHandler(this, &NFXActor::DefaultHandler);
		m_pActorMgr = pActorMgr;
	}

	/**
	* @brief ��������
	*
	*/
	virtual ~NFXActor() {}

	/**
	* @brief ������һ��actor������Ϣ
	*
	* @param address ������Ϣ��actor�ĵ�ַ
	* @param message ���ֵ���Ϣ
	* @return ���ط����Ƿ�ɹ�
	*/
	virtual bool SendMsg(const Theron::Address address, const NFXActorMessage& message)
	{
		return Send(message, address);
	}
protected:
	/**
	* @brief �����Ѿ������������Ϣ
	*
	* @param message Ҫ�������Ϣ
	* @param from	 ������Ϣ��actor��ַ
	* @return ���ط����Ƿ�ɹ�
	*/
	virtual void HandlerEx(const NFXActorMessage& message, const Theron::Address from) {};

	/**
	* @brief �����͵�����
	*
	* @param message Ҫ�������Ϣ
	* @param from	 ������Ϣ��actor��ַ
	* @return
	*/
	virtual void Handler(const NFXActorMessage& message, const Theron::Address from) {};
private:
	/**
	* @brief �첽����Ĺ���
	*
	* @param message Ҫ�������Ϣ
	* @param from	 ������Ϣ��actor��ַ
	* @return
	*/
	void DefaultHandler(const NFXActorMessage& message, const Theron::Address from)
	{
		if (message.nMsgType == NFXActorMessage::ACTOR_MSG_TYPE_COMPONENT)
		{
			Handler(message, from);
		}
		else
		{
			HandlerEx(message, from);
		}
	}
protected:
	/**
	* @brief actor�������
	*/
	NFXActorMgr* m_pActorMgr;
};
