#pragma once

#include "NFXActor.h"

class NFXActorMgr;
class CDB;
class NFTask;

/**
* @brief �첽дDB��actor
*
*/
class NFDBActor : public NFXActor
{
public:
	/**
	* @brief ���캯��
	*/
	NFDBActor(Theron::Framework& framework, NFXActorMgr* pActorMgr);

	/**
	* @brief ��������
	*/
	virtual ~NFDBActor();

	/**
	* @brief ��ʼ��DBϵͳ����ͨ��stDBInfo�����������ݿ�
	*
	* @param fo ���ݿ�����
	* @return true�������ݿ�ɹ�, falseʧ��
	*/
	bool Init();

	/**
	* @brief ��actor�̴߳�����Ϣ
	*
	* @param message Ҫ�������Ϣ����
	* @param from    ����Ϣ��actor�ĵ�ַ
	* @return
	*/
	virtual void Handler(const NFXActorMessage& message, const Theron::Address from);

	/**
	* @brief �������������Ϣ���ظ����߳�
	*
	* @param message �����������Ϣ
	* @param from    ����Ϣ��actor�ĵ�ַ
	* @return
	*/
	virtual void HandlerEx(const NFXActorMessage& message, const Theron::Address from);
public:
	/**
	* @brief ����taskǰ�Ĵ���
	*
	* @param pTask Ҫ���������
	* @return
	*/
	void onProcessTaskStart(NFTask* pTask);
	/**
	* @brief task�����Ĵ���
	*
	* @param pTask Ҫ���������
	* @return
	*/
	void onProcessTaskEnd(NFTask* pTask);
	/**
	* @brief �첽��������ϵͳ
	*
	* @param pTask Ҫ���������
	* @return
	*/
	void processTask(NFTask* pTask);
private:
	/**
	* @brief ���ݿ��Ƿ��ʼ��
	*/
	bool m_bInit;
};

