// -------------------------------------------------------------------------
//    @FileName         :    NFEventDefine.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#pragma once

#include "NFEventObj.h"

enum NFEventDefine
{
	NFEVENT_TEST = 0, //�����¼��� ��������
	NFEVENT_TEST1 = 1, //�����¼��� ��������
	NFEVENT_TEST2 = 2, //�����¼��� ��������
	NFEVENT_PROXY_CONNECT_GAME_SUCCESS, //PROXY ���� GAME SERVER
	NFEVENT_PROXY_CONNECT_GAME_FAIL, //PROXY ���� GAME SERVER
	NFEVENT_PROXY_CONNECT_WORLD_SUCCESS, //PROXY ���� WORLD SERVER
	NFEVENT_PROXY_CONNECT_WORLD_FAIL, //PROXY ���� WORLD SERVER
	NFEVENT_GAME_CONNECT_WORLD_SUCCESS, //GAME ���� WORLD SERVER
	NFEVENT_GAME_CONNECT_WORLD_FAIL, //GAME ���� WORLD SERVER
	NFEVENT_LOGIN_CONNECT_MASTER_SUCCESS, //LOGIN ���� MASTER SERVER
	NFEVENT_LOGIN_CONNECT_MASTER_FAIL, //LOGIN ���� MASTER SERVER
	NFEVENT_WORLD_CONNECT_MASTER_SUCCESS, //LOGIN ���� MASTER SERVER
	NFEVENT_WORLD_CONNECT_MASTER_FAIL, //LOGIN ���� MASTER SERVER
};

