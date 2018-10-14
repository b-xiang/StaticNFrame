// -------------------------------------------------------------------------
//    @FileName         :    NFServerCommon.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/11
//    @Email			:    445267987@qq.com
//    @Module           :    NFServerCommon
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFConfigMgr.h"

class NFServerCommon
{
public:
	static NFServerConfig* GetServerConfig(NFIPluginManager* pPluginManager, NF_SERVER_TYPES eServerType);
};

class NFProxyData
{
public:
	NFProxyData()
	{
		mServerId = 0;
		mLinkId = 0;
	}

	uint32_t mServerId;
	uint32_t mLinkId;

	virtual void print() { }
};

enum NFMsgIdSection
{
	emsgid_net_begin = 1,
	emsgid_net_end = 100,

	emsgid_login_begin = 100,
	emsgid_login_end = 200,

	emsgid_center_begin = 200,
	emsgid_center_end = 300,

	emsgid_gateway_begin = 300,
	eMap2Gateway_BuildConncet		= 351, //��������
	eMap2Gateway_WorldMsg			= 352, //��������
	eMap2Gateway_NotifyOffline	= 353, //֪ͨ�������

	eMap2Gateway_AOISync			= 354, 
	eMap2Gateway_UpdateLink		= 355,
    eMap2Gateway_Broadcast        = 356, //�㲥��Ϣ
	emsgid_gateway_end = 400,

	emsgid_db_begin = 400,
	emsgid_db_end = 900,

	emsgid_platform_begin = 900,
	emsgid_platform_end = 1100,

	emsgid_chat_begin = 1100,
	emsgid_chat_end = 1200,

	emsgid_match_begin = 1200,
	emsgid_match_end = 1300,

	emsgid_pvp_begin = 1300,
	emsgid_pvp_end = 1400,

	emsgid_map_begin = 1400,
	//������Э�飬��������Ҫ��ȡIP��ַ
	eLogin_FGW_QueryPlayerData			= 2001,					//��ȡ�������
	eLogin_FGW_CreateChar				= 2002,

	emsgid_map_end = 5000,

	//game ->  match -> battle
	emsgid_battle_begin = emsgid_map_end,
	eGame2Battle_EnterScene = 5000,
	eGame2Battle_SynSkill_Info = 5001,			//����������Ϣ�Լ��˺�ͬ��
	eGame2Battle_SynSkill_Del = 5002,				//ɾ������(���ּ��ܸ���)
	eGame2Battle_SynSkill_Pos = 5003,				//ֻ��λ�ø���
	eGame2Battle_SynPlayer_Data = 5004,		//��һ�������ͬ��
	eGame2Battle_SyncTower_Data = 5005,			//��������������
	eGame2Battle_SyncRelive = 5006,    					//��������
	eGame2Battle_PlayerDisconnect = 5007,		//��ҶϿ�����
    eGame2Battle_SyncGuild  = 5008,                 //ͬ����ҹ�����Ϣ
	eGame2Battle_SyncFacade = 5009,				//ͬ����ҳɳ�ϵͳ���
	eGame2Battle_ChangeTttle = 5010,				//ͬ���ƺű��
	eGame2Battle_ChangeEquip = 5011,				//ͬ��װ�����
	eGame2Battle_JoinGuildBossSecen = 5012,		//��������boss����
    eGame2Battle_ModPlayerData = 5013,            //�޸��������(GM������)
	eGame2Battle_EnterDungeon = 5020,
	eGame2Battle_ChangeMap = 5021,
	eGame2Battle_UpdatePlayerValue = 5022,	//�����������
	eGame2Battle_CheckTrigger = 5023,	//��鴥����
	eGame2Battle_AddQuestTrigger = 5024,	//���Ӵ�����
	eGame2Battle_UpdateTask = 5025,	//��������
	eGame2Battle_QuestNPCAddBuff = 5026,	//���񴥷�  ��ָ��NPC��buff
	eGame2Battle_WorldBossStart = 5027,	//֪ͨ����boss��ʼ
	eGame2Battle_WorldBossBid = 5028,	//֪ͨ����boss����
	eGame2Battle_ChangeAwaken = 5029,   //��ʼ����
	eGame2Battle_ChangePet = 5030, //
	eGame2Battle_ChangeRide = 5031, //
	eGame2Battle_AddCurHp = 5032, //
	eGame2Battle_AddBuff = 5033, //
	eGame2Battle_BornMercenary = 5034, // ����Ӷ��
	eGame2Battle_TicketBossChallenge = 5035, //��ս��Ʊboss
	eGame2Battle_TakeDropItem = 5036, //ʰȡ������Ʒ
	eGame2Battle_CreateDungeon = 5037, //���˸����� ��������
	eGame2Battle_CreateMonster = 5038, //game���ٻ�����
	eGame2Battle_ChangeAvatar = 5039, //���ʱװͬ��
	eGame2Battle_FollowLeader = 5040,//�л����ӳ�����
	eGame2Battle_ChangeMapPendingBranch= 5041,//Ԥ���л�����
	eGame2Battle_BackOnline = 5042,
	eGame2Battle_UpdateHeadInfo = 5043,				//ͬ���ƺű��
	eGame2Battle_UpdateMercenaryScript = 5044, //ͬ��Ӷ������
	eGame2Battle_UpdateRideScript = 5045, //ͬ��Ӷ������
	eGame2Battle_UpdateAwakenScript = 5046, //ͬ�����Ѽ���
	eGame2Battle_UpdateMyCombat = 5047,//ͬ���Լ���ս����
    eGame2Battle_CaptureFlag = 5049,		//������
	eGame2Battle_LeaveScene = 5050,		//�뿪֮ǰ�ĳ���
	eGame2Battle_QuietFlagStart = 5051, //֪ͨ����֮�쿪ʼ
	eGame2Battle_NotifyGuild = 5052,	//֪ͨ����ı�
	eGame2Battle_UpdateGodArmScript = 5053,	//֪ͨ�������
	eGame2Battle_UpdateWingScript = 5054,	//֪ͨ�����
	eGame2Battle_CreateGBPVP = 5055,	//֪ͨ��������սPVPս��
	eGame2Battle_GuildBattle_Strengthen = 5056,	//����������ҹ���ǿ������
	eGame2Battle_DeleteBuff = 5057,	//ɾ��buff
	eGame2Battle_ReqOpenTicketBox = 5058,	//����ƱBOSS����
	eGame2Battle_ModelChange = 5059, //���ģ���л�(�û�)
    
