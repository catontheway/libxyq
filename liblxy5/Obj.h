#pragma once
#include "_objinc.h"

class cPetData;
class cPcData;
class cObj
{
public:
// 	void LoadCharacter(string name, string path);
// 	void FollowLvForObj(int lv);
// protected:
// 	sNameSexRace* GetObjFather();
// public:
//	bool GetSex();
	void Talk(string context, cTaskFather* pTask, int stage,
		string select1 = "", string select2 = "", string select3 = "", string select4 = "");
	void Answer(cTaskFather* pTask, int stage);
	void Talk(string context, bool needret = false);
//	void ResetIndex();
	void saySkill(string text, int time = 180);
	void say(string text, int time = 0x8FF);
	void SetWeapon强制换模型_不动数据_可能未鉴定(int type, int id);

	void AutoData(int modeid, sItem2* pWeapon = 0, int petid = -1, string name = "");

	void AutoData(int modeid, string name = "");

	sTaskFather m_TaskTrigger;
	int GetSkillLv(int skillid);
	void MoveMagicSuffer();
	void ClearState();
	bool ReMoveState(eBuffType Type);
	bool ReMoveStateID(int id);
	bool AddState(sBuff buf);
	bool CheckHaveState(int skillid);
	bool SetMagiSufferID(ulong MagicID, int MagicPos, cWasFile* pFile, bool up);
	// move? 被打动画还要跟着动？
	void MoveMagicSufferID();

	bool SetMagicCri(cWasFile* pFile);
	void MoveMagicCri();
	void showMagicCri(cCanvas* pCanvas);
	//被打时的法术的容器
	cObjWas m_MagicSuffer; //被打的时候显示的法术
	cObjWas m_MagicCri; //被打的时候法术暴击动画
	bool    m_bMagicSufferUp; //法术效果的位置,1表示上,0表示下
	int  m_MagicSufferPos;
	//下面用于记录角色的状态,比如中毒,催眠等等
	list<sBuff> m_StateList;

	cWasFile m_Wav;
	cWasFile m_WavSuffer;
	cWasFile m_WavAtk;
	cWasFile m_WavAtk2;
	cWasFile m_WavMagic;
	cWasFile m_WavDef;
	//
	cWasFile m_MagicWav;
	cObjWas m_HpLinep;
	cObjWas m_HpEmptyLinep;
	vector<cObjWas> m_FaceTextBackp; //对话背景
	void UpdateHpLine();
	void  MoveDialog();
	void  MoveName();
	void  MoveHpLine();
	void Move2();
	bool m_bNeedShowName = true; //是否显示名字

	void GetPropertyData(cPropertyData* &p);
	cPetData* getPetData();
	cPcData* getPcData();
	cPropertyData* getPropertyData(){ cPropertyData* p; GetPropertyData(p); return p; }
	int GetTopY();//得到角色顶部的位置
	int GetTopY2();
	bool m_bCheckWall;//是否要碰撞检测

	int m_LineNum;
	sFaceText m_ContextList;
	int m_ShowTime;
	bool ShowFaceText(cCanvas* pCanvas);
	bool m_bGhost;
	cObjWas m_Ghost[4][2];
	bool SetGhost(bool b);//幻影
	//
	bool SetTwinkle(bool b);//闪耀

	bool Shake();//让对象左右抖动  战斗
	const sFightPoint* GetFightPoint();
	//int* GetProperty(PropertyType Type);
// 	INT64* GetExp();
// 	INT64* GetExpMax();
	string GetName();
	int  GetModeID();
	bool SetMagicEffectFromItem(cWasFile* MagicEffect, int Pos = 0, int Speed = 4);
	cObjWas m_MagicEffect;  //自己身上的法术效果  比如升级
	bool m_AutoRun;
	bool isPointOn(int x, int y);  //返回1点是否在图片上
	int  m_ScriptSelect;  //由对话框返回 
	string m_ScriptPath;
	bool m_bScriptLoad;
	bool m_bHaveScript;
	int m_ScriptOneType;
	int m_ScriptOneId;
	void InitScript(string path)
	{
		m_ScriptPath = path;
		m_bHaveScript = true;
		m_bScriptLoad = false;
	}
	cMyScript  m_Script;
	bool Move();
	int m_NowPos;  //当前动作类型	
	int m_PrePos;
	void SetStatic(bool isStatic)
	{
		forr (m_data, i)
			m_data[i].m_isStatic = isStatic;
	}
	void SetSpeed(int k);
	// 被打，后仰，回来
	void SufferBack(float speed, int sufferDirection);
	void Reset();
	bool Set(int POS_X, bool bCircle = true);
	void SetSound(int POS_X, bool bPlay = true);
	void PlayWav(int POS_X);
	void SetMagicSound(int SkillID, int position = 0);
	void GetID(int POS_X, vector<ulong>& out);
	ulong GetID(int POS_X);
	void  Free();
	void  FreeData();
	void Stand();
	void setNextTargetOnAstart(float x, float y){ m_xTarget = x; m_yTarget = y; }
	void setNextTargetOnAstart(int x, int y){ m_xTarget = (float)x; m_yTarget = (float)y; }
	virtual bool Show(cCanvas* pCanvas);
	virtual bool ShowOnScreen(cCanvas* pCanvas);
	void AutoFightDirection(int id);

	//-2表示静止, -1表示直走 ,大于-1表示寻路
	int m_AstartPathIndex;

	// 寻路路径
	vector<VecInt> m_AstartPathVecs;
	float m_xTarget;
	float m_yTarget;
	float   m_oldx;
	float   m_oldy;
	cText m_TrueName;
	cText m_Name称谓;
	cText m_ConductFire;
	cText m_ConductSeal;
	void SetTrueName(string Name){ m_TrueName.SetString((char*)Name.c_str()); };


	void Init();
	void SetShine(bool needshine);//高亮显示

	cObj();
	~cObj();

	int m_moveSpeed;    //角色的移动速度
	void SetFrame(int fram);

	bool m_NowShowData = 0;
	array<cWasFile*, 4> m_pShowData;
	array<cWasFile, 8> m_data;
	void SetDataType(int Type);
	int  GetDataType(){ return m_IndexType; }
	void*  m_pIndex;
//	bool CanEquip(int Equiptype, int ID, int Pos);
	bool SetShadow(int iShadow);


//	bool AddZZ(int num, PropertyType typpe);
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
	void SetShake(bool shake);
	void SetShakeFor抖动(bool shake);
	void MoveShadow();
	cObjWas* GetShadow(){ return &m_Shadow; }
	float m_xPos;
	float m_yPos;
	int m_IndexType = 0;
	int m_IDInFightlist = -1;//所在ID,如果是sFightList的子对象,这个参数将被设置
	void SetShow(bool Needshow);
	bool GetShow();
	ulong GetSound(int POS);
//private:
	bool m_NeedShowShadow = true;
	bool m_NeedShowFoot = true;
	cObjWas m_Shadow;
	cWasFile m_Foot;
	int m_Foot2 = -1;
	vector<cObjWas> m_Foot2s;
	int m_direction = -1;

	int  m_bShaketime; //在Shake中用到
	bool m_bShake; //是否抖动
	bool m_bShakeFor抖动; //是否抖动

};