#pragma once
#include "global.h"
#if ccc_m5
const int c_NumFuZhu =  13;
#else
const int c_NumFuZhu = 4;
#endif
struct sSkill;
enum eMengPai
{
	eMP_大唐官府,
	eMP_化生寺,
	eMP_女儿村,
	eMP_方寸山,
	eMP_狮驼岭,
	eMP_魔王寨,
	eMP_盘丝岭,
	eMP_阴曹地府,
	eMP_东海龙宫,
	eMP_五庄观,
	eMP_普陀山,
	eMP_天宫,
	/*eMP_凌波城,
	eMP_无底洞,
	eMP_神木林,*/
	eMP_无,
	eMP_随机
};

enum ePetID
{
	e巨蛙,
	e大海龟,
	e护卫,
	e树怪,
	e赌徒,
	e强盗,
	e海毛虫,
	e大蝙蝠,
	e山贼,
	e野猪,
	e骷髅怪,
	e羊头怪,
	e蛤蟆精,
	e老虎,
	e黑熊,
	e花妖,
	e牛妖,
	e小龙女,
	e野鬼,
	e狼,
	e虾兵,
	e蟹将,
	e龟丞相,
	e兔子怪,
	e蜘蛛精,
	e黑熊精,
	e僵尸,
	e牛头,
	e马面,
	e雷鸟人,
	e蝴蝶仙子,
	e古代瑞兽,
	e白熊,
	e黑山老妖,
	e天兵,
	e天将,
	e地狱战神,
	e风伯,
	e凤凰,
	e蛟龙,
	e雨师,
	e如意仙子,
	e芙蓉仙子,
	e巡游天神,
	e星灵仙子,
	e幽灵,
	e鬼将,
	e吸血鬼,
	e净瓶女娲,
	e律法女娲,
	e灵符女娲,
	e大力金刚,
	e雾中仙,
	e灵鹤,
	e夜罗刹,
	e炎魔神,
	e噬天虎,
	e野猪精,
	e鼠先锋,
	e百足将军,
	e踏云兽,
	e红萼仙子,
	e龙龟,
	e阴阳伞,
	e机关兽,
	e机关鸟,
	e机关人车,
	e连弩车,
	e巴蛇,
	e蚌精,
	e鲛人,
	e碧水夜叉,
	e锦毛貂精,
	e千年蛇魅,
	e犀牛将军人,
	e犀牛将军,
	e机关人,
	e葫芦宝贝,
	e猫灵人,
	e猫灵,
	e狂豹,
	e狂豹人,
	e蝎子精,
	e混沌兽,
	e超级人参娃娃,
	e画魂,
	e长眉灵猴,
	e巨力神猿,
	e修罗傀儡鬼,
	e藤蔓妖花,
	e蜃气妖,
	e修罗傀儡妖,
	e金身罗汉,
	e曼珠沙华,
	e超级泡泡,
	e超级大熊猫,
	e超级金猴,
	e超级大象,
	e超级白泽,
	e超级灵鹿,
	e超级赤焰兽,
	e超级大鹏,
	e善财童子,
	e超级筋斗云,
	e超级神牛,
	e超级神虎,
	e超级海豚,
	e超级神兔,
	e小毛头,
	e小丫丫,
	e小仙灵,
	e小仙女,
	e小精灵,
	e小魔头,
	e孙悟空,
	e沙和尚,
	e蚩尤,
	e猪八戒,
	e狐狸精,
	e知了王,
	e泡泡,
	e赛太岁,
	e周杰伦,
	e超级神龙,
	e章鱼,
	e小浣熊,
	e海星,
	e火星人,
	e转轮王,
	e九头精怪,
	e腾蛇,
	e东海龙王,
	e孙婆婆,
	e牛魔王,
	e镇元大仙,
	e菩提祖师,
	e白晶晶,
	e幽萤娃娃,
	e李靖,
	e程咬金,
	e地藏王,
	e观音姐姐,
	e空度禅师,
	e大大王,
	e啸天犬,
	e地涌夫人,
	e二郎神,
	e烟花占卜师,
	e巫奎虎,
#if ccc_m5
	e啸天犬2,
#else 
	e超级玉兔,
#endif
	e超级孔雀,
	e超级灵狐,
	e超级神蛇,
	e超级神马,
	e超级青鸾,
	e超级麒麟,
	e九色鹿,
	e持国巡守,
	e超级神羊,
	e六耳猕猴,
	e毗舍童子,
	e真陀护法
};

struct sAddPoint
{
	void Save(ofstream& File);
	void Load(ifstream& File);
#if ccc_m5
	int atk=4;
	int def=0;
	int hp=1;
	int mp=0;
	int spd=0;
	int idle=0;
#else
	int atk=5;
	int def=0;
	int hp=0;
	int mp=0;
	int spd=0;
	int idle=0;
#endif
	void Set(int atk2, int def2, int mp2, int hp2, int spd2)
	{
		atk = atk2;
		def = def2;
		hp = hp2;
		mp = mp2;
		spd = spd2;
	}
	void operator=(sAddPoint& target)
	{
		atk = target.atk;
		def = target.def;
		hp = target.hp;
		mp = target.mp;
		spd = target.spd;
		idle = target.idle;
	}
};

class cMap;
class cMyMap;
class CWFile;
class cObjFather
{
public:
	int	m_x=0;
	int	m_y=0;
	int	m_xOffset=0;
	int	m_yOffset=0;
	int	m_xOffset2=0;
	int	m_yOffset2=0;
	int	m_ShowHeight=0;
	int	m_ShowWidth=0;
	int	m_direction=1;
	int	m_bTwinkle=0;
	int m_FrameGap  = 10;
	int	m_NextFrame=0;
	int	now_frame=0;
	int	m_bShadow=0;
	int	m_bShine=0;
	int m_Width=0;
	int m_Height=0;
	void SetFrame(int frame)
	{
		if (now_frame != frame)m_bMove = TRUE;
		now_frame = frame;
	}
	int  GetFrame(){ return now_frame; }


	int GetShowWidth(){ if (m_ShowWidth) return m_ShowWidth; else return m_Width; }
	void SetShowWidth(int k);
	int GetShowHeight(){ if (m_ShowHeight)return m_ShowHeight; else return m_Height; }
	void SetShowHeight(int k);

	void SetxOffset(int xOff);
	void SetyOffset(int yOff);
	void SetxOffset2(int xOff2);
	void SetyOffset2(int yOff2);
	int  GetxOffset(){ return m_xOffset; };
	int  GetyOffset(){ return m_yOffset; };
	int  GetxOffset2(){ return m_xOffset2; };
	int  GetyOffset2(){ return m_yOffset2; };

	int GetHeight(){ return m_Height; }
	int GetTrueWidth(){ return m_Width; }
	void SetHeight(int h){ m_Height = h; }
	void SetWidth(int w){ m_Width = w; }

	int GetX(){ return m_x; }
	int GetY(){ return m_y; }
	void SetXY(int x, int y){ m_x = x; m_y = y;}
	void SetX(int x){ m_x = x; }
	void SetY(int y){ m_y = y; }


	void Init(cObjFather* pObj,int alpha=100); //创建一个和pObj一样大的图片,之前的图片会被释放掉
	void Reset(cObjFather* pObj, int alpha = 100);
	void Reset2(CWFile* pic);
	void Draw(cObjFather* pObj,int xpos=-1,int ypos=-1,int alpha=100);  //在图片上画新的图
	void GetRect(RECT& rect1);
	BYTE* m_pData=0;
	BYTE* m_pAlpha=0;
	BOOL m_NeedShow=TRUE;
	BOOL m_bMove=FALSE;
	RECT m_PreShowRect;
	~cObjFather();
	int m_OldDataSize=0;

public:
	bool _isChat = false;
};
struct sChangeColorData;
class CSprite
{
public:
	cObjFather* m_pOwner = nullptr;
	int GetDataID() { return GetOffsetID(m_Frame, m_pOwner->now_frame, m_MaxDirection, m_pOwner->m_direction); }
	int GetHeight(){ return m_Height; }
	int GetWidth(){ return m_Width; }
    int GetDirectionNum(){ return m_MaxDirection; };

	CSprite(void);
	~CSprite(void);
	BOOL Load(const sSpDecoder* decoder, const sChangeColorData* pChangeColorData = nullptr);
	BOOL LoadBMP(const std::string& filename, bool isTGA);
	int GetMaxFrame(){ return m_Frame; }

	int m_kx;				// 关键点 X
	int m_ky;				// 关键点 Y
	void FreeDatelp(void);

	int m_Frame;			// 每方向帧数

	int m_Width;			// 宽度
	int m_Height;			// 高度
	int m_MaxDirection;		// 方向数

	BOOL ShowOnScreen(BYTE* Pic, RECT rect);
	BOOL Show(BYTE* Pic, RECT rect, cMyMap* pMap);
	
	int  m_Bottom = -1;
	BOOL m_bLoad=FALSE;

public:
	sSpDecoder* _decoder = nullptr;
	cAlphaBmp* _bitmap = nullptr;
	int _matrixid = 0;
	bool isValid();
	static bool toMatrixs(sMatrixs& matrixs, const sChangeColorData* pChangeColorData);
};