	//client->  battle
	emsgid_client2battle_begin = 5200,
	eClient2Battle_ClientLoadOK = 5200,
	eClient2Battle_SyncMove = 5201,
	eClient2Battle_SpeelBegin = 5202, //�л���ͼ��
	eClient2Battle_SpeelEnd = 5203,     //������ͼ�����
	eClient2Battle_GetMapBranch = 5204,	    //��ȡ�����б�
	eClient2Battle_ChangeBranch = 5205,      //������
	eClient2Battle_TriggerEvent = 5207,	//�����¼�(����֮Ծ�������ݴԡ��ݳ���)
	eClient2Battle_GameStoryStart = 5208, 	//���鸱����ʼ
	eClient2Battle_GameStoryEnd = 5209, 	//���鸱������
	eClient2Battle_NPCStopAI = 5210, 	//ֹͣNPC AI
	eClient2Battle_NPCActiveAI = 5211, 	//����NPC AI
	eClient2Battle_Dungeon_PassStory = 5213,	//��������
	eClient2Battle_Dungeon_Event = 5214, //�����¼�
	eClient2Battle_Tower_EnterOk = 5216, // �����������سɹ�
	eClient2Battle_Tower_UserBuffer = 5217, // ʹ��Buff
	eClient2Battle_Tower_LeaveTower = 5218, //�뿪���� 
	eClient2Battle_Tower_ReqEnter = 5219, // �����������
	eClient2Battle_SummonMercenary = 5220,// �ٻ�Ӷ�����Լ����
	eClient2Battle_Transfer = 5221,// ��������
	eClient2Battle_ReloadFov = 5222,// ���¼�����Ұ
    eClient2Battle_ReqTBPlayerInfo = 5223, //���ս������Ϣ(NullMessage) 
	eClient2Battle_Skill_ExcuteSkill = 5300,			//����ͷż���
	eClient2Battle_Skill_RequestHurt = 5301,			//��������˺�
	eClient2Battle_Skill_BlockSkillStart = 5302,		//��ҷŸ񵲼��ܿ�ʼ
	eClient2Battle_Skill_BlockSkillEnd = 5303,			//��ҷŸ񵲼��ܽ���
	
	eClient2Battle_Skill_End = 5350,							//�������Э��ID��

