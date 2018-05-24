#pragma once

#include "NetObject.h"
#include "NFClient.h"
#include <thread>
#include "NFComm/NFCore/NFThread.hpp"
#include "NFComm/NFCore/NFQueue.hpp"

/**
*@brief  ���߳�libevent����ͻ��˷�װ��.
*/
class NFThreadClient : public NFClient
{
public:
	/**
	 *@brief  ���캯��.
	 */
	NFThreadClient(uint32_t nId, const NFClientFlag& flag);

	/**
	 *@brief  ��������.
	 */
	virtual ~NFThreadClient();

	/**
	 * @brief	��ʼ��
	 *
	 * @return �Ƿ�ɹ�
	 */
	virtual bool Init() override;

	/**
	 * @brief	�رտͻ����ͷ�����
	 *
	 * @return  �Ƿ�ɹ�
	 */
	virtual bool Shut() override;

	/**
	 * @brief	������ÿִ֡��
	 *
	 * @return	�Ƿ�ɹ�
	 */
	virtual bool Execute() override;

	/**
	 * @brief	�Խ������������ݽ��д���
	 *
	 * @param type    �������ͣ���Ҫ��Ϊ�˺Ͷ��߳�ͳһ����, ��Ҫ�н������ݴ������ӳɹ������Ͽ����Ӵ���
	 * @param usLink  ���ͻ��˵�Ψһid
	 * @param pBuf    ����ָ��
	 * @param sz      ���ݴ�С
	 * @param nMsgId  ������������Ϣid
	 * @param nValue  ��ϢͷЯ����ֵ�����������ID��Ҳ�����ǶԷ��ͻ������ӵ�Ψһid
	 * @return
	 */
	virtual void OnHandleMsgPeer(eMsgType type, uint32_t usLink, char* pBuf, uint32_t sz, uint32_t nMsgId, uint64_t nValue) override;

	/**
	 * @brief	������߳���������, �Ӷ��̶߳���ȡ�����ݲ�����
	 *
	 * @return	
	 */
	virtual void ProcessMsgLogicThread();

	/**
	 * @brief	�������
	 * @return
	 */
	virtual void CheckConnect() override;

	/**
	 * @brief	�����̴߳�������
	 * @return
	 */
	void StartThread();

	/**
	 * @brief	�������ӳɹ�����Ϣ���Լ�, ��Ϊ�Ƕ��̣߳� Ϊ������������ 
	 * ���÷�����Ϣ�Ļ��ƣ�֪ͨ���߳���������״��
	 * @return
	 */
	void SendConnected();

	/**
	 * @brief	�������ӶϿ�����Ϣ���Լ�, ��Ϊ�Ƕ��̣߳� Ϊ������������ 
	 * ���÷�����Ϣ�Ļ��ƣ�֪ͨ���߳���������״��
	 * @return
	 */
	void SendDisconnect();

	/**
	 * @brief	�ر�����
	 *
	 * @return
	 */
	virtual void Close() override;

	/**
	 * @brief	��ʼ����
	 * @return
	 */
	virtual bool Connect() override;

	/**
	 * @brief	��������
	 *
	 * @return
	 */
	virtual bool Reconnect() override;

	/**
	 * @brief	�������ӳɹ�
	 *
	 * @param nSocket	ϵͳ�����socket
	 * @return
	 */
	virtual void OnHandleConnect(SOCKET nSocket) override;

	/**
	 * @brief	����Ͽ�����
	 *
	 * @return
	 */
	virtual void OnHandleDisConnect() override;

	/**
	 * @brief	�ͻ����߳����к���
	 * @return
	 */
	void OnClientThread();
private:
	/**
	 * @brief	�̹߳�����
	 */
	NFThread m_thread;

	/**
	 * @brief	���߳���Ϣ����
	 */
	NFQueueVector<NFThreadNetMsg*> m_threadNetMsgs;
};
