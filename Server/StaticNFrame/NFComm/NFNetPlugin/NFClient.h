// -------------------------------------------------------------------------
//    @FileName         :    NFClient.h
//    @Author           :    GaoYi
//    @Date             :    2018-05-24
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <string>
#include "NFNetDefine.h"
#include "NFComm/NFPluginModule/NFIModule.h"
#include "NFComm/NFCore/NFBuffer.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"
#include "NetObject.h"

/////////////////////////////////////////////////
/**
 *@file   NFClient.h
 *@brief  ���߳�libevent����ͻ��˷�װ��.
 *
 */
/////////////////////////////////////////////////

/**
*@brief  ���߳�libevent����ͻ��˷�װ��.
*/
class NFClient : public NFIModule
{
public:
	/**
	 *@brief  ���캯��.
	 */
	NFClient(uint32_t nId, const NFClientFlag& flag);

	/**
	 *@brief  ��������.
	 */
	virtual ~NFClient();

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
	 * @brief �ͷ�����
	 *
	 * @return bool
	 */
	virtual bool Finalize() override;

	/**
	 * @brief	������ÿִ֡��
	 *
	 * @return	�Ƿ�ɹ�
	 */
	virtual bool Execute() override;

	/**
	 * @brief	ɾ���رյ�����
	 *
	 * @return	�Ƿ�ɹ�
	 */
	virtual void ExecuteClose();

	/**
	 * @brief	���ӷ����
	 *
	 * @return  ���ӳɹ����
	 */
	virtual bool Connect();

	/**
	 * @brief	�رտͻ�������, ��Conenct��Ӧ
	 * ��������ʱ��ֻ����OnExectue����ã�
	 * �˳�ʱ����������������
	 * @return
	 */
	virtual void Close();

	/**
	 * @brief	���libevent�����ݽṹ
	 * @return
	 */
	event_base* GetMainBase() const;

	/**
	 * @brief	��÷���������
	 *
	 * @return
	 */
	const string& GetName() const;

	/**
	 * @brief	���ؿͻ�����������
	 *
	 * @return
	 */
	const NFClientFlag& GetFlag() const;

	/**
	 * @brief	���ΨһID
	 *
	 * @return
	 */
	uint32_t GetLinkId() const;

	/**
	* @brief	���ΨһID
	*
	* @return
	*/
	void SetLinkId(uint32_t linkId);

	/**
	 * @brief	��������
	 *
	 * @param pData		���͵�����, ����������Ѿ�����������ͷ
	 * @param unSize	���ݵĴ�С
	 * @return
	 */
	virtual bool Send(const void* pData, uint32_t unSize);

	/**
	 * @brief
	 */
	eConnectStatus GetStatus() const;

	/**
	 * @brief
	 */
	void SetStatus(eConnectStatus val);

	/**
	 * @brief
	 */
	bool IsNeedRemve() const;

	/**
	 * @brief
	 *
	 * @return uint64_t
	 */
	uint64_t GetLastActionTime() const;

	/**
	 * @brief
	 *
	 * @param  time
	 * @return void
	 */
	void SetLastActionTime(uint64_t time);

	virtual bool IsWebSocket() const { return m_flag.bWebSocket; }
protected:
	/**
	 * @brief	libevent��react���ݽṹ
	 */
	event_base* m_pMainBase;

	/**
	 * @brief	������������
	 */
	NFClientFlag m_flag;

	/**
	 * @brief	����������
	 */
	std::string m_strName;

	/**
	 * @brief	���Ӷ���
	 */
	NetObject* m_pObject;

	/**
	 * @brief	����������ݵĻص�
	 */
	NET_RECEIVE_FUNCTOR mRecvCB;

	/**
	 * @brief	�����¼��ص�
	 */
	NET_EVENT_FUNCTOR mEventCB;

	/**
	 * @brief	����ͻ������ӵ�ΨһID
	 */
	uint32_t m_usLinkId;

	/**
	 * @brief ����״̬
	 */
	eConnectStatus mStatus;

	/**
	 * @brief ��һ�λʱ��
	 */
	uint64_t mLastActionTime;
};

