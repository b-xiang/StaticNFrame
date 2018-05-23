// -------------------------------------------------------------------------
//    @FileName         :    NFBuffer.h
//    @Author           :    GaoYi
//    @Date             :    2017-04-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <cstring>

/////////////////////////////////////////////////
/**
 *@file   NFBuffer.h
 *@brief  �ֽ�����������װ��.
 *
 */
 /////////////////////////////////////////////////

 /**
  *@brief  �ֽ�����������װ��.
  */
class NFBuffer
{
public:
	/**
	 * @brief ���캯��.
	 *
	 */
	NFBuffer() :
		_readPos(0),
		_writePos(0),
		_capacity(0),
		_buffer(NULL),
		_highWaterPercent(50)
	{
	}

	/**
	 * @brief ��������.
	 */
	~NFBuffer()
	{
		delete[] _buffer;
	}

private:
	/**
	 * @brief ��ֹ����
	 */
	NFBuffer(const NFBuffer&);
	void operator=(const NFBuffer&);

public:
	/**
	 * @brief �����ݷ��뻺��
	 *
	 * @param data  Ҫд���������ʼ��ַ
	 * @param size  Ҫд��������ֽ���
	 * @return      д����ֽ���
	 */
	std::size_t PushData(const void* data, std::size_t size);

	/**
	 * @brief ����������д�α�
	 *
	 * @param bytes Ҫ�������ֽ���
	 */
	void Produce(std::size_t bytes) { _writePos += bytes; }

	/**
	 * @brief �ӻ���ȡ������,���,�������α�
	 *
	 * @param buf   �������ݵ���ʼ��ַ
	 * @param size  buf���ֽ���
	 * @return      ʵ��д����ֽ���,����С��size
	 */
	std::size_t PopData(void* buf, std::size_t size);

	/**
	 * @brief �ӻ���ȡ������,ǳ����,���������α�
	 *
	 * @param buf   �������ݵ�ָ��
	 * @param size  �������ݵĴ�С
	 */
	void PeekData(void*& buf, std::size_t& size);

	/**
	 * @brief �������������α�
	 *
	 * @param bytes Ҫ�������ֽ���
	 */
	void Consume(std::size_t bytes);

	/**
	 * @brief �������ɶ�������ʼ��ַ
	 *
	 * @return �������ɶ�������ʼ��ַ
	 */
	char* ReadAddr() { return &_buffer[_readPos]; }

	/**
	 * @brief ��������д��ʼ��ַ
	 *
	 * @return ��������д��ʼ��ַ
	 */
	char* WriteAddr() { return &_buffer[_writePos]; }

	/**
	 * @brief �������Ƿ�������
	 *
	 * @return True:������û������
	 */
	bool IsEmpty() const { return ReadableSize() == 0; }

	/**
	 * @brief ���������ݴ�С
	 *
	 * @return �����������ֽ���
	 */
	std::size_t ReadableSize() const { return _writePos - _readPos; }

	/**
	 * @brief ��������д�ռ��С
	 *
	 * @return ��������д�ռ��ֽ���
	 */
	std::size_t WritableSize() const { return _capacity - _writePos; }

	/**
	 * @brief ������ռ���ڴ��С
	 *
	 * @return ������ռ���ڴ��ֽ���
	 */
	std::size_t Capacity() const { return _capacity; }

	/**
	 * @brief ���ڴ�ռ�������ݴ�С�������ϣ������ͷ��ڴ�(�������������)
	 *
	 */
	void Shrink();

	/**
	 * @brief �������,�����ͷ��ڴ�
	 *
	 */
	void Clear();

	/**
	 * @brief ������������
	 *
	 * @param buf Ҫ�����Ļ���
	 */
	void Swap(NFBuffer& buf);

	/**
	 * @brief ȷ���������㹻��С����size�ֽڵ�����д��
	 *
	 * @param size ��Ҫд��������ֽ���
	 */
	void AssureSpace(std::size_t size);

	/**
	 * @brief ���ø�����,���ڴ���Shrinkʲô������
	 *
	 * @param percents ������[10,100)
	 */
	void SetHighWaterPercent(size_t percents);
	/**
	 * ��������С����
	 */
	static const std::size_t kMaxBufferSize;

	/**
	 * ������Ĭ�ϴ�С
	 */
	static const std::size_t kDefaultSize;

private:
	/**
	 * ���α�
	 */
	std::size_t _readPos;

	/**
	 * д�α�
	 */
	std::size_t _writePos;

	/**
	 * ������ռ�õ��ڴ��ֽ���
	 */
	std::size_t _capacity;

	/**
	 * ������
	 */
	char* _buffer;

	/**
	 * ��ˮλ�ٷֱȣ�Ӱ��Shrink()
	 */
	size_t _highWaterPercent;

	/**
	 * @brief ���軺����ָ��
	 *
	 * @param ptr ��Ҫ���õ�ָ��
	 */
	void ResetBuffer(void* ptr = NULL);
};