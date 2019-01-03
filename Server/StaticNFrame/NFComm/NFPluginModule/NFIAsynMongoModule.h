// -------------------------------------------------------------------------
//    @FileName         :    NFIAsynMongoModule.h
//    @Author           :    Yi.Gao
//    @Date             :    2019-1-1
//    @Module           :    NFIAsynMongoModule
//
//
// -------------------------------------------------------------------------

#pragma once

#include "NFIModule.h"
#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include <vector>
#include <string>
#include <map>

class NFIAsynMongoModule : public NFIModule
{
public:
// 	/**
// 	* @brief ���serverid������, һ��serverid��Ӧһ���������ݿ������
// 	*
// 	* @return bool
// 	*/
// 	virtual bool AddMongoServer(const int nServerID, const std::string& uri, const std::string& dbname) = 0;
// 
// 	virtual bool AddMongoServer(const int nServerID, const std::string& ip, uint32_t port, const std::string& dbname) = 0;
// 
// 	virtual bool IsExistCollection(const int nServerID, const std::string& collectionName) = 0;
// 
// 	virtual bool CreateCollection(const int nServerID, const std::string& collectionName, const std::string& key) = 0;
// 
// 	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, uint64_t key) = 0;
// 
// 	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, uint64_t key) = 0;
// 
// 	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, const std::string& key) = 0;
// 
// 	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, const std::string& key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindOne(const int nServerID, const std::string& collectionName, const std::string& json_query) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::vector<std::string> FindMany(const int nServerID, const std::string& collectionName, const std::string& json_query, const std::string& json_opts = "") = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindAllToJson(const int nServerID, const std::string& collectionName) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::vector<std::string> FindAll(const int nServerID, const std::string& collectionName) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindOneByKey(const int nServerID, const std::string& collectionName, int64_t key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindOneByKey(const int nServerID, const std::string& collectionName, const std::string& key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const std::string& json, const std::string key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const std::string& json, uint64_t key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, uint64_t key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, const std::string& key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindFieldByKey(const int nServerID, const std::string& collectionName, const std::string& fieldPath, int64_t key) = 0;
// 
// 	/**
// 	* @brief ��������
// 	*
// 	* @return bool
// 	*/
// 	virtual std::string FindFieldByKey(const int nServerID, const std::string& collectionName, const std::string& fieldPath, const std::string& key) = 0;
};