class CPicture:public cObjFather
{
public:
	//图片上次的中心坐标
	int m_xold = 0;
	int m_yold = 0;
	int GetDataID();

	CPicture(void);
	~CPicture(void);
	// 载入数据
	void Load(const sSpDecoder* decoder, sChangeColorData* pChangeColorData = nullptr);
	void Free();	
	CSprite Spr;

	BOOL Show(BYTE* Pic, RECT rect, cMyMap* pMap)
	{
		if (!Spr.m_bLoad)return TRUE;
		Spr.m_pOwner = this;
		return Spr.Show(Pic, rect, pMap);
	}
	void ShowOnScreen(BYTE* pPic, RECT rect)
	{
		if (!Spr.m_bLoad)return;
		Spr.m_pOwner = this;
		Spr.ShowOnScreen(pPic, rect);
	}

	const sSpFrame* getInfoFrame(int iframe = -1);
	const sSpDecode* getDecode(int iframe = -1);

};

class CWFile
{
public:
	int m_PosType=1;
	RECT m_PreShowRect;
	

	void SetShine(BOOL needshow){ m_bMove = TRUE; m_Picture.m_bShine = needshow; }
	int GetCenter(){ return GetX() + (GetWidth() >>1); }
	int GetX(){ return m_Picture.GetX(); }
	int GetY(){ return m_Picture.GetY(); }
	void SetXY(int x, int y){ m_Picture.SetXY(x, y); m_bMove = TRUE; }
	void SetX(int x){ if(m_Picture.GetX() != x)m_bMove = TRUE;  m_Picture.SetX(x); }
	void SetY(int y){ if (m_Picture.GetY() != y)m_bMove = TRUE; m_Picture.SetY(y); }
	int GetWidth(){ return m_Picture.GetTrueWidth(); }
	int GetHeight(){ return m_Picture.GetHeight(); }
	int GetShowWidth(){ return m_Picture.GetShowWidth(); }
	void SetShowWidth(int k){ m_Picture.SetShowWidth(k); }
	int GetShowHeight(){ return m_Picture.GetShowHeight(); }
	void SetShowHeight(int k){ m_Picture.SetShowHeight(k); }
	int GetDirectionNum(){ return m_Picture.Spr.GetDirectionNum(); }
	void SetxOffset(int xOff){ m_Picture.SetxOffset(xOff); }
	void SetyOffset(int yOff){ m_Picture.SetyOffset(yOff); }
	void SetxOffset2(int xOff2){ m_Picture.SetxOffset2(xOff2); }
	void SetyOffset2(int yOff2){ m_Picture.SetyOffset2(yOff2); }
	int  GetxOffset(){ return m_Picture.m_xOffset; };
	int  GetyOffset(){ return m_Picture.m_yOffset; };
	int  GetxOffset2(){ return m_Picture.m_xOffset2; };
	int  GetyOffset2(){ return m_Picture.m_yOffset2; };
	BOOL m_bMove;
	DWORD m_NowID ;
	
	BOOL m_isStatic;
	CWFile();
	~CWFile();
	void GetPicRange(RECT& rect);//得到图片的范围
	RECT GetPicRange();//得到图片的范围
	BOOL isSelectOn(int x, int y);
	void SetStatic(BOOL bIsStatic){ m_isStatic = bIsStatic; }
	BOOL m_NeedShow=TRUE;
	
	int m_Type;
	BOOL LoadBMP(const std::string& filename, bool isTGA = false);
	BOOL Load(DWORD uid, sChangeColorData* pChangeColorData = 0);
	bool loadSmap(DWORD uid);
	void LoadWav(DWORD uid, int position = 0, BOOL bPlay = TRUE);
	void PlayWav();

	BOOL Show(BYTE* Pic, RECT rect, cMyMap* pMap)
	{
		if (!m_NeedShow)return TRUE;
		return m_Picture.Show(Pic, rect, pMap);
	}
	
	void ShowOnScreen(BYTE* Pic, RECT rect){ m_Picture.ShowOnScreen(Pic, rect); };
	void SubFrame(){ m_Picture.m_NextFrame = 0; (m_Picture.GetFrame() > 0) ? (m_Picture.SetFrame(m_Picture.GetFrame() - 1)) : m_Picture.SetFrame(0); }
	void SetFrame(int frame);
	int  GetNowFrame(){ return m_Picture.GetFrame(); }
	int  GetMaxFrame(){ return m_Picture.Spr.GetMaxFrame(); }
	BOOL  GetWillNextFrame();
	BOOL Free();
	BOOL CloseWDF();
	static BOOL openWdf(const CHAR* FileName);
	static void openSmap(const char* filename);

 	CPicture m_Picture;
 	cMyWav m_Wav;
	BOOL NextFrame();
	BOOL m_bCircle=TRUE;
	BOOL PreFrame();
	void SetDirection(int dir);
	BOOL m_ShowOnce = FALSE;//只显示一次
private:
	int  m_Direction;
public:
	cReader* _reader = nullptr;
	bool _isSmap;
	void setReader(const cReader* reader);
};

enum eBuffType
{
	eBuffType封印,
	eBuffType增益,
	eBuffType负面,
	eBuffType毒,
	eBuffType其它
};
struct sBuff
{
	int ID;   //BUFF的ID
	DWORD MagicID;
	//int Type; 
	int times;//剩余时间
	//buf的法术显示效果
	int bufPos;  //位置
	CWFile data;
	BOOL bBuffup; //在上面还是下面
	int userID;
	int targetID;
	eBuffType EffectType;//这个BUFF的类型, 0 增异  1 异常 2 毒 3 死亡召唤  
	int damage;
	int damage2;
	int skilllv = -1;
};

class cWfileP:public cObjFather
{
public:
	int GetNowFrame(){ return now_frame; }
	int GetWidth(){ return m_pFile->GetWidth(); };
	int GetCenter();
	vector<int> m_oldmask;
	//图片上次的中心坐标
	int m_xold = 0;
	int m_yold = 0;
	int GetDataID(){return GetOffsetID(m_pFile->m_Picture.Spr.GetMaxFrame(), now_frame, m_pFile->m_Picture.Spr.GetDirectionNum(),m_direction);}
	RECT m_PreShowRect;
	void operator=(cWfileP& file);
	
	cWfileP();
	void Set(CWFile* p);
	BOOL ShowOnScreen(BYTE* pPic, RECT rect)
	{
		if (!m_NeedShow)return TRUE;
		if (!m_pFile)return FALSE;
		CSprite& spr = m_pFile->m_Picture.Spr;
		if (!spr.m_bLoad)return TRUE;
		spr.m_pOwner = this;
		if (m_Width == 0 && m_Height == 0)
		{
			m_Width = m_pFile->GetWidth();
			m_Height = m_pFile->GetHeight();
		}
		spr.ShowOnScreen(pPic, rect);
		return TRUE;
	}
	BOOL Show(BYTE* pPic, RECT rect, cMyMap* pMap)
	{
		if (!m_NeedShow)return TRUE;
		if (!m_pFile)return FALSE;
		CSprite& spr = m_pFile->m_Picture.Spr;
		if (!spr.m_bLoad)return TRUE;
		spr.m_pOwner = this;
		return spr.Show(pPic, rect, pMap);
	}
	BOOL m_NeedShow;
	
	BOOL m_bStatic;

	BOOL NextFrame();//如果帧数改变,返回true否则返回false
	RECT GetPicRange();
	CWFile* m_pFile;
};

class cCanvas5;
class cSprite9 : public CWFile
{
public:
	void load(ulong uid);
	void setSize(int w, int h);
	void add2Canvas(cCanvas5* canvas);

	std::array<cWfileP, 4> _pfiles;
	int _w, _h, _wOri, _hOri;
};

