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
#include "NFMessageDefine/NFMsgDefine.h"

#include "mongoc.h"
#include "bson.h"
#include "bcon.h"

//�����������¼��ǰ���ݿ⣬������ _id������������һ��
#define PRIMARY_TABLE "max_id_index"
#define PRIMARY_TABLE_COL "primary"
#define PRIMARY_TABLE_KEY "_id"

/*
**	���Ե�ʱ���֣�mongocֻҪ����Ϊ��������ʹ������������ҵ�ʱ��������ַ����ķ�ʽ���ң���Ȼ�Ҳ�������
*	��������ݲ��ң�ʹ�����ݱ���������
*/
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

	/**
	* @brief �Ƿ���ڱ��
	*
	* @return bool
	*/
	virtual bool IsExistCollection(const std::string& collectionName);

	/**
	* @brief ������񣬲�����primay_keyΪ����
	*
	* @return bool
	*/
	virtual bool CreateCollection(const std::string& collectionName, const std::string& primay_key = "");

	/**
	* @brief ɾ�����
	*
	* @return bool
	*/
	virtual bool DropCollection(const std::string& collectionName);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOne(const std::string& collectionName, const std::string& json_query);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::vector<std::string> FindMany(const std::string& collectionName, const std::string& json_query, const std::string& json_opts = "");

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::vector<std::string> FindAll(const std::string& collectionName);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneyByKey(const std::string& collectionName, int64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneyByKey(const std::string& collectionName, const std::string& key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool InsertOne(const std::string& collectionName, bson_t *doc);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool InsertOne(const std::string& collectionName, const std::string& json_query);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool InsertOne(const std::string& collectionName, const google::protobuf::Message& message);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const std::string& collectionName, const std::string& json, const std::string key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const std::string& collectionName, const std::string& json, uint64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const std::string& collectionName, const google::protobuf::Message& message, uint64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const std::string& collectionName, bson_t *select, bson_t *doc);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const std::string& collectionName, const std::string& json);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const std::string& collectionName, const google::protobuf::Message& message);

	/**
	* @brief �����������
	*
	* @return bool
	*/
	virtual bool InsertPrimaryKey(const std::string& collectionName, const std::string& primaryKey);

	/**
	* @brief ���ص�ǰ�������
	*
	* @return bool
	*/
	virtual void FindAllPrimaryKey();

	/**
	* @brief ��ñ��
	*
	* @return bool
	*/
	virtual mongoc_collection_t* GetCollection(const std::string& collectionName);

	/**
	* @brief ��ӡ�������
	*
	* @return bool
	*/
	static bool HandleMongocError(const bson_error_t& error);
private:
	mongoc_client_t		*m_pClient;
	mongoc_database_t    *m_pDatabase;
	mongoc_uri_t* m_uri;
	std::string m_ip;
	uint32_t m_port;
	std::string m_dbname;

	NFMap<std::string, mongoc_collection_t> m_collectionMap;
	std::map<std::string, std::string> m_collectionPrimaryKeyMap;

	float mfCheckReconnect; //���������ʱ��

	int mnReconnectTime;
	int mnReconnectCount;
};
