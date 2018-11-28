// -------------------------------------------------------------------------
//    @FileName         :    NFConsistentHashNew.h
//    @Author           :    GaoYi
//    @Date             :    2018-11-27
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include "NFMD5.h"
#include "NFAutoPtr.h"
#include "NFHash.hpp"
#include "NFCommon.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

struct NFNode_T_New
{
	/**
	*�ڵ�hashֵ
	*/
	long iHashCode;

	/**
	*�ڵ��±�
	*/
	unsigned int iIndex;
};

enum NF_HashAlgorithmType
{
	E_TC_CONHASH_KETAMAHASH = 0,
	E_TC_CONHASH_DEFAULTHASH = 1
};

/**
*  @brief hash �㷨�����
*/
class NF_HashAlgorithm : public NF_HandleBase
{
public:
	virtual long hash(const std::string & sKey) = 0;
	virtual NF_HashAlgorithmType getHashType() = 0;

protected:
	long subTo32Bit(long hash)
	{
		return (hash & 0xFFFFFFFFL);
	}

};

typedef NFAutoPtr<NF_HashAlgorithm> TC_HashAlgorithmPtr;

/**
*  @brief ketama hash �㷨
*/
class NF_KetamaHashAlg : public NF_HashAlgorithm
{
public:
	virtual long hash(const std::string & sKey)
	{
		string sMd5 = NFMD5::md5bin(sKey);
		const char *p = (const char *)sMd5.c_str();

		long hash = ((long)(p[3] & 0xFF) << 24)
			| ((long)(p[2] & 0xFF) << 16)
			| ((long)(p[1] & 0xFF) << 8)
			| ((long)(p[0] & 0xFF));

		return subTo32Bit(hash);
	}

	virtual NF_HashAlgorithmType getHashType()
	{
		return E_TC_CONHASH_KETAMAHASH;
	}
};

/**
*  @brief Ĭ�ϵ� hash �㷨
*/
class NF_DefaultHashAlg : public NF_HashAlgorithm
{
public:
	virtual long hash(const std::string & sKey)
	{
		std::string sMd5 = NFMD5::md5bin(sKey);
		const char *p = (const char *)sMd5.c_str();

		long hash = (*(int*)(p)) ^ (*(int*)(p + 4)) ^ (*(int*)(p + 8)) ^ (*(int*)(p + 12));

		return subTo32Bit(hash);
	}

	virtual NF_HashAlgorithmType getHashType()
	{
		return E_TC_CONHASH_DEFAULTHASH;
	}
};

/**
*  @brief hash alg ����
*/
class NF_HashAlgFactory
{
public:
	static NF_HashAlgorithm *getHashAlg()
	{
		NF_HashAlgorithm *ptrHashAlg = new NF_DefaultHashAlg();

		return ptrHashAlg;
	}

	static NF_HashAlgorithm *getHashAlg(NF_HashAlgorithmType hashType)
	{
		NF_HashAlgorithm *ptrHashAlg = NULL;

		switch (hashType)
		{
		case E_TC_CONHASH_KETAMAHASH:
		{
			ptrHashAlg = new NF_KetamaHashAlg();
			break;
		}
		case E_TC_CONHASH_DEFAULTHASH:
		default:
		{
			ptrHashAlg = new NF_DefaultHashAlg();
			break;
		}
		}

		return ptrHashAlg;
	}
};

/**
*  @brief һ����hash�㷨��
*/
class  NFConsistentHashNew
{
public:

	/**
	*  @brief ���캯��
	*/
	NFConsistentHashNew()
	{
		_ptrHashAlg = NF_HashAlgFactory::getHashAlg();
	}

	/**
	*  @brief ���캯��
	*/
	NFConsistentHashNew(NF_HashAlgorithmType hashType)
	{
		_ptrHashAlg = NF_HashAlgFactory::getHashAlg(hashType);
	}

	/**
	* @brief �ڵ�Ƚ�.
	*
	* @param m1 node_T_new���͵Ķ��󣬱ȽϽڵ�֮һ
	* @param m2 node_T_new���͵Ķ��󣬱ȽϽڵ�֮һ
	* @return less or not �ȽϽ����less����ture�����򷵻�false
	*/
	static bool less_hash(const NFNode_T_New & m1, const NFNode_T_New & m2)
	{
		return m1.iHashCode < m2.iHashCode;
	}

	/**
	* @brief ���ӽڵ�.
	*
	* @param node  �ڵ�����
	* @param index �ڵ���±�ֵ
	* @return      �ڵ��hashֵ
	*/
	int sortNode()
	{
		sort(_vHashList.begin(), _vHashList.end(), less_hash);

		return 0;
	}