enum eChannel5
{
	ec当前, //0
	ec队伍,    //1
	ec世界,
	ec系统,
	ec私聊
};
class cCanvas5;
class cText5 :public cObjFather
{
public:
	HPEN m_hPen;
	HFONT m_hFont = nullptr;
	void SetColor(DWORD color);
	void SetString(char* str);
	void SetString(string str);
	void SetString(string str, DWORD color);
	void SetString(int str);
	void SetString(INT64 str);
	void UpdateData();
	//0 正常,1 立体 2 描边
	void SetStyle(int style){ m_Style = style; }
	string GetString(){ return m_Text; }
	BOOL DrawAlphaEx(BYTE* Pic, RECT rect, cMap* pMap);
	void Show(cCanvas5* pCanvas);
	cText5();
	~cText5();
	void SetBackColor(DWORD color);
	void LockWidth(int Width){ m_MaxWidth = Width; }
	void CountSize(SIZE& size);
	void SetXCenter(int xCenter){ m_xCenter = xCenter; };//设置文字的中心
	BOOL m_bShowOnScreen = TRUE;
	void UpdateXCenter(){ m_x = m_xCenter - m_Width / 2; };
	BOOL m_bBold = FALSE;
	void SetTagColor(int starttag, int endtag, DWORD color);
	void SetTransparentColor(int startpos, int endpos, DWORD color);
	void UnTransparentColor(int startpos, int endpos, DWORD transparentcolor);
	//图片显示要8字节对齐,所以m_Width保存的值是大于等于显示宽度的.m_tuewidth保存对齐前的宽度
	int  GetTrueWidth(){return m_tuewidth;} 
	void SetTime(int time){ m_time = time; m_NeedShow = TRUE; }
private:
	int m_tuewidth;
	DWORD m_color=0;
	DWORD m_BacColor=0;
	string m_Text;
	int m_Style=0;
	BYTE* m_pData2 = 0;
	int m_Size=0;
	int m_MemSize2 = 0;;
	int m_MemSize=0;
	int m_MaxWidth = 0;
	int m_xCenter=0;
	int m_time=0;
	void ChangeColor(DWORD originalcolor, DWORD outcolor);

public:
	cAlphaBmp _bmp;
	void onChange();
	cCanvas* _canvas = nullptr;
};
struct sNpcData
{
	int  m_ModeId;
	string  m_name;
	DWORD	m_stand;
	DWORD	m_walk;
	DWORD	m_dialog;
};
struct sItemData
{
	string m_name;
	DWORD	m_smallhead;
};
struct sFabaoData
{
	string m_name;
	DWORD	m_smallhead;
};


struct sSkillData
{
	string m_name;
	DWORD	m_smallhead;
	DWORD	m_bighead;
	DWORD	m_majic;
	DWORD	m_defend;
};


#define WORKTYPE_ATTACK    1    //攻击
#define WORKTYPE_MAGIC     3    //施法
#define WORKTYPE_APPROACH  4    //接近
#define WORKTYPE_DEFEND    5    //防
#define WORKTYPE_SUFFER    6    //受到物理攻击
#define WORKTYPE_RETURN    7    //返回
#define WORKTYPE_MAGICSUFFER  8  //受到魔法攻击
#define WORKTYPE_MAGICATTACK  9   //法术驱动的物理攻击
#define WORKTYPE_FLY       10     //召唤兽被击飞
#define WORKTYPE_FALLDOWN  11  //角色死亡
#define WORKTYPE_CATCH  12  // 抓捕
#define WORKTYPE_AVOID  13  // 回避
#define WORKTYPE_MAGIC2   14    //使用特殊法术 比如防御,攻击
#define WORKTYPE_ITEM     15    //用道具
#define WORKTYPE_SUMMON   16    //召唤
#define WORKTYPE_GUARD   17    //保护
#define WORKTYPE_COUNTER 18  //反击

#define INDEXTYEP_CHARACTER 100
#define INDEXTYEP_PET       101
#define INDEXTYEP_NPC       102

enum PropertyType
{
	typeAtkZZ,
	typeDefZZ,
	typeHPZZ,
	typeMagZZ,
	typeSpdZZ,
	typeAvoidZZ
};

struct sCharacterData;
class cMyScript;
struct sFightOffset;

class cInterfaceChannel;
class cCanvas5;
struct sTextLine   //一行
{
	static const int MaxLine = 64;
	array<cWfileP, MaxLine> m_Face;
	array<int, MaxLine>    m_xFace;
	int m_NumFace;
	cText5 m_line;
	int m_Height;
};
struct sColorTag
{
	int m_linenum; //所在行数
	int m_start;  //所在字数
	DWORD m_Color; //颜色
};
struct sFaceText //一句 带表情的文字
{
	vector<sColorTag> m_ColorTag;
	int m_Height=0;
	int m_Gap = 0;
	int m_FirstAdd;//首行缩进
	void Show(cCanvas5* pCanvas);
	void SetPos(int x, int y);
	cWfileP m_Channel; //频道
	cText5 m_Name;  //名字
	int m_LineNum;  //行数
	void SetColor(DWORD color){ for (int i = 0; i < sTextLine::MaxLine; i++)m_TextLineList[i].m_line.SetColor(color); }
	vector<sTextLine> m_TextLineList; //一句最多9行
	//                  
	BOOL SetFaceText(CWFile* pChannel, string name, string tex, HFONT hFont, int LineWidth);
	BOOL SetFaceText(string tex, HFONT hFont, int LineWidth);
	sFaceText()
	{
		m_TextLineList.resize(sTextLine::MaxLine);
		m_Channel.m_bStatic = TRUE; 
		for (int i = 0; i < sTextLine::MaxLine; i++)
		{
			m_TextLineList[i].m_line.SetColor(RGB(255,255,255));
		}
	}
	int m_ShowStyle=0;  //0表示不显示频道和名字 1表示不显示名字  2表示全部表示  
	void SetTagColor(sColorTag& starttag, sColorTag& endtag);
	void setChat();
};
class cJinJieNum
{
public:
	int m_PositionID = 0;
	int m_JinJieNum = 0;
	BOOL GetBJinJie()
	{
		switch (m_PositionID)
		{
		case 0:
		case 1:
			return 0;
		default:
			return 1;
		}
	}
	void operator=(cJinJieNum& data)
	{
		m_PositionID = data.m_PositionID;
		m_JinJieNum = data.m_JinJieNum;
	}
	void Save(ofstream& File)
	{
		File << " ";
		File << m_PositionID << " ";
		File << m_JinJieNum << " ";
	}
	void Load(ifstream& File)
	{
		File >> m_PositionID;
		File >> m_JinJieNum;
	}
	void Reset()
	{
		m_PositionID=0;
		m_JinJieNum=0;
	}
};
struct sChangeColorData
{
	void Reset()
	{
		partnum = 0;
		for (int i = 0; i < 4; i++)
		{
			m_colorchange[i] = 0;
		}
	}
	enum eRanseType
	{
		ePc,
		ePet,
		eZuoQi,
		eZhuangShi
	};
	//染色
	int partnum = 0;
	int GetColorChange(int id){ return m_colorchange[id]; }
	BOOL SetColorChange(int id, int num);
	BOOL AddColorChange(int id);
	sChangeColorMatrix m_colormatrix[4];
	sChangeColorData()
	{
		for (int i = 0; i < 4; i++)
		{
			m_colorchange[i] = 0;
		}
	}
	void operator=(sChangeColorData& data);
	
	void Set(int d0,int d1,int d2,int d3);
	void Save(ofstream& File);
	void Read(ifstream& File, int modeid, eRanseType k, int partid);
// private:
	int  m_colorchange[4];
};
struct sChangeColorData2
{
	sChangeColorData m_ranse[4];
	void Read(int modeid, ifstream& File, int posid=0);
	void Save(ofstream& File);
	void operator=(sChangeColorData2& data)
	{
		for (int i = 0; i < 4; i++)
		{
			m_ranse[i] = data.m_ranse[i];
		}
	}
	void Reset()
	{
		for (int i = 0; i < 4; i++)
			m_ranse[i].partnum = 0;
	}
};
struct sNpc
{
	cJinJieNum m_JinJieID;
	int weaponid = -1;
	int weapontype = -1;
	sChangeColorData2 m_Ranse;
	int m_modeid = -1;
	string m_name;
	string m_mapname="";//所处位置
	int m_x;
	int m_y;
	int  m_direction;
	void Reset();
	void SetRanse(int id0, int id1 = 0, int id2 = 0, int id3 = 0, int part = 0);
	void AutoDirection4(){ m_direction = Direction8To4(rand() % 10); }
	void operator =(sNpc& data)
	{
		m_x = data.m_x;
		m_y = data.m_y;
		m_name = data.m_name;
		m_mapname = data.m_mapname;
		m_modeid = data.m_modeid;
		m_direction = data.m_direction;

		weapontype = data.weapontype;
		weaponid = data.weaponid;
		m_JinJieID=  data.m_JinJieID;
		
	}
	void Set(int x1, int y1){ m_x = x1; m_y = y1; }
	void Set(string name, string mapname, int modeid, int x, int y, int direction = -1, int jinjie = 0);
	
	void Save(ofstream& File);
	void Load(ifstream& File);
};
struct sZiZhi
{
	//资质
	int m_ATKZZ = 0;
	int m_DEFZZ = 0;
	int m_MAGZZ = 0;
	int m_HPZZ = 0;
	int m_SPDZZ = 0;
	int m_AVOIDZZ = 0;
	int m_Growing = 0;
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Set(int atk, int def, int mag, int hp, int spd, int avoid, int grow)
	{
		m_ATKZZ = atk;
		m_DEFZZ = def;
		m_HPZZ = hp;
		m_MAGZZ = mag;
		m_AVOIDZZ = avoid;
		m_SPDZZ = spd;
		m_Growing = grow;
	}
	//成长
	void Set(sZiZhi& zishi, int strong, int limit)
	{
		int ZiZhiOffset = 100 + (limit*strong) / 100;

		m_ATKZZ = zishi.m_ATKZZ + rand() % (ZiZhiOffset);
		m_DEFZZ = zishi.m_DEFZZ + rand() % (ZiZhiOffset);
		m_MAGZZ = zishi.m_MAGZZ + rand() % (2 * (ZiZhiOffset));
		m_HPZZ = zishi.m_HPZZ + rand() % (4 * (ZiZhiOffset));
		m_SPDZZ = zishi.m_SPDZZ + rand() % (ZiZhiOffset);
		m_AVOIDZZ = zishi.m_AVOIDZZ + rand() % (ZiZhiOffset);
		m_Growing = zishi.m_Growing + rand() % ((ZiZhiOffset) >> 4);
	}
	void operator=(sZiZhi& zizhi)
	{
		//资质
		m_ATKZZ = zizhi.m_ATKZZ;
		m_DEFZZ = zizhi.m_DEFZZ;
		m_MAGZZ = zizhi.m_MAGZZ;
		m_HPZZ = zizhi.m_HPZZ;
		m_SPDZZ = zizhi.m_SPDZZ;
		m_AVOIDZZ = zizhi.m_AVOIDZZ;
		m_Growing = zizhi.m_Growing;
	}
};