	//=====pvpstart=====
	ePVP_CP_NoticeConnectOK = 5400,
	ePVP_CP_LeaveAttack = 5401,
	ePVP_CP_LoadBattleOk = 5402,					//֪ͨ���س���OK
	ePVP_CP_DoPVPBuffer = 5403,					//����PVP buffer
	ePVP_CP_PVPSurrender = 5406,					//Ͷ��

	//=====pvpend=====

	eClient2Battle_WorldBoss_Challenge = 5450,	//��ս����boss
	eClient2Battle_WorldBoss_SaledItem = 5451,	//��ѯ������������Ʒ��Ϣ
	eClient2Battle_WorldBoss_SaleList = 5452,	//����������Ϣ
	eClient2Battle_WorldBoss_HurtRankList = 5453,	//�����˺�����
	eClient2Battle_Ping = 5454,  //����ping
	eClient2Battle_ChangeAttackMode = 5455,  //�л�����ģʽ
	eClient2Battle_Anchor = 5456,  //��ê

	//=====collect start=======
	eClient2Battle_Collect_Operate = 5460, //�ɼ�
	eClient2Battle_Qte = 5461, 	   //�ύ�ɼ�
	
	
	//=====collect end=========

	eClient2Battle_PlayerCaptureFlag = 5462,	//����

	emsgid_client2battle_end = 6000,
	emsgid_battle_end = 6000,


	//battle -> match
	emsgid_battle2match_begin = 6000,
	eBattle2Match_ServerInfo = 6000,
	eBattle2Match_UpdatePlayerNum = 6001,
	eBattle2Match_CreateDungeon = 6002,
	eBattle2Match_BloodSeaCreateScene = 6003, //��Ѫ���򴴽�����
	eBattle2Match_BloodSeaCloseScene = 6004, //��Ѫ�������ս��
	emsgid_battle2match_end = 6200,


	//battle -> match -> game
	emsgid_battle2game_begin = 6200,
	eBattle2Game_EnterScene = 6200,
	eBattle2Game_EnterDungeon = 6201,
	eBattle2Game_AddDropItem = 6203,		//������Ʒ
	eBattle2Game_SynSKill_Cost = 6204, //��������ͬ��
	eBattle2Game_DungeonResult = 6205,		//�������
	eBattle2Game_SyncMove = 6206,		//ͬ������
	eBattle2Game_UpdateQuest = 6207,	//��������
	eBattle2Game_TriggerQuest = 6208,	//��������
	eBattle2Game_MonsterDie = 6209,	//��������֪ͨ
	eBattle2Game_LeaveDungeon = 6210,	//�뿪����
	eBattle2Game_SyncTower_Data = 6211, //��������
	eBattle2Game_DungeonLoadOk = 6212, //�����������
	eBattle2Game_WolrdBoss_HpChange = 6213, //
	eBattle2Game_WolrdBoss_SaleResult = 6214,	//�������
	eBattle2Game_ChangeMapForceAwakenOff = 6215, //�л�����ǿ�Ʊ������
	eBattle2Game_SceneLoadOk = 6216,//��ҽ��볡�����
	eBattle2Game_CreateDungeon = 6217,
	eBattle2Game_SyncData = 6218,  //ͬ�����ĵ�����
	eBattle2Game_Notice = 6219,  //�㲥֪ͨ
	eBattle2Game_DieToChangeAwakenAndRide = 6220, //�л�����ǿ�Ʊ������
	eBattle2Game_UpdateBossDamage = 6222,	//ͬ��boss�˺�
	eBattle2Game_MercenaryDieInfo =  6223, // Ӷ��������Ϣ
    eBattle2Game_SyncGuildData = 6224,      //ͬ��������Ϣ
    eBattle2Game_GuildBossOver = 6225,      //����bossս����
	eBattle2Game_SendMail = 6226,       //���ͽ����ʼ�
	eBattle2Game_BackToRecordMap = 6227,       //��֮ǰ�ĳ���
	eBattle2Game_SaveMercenaryPer = 6228,  //����Ӷ��Ѫ��
	eBattle2Game_UpdatePlayerStatus = 6229, //ͬ�����״̬
	eBattle2Game_GetRoomList = 6230,//���ط�����Ϣ
    eBattle2Game_BackToCity = 6231, //�س�
    eBattle2Game_TBKillReward = 6232,  //��������ս ɱ�˽���
    eBattle2Game_TBResult = 6233,           //��������ս����
    eBattle2Game_IsLoadOK = 6234,           //�����Ƿ����(�����������)
	eBattle2Game_KickPlayer = 6235,		//���س����쳣 ������ ��ֹ�޷�������½������
	eBattle2Game_SurvivalOver = 6236,	//����ɱ����
	eBattle2Game_PlayerCaptureFlag = 6237,	//��ȡ���԰���
    eBattle2Game_GoldBattleKillReward = 6240,  //�ƽ�����ս ɱ�˽���
    eBattle2Game_GoldBattleResult = 6241,           //�ƽ�����ս����
	eBattle2Game_GoldBattle_PlayerCaptureFlag = 6242,	//�ƽ�����ս����
	eBattle2Game_AttackWorldBoss = 6243,	//���ζ�����boss����˺�
	eBattle2Game_GuildBattle_Leave = 6244,						//��������ս����뿪���
	eBattle2Game_GuildBattle_Over = 6245,						//�������Խ���
	eBattle2Game_BloodSea_Over = 6246,					//��Ѫ������»���
	eBattle2Game_TicketBossRank = 6247,					//��ƱBOSS����
	emsgid_battle2game_end = 6500,

