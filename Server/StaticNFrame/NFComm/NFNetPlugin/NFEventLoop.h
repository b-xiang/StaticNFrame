// -------------------------------------------------------------------------
//    @FileName         :    NFEventLoop.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/26
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFLoopThreadStatus.h"
#include "NFComm/NFCore/NFPlatform.h"
#include <mutex>
#include <vector>

struct event_base;
class NFPipeEventWatcher;

// This is the IO Event driving kernel. Reactor model.
// This class is a wrapper of event_base but not only a wrapper.
// It provides a simple way to run a IO Event driving loop.
// One thread one loop.
/**
* @brief ����IO�¼���������, Reactorģʽʵ��
* ������װ��event_base������������һ����װ���ѣ�
* ���ṩ��һ���򵥵ķ�ʽ��ѭ��������ȥ����IO�¼�
*  һ���߳�һ��ѭ��
*/
class NFEventLoop : public NFLoopTheadStatus
{
public:
	typedef std::function<void()> Functor;
public:
	/**
	 * @brief ���캯��, �����Լ�����һ���Լ���event_base, ��һֱ������
	 */
	NFEventLoop();

	/**
	* @brief ���캯���� ����ʹ��һ���Ѿ����ڵ�event_base�ṹ��
	*/
	explicit NFEventLoop(struct event_base* base);

	/**
	 * @brief ��������
	 */
	~NFEventLoop();

	// @brief Run the IO Event driving loop forever
	// @note It must be called in the IO Event thread

	/**
	 * @brief �߳����е���ѭ��, ��һֱ����IO�¼�����
	 * �������������IO�߳�������
	 * @return void
	 */
	void Run();

	/**
	 * @brief ֹͣIO�¼�ѭ��
	 *
	 * @return void
	 */
	void Stop();

	/**
	 * @brief ��IO�߳������к���handler��
	 * �����������������io�߳����ô����ִ��
	 * ����ڱ���߳�����Ȱ��¼����͵�������Ȼ����ѭ����ִ��
	 *
	 * @param  handler Ҫִ�еĺ���
	 * @return void
	 */
	void RunInLoop(const Functor& handler);

	/**
	 * @brief �Ѻ������浽������, Ȼ����IO�߳���ִ��
	 *
	 * @param  handler Ҫִ�еĺ���
	 * @return void
	 */
	void QueueInLoop(const Functor& handler);

	/**
	* @brief ��IO�߳������к���handler��
	* �����������������io�߳����ô����ִ��
	* ����ڱ���߳�����Ȱ��¼����͵�������Ȼ����ѭ����ִ��
	*
	* @param  handler Ҫִ�еĺ���
	* @return void
	*/
	void RunInLoop(Functor&& handler);

	/**
	* @brief �Ѻ������浽������, Ȼ����IO�߳���ִ��
	*
	* @param  handler Ҫִ�еĺ���
	* @return void
	*/
	void QueueInLoop(Functor&& handler);

	/**
	 * @brief �������event_base
	 *
	 * @return struct event_base*
	 */
	struct event_base* event_base();

	/**
	 * @brief ��ǰ�Ƿ���IO�߳�������
	 *
	 * @return bool
	 */
	bool IsInLoopThread() const
	{
		return tid_ == std::this_thread::get_id();
	}

	/**
	 * @brief ������ĺ����������, �̰߳�ȫ
	 *
	 * @return int
	 */
	int pending_functor_count() const
	{
		return pending_functor_count_.load();
	}

	/**
	 * @brief �߳�ID
	 *
	 * @return const std::thread::id&
	 */
	const std::thread::id& tid() const
	{
		return tid_;
	}

private:
	/**
	 * @brief ��ʼ������
	 *
	 * @return void
	 */
	void Init();

	/**
	 * @brief ��ʼ��watcher�� ���ڶ��߳�֮���ͨ��
	 *
	 * @return void
	 */
	void InitNotifyPipeWatcher();

	/**
	 * @brief ��IO�߳������IOѭ���˳�����
	 *
	 * @return void
	 */
	void StopInLoop();

	/**
	 * @brief ��IO�߳���ִ�ж�����ĺ�������
	 *
	 * @return void
	 */
	void DoPendingFunctors();

	/**
	 * @brief ��ö����ﺯ���������, �̷߳ǰ�ȫ��ֻ����IO�߳�������
	 *
	 * @return size_t
	 */
	size_t GetPendingQueueSize();

	/**
	 * @brief �Ƿ����Ϊ�գ����̰߳�ȫ��ֻ����IO�߳�������
	 *
	 * @return bool
	 */
	bool IsPendingQueueEmpty();

	/**
	* @brief libevent��Ҫ���ݽṹ
	*/
	struct event_base* evbase_;

	/**
	* @brief evbase�Ƿ����Լ�����
	*/
	bool create_evbase_myself_;

	/**
	* @brief �߳�ID���߳�û������ǰ�����߳�ID�� �߳����к���IO�߳�ID
	*/
	std::thread::id tid_;

	/**
	* @brief �߳���, ��������pending_functors_
	*/
	std::mutex mutex_;

	/**
	* @brief ֪ͨ�̣߳� ����һ�������̶߳�����
	*/
	std::shared_ptr<NFPipeEventWatcher> watcher_;

	/**
	* @brief �����Ƿ�һ�����񵽶���� ��Ҫ֪ͨ�߳�ȥ���У������뷴��֪ͨ
	*/
	std::atomic<bool> notified_;

	/**
	* @brief ����������, ����߳�ʹ��
	*/
	std::vector<Functor>* pending_functors_; // @Guarded By mutex_

	/**
	* @brief ���������С, ������߳���
	*/
	std::atomic<int> pending_functor_count_;
};
