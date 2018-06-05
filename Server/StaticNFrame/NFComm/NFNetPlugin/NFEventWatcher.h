// -------------------------------------------------------------------------
//    @FileName         :    NFEventWatcher.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/26
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFDuration.h"
#include <functional>
#include <event2/util.h>

struct event;
struct event_base;

class NFEventLoop;

/**
* @brief ���߳��¼�֪ͨ�������
*/
class NFEventWatcher
{
public:
	typedef std::function<void()> Handler;

	/**
	 * @brief ��������
	 */
	virtual ~NFEventWatcher();

	/**
	 * @brief ��ʼ������Ҫ�ĳ�ʼ���ڼ̳���DoInit�����У�
	 * ����������հ��¼�set��event_base��, ��IOѭ����������¼�
	 *
	 * @return bool
	 */
	bool Init();

	/**
	 * @brief �ͷ�event�� �����cancel�ص����������ûص�, ������event�߳�������
	 *
	 * @return void
	 */
	void Cancel();

	/**
	 * @brief ����event cancel�ص�����
	 *
	 * @param  cb
	 * @return void
	 */
	void SetCancelCallback(const Handler& cb);

	/**
	 * @brief ������¼��ص���������
	 *
	 * @return void
	 */
	void ClearHandler()
	{
		handler_ = Handler();
	}

protected:
	/**
	 * @brief �������ʱ�ȴ��� 0 ���õȴ��� ֱ�����¼����ͣ� ������event�߳������
	 *
	 * @param  timeout
	 * @return bool
	 */
	bool Watch(NFDuration timeout);

	/**
	 * @brief ���캯��, ����event_base, �¼�����ʱҪ�ص��ĺ���
	 *
	 * @param  evbase
	 * @param  handler
	 * @return
	 */
	NFEventWatcher(struct event_base* evbase, const Handler& handler);
	NFEventWatcher(struct event_base* evbase, Handler&& handler);

	/**
	 * @brief ��Ҫ����DoClose, �ɼ̳���ʵ��
	 *
	 * @return void
	 */
	void Close();

	/**
	 * @brief �ͷ��¼�
	 *
	 * @return void
	 */
	void FreeEvent();

	/**
	 * @brief ��Ҫ�ĳ�ʼ�����ڼ̳�����ʵ��
	 *
	 * @return bool
	 */
	virtual bool DoInit() = 0;

	/**
	* @brief ��Ҫ�Ĺرպ������ڼ̳�����ʵ��
	*
	* @return bool
	*/
	virtual void DoClose()
	{
	}

	/**
	* @brief �¼��ṹ�壬�Լ�����
	*/
	struct event* event_;

	/**
	* @brief ������event_base�ṹ
	*/
	struct event_base* evbase_;

	/**
	* @brief �¼��ṹ����û��add
	*/
	bool attached_;

	/**
	* @brief ���¼��ص�
	*/
	Handler handler_;

	/**
	* @brief cancel�ص�
	*/
	Handler cancel_callback_;
};

/**
* @brief �ܵ�ͨ����
*/
class NFPipeEventWatcher : public NFEventWatcher
{
public:
	/**
	* @brief ���캯��, ����event_base, �¼�����ʱҪ�ص��ĺ���
	*
	* @param  evbase
	* @param  handler
	* @return
	*/
	NFPipeEventWatcher(NFEventLoop* loop, const Handler& handler);
	NFPipeEventWatcher(NFEventLoop* loop, Handler&& handler);

	/**
	 * @brief ��������
	 *
	 * @return
	 */
	~NFPipeEventWatcher();

	/**
	 * @brief ��Ҫ�����ǰ��¼��ӵ��¼��б��У�������д���첽�ȴ��Ǽ�����˼
	 *
	 * @return bool
	 */
	bool AsyncWait();

	/**
	 * @brief ͨ����д�ܵ�д���ݣ�����֪ͨ
	 *
	 * @return void
	 */
	void Notify();

	/**
	 * @brief ����дͨ��
	 *
	 * @return evutil_socket_t
	 */
	evutil_socket_t wfd() const
	{
		return pipe_[0];
	}

private:
	/**
	 * @brief ��ʼ���ܵ�, ��˼�����
	 * ��notify��дͨ��д����ʱ����ͨ�������¼�������HandlerFn,
	 *  HandlerFn�Ӷ�ͨ����ȡ���ݺ󣬵����¼��ص�
	 *
	 * @return bool
	 */
	virtual bool DoInit();

	/**
	 * @brief �رչܵ�
	 *
	 * @return void
	 */
	virtual void DoClose();

	/**
	 * @brief ��ͨ�������¼��ص�
	 *
	 * @param  fd
	 * @param  which
	 * @param  v
	 * @return void
	 */
	static void HandlerFn(evutil_socket_t fd, short which, void* v);

	/**
	* @brief �ܵ��� 0��дͨ����1�Ƕ�ͨ��
	*/
	evutil_socket_t pipe_[2]; // Write to pipe_[0] , Read from pipe_[1]
};

/**
* @brief ��ʱ����ʱ
*/
class NFTimerEventWatcher : public NFEventWatcher
{
public:
	/**
	 * @brief ���캯��, ����event_base, ���������Լ�ʱ��
	 *
	 * @param  loop
	 * @param  handler
	 * @param  timeout
	 * @return
	 */
	NFTimerEventWatcher(NFEventLoop* loop, const Handler& handler, NFDuration timeout);
	NFTimerEventWatcher(NFEventLoop* loop, Handler&& handler, NFDuration timeout);
	NFTimerEventWatcher(struct event_base* loop, const Handler& handler, NFDuration timeout);
	NFTimerEventWatcher(struct event_base* loop, Handler&& handler, NFDuration timeout);

	/**
	 * @brief ��ʱ�ȴ��������涨ʱ��͵���HandlerFn����
	 *
	 * @return bool
	 */
	bool AsyncWait();

private:
	/**
	 * @brief ��ʼ��������ʱ��͵���HandlerFn
	 *
	 * @return bool
	 */
	virtual bool DoInit();

	/**
	 * @brief �ص��¼�����
	 *
	 * @param  fd
	 * @param  which
	 * @param  v
	 * @return void
	 */
	static void HandlerFn(evutil_socket_t fd, short which, void* v);
private:
	NFDuration timeout_;
};

/**
* @brief �ź��¼�����, �յ��źžʹ����¼��ص�handler
*/
class NFSignalEventWatcher : public NFEventWatcher
{
public:
	NFSignalEventWatcher(evutil_socket_t signo, NFEventLoop* loop, const Handler& handler);
	NFSignalEventWatcher(evutil_socket_t signo, NFEventLoop* loop, Handler&& handler);

	/**
	 * @brief һֱ�ȴ���ֱ���¼�������
	 *
	 * @return bool
	 */
	bool AsyncWait();
private:
	/**
	 * @brief ��ʼ�����յ��źž͵���HandlerFn
	 *
	 * @return bool
	 */
	virtual bool DoInit();

	/**
	 * @brief ����handler
	 *
	 * @param  sn
	 * @param  which
	 * @param  v
	 * @return void
	 */
	static void HandlerFn(evutil_socket_t sn, short which, void* v);

	/**
	* @brief �ź�
	*/
	int signo_;
};