	//battle -> client
	emsgid_battle2client_begin = 6500,
	eBattle2Client_EnterScene = 6500,
	eBattle2Client_SyncPlayerAppear = 6501,
	eBattle2Client_SyncObjDisappear = 6502,
	eBattle2Client_SyncObjMove = 6503,
	eBattle2Client_SpeelBegin = 6504, //�л���ͼ��

	eBattle2Client_GetMapBranch = 6505,		//��ȡ�����б���
	eBattle2Client_ChangeBranch = 6506,      //���߽��


	eBattle2Client_CheckPosition = 6507,      //�������
	eBattle2Client_MonsterStopMove = 6508,      //ֹͣ�ƶ�
	eBattle2Client_TriggerEvent = 6509,		//�����¼�
	eBattle2Client_SyncMonsterAppear = 6510,	//�������

	eBattle2Client_ChangeTitle = 6511,			//ͬ���ƺű��
	eBattle2Client_ChangeEquip = 6512,		//ͬ��װ�����
	eBattle2Client_ClientLoadOK = 6513,		//���͵�ǰ����ID
	
	eBattle2Client_Story = 6514,		//���鲥��
	eBattle2Client_Customs = 6515,		//�ؿ�
	eBattle2Client_ChangeFacade = 6516, //ͬ���ɳ�ϵͳ��۱仯
	eBattle2Client_MonsterTalk = 6517,		//NPC����

	eBattle2Client_MonsterNum = 6518,		//���ﲨ��
	eBattle2Client_ChangeCamp = 6519,		//������
	eBattle2Client_PretendStart = 6520,		//αװ��ʼ
	eBattle2Client_PretendEnd = 6521,		//αװ����
	eBattle2Client_SyncAttInBat = 6522,  //ͬ��ս����������
	eBattle2Client_DropItem = 6523,			//��Ʒ����

