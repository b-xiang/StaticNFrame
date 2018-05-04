// -------------------------------------------------------------------------
//    @FileName			:    {Filename}
//    @Author           :    GaoYi
//    @Date             :    2017-09-27
//    @Module           :   {Filename}
//
// -------------------------------------------------------------------------

#pragma once

#include "NFPlatform.h"

#include <unordered_map>
#include <stdint.h>

/// @brief ��Դ��ͳ�ƽ��
class ResourceStatItem {
public:
	float _average_value;
	float _max_value;
	float _min_value;

	ResourceStatItem() {
		_average_value = 0;
		_max_value = 0;
		_min_value = 0;
	}
};

/// @brief ��Ϣ��ͳ�ƽ��
class MessageStatItem {
public:
	float _failure_rate;
	std::unordered_map<int32_t, uint32_t> _result;
	uint32_t _average_cost_ms;
	uint32_t _max_cost_ms;
	uint32_t _min_cost_ms;

	MessageStatItem() {
		_failure_rate = 0;
		_average_cost_ms = 0;
		_max_cost_ms = 0;
		_min_cost_ms = UINT32_MAX;
	}
};


typedef std::unordered_map<std::string, ResourceStatItem> ResourceStatResult;
typedef std::unordered_map<std::string, MessageStatItem> MessageStatResult;


/// @brief ������ͳ��ģ�飬ֻ�ṩ���ݵļ�¼�ͼ��㣬���ݵ�ʹ�ý���������
class NFStat {
public:
	NFStat() : m_message_counts(0), m_failure_message_counts(0) {}

	~NFStat() {}

	/// @brief �����Ѿ���¼������
	void Clear();

	/// @brief �����Դͳ�����Դ��ͳ��һ�㶨ʱ�������������(������ƽ���������С��)
	/// @param name ��Դ�����ƣ�Ҫ��ǿ�
	/// @param value ����ֵ
	/// @return 0 �ɹ�
	/// @return ��0 ʧ��
	int32_t AddResourceItem(const std::string& name, float value);

	/// @brief �����Ϣͳ��
	/// @param name ��Ϣ��ʶ������Ϣ����Ҫ��ǿ�
	/// @param result ��Ϣ��������0��ʾ�ɹ�����0Ϊ�����룬��ʾʧ��
	/// @param time_cost_ms ��Ϣ����ʱ�ӣ���λ����
	/// @return 0 �ɹ�
	/// @return ��0 ʧ��
	int32_t AddMessageItem(const std::string& name, int32_t result, int32_t time_cost_ms);

	/// @brief �����Ϣͳ�ƣ�����޴���Ϣ��ͳ��������һ��ͳ���ֵΪ0�������
	/// @param name ��Ϣ��ʶ������Ϣ����Ҫ��ǿ�
	/// @return 0 �ɹ�
	/// @return ��0 ʧ��
	int32_t AddMessageItem(const std::string& name);

	/// @brief �����ֻ�ȡ��Դ��ͳ�ƽ��
	/// @return NULL ʧ�� �޴����ֵ�ͳ��
	/// @return ��NULL �ɹ�
	const ResourceStatItem* GetResourceResultByName(const std::string& name);

	/// @brief �����ֻ�ȡ��Ϣ��ͳ�ƽ��
	/// @return NULL ʧ�� �޴����ֵ�ͳ��
	/// @return ��NULL �ɹ�
	const MessageStatItem* GetMessageResultByName(const std::string& name);

	/// @brief ��ȡ������Դ��ͳ�ƽ��
	const ResourceStatResult* GetAllResourceResults();

	/// @brief ��ȡ������Ϣ��ͳ�ƽ��
	const MessageStatResult* GetAllMessageResults();

	/// @brief ��ȡ������Ϣ��
	uint32_t GetAllMessageCounts() {
		return m_message_counts;
	}

	/// @brief ��ȡ����ʧ�ܵ���Ϣ��
	uint32_t GetAllFailureMessageCounts() {
		return m_failure_message_counts;
	}

private:
	// ��Դ��ͳ���е���ʱ����
	class ResourceStatTempData {
	public:
		uint32_t _count;
		float    _total_value;
		ResourceStatItem* _result;

		ResourceStatTempData() {
			_count = 0;
			_total_value = 0;
			_result = NULL;
		}
	};

	// ��Ϣ��ͳ���е���ʱ����
	class MessageStatTempData {
	public:
		int64_t _total_count;
		int64_t _total_cost_ms;
		float   _failure_count;
		MessageStatItem* _result;

		MessageStatTempData() {
			_total_count = 0;
			_failure_count = 0;
			_total_cost_ms = 0;
			_result = NULL;
		}
	};

	void CalculateResourceStatResult(ResourceStatTempData* resource_stat_temp);
	void CalculateMessageStatResult(MessageStatTempData* message_stat_temp);

private:
	uint32_t m_message_counts;
	uint32_t m_failure_message_counts;
	ResourceStatResult m_resource_stat_result;
	MessageStatResult  m_message_stat_result;

	// ͳ�ƹ����е���ʱ����
	typedef std::unordered_map<std::string, ResourceStatTempData> ResourceStatTemp;
	typedef std::unordered_map<std::string, MessageStatTempData> MessageStatTemp;
	ResourceStatTemp   m_resource_stat_temp;
	MessageStatTemp    m_message_stat_temp;
};