#pragma once
#include "_txtinc.h"
#include "eMod.h"

ccc_txt_class_begin(txtMap);

txtMap();
enum class eD
{
	// Right Down 
	RD,
	// Left Down 
	LD,
	// Left Up 
	LU,
	// Right Up 
	RU,
	// Down 
	D,
	// Left
	L,
	// Up
	U,
	// Right
	R,
};


struct sNpc
{
	eMod mod;
	int x;
	int y;
	// 方向
	eD direction;
	// 名字
	std::string name;
	// 称谓
	std::string appellation;
	// 脚本
	std::string script;
};

// 传送
struct sTransmit
{
	int x;
	int y;
	std::string name;
	int tx;
	int ty;
};

struct sMap
{
	int mapid = 0;
	ulong uid;
	std::string music;
	// npc组
	std::vector<sNpc> npcs;
	// 传送组
	std::vector<sTransmit> transmits;
};

private:
	void init(const std::string& mapname, int mapid, ulong uid, const std::string& music);
	void insert(int x, int y, const std::string& mapname, int tx, int ty);
	void insert(eMod e, int x, int y, eD direction, const std::string& name = "", const std::string& script = "", const std::string& appellation = "");



	void initCA();
	void initJY();
	void initAL();
	void initCS();
	void initCity();
	void initHome();
	void initMenpai();
	void initMaze();
	void initField();
	sNpc _npc;
	sTransmit _transMit;
	sMap* _map, _mapEmpty;

public:
static const char* _地图传送;
static const char* _驿站老板;
static const char* _驿站酆都;

static const char* _门派传送弟子;
static const char* _门派传送人;
static const char* _门派师父;

static const char* _帮派传送;
static const char* _帮派修炼指导师;
static const char* _帮派福利总管;

static const char* _系统商店;
static const char* _专卖店;
static const char* _系统装扮坐骑;
static const char* _系统装扮炫光;
static const char* _系统装扮足迹;
static const char* _系统装扮令牌;
static const char* _系统装扮祥瑞;
static const char* _系统装扮染色;

static const char* _仓库管理员;
static const char* _打造镶嵌分解;
static const char* _角色转换;
static const char* _打宝图;

static const char* _超级巫医;
static const char* _钱庄老板;
static const char* _陈长寿;
static const char* _建房吏;
static const char* _钟馗捉鬼;
static const char* _装备鉴定商;
static const char* _装备收购商;

static const char* _我的庭院管家;
static const char* _大唐国境土地;

ccc_txt_class_end(std::string, sMap);