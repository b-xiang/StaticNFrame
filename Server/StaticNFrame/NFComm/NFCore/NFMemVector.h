// -------------------------------------------------------------------------
//    @FileName         :    NFMemVector.h
//    @Author           :    GaoYi
//    @Date             :    2018-11-27
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <sstream>
#include <string.h>
#include "NFPlatform.h"
#include "NFException.hpp"

/////////////////////////////////////////////////
/**
* @file tc_mem_vector.h
* @brief  �����ڴ�������.
*
*/
/////////////////////////////////////////////////

/**
* @brief �쳣��
*/
struct NF_MemVectorException : public NFException
{
	NF_MemVectorException(const string &buffer) : NFException(buffer) {};
	NF_MemVectorException(const string &buffer, int err) : NFException(buffer, err) {};
	~NF_MemVectorException() throw() {};
};

/**
* @brief �����ڴ�����������ݿ�.
*
* ÿ�����ݿ��С��ȣ�ģ�����Tֻ���Ǽ򵥵���������
*
* ��Ҫ�߱�bit-copy���������
*/
template<typename T>
class NFMemVector
{
public:

	/**
	* @brief ���캯��
	*/
	NFMemVector() : _pHead(NULL), _pData(NULL)
	{
	}

	/**
	* @brief
	* @param mv
	*/
	NFMemVector(const NFMemVector<T> &mv)
		: _pHead(mv._pHead), _pData(mv._pData)
	{

	}

	/**
	* @brief
	* @param mv
	*
	* @return bool
	*/
	bool operator==(const NFMemVector<T> &mv)
	{
		return _pHead == mv._pHead && _pData == mv._pData;
	}

	/**
	* @brief
	* @param mv
	*
	* @return bool
	*/
	bool operator!=(const NFMemVector<T> &mv)
	{
		return _pHead != mv._pHead || _pData != mv._pData;
	}

	/**
	* @brief ������Ҫ���ڴ�ռ�
	* @param iCount  ���ݸ���
	* @return size_t  �ڴ�ռ��С
	*/
	static size_t calcMemSize(size_t iCount)
	{
		return sizeof(T) * iCount + sizeof(tagMemQueueHead);
	}

	/**
	* @brief ��ʼ��
	* @param pAddr       ָ����пռ��ָ��
	* @param iSize       �ռ��ָ��
	* @param iBlockSize ÿ��block�Ĵ�С
	*/
	void create(void *pAddr, size_t iSize);

	/**
	* @brief �����϶���
	* @param pAddr ָ����пռ��ָ��
	*/
	void connect(void *pAddr) { init(pAddr); assert(_pHead->_iBlockSize == sizeof(T)); }

	/**
	* @brief Ԫ�ظ���
	* @return size_t�����г���
	*/
	size_t size() { return _pHead->_iBlockCount; }

	/**
	* @brief �����ڴ泤��
	* @return size_t : �����ڴ泤��
	*/
	size_t getMemSize() { return _pHead->_iSize; }

	/**
	* @brief �ؽ�
	*/
	void clear();

	/**
	* @brief
	* @param simple
	*
	* @return string
	*/
	string desc() const;

	/**
	* @brief ������
	*/
	class NF_MemVectorIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		/**
		* @brief ���캯��
		* @param pmv
		* @param iIndex
		*/
		NF_MemVectorIterator(NFMemVector *pmv, size_t iIndex) : _pmv(pmv), _iIndex(iIndex)
		{
		}

		/**
		* @brief ǰ��++
		*
		* @return TC_MemVectorIterator&
		*/
		NF_MemVectorIterator& operator++()
		{
			++_iIndex;
			return *this;
		}

		/**
		* @brief ����++
		*/
		NF_MemVectorIterator operator++(int)
		{
			NF_MemVectorIterator tmp = *this;

			++_iIndex;
			return tmp;
		}

		/**
		* @brief
		* @param mv
		*
		* @return TC_MemVectorIterator
		*/
		bool operator==(const NF_MemVectorIterator& mv)
		{
			return _iIndex == mv._iIndex && _pmv == mv._pmv;
		}

