#pragma once


enum eBuffType
{
	eBuffType封印,
	eBuffType增益,
	eBuffType负面,
	eBuffType毒,
	eBuffType其它
};





// #define TYPE_EQUIP 1
// #define TYPE_ITEM  2





#define STATE_FIGHT 2
#define STATE_FIGHT_MUSIC 6
#define STATE_MAIN  1
#define STATE_EXT  3
#define STATE_MENU 4
#define STATE_GAMEOVER 5



//8个方向
#define DIRECTION_UP		 8
#define DIRECTION_DOWN		 2
#define DIRECTION_RIGHT		 6
#define DIRECTION_LEFT		 4
#define DIRECTION_LEFT_UP	 7
#define DIRECTION_RIGHT_UP	 9
#define DIRECTION_LEFT_DOWN  1
#define DIRECTION_RIGHT_DOWN 3

//#define OBJ_TYPE_PC       1
//#define OBJ_TYPE_NPC      2
//#define OBJ_TYPE_PET     3


#define POS_STAND    1
#define POS_WALK     2
#define POS_FIGHT_STAND 3
#define POS_RUN       4
#define POS_ATTACK       5
#define POS_MAGIC       6
#define POS_DEF       7
#define POS_SUFFER       8
#define POS_DEAD       9
#define POS_RETURN       10
#define POS_ATTACK2      11
#define POS_GREET      12
#define POS_DANCE      13
#define POS_BOW      14
#define POS_ANGRY      15
#define POS_CRY      16
#define POS_SIT      17
#define POS_BIGHEAD      18
#define POS_DIALOG      19
#define POS_SMALLHEAD    20

#define POS_SOUNDATTACK       21
#define POS_SOUNDMAGIC       22
#define POS_SOUNDDEF       23
#define POS_SOUNDSUFFER       24
#define POS_SOUNDDEAD       25
#define POS_SOUNDATTACK2      26