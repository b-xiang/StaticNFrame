// -------------------------------------------------------------------------
//    @FileName         :    NFEventObj.h
//    @Author           :    GaoYi
//    @Date             :    2017-04-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <string>
#include <stdint.h>

/* �¼�ʹ��ע������
 ȡ�������¼���ʱ����Ĳ���һ��Ҫ�Ͷ����¼�ʱ����Ĳ���һ�£�
 �¼��ڲ����Զ����¼�����Ĳ����������ص�ָ�룩���Ϊ�¼�key�ģ�
 ���ȡ���Ͷ���ʱ������һ�£� ȡ�����ľͻ�ʧ�ܣ��ͻᵼ�����¼�����������Ұָ�룩���´θ��¼�������ʱ�򴥷��ص��ͻ��쳣

 �¼�Ƕ�ײ�������̫�࣬������ԣ�������Ҫʹ���¼�Ƕ�ף���Ҫ��Ϊ�˱��������ѭ����Ŀǰ�¼����Ƕ�ײ���֧��5��
*/

//�����¼����͹�ȥ�����ݱ���̳�
class NFEventContext
{

};

/** 
 *@brief �¼�ϵͳ����������ʹ���¼�ϵͳ�Ķ�����̳��������
 */
class NFEventObj
{
public:
	/** 
	 *@brief ���캯��
	 */
	NFEventObj();

	/** 
	 *@brief ��������
	 */
	virtual ~NFEventObj();
public:
	/**
	* @brief �յ��¼�����, ���յ����¼����д���
	*  
	* @param nEventID		�¼�ID
	* @param nSrcID			�¼�ԴID��һ�㶼����ң�����Ψһid
	* @param bySrcType		�¼�Դ���ͣ�������ͣ���������֮���
	* @param pEventContext	���������¼�����
	* @return				
	*/
	virtual void OnExecute(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext) = 0;
public:
	/**
	* @brief �����¼�,��ִ���յ��¼��Ķ���Ķ�Ӧ����
	*  
	* @param nEventID		�¼�ID
	* @param nSrcID			�¼�ԴID��һ�㶼����ң�����Ψһid
	* @param bySrcType		�¼�Դ���ͣ�������ͣ���������֮��� 
	* @param pEventContext	�¼����������
	* @return				ִ���Ƿ�ɹ� 
	*/
	void FireExecute(uint16_t nEventID,uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext);

	/**
	* @brief �����¼�
	*  
	* @param nEventID	�¼�ID
	* @param nSrcID		�¼�ԴID��һ�㶼����ң�����Ψһid
	* @param bySrcType	�¼�Դ���ͣ�������ͣ���������֮���
	* @param desc		�¼����������ڴ�ӡ����ȡ��Ϣ���鿴BUG֮���
	* @return			�����¼��Ƿ�ɹ� 
	*/
	bool Subscribe(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, const std::string& desc);

	/**
	* @brief ȡ�������¼�
	*  
	* @param nEventID	�¼�ID
	* @param nSrcID		�¼�ԴID��һ�㶼����ң�����Ψһid
	* @param bySrcType	�¼�Դ���ͣ�������ͣ���������֮���
	* @return			ȡ�������¼��Ƿ�ɹ� 
	*/
	bool UnSubscribe(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType);

	/**
	* @brief ȡ��NFEventObj���ж����¼�
	*  
	* @return			ȡ�������¼��Ƿ�ɹ� 
	*/
	bool UnSubscribeAll();
};