	eBattle2Client_Tower_EnterScene = 6524, //���Խ�����������
	eBattle2Client_Tower_AddBuffer = 6525,//����Buffer
	eBattle2Client_Tower_DelBuffer = 6526,//ɾ��Buffer
	eBattle2Client_Tower_NewFloor = 6527,//������һ��
	eBattle2Client_Tower_EndTower = 6528,//��������
	//�³ɳ�ϵͳ���
	eBattle2Client_ChangePet = 6529,			// ͬ��������
	eBattle2Client_ChangeRide = 6530,			// ͬ��������
	eBattle2Client_ChangeAwaken = 6531,			// ͬ�����ѱ��
	eBattle2Client_SyncMercenaryAppear = 6532,			// Ӷ����������Ұ
	eBattle2Client_ChangeAvatar = 6533,			// ͬ��Avatar
	eBattle2Client_ChangeSuit = 6534,			// ͬ��suit
	eBattle2Client_ReconnectUnDoTrigger = 6535,
	eBattle2Client_TriggerServerTips = 6536, //����servertips
	eBattle2Client_SafeAreaStatus = 6537,		//������ȫ��֪ͨ
	eBattle2Client_ServerMove = 6538,    //�����������ƶ�
	eBattle2Client_PlayerDie = 6539,		//����֪ͨ
	eBattle2Client_SyncSceneObjAppear = 6540, //�����е������������Ұ�У������ˣ����Ӷ��.......
	eBattle2Client_SyncSceneObjDisappear = 6541,  //�����е�������ʧ����Ұ��
	eBattle2Client_SyncModelChange = 6542,		//ͬ����һû�ģ���л�
	eBattle2Client_Skill_ExcuteSelf = 6600,    // �ͷż��ܷ��ظ��Լ�����Ϣ
	eBattle2Client_Skill_ExcuteOther = 6601,    	// �ͷż��ܷ��ظ�ͬ������������ҵ���Ϣ
	eBattle2Client_Skill_UpdateHurtData = 6602,    	// ��������
	eBattle2Client_Skill_AttackBack = 6603,    	// ����
	eBattle2Client_Skill_AddBuffer = 6604,    	//��buffer
	eBattle2Client_Skill_DelBuffer = 6605,   	//��buffer
	eBattle2Client_Skill_UpdateBuffer = 6606,		//����buffer
	eBattle2Client_Skill_AttackSprint = 6607,    	//���
	eBattle2Client_Skill_AttackDie = 6608,    	//����������
	eBattle2Client_Skill_BlockBack = 6609,     //��ҷŸ񵲼��ܷ���
	eBattle2Client_Skill_BlockStart = 6609,     //��ҷŸ񵲼��ܿ�ʼ
	eBattle2Client_Skill_BlockEnd = 6610,     //��ҷŸ񵲼��ܽ���
	eBattle2Client_Skill_UpdateAttacking = 6611,     //�Ƿ���ս��״̬
	eBattle2Client_Skill_Strike = 6612,     //����
	eBattle2Client_Die = 6613,     //����
	eBattle2Client_Skill_Shout = 6614,     //����
	eBattle2Client_Skill_ClearCD = 6615,     //��ռ���CD	
	eBattle2Client_Skill_UpdateAttackStatus = 6616,     //����ս��״̬
	eBattle2Client_Relive = 6617, 		//����״̬�ظ�	
	eBattle2Client_UpdateMonsterAttackStatus = 6618,     //���¹���ս��״̬
	eBattle2Client_Skill_Block = 6619,     //��ס
	eBattle2Client_Skill_UpdateTP = 6620,    	//����TPֵ
	eBattle2Client_Skill_UpdateFlagCamp = 6621,    	//����������Ӫ
	eBattle2Client_RelivePos = 6622,		//�����λ��ͬ��
	eBattle2Client_UpdateSkillGroupCD = 6623,		//�����鼼��ID
	eBattle2Client_Skill_Skill_End = 6650,		//�������Э��ID��


	//����boss
	eBattle2Client_WolrdBoss_DorpItemList = 6651,		//����boss����֪ͨ
	eBattle2Client_WolrdBoss_SaleStart = 6652,		//����boss������Ʒ��ʼ����
	eBattle2Client_WolrdBoss_SaleBid = 6653,		//����boss  ��������֪ͨ
	eBattle2Client_WolrdBoss_SaleResult = 6654,		//����boss  �������֪ͨ
	eBattle2Client_WolrdBoss_HpChange = 6655,		//����boss  HP
	eBattle2Client_WolrdBoss_SaledItem = 6656,		//����boss  ��ѯ������������Ʒ��Ϣ
	eBattle2Client_WolrdBoss_HurtRankList = 6657,		//�˺��б�

    eBattle2Client_TicketBoss_DropItem = 6658,

    eBattle2Client_SyncDropItemAppear = 6659,		//����������Ʒ������Ұ
    eBattle2Client_SyncDropItemChange = 6660,		//����������Ʒ����
    eBattle2Client_Ping = 6661, 
    eBattle2Client_AttackMode = 6662,	//����ģʽ���֪ͨ
    eBattle2Client_Transfer = 6663,// ��������
    eBattle2Client_GuildBossDie=6664, //֪ͨ�ͻ��˹���boss���� �Լ� ����
    eBattle2Client_Anchor = 6665,  //��ê
    eBattle2Client_UpdateHeadInfo = 6666,//���ͷ����Ϣ����
    eBattle2Client_UpdateMercenaryRank = 6667, //���Ӷ����������
    eBattle2Client_TriggerRadius = 6668,//�������жϷ�Χ֪ͨ
    eBattle2Client_ScenePlayerNum = 6669,//��ǰ����������
    eBattle2Client_GradeDataChanged = 6670, //��������������ݱ��
    eBattle2Client_Boss_HurtRankList = 6671,		//�Լ��Ļ�������
    eBattle2Client_SyncMonsterOnwer = 6672, //ͬ������Ȩ�仯��Ϣ
    eBattle2Client_MonsterCountChanged = 6673, //ͬ�����������������
    eBattle2Client_AckTBPlayerInfo = 6674, //���ս������Ϣ
	eBattle2Client_SurvivalStartFight = 6675, //����ɱ��ʼս��


