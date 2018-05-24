// -------------------------------------------------------------------------
//    @FileName         :    NFThread.hpp
//    @Author           :    GaoYi
//    @Date             :    2017-04-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include<thread>
#include<functional>
#include<memory>
#include <atomic>
#include<mutex>

#include "NFPlatform.h"

//�̶߳���

class NFThread
{
public:
	NFThread()
	{
		m_running = false;
	}

	virtual ~NFThread()
	{
		StopThread();
	}

public:
	//�����߳�
	template <class BaseType>
	bool StartThread(BaseType* baseType, void (BaseType::*HandleFunction)())
	{
		m_running = true;
		m_thread = std::make_shared<std::thread>(HandleFunction, baseType);
		return true;
	}

	//��ֹ�߳�
	virtual bool StopThread()
	{
		std::call_once(m_flag, [this]
		               {
			               StopThreadFunction();
		               }); //��֤���߳������ֻ����һ��StopThread
		return true;
	}

private:
	void StopThreadFunction()
	{
		m_running = false;
		m_thread->join();
		m_thread = nullptr;
	}

protected:
	NF_SHARE_PTR<std::thread> m_thread; //�̶߳���
	atomic_bool m_running; //���б�־
	std::once_flag m_flag;
};

