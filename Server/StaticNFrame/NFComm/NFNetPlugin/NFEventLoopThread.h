// -------------------------------------------------------------------------
//    @FileName         :    NFEventLoopThread.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/26
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFLoopThreadStatus.h"

#include <thread>
#include <mutex>

class NFEventLoop;

class NFEventLoopThread : public NFLoopTheadStatus
{
public:
	enum
	{
		kOK = 0
	};

	// Return 0 means OK, anything else means failed.
	typedef std::function<int()> Functor;

	/**
	 * @brief
	 *
	 * @return 
	 */
	NFEventLoopThread();

	/**
	 * @brief
	 *
	 * @return 
	 */
	~NFEventLoopThread();

	/**
	 * @brief �����߳�
	 *
	 * @param  wait_thread_started =true, ���߳̽���������֪���߳̿�ʼ����
	 * @param  pre		�߳�һ��ʼ������ִ��
	 * @param  post     �߳̽�ֹͣǰ���ᱻ����
	 * @return bool
	 */
	bool Start(bool wait_thread_started = true,
	           Functor pre = Functor(),
	           Functor post = Functor());

	/**
	 * @brief ֹͣ�̵߳�����, ֻ�����߳�����
	 *
	 * @param  wait_thread_exit = true ���ȴ��߳��˳��󣬲ż�������
	 * @return void
	 */
	void Stop(bool wait_thread_exit = false);

	/**
	 * @brief �ȴ��߳��˳���ֻ�������߳������
	 *
	 * @return void
	 */
	void Join();

	/**
	 * @brief �����߳�����
	 */
	void SetName(const std::string& n);

	/**
	* @brief �߳�����
	*/
	const std::string& GetName() const;

	NFEventLoop* Loop() const;

	struct event_base* event_base();

	std::thread::id GetTid() const;

	/**
	 * @brief �߳��Ƿ�������
	 *
	 * @return bool
	 */
	bool IsRunning() const;
private:
	/**
	 * @brief �߳�Ҫ���еĺ���
	 */
	void Run(const Functor& pre, const Functor& post);

	/**
	* @brief �߳�ѭ���ṹ��
	*/
	std::shared_ptr<NFEventLoop> event_loop_;

	/**
	* @brief �߳���
	*/
	std::mutex mutex_;

	/**
	* @brief �̶߳���
	*/
	std::shared_ptr<std::thread> thread_; // Guard by mutex_

	/**
	 * @brief ����
	 */
	std::string name_;
};