struct sMapObjTrigger;
struct sShangPinPet;
class cPetData;
class cTaskFather
{
public:
	cPetData* AddPetEnemyF(int hp, ePetID id, int lv=-1, string name="", BOOL bOur=0, int pos=-1);
	cPetData* AddPCPetEnemyF(int hp, ePetID id, int lv=-1, eMengPai mp = eMP_随机, string name = "", BOOL bOur = 0, int pos = -1);
	cPetData* AddPCEnemyF(int hp, int id, sZiZhi* zz, int lv=-1, eMengPai mp = eMP_随机, string name = "", int weapontype = -1, int weaponid = -1, BOOL bOur = 0, int pos = -1);

	void AutoGetPet(string datafilename, int id,int id1=-1,int id2=-1,int id3=-1);
#if ccc_date
	void AutoGetPet(string name){ return AutoGetPet(name, rand() % 40); }
#endif
	void SetMusic(string name = "");
	BOOL CheckHeroMoney(int money,BOOL bTag=TRUE);
	void DialogTalkObj(string text, cObj* p);
	void DialogTalkNObj(string text);
	void NowNpcTalk(string text);
	void UnInviteAll();//解散队伍
	void UpdateJob(string context, string title, int time, int ret);
	void UpdateJob(string context, string title);
	void SetNpc(sMapObjTrigger& data, int ret, string name, string map, int modeid, int x, int y, int direction = -1);
	void AddTriggerFightTurn(int ret);
	
	void RemoveTriggerObj();
	void RemoveTriggerGive();
	void RemoveTriggerObjMap(int ret=-1);
	void RemoveTriggerObjMap(int x,int y);
	void RemoveTriggerObjMap2(cObj* pObj);
	void RemoveTriggerSuccess();
	void RemoveTriggerFalse();
	void RemoveTriggerEscape();
	void AddChannel(string text,string name="",int channel=3);
	void AddTriggerTalkList(string path, int id, int ret);
	void AddTriggerGive(string name, int type, int id, int ret,BOOL bHuChi=FALSE);
	void AddTriggerFightStart(int ret);
	void AddTriggerFightSuccess(int ret);
	void AddTriggerFightFalse(int ret);
	void AddTriggerFightEscape(int ret);
	void AddTriggerLv(int ret,int lv);
	virtual void AddTriggerDialog(string path, int id, int ret);
	void AddTriggerObjMap(string mapname, int ret, BOOL bHuChi = TRUE);
	void AddTriggerObjMap(sNpc* npc, int ret,BOOL bHuChi=TRUE);
	void AddTriggerObjMap(sMapObjTrigger* data);
	void AddTriggerObj(sNpc* npc, int ret);
	void AddTriggerObj(string name,string map, int ret,BOOL bHuChi=TRUE);
	void AddNpcOne(sMapObjTrigger* data, BOOL needfind=FALSE);
	virtual void AddTag(string text, int time = 500);
	BOOL CheckNpc(string mapname, string npcname);//测检鼠标是否点在某NPC上
	int m_HuanShu = 0;
	BOOL m_bInit = FALSE;
	virtual void Init()=0;
	void CheckInit(){if (!m_bInit)Init(); m_bInit = TRUE;}
	virtual BOOL Process(int stage) = 0;
	int m_type;
	void SetJiangLi(int time, BOOL needtag = FALSE, int money = 100, int chubei = 0, int exp = 100, int expbb = 0);
	void SetJiangLi2(int exp,int money=0,int chubei=0,int petexp=0,BOOL needtag=TRUE);
	void SetJiangLiItem(int id, int type, int num = 1);
	void FollowLv(int id, int lv);
	void GetPet(string datafilename, sShangPinPet* pet,int stronglv);
	void GetPet2(sShangPinPet* pet, int stronglv);
};

struct sTaskFather
{
	cTaskFather* m_pTask=0;
	int m_Stage=-1;
};

struct sObjFather;
class cPetData;
class cPCData;
struct sItem2;
class cObj
{
public:
	void LoadCharacter(string name, string path);
	void FollowLv(int lv=-1);
	sObjFather* GetObjFather();
	BOOL GetSex();
	void Talk(string context, cTaskFather* pTask, int stage,
		string select1 = "", string select2 = "", string select3 = "", string select4 = "");
	void Answer(cTaskFather* pTask, int stage);
	void Talk(string context,BOOL needret=FALSE);
	void ResetIndex();
	void SetWeapon(int type, int id);
	void AutoPCData(
		string name,
		int modeid,
		sAddPoint* addpoint,
		sZiZhi* zizhi,
		eMengPai mengpaid = eMP_无,
		sItem2* pWeapon = 0,
		int petid = -1,
		int stonglv=-1
		);
	void AutoPCPetData(
		string name,
		int  petid,
		sAddPoint* addpoint,
		eMengPai mengpaid = eMP_无,
		int stonglv = -1
		);
	void AutoPetData(
		string name, int modeid, int strongid
		, sAddPoint* addpoint,BOOL Needskill=TRUE
		);

	sTaskFather m_TaskTrigger;
	int GetSkillLv(int skillid);
	void MoveMagicSuffer();
	void ClearState();
	BOOL ReMoveState(eBuffType Type);
	BOOL ReMoveStateID(int id);
	BOOL AddState(sBuff buf);
	BOOL CheckHaveState(int skillid);
	BOOL SetMagiSufferID(DWORD MagicID, int MagicPos, CWFile* pFile, BOOL up);
	void MoveMagicSufferID();
	//被打时的法术
	cWfileP m_MagicSuffer; //被打的时候显示的法术
	BOOL    m_bMagicSufferUp; //法术效果的位置,1表示上,0表示下
	int  m_MagicSufferPos;
	//下面用于记录角色的状态,比如中毒,催眠等等
	list<sBuff> m_StateList;

	CWFile m_Wav;
	CWFile m_WavSuffer;
	CWFile m_WavAtk;
	CWFile m_WavAtk2;
	CWFile m_WavMagic;
	CWFile m_WavDef;
	//
	CWFile m_MagicWav;
	cWfileP m_HpLinep;
	cWfileP m_HpEmptyLinep;
	vector<cWfileP> m_FaceTextBackp; //对话背景
	cSprite9 m_FaceTextBack;
	void UpdateHpLine();
	void  MoveDialog();
	void  MoveName();
	void  MoveHpLine();
	void Move2();
	BOOL m_bNeedShowName = TRUE; //是否显示名字

	void GetDateP(cPetData* &p);//得到指向召唤兽部分数据的指针
	int GetTopY();//得到角色顶部的位置
	int GetTopY2();
	BOOL m_bCheckWall;//是否要碰撞检测
	
	int m_LineNum;
	sFaceText m_ContextList;
	int m_ShowTime;
	BOOL ShowFaceText(cCanvas5* pCanvas);
	BOOL m_bGhost;
	cWfileP m_Ghost[4][2];
	BOOL SetGhost(BOOL b);//幻影
	//
	BOOL SetTwinkle(BOOL b);//闪耀
		
	BOOL Shake();//让对象左右抖动  战斗
	sFightOffset* GetFightOffset();
	//int* GetProperty(PropertyType Type);
	INT64* GetExp();
	INT64* GetExpMax();
	string GetAutoName();
	int   GetModeID();
	BOOL SetMagicEffect(CWFile* MagicEffect,int Pos=0,int Speed=4);
	cWfileP m_MagicEffect;  //自己身上的法术效果  比如升级
	BOOL m_AutoRun;
	BOOL isPointOn(int x,int y);  //返回1点是否在图片上
	int  m_ScriptSelect;  //由对话框返回 
	string m_ScriptPath;
	BOOL m_bScriptLoad;
	BOOL m_bHaveScript;
	int m_ScriptOneType;
	int m_ScriptOneId;
	void InitScript(string path)
	{
		m_ScriptPath = path;
		m_bHaveScript = TRUE;
		m_bScriptLoad = FALSE;
	}
	cMyScript  m_Script;
	BOOL Move();
	int  m_NowPos;  //当前动作类型	
	int m_PrePos;
	void SetStatic(BOOL isStatic)
	{
		for (int i = 0; i < 6;i++)
			m_data[i].m_isStatic = isStatic;
	}
	void SetSpeed(int k);
	void SufferBack(float speed,int sufferDirection);
	void Reset();
    BOOL Set(int POS_X,BOOL bCircle=TRUE);
	void SetSound(int POS_X,BOOL bPlay=TRUE);
	void PlayWav(int POS_X);
	void SetMagicSound(int SkillID,int position=0);
	void GetIndex(int POS_X, vector<DWORD>& out);
	DWORD GetIndex(int POS_X);
	void  Free();
	void  FreeIndex();
	void Stand();
	void SetTarget(float x, float y){ m_xTarget = x; m_yTarget = y; }
	void SetTarget(int x, int y){ m_xTarget = (float)x; m_yTarget = (float)y; }
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL ShowOnScreen(cCanvas5* pCanvas);
	void AutoFightDirection(int id);
	int m_time;  //-2表示静止, -1表示直走 ,大于-1表示寻路
	
