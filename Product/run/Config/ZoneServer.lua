

--GameServer ��Ϸ������, һ��һ��С��ֻ��һ���� ������Ϸ��ս����ҵ�� �������������
Server[#Server+1] = {
		ServerName = "GameServer";
		ServerType = NF_ST_GAME;
		ServerId = 10;			--��ÿһ����������˵����Ψһ�ģ� Ӧ�ó�����Ҫͨ�����ServerId����֪����Ҫ���ص���������
		MasterId = 1;			--��Ҫ��MasterServer��MasterId����һ��
		WorldId = 100;			--��Ҫ��һ�������������WorldIdһ��
		ZoneId = ZoneServerId;
		ServerIp = ZoneIP;
		ServerPort = ZonePort+#Server;
		MaxConnectNum = 100;
		WorkThreadNum = 1;
		Security = false;
	};
	
--ProxyServer ���ܷ������� �������ⲿ�Ŀͻ�������, ת������
Server[#Server+1] = {
		ServerName = "ProxyServer";
		ServerType = NF_ST_PROXY;
		ServerId = 11;			--��ÿһ����������˵����Ψһ�ģ� Ӧ�ó�����Ҫͨ�����ServerId����֪����Ҫ���ص���������
		MasterId = 1;			--��Ҫ��MasterServer��MasterId����һ��
		WorldId = 100;			--��Ҫ��һ�������������WorldIdһ��
		ZoneId = ZoneServerId;
		ServerIp = ZoneIP;
		ServerPort = 5509;
		MaxConnectNum = 1000;
		WorkThreadNum = 5;
		Security = false;
	};