	eBattle2Client_QuietFlagBossInfo = 6680, //����֮��BOSS��Ϣ
	eBattle2Client_QuietFlagBossRefresh = 6681, //����֮��BOSSˢ��
	eBattle2Client_QuietFlagBossDied = 6682, //����֮������
	eBattle2Client_QuietFlagBossReward = 6683, //��ɱ����BOSS����ͬ����ķ�����

	eBattle2Client_CollectNotifyError = 6690, //�ɼ������ƶ������������������ˣ���ϲɼ�
	eBattle2Client_CollectNotifyState = 6691, //֪ͨ�ɼ�״̬
	eBattle2Client_Collect_Action_BroadCast = 6692, //�㲥�����������Լ��ĵ�ǰ�ɼ�״̬
	eBattle2Client_Collect_Operate = 6693,	//�ͻ��˲����ɼ�
	eBattle2Client_Collect_Qte = 6694,		//�ͻ����ύ�ɼ����

	eBattle2Client_TreasureSeaPlayerInfo = 6697, //Ѳ��̽�������Ϣ
	eBattle2Client_TreasureSeaPlayerExpInfo = 6698, //Ѳ��̽����Ҿ�����Ϣ

	eBattle2Client_Died_In_Relive_Position = 6699,	//����Ƿ��ڸ���������

    //TB PVP start 6700
    ePVP_PC_SyncOnePlayer = 6700,               	//ͬ��������
    ePVP_PC_SyncMultiPlayer = 6701,             	//ͬ��һ�����
    ePVP_PC_RemovePlayer = 6702,					//ɾ��һ�����
    ePVP_PC_LoadBattle = 6703,					//֪ͨ���س���
    ePVP_PC_LoadPVPBuffer = 6704,                //�����¼�
    ePVP_PC_AddPVPBuffer = 6705,                //�����¼�
    ePVP_PC_DelPVPBuffer = 6706,                //�����¼�
    ePVP_PC_LoadPVPFlagEvent = 6707,					//��������
    ePVP_PC_AddFlag = 6708,					//����һ������
    ePVP_PC_DelFlag = 6709,					//ɾ������
    ePVP_PC_DesFlag = 6710,					//���ӵ�Ŀ��
    ePVP_PC_AttackEnd = 6711,					//ս������
    ePVP_PC_KillRanking = 6712,					//��ɱ���а�
    ePVP_PC_IntegralRanking = 6713,					//�������а�
    ePVP_PC_BattleBegin = 6714,					//ս����ʼ
    eBattle2Client_TB_SyncFlagPos = 6715,       //ͬ������λ��
    eBattle2Client_GoldBattle_SyncFlagPos = 6715,       //�ƽ�����ͬ������λ��
	eBattle2Client_GuildBattle_OfficeKilled = 6717,			//��������ս�᳤���᳤����ɱ
	eBattle2Client_GuildBattle_Action = 6718,			//��������ս��Ҵ�����Ϊ�¼�


	eBattle2Client_BloodSeaBattleResult = 6730,			//��Ѫ�������
	eBattle2Client_BloodSeaSynHp = 6731,				//ͬ��HP
	eBattle2Client_BloodSeaSynKill = 6732,				//ͬ����ɱ
	eBattle2Client_BloodSeaTime = 6733,					//����ʱЭ��
	eBattle2Client_BroadPlayerBattleInfo = 6734,		//ͬ�������Ϣ
    //pvpend

	eBattle2Client_NoticePlayerCaptureFlag = 6735,		//֪ͨ��Ұ���

	eBattle2Client_NoticeChangeBoxStatus = 6736,		//��ƱBOSS����״̬

    emsgid_battle2client_end = 7000,
    emsgid_errorcode_begin = 20000,
    emsgid_errorcode_end = 20000,

    emsg_id_Num,	
};