	vector<Coordinate> m_Path;
	float m_xTarget;
	float m_yTarget;
	float   m_oldx;
	float   m_oldy;
	cText5 m_TrueName;
	void SetTrueName(string Name){ m_TrueName.SetString( (char*)Name.c_str()); };

	
	void Init();
	void SetShine(BOOL needshine);//高亮显示
	
	cObj();
	~cObj();

	int m_speed;    //角色的移动速度
	void SetFrame(int fram);

	BOOL m_NowShowData=0;
	CWFile* m_pShowData[4];
	CWFile m_data[8];
	void SetDataType(int Type);
	int  GetType(){ return m_IndexType; }
	void*  m_pIndex;
	BOOL CanEquip(int Equiptype, int ID, int Pos);
	BOOL SetShadow(int iShadow);
	

	BOOL AddZZ(int num, PropertyType typpe);
	int GetX(){ return (int)m_xPos; };
	int GetY(){ return (int)m_yPos; };
	void SetPos(int x, int y){ SetPos((float)x, (float)y); }
	void SetPos(float x, float y);
	void SetX(int x);
	void SetY(int y);
	void SetX(float x){ SetX((int)x); m_xPos = x; }
	void SetY(float y){ SetY((int)y); m_yPos = y; }
	void SetXY(int x, int y);
	void SetXY(float x, float y){ SetXY((int)x, (int)y); m_yPos = y; m_xPos = x; };
	void SetDirection(int direction);
	int  GetDirection(){ return m_direction; }
	void SetShake(BOOL shake);
	// 日期版专用
	void SetShakeFor抖动(BOOL shake);
	void MoveShadow();
	cWfileP* GetShadow(){ return &m_Shadow; }
	float m_xPos;
	float m_yPos;
	int    m_IndexType = 0;
	int m_IDInFightlist=-1;//所在ID,如果是sFightList的子对象,这个参数将被设置
	void SetShow(BOOL Needshow);
	BOOL GetShow();
	DWORD GetSound(int POS);
private:
	BOOL m_NeedShow2 = TRUE;
	cWfileP m_Shadow;
	int m_direction = -1;
	
	int    m_bShaketime; //在Shake中用到
	BOOL m_bShake; //是否抖动
	// 日期版专用
	BOOL m_bShakeFor抖动; //是否抖动
	
};
enum eXiuLian
{
	eXLATK,
	eXLDEF,
	eXLMAG,
	eXLDMAG,
};
struct sBBXiuLian
{
	void Reset()
	{
		m_Atk = 0;
		m_Def = 0;
		m_Mag = 0;
		m_DMag = 0;
		m_AtkExp = 0;
		m_DefExp = 0;
		m_MagExp = 0;
		m_DMagExp = 0;
	}
	int& GetAtk(){ return m_Atk; }
	int& GetDef(){ return m_Def; }
	int& GetMag(){ return m_Mag; }
	int& GetDMag(){ return m_DMag; }
	int& GetAtkExp(){ return m_AtkExp; }
	int& GetDefExp(){ return m_DefExp; }
	int& GetMagExp(){ return m_MagExp; }
	int& GetDMagExp(){ return m_DMagExp; }
	void AddXiuLianLv(int num, eXiuLian type);
	int AddExp(int lv, int num, eXiuLian type);//0 修炼没有增加 1 经验提升了 2 等级提升了
	void Set(int atk, int def, int mag, int dmag)
	{
		m_Atk = atk;
		m_Def = def;
		m_Mag = mag;
		m_DMag = dmag;
	}
	void Save(ofstream& File);
	void Load(ifstream& File);
	void operator=(sBBXiuLian& data)
	{
		m_Atk = data.m_Atk;
		m_Def = data.m_Def;
		m_Mag = data.m_Mag;
		m_DMag = data.m_DMag;
		m_AtkExp = data.m_AtkExp;
		m_DefExp = data.m_DefExp;
		m_MagExp = data.m_MagExp;
		m_DMagExp = data.m_DMagExp;
	}
private:
	int  m_Atk;
	int  m_Def;
	int  m_Mag;
	int  m_DMag;
	//修炼经验
	int  m_AtkExp;
	int  m_DefExp;
	int  m_MagExp;
	int  m_DMagExp;
};


struct spInt
{
	int d1 = 0;
	int d2 = 0;
	void Save(ofstream& File)
	{
		File << d1 << " ";
		File << d2 << " ";
	}
	void Load(ifstream& File)
	{
		File >> d1;
		File >> d2;
	}
	void Reset()
	{
		d1 = 0;
		d2 = 0;
	}
};
struct sInt
{
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Reset()
	{
		m_Data = 0;
		m_DataAdd = 0;
		m_DataAddPercent = 0;
		m_DataOriginal = 0;
	}
	void InitAll(int DataOriginal, int Percent, int Add)
	{
		m_DataOriginal = DataOriginal;
		m_DataAdd = Add;
		m_DataAddPercent = Percent;
		Update();
	}
	void SetDataAdd(int num)
	{
		m_DataAdd = num;
		Update();
	};
	void AddDataAdd(int num)
	{
		if (!num)return;
		m_DataAdd += num;
		Update();
	}
	void SetDataOriginal(int num)
	{
		m_DataOriginal = num;
		Update();
	};
	void AddDataOriginal(int num)
	{
		m_DataOriginal += num;
		Update();
	}
	void SetDataAddPercent(int num)
	{
		if (!num)return;
		m_DataAddPercent = num;
		Update();
	};
	void AddDataAddPercent(int num)
	{
		if (!num)return;
		m_DataAddPercent += num;
		Update();
	}
	int* GetDatap(){ return &m_Data; }
	int* GetPercentp(){ return &m_DataAddPercent; }
	int* GetOriginalp(){ return &m_DataOriginal; }
	int* GetAddp(){ return &m_DataAdd; }


	const int GetData()const{ return m_Data; }
	const int GetPercent()const{ return m_DataAddPercent; }
	const int GetOriginal()const{ return m_DataOriginal; }
	const int GetAdd()const{ return m_DataAdd; }
	void SetData(int k){  m_Data=k; }
	void SetPercent(int k){  m_DataAddPercent=k; }
	void SetOriginal(int k){  m_DataOriginal=k; }
	void SetAdd(int k){  m_DataAdd=k; }
	void operator=(sInt& k)
	{
		m_Data = k.GetData();
		m_DataAdd = k.GetAdd();
		m_DataAddPercent = k.GetPercent();
	}
private:
	void Update(){ m_Data = (m_DataOriginal*(100 + m_DataAddPercent)) / 100 + m_DataAdd; }
	int m_Data=0;
	int m_DataAddPercent=0;
	int m_DataOriginal=0;
	int m_DataAdd=0;
};
struct sPetSkill;
class cPet;
struct sFightData  //表示角色战斗时的属性 (战斗时属性会随得到的BUFF而改变.我们当然不能直接拿角色的永久属性来变)
{
	sInt  m_oldATK;   //伤害
	sInt  m_oldHIT;   //命中
	sInt  m_oldDEF;   //防御
	sInt  m_oldWakan; //灵力
	sInt  m_oldSPD;   //速度
	sInt  m_oldEvade; //躲闪
	spInt  m_oldGoldLive;//神佑
	//一个角色的状态列表
	int SufferNum;	//记录当回合被打的次数
	int AttackNum;	//记录当回合的攻击数
	int cannotAttack; //是否可以使用物理攻击   
	int cannotMagic;  //是否可以使用魔法
	int cannotSkill;  //是否可以使用特技
	int cannotUseItem;//是否可以使用道具
	int cannotAddHP;  //是否可以加血
	int cannotAll;  //是否可以动  催眠符的效果就是这个,后发制人也是这个
	int chaos;		//是否混乱
	int cannotLive;  //是否可以被复活
	BOOL m_bHit; //记录是否被命中  用这个值来判断是否需要保护	
	BOOL m_bDefend;//是否防御
	BOOL m_bCri;//是否被必杀
	vector<int>  m_guardID;//记录是否被成功保护 和 保护它的角色的ID

