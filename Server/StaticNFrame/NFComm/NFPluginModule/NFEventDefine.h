#pragma once

#include "NFEventObj.h"

enum NFEventDefine
{
	NFEVENT_TEST = 0, //�����¼��� ��������
	NFEVENT_TEST1 = 1, //�����¼��� ��������
	NFEVENT_TEST2 = 2, //�����¼��� ��������
};

class NFTestEventContext : public NFEventContext
{
public:
	int a = 1;
	int b = 2;
	int c = 3;
};
