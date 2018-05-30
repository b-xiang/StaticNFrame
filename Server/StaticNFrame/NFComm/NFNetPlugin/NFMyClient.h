// -------------------------------------------------------------------------
//    @FileName         :    NFMyClient.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/28
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFSocket.h"
#include "NFPoll.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"
#include <NFComm/NFCore/NFBuffer.h>
#include "NFClient.h"

struct NFClientFlag;

class NFMyClient : public NFIModule
{
public:
	/**
	 * @brief ���캯��
	 */
	NFMyClient(uint32_t nId, const NFClientFlag& flag);

	/**
	 * @brief ��������
	 */
	virtual ~NFMyClient();

		/**
	 *@brief  ���ý��ջص�.
	 */
	template <typename BaseType>
	void SetRecvCB(BaseType* pBaseType, void (BaseType::*handleRecieve)(const uint32_t unLinkId, const uint64_t valueId, const uint32_t nMsgId, const char* msg, const uint32_t nLen))
	{
		mRecvCB = std::bind(handleRecieve, pBaseType, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
	}

	/**
	 *@brief  ���������¼��ص�.
	 */
	template <typename BaseType>
	void SetEventCB(BaseType* pBaseType, void (BaseType::*handleEvent)(const eMsgType nEvent, const uint32_t unLinkId))
	{
		mEventCB = std::bind(handleEvent, pBaseType, std::placeholders::_1, std::placeholders::_2);
	}

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
	 * @brief ����
	 *
	 * @param  ip
	 * @param  port
	 * @return bool 
	 */
	virtual bool Connect(const std::string& ip, int port);

	/**
	 * @brief ��������
	 *
	 * @param  buf
	 * @param  len
	 * @return bool 
	 */
	virtual bool Send(const char* buf, uint32_t len);

	/**
	 * @brief ������ܷ���
	 *
	 * @param  timeout
	 * @return bool 
	 */
	virtual bool Dispatch(uint32_t timeout);

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
	virtual void OnHandleMsgPeer(eMsgType type, uint32_t usLink, char* pBuf, uint32_t sz, uint32_t nMsgId, uint64_t nValue);

	/**
	 * @brief	�������ӳɹ�
	 *
	 * @param nSocket	ϵͳ�����socket
	 * @return
	 */
	virtual void OnHandleConnect();

	/**
	 * @brief	����Ͽ�����
	 *
	 * @return
	 */
	virtual void OnHandleDisConnect();

	/**
	 * @brief	��������
	 *
	 * @return	�Ƿ�ɹ�
	 */
	virtual bool OnRecvData();

	/**
	 * @brief	ȡ�����ݣ������д���
	 *
	 * @return	< 0, ��ʾ��������������, = 0, ��ʾ�������ݼ�������> 0��ʾ���ݴ������
	 */
	virtual int Dismantle();

	/**
	 * @brief	���ΨһID
	 *
	 * @return
	 */
	virtual uint32_t GetLinkId() const;
protected:
	/**
	 * @brief	����������ӵ�socket
	 */
	SOCKET m_nSocketId;

	/**
	 * @brief	����ͻ������ӵ�ΨһID
	 */
	uint32_t m_usLinkId;

	/**
	 * @brief �¼��ṹ����Ҫ��ȡ�����¼���־���Լ�����д�����¼��Ĵ���
	 */
	EventData* m_pEventData;

	/**
	 * @brief	����������ݵĻص�
	 */
	NET_RECEIVE_FUNCTOR mRecvCB;

	/**
	 * @brief	�����¼��ص�
	 */
	NET_EVENT_FUNCTOR mEventCB;

	/**
	 * @brief	�����������緢��������ʱ����
	 */
	NFBuffer m_buffer;

	/**
	 * @brief	������������
	 */
	NFClientFlag m_flag;
};