	int m_MaxDef;
	int m_MaxMagicDef;
	//记录强化状态
	int m_AtkIntensify;
	int m_DefIntensify;
	int m_SpdIntensify;
	int m_WallNum; //
	void Reset();
	void Clear()
	{
		m_guardID.clear();
		m_AtkIntensify=0;
		m_DefIntensify=0;
		m_SpdIntensify=0;
		m_WallNum=0; //
		Reset();
	}
	BOOL Init();
	int m_TurnHPAdd;
	int m_TurnHPHurtAdd;
	int m_TurnMPAdd;
};

struct sItem;
struct sItem2
{
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Set(int type, int id,BOOL needclear=TRUE);
	int GetType();
	int GetID();
	string GetName();
	string GetText();

	int GetNum(){ return m_Num; }
	sItem* m_pItemData = 0;
	int m_Num=0;
	vector<int>  m_Property; //属性  
	string m_strProperty="";
	void Reset()
	{
		m_Num = 0;
		m_Property.clear();
		m_pItemData = 0;
		m_strProperty="";
	}
	void Swap(sItem2& item2)
	{
		swap(m_Num, item2.m_Num);
		swap(m_pItemData, item2.m_pItemData);
		m_strProperty.swap(item2.m_strProperty);
		m_Property.swap(item2.m_Property);
	}
	void operator=(sItem2& item)
	{
		m_pItemData = item.m_pItemData;
		m_Num = item.m_Num;
		m_Property.clear();
		for (UINT i = 0; i < item.m_Property.size(); i++)
			m_Property.push_back(item.m_Property[i]);
		m_strProperty = item.m_strProperty;
	}
	BOOL operator==(sItem2& item)
	{
		if (item.GetType()==GetType())
		if (item.GetID() == GetID())
			return TRUE;
		return FALSE;
	}
};
struct sShangPinPet;
struct sControler
{
	void Set(int bfly=1, int bdel=1, int bBb=0, int bHavebb=0,int bCanGrab=0)
	{
		m_bBB = bBb;
		m_bDelete = bdel;
		m_HaveBB = bHavebb;
		m_bFly = bfly;
		m_CanGrab = bCanGrab;
	}
	void Save(ofstream& File);
	void Load(ifstream& File);
//	int GetOwner(){ return m_Hero; };

	int  GetFly(){return m_bFly; }
	int GetDel(){return m_bDelete; }
	int CheckBB(){ return m_bBB; }
	int CheckHaveBB(){ return m_HaveBB; }
	void SetHaveBB(int k){ m_HaveBB = k; }
	BOOL CheckGrab(){ return m_CanGrab; }
private:
	int m_CanGrab = 0; //是否可以抓 一般都是不能抓的
	int m_bFly = 1;//是否会被击飞
	int m_bDelete = 1; //战斗后是否删除
	int m_bBB = 0;//是否是某人的召唤兽;
	int m_HaveBB = 0;//是否有BB
};
enum ePetSkill
{
	ePS_反击,
	ePS_高级反击,
	ePS_反震,
	ePS_高级反震,
	ePS_吸血,
	ePS_高级吸血,
	ePS_连击,
	ePS_高级连击,
	ePS_飞行,
	ePS_高级飞行,
	ePS_夜战,
	ePS_高级夜战,
	ePS_隐身,
	ePS_高级隐身,
	ePS_感知,
	ePS_高级感知,
	ePS_再生,
	ePS_高级再生,
	ePS_冥思,
	ePS_高级冥思,
	ePS_慧根,
	ePS_高级慧根,
	ePS_不幸,
	ePS_必杀,
	ePS_高级必杀,
	ePS_幸运,
	ePS_高级幸运,
	ePS_神迹,
	ePS_高级神迹,
	ePS_招架,
	ePS_高级招架,
	ePS_永恒,
	ePS_高级永恒,
	ePS_敏捷,
	ePS_高级敏捷,
	ePS_强力,
	ePS_高级强力,
	ePS_防御,
	ePS_高级防御,
	ePS_偷袭,
	ePS_高级偷袭,
	ePS_毒,
	ePS_高级毒,
	ePS_驱鬼,
	ePS_高级驱鬼,
	ePS_鬼魂术,
	ePS_高级鬼魂术,
	ePS_魔之心,
	ePS_高级魔之心,
	ePS_神佑复生,
	ePS_高级神佑复生,
	ePS_精神集中,
	ePS_高级精神集中,
	ePS_否定信仰,
	ePS_高级否定信仰,
	ePS_法术连击,
	ePS_高级法术连击,
	ePS_法术暴击,
	ePS_高级法术暴击,
	ePS_法术波动,
	ePS_高级法术波动,
	ePS_迟钝,
	ePS_弱点火,
	ePS_弱点水,
	ePS_弱点土,
	ePS_弱点雷,
	ePS_雷属性吸收,
	ePS_高级雷属性,
	ePS_土属性吸收,
	ePS_高级土属性,
	ePS_火属性吸收,
	ePS_高级火属性,
	ePS_水属性吸收,
	ePS_高级水属性,
	ePS_移花接木,
	ePS_风刃,
	ePS_嗜血追击,
	ePS_龙鳞防御,
	ePS_龙神守护,
	ePS_法术抵抗,
	ePS_高级法术抵抗,
	ePS_直死,
	ePS_风华武圣,
	ePS_法术陷井,
	ePS_雷击,
	ePS_奔雷咒,
	ePS_落岩,
	ePS_泰山压顶,
	ePS_水攻,
	ePS_水漫金山,
	ePS_烈火,
	ePS_地狱烈火,
	ePS_惊心一剑,
	ePS_夜舞倾城,
	ePS_死亡召唤,
	ePS_力劈华山,
	ePS_浮云神马,
	ePS_法术防御,
	ePS_善恶有报,
	ePS_壁垒击破,
	ePS_苍鸾怒击,
	ePS_迷你空间震,
	ePS_大蛇破坏光线,
	ePS_须弥真言,
	ePS_从天而降,
	ePS_月光
};

class cCharacter;
class cPCData;
class cPetData   //一个BB应该有的数据
{
private:
	BOOL m_bSetupXiuLian = FALSE;
#if ccc_date
protected:
	bool _isBabyModeForLvup = true;
#endif
public:
	void ReadPet(string name, string path);
	void SetXLEffect(BOOL bSetup);
	void ResetAddPoint();
	void ResetAddPoint(bool isBB);
	void AutoGetSkill(int id);
	void AddSkill(ePetSkill id);
	//染色
	sChangeColorData2 m_RanSe;
	void SetJinJie(int num);
	cJinJieNum m_JinJieNum;//进阶
	void lvUpFuZhuSkill(int lv,int FuZhuSkillID);
#if ccc_m5
	virtual void Followlv(int lv = -1);
#else
	virtual void Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip);
#endif
	void FillHPMP();
	void EquipExtra(vector<int>& prop, int& startid,BOOL m_bEquip);
	void PetEquip(int Pos,int bequip=1);
	void UnPetEquip(int Pos);
	
	void Set(sShangPinPet* pet);
	BOOL CheckHavePetSkill(int SkillID);
	void AutoPetData(BOOL m_bNeedSkill=TRUE);
#if ccc_m5
	BOOL LeveUp(int lv = 1, BOOL bCost = TRUE);
#else
	BOOL LeveUp(int lv, bool isBaby, bool isAdd);
#endif
	void AddProPertyAtk(int num);
	void AddProPertyDef(int num);
	void AddProPertyMag(int num);
	void AddProPertyHp(int num);
	void AddProPertySpd(int num);
	void AddHpZZ(int num);
	void AddMagZZ(int num);
	void AddAtkZZ(int num);
	void AddAvoidZZ(int num);
	void AddSpdZZ(int num);
	void AddDefZZ(int num);
	void AddGrowing(int num);
	int CountATK();//计算伤害
	int CountDEF();//计算防
	int CountHP();//计算HP
	int CountWakan();//计算灵力
	int CountMP(); //计算MP
	int CountSpd(); //计算速度
	int CountEvade(); //计算躲避率
	int CountHit();//计算命中率
	void Reset();
//
	void AddPopularity(int num);
	int   m_Popularity = 0;  //人气
	//
	sBBXiuLian m_XiuLian;
	
	sItem2 m_PetEquip[3];
	//加点方式
	sAddPoint m_AddPoint;
	//资质
	sZiZhi m_ZiZhi;
	// 日期版专用
	std::array<int, 6> _spesialSkills;
	//BB技能
	int  m_NumofBBSkill=0;
	vector<sSkill*> m_pPetSkill;
	//经验
	INT64 EXP = 0;
	INT64 ExpMax = 0;
	

	//战斗属性表
	sFightData   m_FightProperty;
	string m_Name;
	string m_dataFileName;
	sControler  m_Controler;

	//辅助技能
	int   m_FuZhuSkillLvList[c_NumFuZhu];
	//
#if ccc_m5
	int  modeid = -1;
#else
	int  modeid = 0;