	/**
	* @brief ��ӡ�ڵ���Ϣ
	*
	*/
	void printNode()
	{
		std::map<unsigned int, unsigned int> mapNode;
		size_t size = _vHashList.size();

		for (size_t i = 0; i < size; i++)
		{
			if (i == 0)
			{
				unsigned int value = 0xFFFFFFFF - _vHashList[size - 1].iHashCode + _vHashList[0].iHashCode;
				mapNode[_vHashList[0].iIndex] = value;
			}
			else
			{
				unsigned int value = _vHashList[i].iHashCode - _vHashList[i - 1].iHashCode;

				if (mapNode.find(_vHashList[i].iIndex) != mapNode.end())
				{
					value += mapNode[_vHashList[i].iIndex];
				}

				mapNode[_vHashList[i].iIndex] = value;
			}

			std::cout << "printNode: " << _vHashList[i].iHashCode << "|" << _vHashList[i].iIndex << "|" << mapNode[_vHashList[i].iIndex] << std::endl;
		}

		std::map<unsigned int, unsigned int>::iterator it = mapNode.begin();
		double avg = 100;
		double sum = 0;

		while (it != mapNode.end())
		{
			double tmp = it->second;
			std::cerr << "result: " << it->first << "|" << it->second << "|" << (tmp * 100 * mapNode.size() / 0xFFFFFFFF - avg) << std::endl;
			sum += (tmp * 100 * mapNode.size() / 0xFFFFFFFF - avg) * (tmp * 100 * mapNode.size() / 0xFFFFFFFF - avg);
			it++;
		}

		std::cerr << "variance: " << sum / mapNode.size() << ", size: " << _vHashList.size() << std::endl;
	}

	/**
	* @brief ���ӽڵ�.
	*
	* @param node  �ڵ�����
	* @param index �ڵ���±�ֵ
	* @param weight �ڵ��Ȩ�أ�Ĭ��Ϊ1
	* @return      �Ƿ�ɹ�
	*/
	int addNode(const std::string & node, unsigned int index, int weight = 1)
	{
		if (_ptrHashAlg.get() == NULL)
		{
			return -1;
		}

		NFNode_T_New stItem;
		stItem.iIndex = index;

		for (int j = 0; j < weight; j++)
		{
			std::string virtualNode = node + "_" + NFCommon::tostr<int>(j);

			// TODO: Ŀǰд��2 ��hash �㷨�����Ը�����Ҫѡ��һ�֣�
			// TODO: ����KEMATA Ϊ�ο�memcached client ��hash �㷨��default Ϊԭ�е�hash �㷨�����Խ����ڱ������
			if (_ptrHashAlg->getHashType() == E_TC_CONHASH_KETAMAHASH)
			{
				std::string sMd5 = NFMD5::md5bin(virtualNode);
				char *p = (char *)sMd5.c_str();

				for (int i = 0; i < 4; i++)
				{
					stItem.iHashCode = ((long)(p[i * 4 + 3] & 0xFF) << 24)
						| ((long)(p[i * 4 + 2] & 0xFF) << 16)
						| ((long)(p[i * 4 + 1] & 0xFF) << 8)
						| ((long)(p[i * 4 + 0] & 0xFF));
					stItem.iIndex = index;
					_vHashList.push_back(stItem);
				}
			}
			else
			{
				stItem.iHashCode = _ptrHashAlg->hash(virtualNode);
				_vHashList.push_back(stItem);
			}
		}

		return 0;
	}

	/**
	* @brief ��ȡĳkey��Ӧ���Ľڵ�node���±�.
	*
	* @param key      key����
	* @param iIndex  ��Ӧ���Ľڵ��±�
	* @return        0:��ȡ�ɹ�   -1:û�б���ӵĽڵ�
	*/
	int getIndex(const std::string & key, unsigned int & iIndex)
	{
		if (_ptrHashAlg.get() == NULL || _vHashList.size() == 0)
		{
			iIndex = 0;
			return -1;
		}

		long iCode = _ptrHashAlg->hash(NFMD5::md5bin(key));

		return getIndex(iCode, iIndex);
	}

	/**
	* @brief ��ȡĳhashcode��Ӧ���Ľڵ�node���±�.
	*
	* @param hashcode      hashcode
	* @param iIndex  ��Ӧ���Ľڵ��±�
	* @return        0:��ȡ�ɹ�   -1:û�б���ӵĽڵ�
	*/
	int getIndex(long hashcode, unsigned int & iIndex)
	{
		if (_ptrHashAlg.get() == NULL || _vHashList.size() == 0)
		{
			iIndex = 0;
			return -1;
		}

		// ֻ����32λ
		long iCode = (hashcode & 0xFFFFFFFFL);

		int low = 0;
		int high = _vHashList.size();

		if (iCode <= _vHashList[0].iHashCode || iCode > _vHashList[high - 1].iHashCode)
		{
			iIndex = _vHashList[0].iIndex;
			return 0;
		}

		while (low < high - 1)
		{
			int mid = (low + high) / 2;
			if (_vHashList[mid].iHashCode > iCode)
			{
				high = mid;
			}
			else
			{
				low = mid;
			}
		}
		iIndex = _vHashList[low + 1].iIndex;
		return 0;
	}

	/**
	* @brief ��ȡ��ǰhash�б�ĳ���.
	*
	* @return        ����ֵ
	*/
	size_t size()
	{
		return _vHashList.size();
	}

	/**
	* @brief ��յ�ǰ��hash�б�.
	*
	*/
	void clear()
	{
		_vHashList.clear();
	}

protected:
	std::vector<NFNode_T_New>    _vHashList;
	TC_HashAlgorithmPtr _ptrHashAlg;
};