		/**
		* @brief
		* @param mv
		*
		* @return TC_MemVectorIterator
		*/
		bool operator!=(const NF_MemVectorIterator& mv)
		{
			return _iIndex != mv._iIndex || _pmv != mv._pmv;
		}

		/**
		* @brief
		*
		* @return T&
		*/
		T& operator*() const { return (*_pmv)[_iIndex]; }

		/**
		* @brief
		*
		* @return T*
		*/
		T* operator->() const { return &(*_pmv)[_iIndex]; }

	private:
		/**
		*
		*/
		NFMemVector    *_pmv;

		/**
		*
		*/
		size_t          _iIndex;
	};

	typedef NF_MemVectorIterator iterator;

	/**
	*
	*
	* @return TC_MemVectorIterator
	*/
	NF_MemVectorIterator begin() { return NF_MemVectorIterator(this, 0); }

	/**
	*
	*
	* @return TC_MemVectorIterator
	*/
	NF_MemVectorIterator end() { return NF_MemVectorIterator(this, _pHead->_iBlockCount); }

	/**
	* @brief ��ȡ����
	* @param pData
	* @param iDataLen
	*/
	T& operator[](size_t iIndex)
	{
		if (iIndex >= _pHead->_iBlockCount)
		{
			ostringstream s;
			s << string("[TC_MemVector::get] index beyond : index = ") << iIndex << " > " << _pHead->_iBlockCount;

			throw NF_MemVectorException(s.str());
		}

		return *(T*)((char*)_pData + iIndex * _pHead->_iBlockSize);
	}

	/**
	* @brief ��ȡͷ��ַ
	*
	* @return void*
	*/
	void *getAddr() { return (void*)_pHead; }

#if NF_PLATFORM == NF_PLATFORM_WIN
#pragma  pack (push,1)
	/**
	*  @brief ���п��ƽṹ
	*/
	struct tagMemQueueHead
	{
		size_t _iSize;          //�ڴ��С
		size_t _iBlockCount;    //Ԫ�ظ���
		size_t _iBlockSize;     //�����С
	};
#pragma pack(pop)
#else
	/**
	*  @brief ���п��ƽṹ
	*/
	struct tagMemQueueHead
	{
		size_t _iSize;          //�ڴ��С
		size_t _iBlockCount;    //Ԫ�ظ���
		size_t _iBlockSize;     //�����С
	}__attribute__((packed));
#endif

protected:

	/**
	* @brief
	* @param pAddr
	*/
	void init(void *pAddr)
	{
		_pHead = static_cast<tagMemQueueHead*>(pAddr);
		_pData = (char*)_pHead + sizeof(tagMemQueueHead);
	}


	/**
	* ���п��ƿ�
	*/
	tagMemQueueHead *_pHead;

	/**
	* �����ڴ��ַ
	*/
	void            *_pData;
};

template<typename T>
void NFMemVector<T>::create(void *pAddr, size_t iSize)
{
	size_t iBlockSize = sizeof(T);

	if (iSize <= sizeof(tagMemQueueHead) || ((iSize - sizeof(tagMemQueueHead)) / iBlockSize == 0))
	{
		throw NF_MemVectorException("[TC_MemVector::create] memory size not enough.");
	}

	init(pAddr);

	memset(pAddr, 0x00, iSize);

	_pHead->_iSize = iSize;
	_pHead->_iBlockCount = (iSize - sizeof(tagMemQueueHead)) / iBlockSize;
	_pHead->_iBlockSize = iBlockSize;
}

template<typename T>
void NFMemVector<T>::clear()
{
	assert(_pHead);

	memset(_pData, 0x00, _pHead->_iBlockSize * _pHead->_iBlockCount);
}

template<typename T>
string NFMemVector<T>::desc() const
{
	ostringstream s;
	s << "[TC_MemVector] [_iSize=" << _pHead->_iSize << "] "
		<< "[_iBlockCount=" << _pHead->_iBlockCount << "] "
		<< "[_iBlockSize=" << _pHead->_iBlockSize << "] "
		<< endl;
	s << "[~TC_MemVector]";

	return s.str();
}