#endif
	int  m_AiLv = 0;//AI等级  决定角色在战斗时的行为 0-100
	int  m_StrongLv = 0; //强度  决定角色的属性强弱
	int  m_LV = 0;
	int  m_HP = 0;
	int  m_HPHurtMax = 0;
	int  m_MP = 0;
	int  m_CP = 0;      //愤怒
	int  m_CPMax = 150;
	int m_LiveHpLv = 0;//再生能力
	int m_LiveMpLv = 0;//冥思
	int m_LiveCp = 0; //每回合CP回复

	int   m_Physical=0;    //体力
	int   m_PhysicalMax=0; //体力上限
	int   m_Energy=0;      //活力
	int   m_EnergyMax=0;  //活力上限
	//属性点总数
	int  m_ProPertyAtk =0;
	int  m_ProPertyDef =0;
	int  m_ProPertyMag =0;
	int  m_ProPertyHP = 0;
	int  m_ProPertySpd = 0;
	// 日期版专用
	int  m_ProPerty未分配点 = 0;
	
	int nightLv = 0;//等级夜战能力
	int mpsavepercent = 0; //慧根	
	int restoreRate = 0; //状态恢复率
	int  abnormalResist = 0; //精神集中
	int  magicWavePercent=0;  //法术波动

	int buffAdd = 0;//BUFF时间
	int m_MagicNumAdd = 0;//法术作用对像增加

	
	sInt  m_HPMax;
	sInt  m_MPMax;
	sInt  m_ATK;   //伤害
	sInt  m_HIT;   //命中
	sInt  m_DEF;   //防御
	sInt  m_Wakan; //灵力
	sInt  m_SPD;   //速度
	sInt  m_Evade; //躲闪


	spInt GoldLivePercent;//神估
	spInt  m_ParryRate; //格档率  
	//必杀率
	spInt  m_CriRate; //物理
	spInt  m_MagicCriRate; //法术
	spInt  m_CureCriRate;//治疗

	spInt  m_CriAddPercent; //必杀伤害提升
	//连击
	int comboNumDown = 1;//连击下限
	int comboNumUp = 2;//连击上限
	int ShiXueAdd = 0; //连击伤害增加
	spInt  m_Combo;  //连击率
	spInt  m_MagicComboRate; //法连率

	spInt  m_Pierce;//无视防御率
	spInt  m_PierceMagic; //无视灵力率

	//命中率  躲避率
	spInt m_HitRate;  //物理
	spInt  m_MagicHitRate;//法术
	spInt  m_SealRate;//封印
	spInt poisonRate; //毒
	//伤害加成  防御加成
	spInt  m_DamageAddPercentMagic2;//固定
	spInt  m_DamageAddPercentMagic;//法术
	spInt  m_DamagePercent;//物理
	spInt  m_HiddenWeaponDamagePercent; //暗器
	spInt  m_DamageAddPercentPoision; //毒
	spInt  m_DamageAddPercentCure;//治疗  被治疗
	//召唤兽伤害加成
	spInt  m_PetDamagePercentMagic;//法术伤害
	spInt  m_PetDamagePercent;//物理伤害
	//伤害修正
	spInt  m_DamageAddMagic;//伤害结果增加
	spInt  m_DamageAddMagicLv;//法术伤害结果增加lv
	spInt  m_DamageAdd;//物理伤害结果增加
	spInt  m_DamageAddLv;  //物理伤害结果
	spInt  m_DamageAddCure;//治疗效果增加
	//反击
	spInt m_CounterRate;
	//反震
	spInt m_StabRate;
	spInt m_StabRateMagic;    //法术反弹伤害
	spInt m_StabDamageRate;
	spInt m_StabDamageRateMagic; //法术反弹率
	//
	spInt m_SuckBloodRate;//吸血率
	//
	
	//攻击降属性,被攻击提升属性
	spInt m_AtkDownCP;//攻击降CP
	spInt m_StartMagic;//开场法术
	spInt m_MagDownHPHurt;
	spInt m_AtkDownHPHurt;
	spInt m_AtkDownMP;
	spInt m_AtkDownAtk;
	spInt m_AtkDownHit;
	spInt m_AtkDownDef;
	spInt m_AtkDownWakan;
	spInt m_AtkDownSpd;
	spInt  m_Spurting;//溅射;
	//
	//金甲仙衣和降魔斗篷效果
	spInt m_JinJiaRate;
	spInt m_XiangMoRate;
	//法术属性伤害,0-100
	spInt  m_MagicFire; //火
	spInt  m_MagicSoil; //土
	spInt  m_MagicWater;  //水
	spInt  m_MagicThunder;//雷
	//特攻 
	spInt BoySpecial ;  //男
	spInt GirlSpecial;   //女
	spInt GoldSpecial;     //神族特攻
	spInt MagSpecial ;    //魔族特攻
	spInt ImmortalSpecial; //仙族特攻
	spInt MonsterSpecial;//妖怪特攻
	spInt PeopleSpecial ; //人
	spInt ghostSpecial;  //鬼特攻
	spInt machineSpecial ;//机械特攻

	cPetData();
	BOOL Save(ofstream& File, BOOL bPet = TRUE);
	BOOL Load(ifstream& File,BOOL bPet=TRUE);
	int m_IDinFightList=-1;//在fightlist列表中的位置
	int m_race = -1;//种族
};

class cMengPai;
struct sSkill;

struct sFightSkillSelect
{
	int Lv=0;
	int SkillID=-1;
	int TargetID=-1;
};
struct sZuoQiZhuangShi
{
	DWORD m_ColorID;
	DWORD  NodeStand;
	DWORD  NodeWalk;
	DWORD  Stand[15];
	DWORD  Walk[15];
};
struct sZuoQi
{
	DWORD m_ColorID;
	int ID;
	string Name;
	DWORD  nodeStand;
	DWORD  nodeWalk;
	DWORD  CharStand[15];
	DWORD  CharWalk[15];
};
struct sZuoQi2
{
	int m_ownerID;
	sZuoQi* m_pZuoQi = 0;
	sItem2  m_ZhuangShi;
	DWORD GetID(int Pos){ vector<DWORD> out; GetID(Pos, out); return out[0];}
	void GetID(int Pos, vector<DWORD>& out, BOOL haveChar = TRUE);
};
enum eCharacterEquip
{
	eChaEquipWuqi,
	eChaEquipTouKui,
	eChaEquipYaoDai,
	eChaEquipXieZi,
	eChaEquipXiangLian,
	eChaEquipYiFu
};

struct sWeaponData2;
struct sCharacterData3;
class cPCData :public cPetData  //一个主角应该有的数据
{
public:
	void Read(string name, string path);
	BOOL AddMoney(int xianjin, int chubei = 0, int cunyin = 0,BOOL cost=TRUE);//增加现金,储备,存银 如果小于0,是否扣除
	BOOL AddExp(INT64 exp, INT64 expbb = 0, BOOL bCost=TRUE);
#if ccc_m5
	void Followlv(int lv);
#else
	void Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip);
	void FollowlvAddPoint(int lv, bool isBabyMode, bool isEquip, bool isXiulian);
	void FollowSkill();
	void FollowXiulian();
	void FollowEuip(bool is穿盔甲 = true);
	void FollowWeapon();
	void FollowShoe();
	void FollowEquipAll();
	void FollowItem(bool isUnseal);
	void FollowBaby();
	void FullFuzhuBut暗器();
#endif
	int FindItem(int type, int id);
	void Save(ofstream& File);
	void Load(ifstream& File);
	//商人等级
	int m_traderLV=0;
	INT64 m_traderExp=0;
	INT64 m_traderExpMax=0;
	BOOL AddTraderExp(int num);
	//
	int m_Accelarate[8];//快捷键
	BOOL CostBangGong(int num);
	sWeaponData2*    m_pWeaponData2 = 0;
	sCharacterData3* m_pCharacterData2 = 0;
	sItem2* GetItem(int ID);
	void Reset();
	void AutoPCData(
		string name,
		int modeid,
		sAddPoint* addpoint=0,
		sZiZhi* zizhi=0,
		eMengPai mengpaid = eMP_无,
		int  petid = -1
		);
	//变身
	BOOL m_bUseCard=FALSE;
	void SetCard(int id);
	int&  GetCard();
	int m_CardPetID = -1;
	int    m_bDuJie=0;//是否渡劫
	int		m_face = 0;//脸
public:
	//sChangeColorData2 m_CardRanSe;//有一定几率变成变异召唤兽
	cPet*  m_pCardPetData = nullptr;
	//坐骑
	BOOL m_bOnZuoQi=FALSE; //是否坐上坐骑
	int zuoqiid=-1;  //坐骑ID
	sChangeColorData m_ZuoQiRanSe;//坐骑染色
	sChangeColorData m_ZhuangShiRanSe;//装饰染色
	sZuoQi2 m_ZuoQi;

	void operator=(cPCData& target);
	cPCData();
	//持有的召唤兽数
	int  m_NumofBB=0;
	vector<cPet*> m_pPetDataList;
	int m_FightPetID=-1;
	BOOL DeletePet(int ID); //给角色减去一个BB
	BOOL GetPet(cPet* pPet);//给角色增加一个BB
	void GetShangPinPet(int ShangPinID);

	vector<sSkill*> m_SkillEnablelist;
	int m_MengPaiPoint;
	int  m_SpecialSkillList[6];  //装备特技
	//门派
	int  m_MengPaiID=-1;
	int  m_MengPaiSkillLV[7];
	
	//帮派
	int  m_BangPaiID=-1;
	int   m_BangPaiPoint=0;
	//召唤兽修炼
	sBBXiuLian m_BBXiuLian;

	int   m_Money[3];       //钱  存银 储备金  
	
	sItem2 m_Item[61];  // 人物道具 


	~cPCData();
	BOOL Equip(sItem2& item,int m_bEquip=TRUE);
	//void EquipSpecial(vector<int>& prop,int& proppos, int Pos, int m_bEquip = 1);
	BOOL UnEquip(int id){ if (id >= 10000)id -= 10000; return Equip(m_Equip[id], -1); }
	BOOL CanEquip(sItem2& item);
	BOOL CanEquip(int type);
