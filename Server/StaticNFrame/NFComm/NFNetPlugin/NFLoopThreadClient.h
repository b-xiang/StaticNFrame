// -------------------------------------------------------------------------
//    @FileName         :    NFThreadClient.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NetObject.h"
#include "NFComm/NFCore/NFQueue.hpp"
#include "NetThreadObject.h"
#include "NFEventLoopThread.h"

/**
*@brief  ���߳�libevent����ͻ��˷�װ��.
*		 m_thread��Ҫʹ�������߳���
*		 m_threadNetMsgs�����������߳��д������� 
*		 event_base* m_pMainBase���������̣߳�ʹ����client�̣߳����������߳�
*        struct bufferevent* m_pBev������client�߳�, ����client�̣߳�д�����̣߳�û�п���ͬ����
*        mRecvCB, mEventCB��ʹ�������߳�
*		 SOCKET m_nSocketId����client�߳�
*        NFBuffer m_buffer����client�߳�
*        eConnectStatus m_eStatusд��Ҫ��client�̣߳�����ʱд��һ�Σ�����ط�û�����⣬�Ͽ�����ʱд��һ�Σ����ܻᵼ�����⣬
*        Sendʱ���ж��жϣ� ��û��ͬ����ʩ���п�����client�߳��Ѿ��Ͽ������ˣ��������ﻹ��д? ��֪��libevent��᲻�����ж�
*        Reconnectû��ͬ��eStatus��Ҳ����������
* ����1��m_eStatus�������߳���ʹ�ã��󲿷�ʱ��û�����⣬ �����ӶϿ�ʱ�����ܻ�������
* ����2��Close���������߳������������⣬�ڲ�ֹclient�߳�����ʲô������£�óȻ����	SetStatus(eConnectStatus_Disconnect);
	m_buffer.Clear(); ���ܵ���δ�������⣬�����. Ӧ����breakѭ�����ر��̣߳�Ȼ���ڵ���
*/
class NFLoopThreadClient : public NetThreadObject
{
public:
	/**
	 *@brief  ���캯��.
	 */
	NFLoopThreadClient(uint32_t nId, const NFClientFlag& flag);

	/**
	 *@brief  ��������.
	 */
	virtual ~NFLoopThreadClient();

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
	virtual void CheckConnect();

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
	 * @brief	�ر�����, ��������ߵ������������Ӧ����break�����̣߳�
	 * Ȼ��m_thread.StopThread()�ر������߳�
	 * �����Ͳ������̳߳�ͻ, Ȼ���ڵ���
	 *
	 * @return
	 */
	virtual int Close();

	/**
	 * @brief	��ʼ����
	 * @return
	 */
	virtual bool Connect();

	/**
	 * @brief	��������
	 *
	 * @return
	 */
	virtual bool Reconnect();

	/**
	 * @brief	�������ӳɹ�
	 *
	 * @param nSocket	ϵͳ�����socket
	 * @return
	 */
	virtual void OnHandleConnect(SOCKET nSocket);

	/**
	 * @brief	����Ͽ�����
	 *
	 * @return
	 */
	virtual void OnHandleDisConnect();

	/**
	 * @brief	�ͻ����߳����к���
	 * @return
	 */
	int OnClientThread();
private:
	/**
	 * @brief	�̹߳�����
	 */
	std::unique_ptr<NFEventLoopThread> m_loopThread;

	/**
	 * @brief	���߳���Ϣ����
	 */
	NFQueueVector<NFThreadNetMsg*> m_threadNetMsgs;

	/**
	* @brief	����������ݵĻص�
	*/
	NET_RECEIVE_FUNCTOR mRecvCB;

	/**
	* @brief	�����¼��ص�
	*/
	NET_EVENT_FUNCTOR mEventCB;

	/**
	* @brief	������������
	*/
	NFClientFlag m_flag;

	/**
	* @brief	����������
	*/
	std::string m_strName;
};

