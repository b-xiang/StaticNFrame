// -------------------------------------------------------------------------
//    @FileName         :    NFCMysqlModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFCMysqlModule
//
// -------------------------------------------------------------------------

#pragma once

#include "NFCMongoDriver.h"
#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFIMongoModule.h"
#include "NFCMongoDriverManager.h"

class NFCMongoModule : public NFIMongoModule
{
public:
	/**
	 * @brief
	 *
	 * @param  p
	 * @return  
	 */
	NFCMongoModule(NFIPluginManager* p);
	/**
	 * @brief
	 *
	 * @return  
	 */
	virtual ~NFCMongoModule();

	/**
	 * @brief
	 *
	 * @return bool 
	 */
	virtual bool Init() override;
	/**
	 * @brief
	 *
	 * @return bool 
	 */
	virtual bool Shut() override;
	/**
	 * @brief
	 *
	 * @return bool 
	 */
	virtual bool Execute() override;
	/**
	 * @brief
	 *
	 * @return bool 
	 */
	virtual bool AfterInit() override;

	/**
	* @brief ���serverid������, һ��serverid��Ӧһ���������ݿ������
	*
	* @return bool
	*/
	virtual bool AddMongoServer(const int nServerID, const std::string& ip, uint32_t port, const std::string& dbname) override;

	/**
	* @brief ���serverid������, һ��serverid��Ӧһ���������ݿ������
	*
	* @return bool
	*/
	virtual bool AddMongoServer(const int nServerID, const std::string& uri, const std::string& dbname) override;

	/**
	* @brief �Ƿ���ڱ��
	*
	* @return bool
	*/
	virtual bool IsExistCollection(const int nServerID, const std::string& collectionName) override;

	/**
	* @brief �������
	*
	* @return bool
	*/
	virtual bool CreateCollection(const int nServerID, const std::string& collectionName, const std::string& key) override;

	/**
	* @brief ɾ�����
	*
	* @return bool
	*/
	virtual bool DropCollection(const int nServerID, const std::string& collectionName) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool InsertJson(const int nServerID, const std::string& collectionName, const std::string& json_query) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool InsertMessage(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, uint64_t key) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, uint64_t key) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, const std::string& key) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOneByKey(const int nServerID, const std::string& collectionName, const std::string& json, const std::string& key) override;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const int nServerID, const std::string& collectionName, const std::string& json) override;;

	/**
	* @brief ����һ������
	*
	* @return bool
	*/
	virtual bool UpdateOne(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message) override;

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
	virtual std::string FindAllToJson(const int nServerID, const std::string& collectionName);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneByKey(const int nServerID, const std::string& collectionName, int64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindOneByKey(const int nServerID, const std::string& collectionName, const std::string& key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const std::string& json, const std::string key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const std::string& json, uint64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, uint64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual bool UpdateFieldByKey(const int nServerID, const std::string& collectionName, const google::protobuf::Message& message, const std::string& key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindFieldByKey(const int nServerID, const std::string& collectionName, const std::string& fieldPath, int64_t key);

	/**
	* @brief ��������
	*
	* @return bool
	*/
	virtual std::string FindFieldByKey(const int nServerID, const std::string& collectionName, const std::string& fieldPath, const std::string& key);
private:
	NFCMongoDriverManager* m_pMongoDriverManager;

	uint64_t mnLastCheckTime;
};