#if ccc_date
	int getEquipAtk();
#endif
	sItem2 m_Equip[6];//   人物装备
};

class cNpc
{
public:
	sNpcData* m_pNpcData;
	void GetID(int POS_X,vector<DWORD>& out);
private:

};

struct sAttackPoint
{
	string name;
	int xOffset;
	int yOffset;
	int point;
};

struct sFightOffset
{
	int  m_xOff;
	int  m_yOff;
	int  m_Point[2];
	int  m_Point2[2];
	int  m_MagicPoint;
	void ReadChar(ifstream& File)
	{
		File >> m_xOff;
		m_yOff = m_xOff >> 1;
		File >> m_Point[0];
		File >> m_Point[1];
		//角色只有一种攻击
		m_Point2[0] = m_Point[0];
		m_Point2[1] = m_Point[1];
		File>>m_MagicPoint;
	}
	void ReadPet(ifstream& File)
	{
		File >> m_xOff;
		m_yOff = m_xOff >> 1;
		File >> m_Point[0];
		File >> m_Point[1];
		File>> m_Point2[0];
		File>>m_Point2[1];
		File >> m_MagicPoint;
	}
	void operator=(sFightOffset& target)
	{
		m_xOff = target.m_xOff;
		m_yOff = target.m_yOff;
		m_Point[0] = target.m_Point[0];
		m_Point[1] = target.m_Point[1];
		m_Point2[0] = target.m_Point2[0];
		m_Point2[1] = target.m_Point2[1];
		m_MagicPoint = target.m_MagicPoint;
	}
};
struct sObjFather
{
	int m_ID;
	string m_Name;
	BOOL m_bSex;
	int m_Autorace;
};
struct sPosSound
{
	//声音
	DWORD	m_soundattack;
	DWORD	m_soundattack2;
	DWORD	m_soundmajic;
	DWORD	m_sounddefend;
	DWORD	m_soundsuffer;
	DWORD   m_sounddead;
	DWORD GetSoundID(int Pos);
};
struct sCharacterSound :public sPosSound
{
	void Read(ifstream& File)
	{
		File >> m_sounddead;
		File >> m_soundsuffer;
		File >> m_soundmajic;
		File >> m_soundattack;
		m_soundattack2 = m_soundattack;
		
		File >> m_sounddefend;
		
		
	}
};
struct sPetDataPart
{
public:
	DWORD m_ColorID;
	DWORD m_stand;
	DWORD m_walk;
	DWORD m_fstand;
	DWORD m_run;
	DWORD m_attack;
	DWORD m_attack2;
	DWORD m_majic;
	DWORD m_defend;
	DWORD m_suffer;
	DWORD m_dead;
	DWORD m_return;
	virtual DWORD GetID(int posid);
	virtual void Read(ifstream& File)
	{
		File >> m_ColorID;
		File >> m_attack;
		File >> m_attack2;
		File >> m_dead;
		File >> m_defend;
		File >> m_stand;
		File >> m_fstand;
		File >> m_majic;
		File >> m_return;
		File >> m_run;
		File >> m_suffer;
		File >> m_walk;
	}
};

struct sCharacterData3 :public sPetDataPart
{
	
	sCharacterSound m_Sound;
	sFightOffset m_Offset;
	void Read(ifstream& File)
	{		
		File >> m_attack;
		m_attack2 = m_attack;
		File >> m_dead;
		File >> m_defend;
		File >> m_fstand;
		File >> m_majic;
		File >> m_return;
		File >> m_run;
		File >> m_stand;
		File >> m_suffer;
		File >> m_walk;
		m_Offset.ReadChar(File);
		string dustbin;
		getline(File, dustbin);
	}
};
struct sCharacterHead2
{
	DWORD	m_smallhead;
	DWORD	m_bighead;
};
struct sCharacterHead
{
	sCharacterHead2 m_Head[4];
	DWORD	m_dialog;
	DWORD   m_FriendHead;
	void Read(ifstream& File)
	{
		File >> m_dialog;
		File >> m_FriendHead;
		for (int i = 0; i < 4; i++)
		{
			File >> m_Head[i].m_smallhead; //右上角的头像
			File >> m_Head[i].m_bighead; //道具栏中的头像
		}
	}
};



//一种角色
struct sCharacterData:public sObjFather
{
	DWORD m_ColorID;
	vector<sCharacterData3> m_Pos; //动作 声音 和偏移
	sCharacterHead m_Head[2]; //头像
	//表情
	DWORD	m_posgreet;
	DWORD	m_posbow;
	DWORD	m_posdance;
	DWORD	m_poscry;
	DWORD   m_posangry;
	DWORD   m_possit;
	void Read(ifstream& File)
	{
		File >> m_ID;
		int num;
		File >> num;
		m_Pos.resize(num);
		File >> m_ColorID;
		File >> m_Name;
		File >> m_Autorace;
		File >> m_bSex;
		File >> m_posbow;
		File >> m_poscry;
		File >> m_posdance;
		File >> m_posgreet;
		File >> m_possit;
		File >> m_posangry;
		for (int i = 0; i < num; i++)
		{
			m_Pos[i].Read(File);
		}
		m_Head[0].Read(File);
		m_Head[1].Read(File);
	}
	void ReadSound(int i, ifstream& File)
	{
		m_Pos[i].m_Sound.Read(File);
	}
	BOOL CanEquip(int EquipType);
	
	
};

class cPCData;
class CMainState;



#define TYPE_EQUIP 1
#define TYPE_ITEM  2
struct sZuoQi;
class cSkillManager;

class cCharacter
{
public:
	void UseCard(int id);
	int GetRace();
	void Free();
	void Talk(string str);
	void AutoPCData(
		string name,
		int modeid,
		sAddPoint* addpoint=0,
		sZiZhi* zizhi=0,
		eMengPai mengpaid=eMP_无,
		int petid = -1
		);


	int GetSkillLv(int id, cSkillManager* p);
	//int m_Modeid;
	BOOL AddMoney(int xianjin, int chubei=0,int cunyin=0);//增加现金,储备,存银
	
	//属性数据
	cPCData m_PCData;	
	
	DWORD GetID(int Pos)
	{ 
		vector<DWORD> out; 
		GetID(Pos, out); 	
		if (out.size())
			return out[0];
		return 0;
	}
	void GetID(int Pos, vector<DWORD>& out);
	void GetRanse(int Pos,  sChangeColorData* (&pChangeColor)[4]);
	sFightOffset* GetFightOffset();
	string GetName(){ return m_PCData.m_Name; }//得到角色名字
	BOOL CanEquip(int EquipType,int EquipLv,int Pos=-1);
	void SetData(sCharacterData* data);
	sCharacterData* GetData(){ return m_pCharacterData; }
private:
	//图像数据
	sCharacterData* m_pCharacterData;
};


struct sJiaJu
{
	sItem2 m_JiaJu;
	int m_xPos;
	int m_yPos;
	int m_Direction=0;
	void Save(ofstream& File)
	{
		File << " ";
		File << m_xPos<<" ";
		File << m_yPos << " ";
		File << m_Direction << " ";
		m_JiaJu.Save(File);
	}
	void Load(ifstream& File)
	{
		File >> m_xPos ;
		File >> m_yPos ;
		File >> m_Direction;
		m_JiaJu.Load(File);
	}
};

class cFangWu
{
public:
	void GetBB();
	void RemoveBB(cObj* yahuan);
	void RemovePreJiaJu();
	cFangWu();
	void Init();
	int GetHuanJin();
	void GoIn();
	void CheckHuanJin();
	BOOL AddJiaJu(sJiaJu& jiaju);
	string GetMapName();
	void Move(int x, int y, cObj* p);

	int GetGuiMo(){ return m_GuiMo; }
	void SetGuiMo(int num);
	void Save(ofstream& File);
	void Load(ifstream& File);

	vector<sNpc> m_List; //镇宅兽数  影响环境度 =5点环境度
	
	sNpc m_GuanJia;//管家 
	sItem2 m_DiBan;//地板
	vector<sJiaJu> m_JiaJu;//家具
	vector<int>  m_YaHuangIDList;
private:
	int m_PreHuanJin=0;
	BOOL m_bInit=FALSE;
	int m_GuiMo=-1;//规模 规模越大,能摆放的家具越多
	int m_HuanJinDu = 0;//环境度  
};
