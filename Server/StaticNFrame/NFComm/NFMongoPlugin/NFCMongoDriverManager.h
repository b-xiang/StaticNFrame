// -------------------------------------------------------------------------
//    @FileName         :    NFCMysqlDriverManager.h
//    @Author           :    Chuanbo.Guo
//    @Date             :    2014-11-10
//    @Module           :    NFCMysqlDriverManager
//
// -------------------------------------------------------------------------

#pragma once


#include "NFCMongoDriver.h"
#include <NFComm/NFCore/NFMap.hpp>

class NFCMongoDriverManager
{
public:
	NFCMongoDriverManager();

	virtual ~NFCMongoDriverManager();

	/**
	* @brief ���serverid������, һ��serverid��Ӧһ���������ݿ������
	*
	* @return bool
	*/
	virtual bool AddMongoServer(const int nServerID, const std::string& ip, uint32_t port, const std::string& dbname);

	/**
	* @brief �Ƿ���ڱ��
	*
	* @return bool
	*/
	virtual bool IsExistCollection(const int nServerID, const std::string& collectionName);

	/**
	* @brief �������
	*
	* @return bool
	*/
	virtual bool CreateCollection(const int nServerID, const std::string& collectionName, const std::string& key);

	/**
	* @brief ɾ�����
	*
	* @return bool
	*/
	virtual bool DropCollection(const int nServerID, const std::string& collectionName);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool InsertOne(const int nServerID, const std::string& collectionName, const std::string& json_query);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOne(const int nServerID, const std::string& collectionName, const std::string& json_query);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::vector<std::string> FindMany(const int nServerID, const std::string& collectionName, const std::string& json_query, const std::string& json_opts = "");

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::vector<std::string> FindAll(const int nServerID, const std::string& collectionName);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneyByKey(const int nServerID, const std::string& collectionName, int64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneyByKey(const int nServerID, const std::string& collectionName, const std::string& key);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool InsertOne(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, const std::string key);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, uint64_t key);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, uint64_t key);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const int nServerID, const std::string& collectionName, const std::string& json);

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message);

	/**
	* @brief ��ʱ�������
	*
	* @return bool
	*/
	virtual void CheckMongo();
protected:
	NFMap<int, NFCMongoDriver> mMongoDriver;
	NFMap<int, NFCMongoDriver> mInvalidMongoDriver;
	uint64_t mnLastCheckTime;
};

