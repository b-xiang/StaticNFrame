// -------------------------------------------------------------------------
//    @FileName         :    NFCMongoDriver.h
//    @Author           :    GaoYi
//    @Date             :    2018-07-28
//    @Module           :    NFCMongoDriver
//    @Desc             :
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFIModule.h"
#include <string>
#include "NFComm/NFCore/NFMap.hpp"

#include "mongoc.h"
#include "bson.h"
#include "bcon.h"

class NFCMongoDriver : public NFIModule
{
public:
	NFCMongoDriver(const int nReconnectTime = 60, const int nReconnectCount = -1);

	virtual ~NFCMongoDriver();

	virtual bool Connect(const std::string& ip, uint32_t port, const std::string& dbname);

	virtual bool Ping();

	/**
	* @brief �ر�����
	*
	* @return void
	*/
	virtual void CloseConnection();

	/**
	* @brief �Ƿ�������Ч
	*
	* @return bool
	*/
	virtual bool Enable();

	/**
	* @brief �Ƿ��������
	*
	* @return bool
	*/
	virtual bool CanReconnect();

	/**
	* @brief ����
	*
	* @return bool
	*/
	virtual bool Reconnect();

	/**
	* @brief �Ƿ���Ҫ����
	*
	* @return bool
	*/
	bool IsNeedReconnect();

	/**
	* @brief ����
	*
	* @return bool
	*/
	bool Connect();

	/**
	* @brief ѭ��ִ��
	*
	* @return bool
	*/
	virtual bool Execute();

	virtual bool IsExistCollection(const std::string& collectionName);

	virtual bool CreateCollection(const std::string& collectionName, const std::string& primay_key);

	virtual bool DropCollection(const std::string& collectionName);

	virtual std::string FindOne(const std::string& collectionName, const std::string& json_query);
	virtual std::vector<std::string> FindMany(const std::string& collectionName, const std::string& json_query);

	virtual bool Update(const std::string& json);

	virtual mongoc_collection_t* GetCollection(const std::string& collectionName);

	static bool HandleMongocError(const bson_error_t& error);
private:
	mongoc_client_t		*m_pClient;
	mongoc_database_t    *m_pDatabase;
	mongoc_uri_t* m_uri;
	std::string m_ip;
	uint32_t m_port;
	std::string m_dbname;

	NFMap<std::string, mongoc_collection_t> m_collectionMap;

	float mfCheckReconnect; //���������ʱ��

	int mnReconnectTime;
	int mnReconnectCount;
};
