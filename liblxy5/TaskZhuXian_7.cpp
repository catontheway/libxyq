#include "_global.h"


bool TaskZhuXian::Process7(int stage)
{
int next = stage + 1;
setJobTitle("真假美猴王");
int i = 10;
int r = rand() % 20;

static int s_hadG;
switch (stage)
{
case 0:
	AddTriggerDialog("", "#G喂，猴头，听说你跟唐憎、猪八戒、沙和尚他们3个打副本，你中途挂机了！他们正满世界找你呢#G#103"
		, "草~别说了,那3个傻逼，我都无语了？",
		"什么个情况啊这是#17#4",
		"与其跟那3傻组队还不如不打了，文能挂机喷队友，武能越塔送人头。进可孤身一挑五，退可坐等二十投。前能飞脚救残敌，后能放墙堵队友。静则百年不见人，动则千里送超神。英勇闪现送一血，卖起队友不回头。顺风浪，逆风投。问君能有几多愁，恰似五人四坑20投。#1",
		"可是佛主规定只有玄奘才能去西天取经啊#24",
		"我这里也有玄奘啊#24,");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n看看假冒伪劣的糖増师徒 ");
	break;
case 1:
	AddTriggerObj("美猴王");
	break;
case 2:

	g_pMainState->FindObjByName("美猴王")->say("出来吧！师傅，师弟们");
	g_pHeroObj->say("#24");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n和猴子再次交谈 ");
	AddTriggerObj("美猴王", "花果山",_next+1);
	//break;
case 3:
{
	sNpc npc;
	npc.Set("糖増", "花果山", e空度禅师, 77, 101, DIRECTION_LEFT);
	AddTriggerObjMap(&npc, _next, false);

	npc.Set("莎河上", "花果山", e沙和尚, 88, 105, DIRECTION_RIGHT);
	AddTriggerObjMap(&npc, _next, false);

	npc.Set("褚八街", "花果山", e猪八戒, 89, 99, DIRECTION_UP);
	AddTriggerObjMap(&npc, _next, false);
	npc.Set("柏龙玛", "花果山", e龙马, 99, 104, DIRECTION_UP);
	AddTriggerObjMap(&npc, _next, false);
}
	g_pMainState->FindObjByName("糖増")->say("尸主！你好#52");
	g_pMainState->FindObjByName("莎河上")->say("二师兄最近好像胖了#52");
	g_pMainState->FindObjByName("褚八街")->say("胖你妹，怼你屎忽呢！#52");
	AddTriggerObj("美猴王", "花果山", _next + 1);
	break;
case 4:
	AddTriggerDialog(
		"看，我没骗你吧！我这里也有",
		"可恶,我最讨厌假冒伪劣产品了#54",
		"有本事你打假啊#4",
		"看来你是不见棺材不流泪啊。",
		"你是存心来闹事的吧,傻逼!吃俺老孙一棒#4",
		"放猴过来#2");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n看看假冒伪劣的糖増师徒 ");
	break;
case 5:
{

	auto pc = AddEnemy(990000, e孙悟空, 69, eMP_狮驼岭, "美猴王");
	pc->getObj()->say("#17狗日的，没事找事，看我厉害#2");
	pc->DmgAdd.d1 += 0x1fff;
	AddEnemy(15000, e猪八戒, 60, eMP_随机, "褚八街");
	AddEnemy(15000, e沙和尚, 60, eMP_随机, "莎河上");
	AddEnemy(15000, e龙马, 60, eMP_随机, "柏龙玛");
	AddEnemy(15000, e空度禅师, 60, eMP_随机, "糖増");
	auto p = AddEnemy(15000, 2000 + rand() % 16, 160, eMP_随机, "吃瓜群众");
	p->getObj()->say("#R骚年，必死的不要作无谓的挣扎#R");
	g_StateType = STATE_FIGHT;
	AddTriggerFightSuccess(_next);
	AddTriggerFightEscape(_next);
	AddTriggerFightEscape(_next);
	break;
}
	//return TRUE;
case 6:
	AddTriggerDialog("",
		"#G这猴子成精了，这么厉害，看来得去找下观音阿姨帮下忙了#103"
		, "滚远点，不然送你归西");
	g_pHeroObj->say("#24");
	AddJob("#R任务提示#R：\n#B潮音洞#B\n#R相关人物：#R\n#B观音 #B\n#R任务介绍#R\n求救观音 ");

	break;
case 7:
	AddTriggerObj("观音姐姐","潮音洞");
	break;
case 8:
	AddTriggerDialog("少侠，你看我美么？",
		"#G观音阿姨，花果山的猴头不肯跟唐三藏做副本了怎么办#103"
		, "你叫我啥？观音阿姨#4，你还想不想见明天的太阳",
		"#G#4,对不起，一时口误，观音姐姐可有办法解决！#G",
		"#G花果山那个悟空是假的,建议你去找李天王借照妖镜#103#G",
		"#G你教我紧箍咒吧,这样就能分辨了#1#G",
		"#G这个简单,你把观音咒学到30级就行了.哦对了,你不是普陀弟子,和长得实在对不起观众，那就别想了,后悔去吧#28#G",
		"#G你怎么就这么腹黑呢#71");
	AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B李靖 #B\n#R任务介绍#R\n找李靖找照妖镜 ");
	break;

case 9:
	AddTriggerObj("李靖", "凌宵宝殿");
	break;
case 10:
	AddTriggerDialog("少侠，你又来了，来试试我新改进的照妖镜",
		"#G我很好奇你加入了什么高科技玩意，难道会发射光波？#G",
		"还没达到那种程度，只是运用了生物识别AR技术，对各种动物都有效",
		"#G#4这么厉害，我试试24##G",
		"#G看，镜子里面是不是出现了一头猪#1#G",
		"#G。。。。。，你才是猪。。。#4#G",
		"#G哈哈，开玩笑的了，拿着镜子去办你的事情吧#28#G",
		"#G谢谢李天王#71");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n用照妖镜分辨假冒伪劣的孙悟空 ");
	getTag("你得到了照妖镜");
	break;

case 11:
	AddTriggerObj("美猴王", "花果山");
	break;
case 12:
	getTag("你拿着镜子对美猴王照了照");
	g_pHeroObj->say("这个居然是真的，那另外一个就是假的罗。");
	AddJob("#R任务提示#R：\n#B水帘洞#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n去水帘洞找假的美猴王 ");
	AddTriggerObj("美猴王", "水帘洞", _next);
	break;
case 13:
	AddTriggerDialog(
		"什么人，你拿着镜子照我干什么",
		"妖孽,齐天大圣你也敢假冒,上次是因为我没点技能,这回让你见识见识我的厉害#4",
		"住手,我才是真的美猴王.....",
		"用照妖镜一照就知道了", "",
		"嗯?这个居然也是真的......看来照妖镜对这妖怪没用啊.总之先把镜子还给李天王吧",
		"#2");
	AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B李靖 #B\n#R任务介绍#R\n找李靖说照妖镜不管用 ");
	break;

case 14:
	AddTriggerObj("李靖", "凌宵宝殿");
	break;
case 15:
	AddTriggerDialog("",
		"#G李天王，你的照妖镜是不是街边2块钱买回来玩的啊#103",
		"胡说，我信心苦苦研究了几小时做出来。",
		"卧槽，怪不得质量这么差",
		"没想到照妖镜居然对那妖怪没用....看来我得让科技大佬太上老君改善技术了啊#8",
		"那怎么办啊#74",
		"地藏王的谛听也能分辩妖怪,我们去找他吧" );
	AddJob("#R任务提示#R：\n#B地藏王府#B\n#R相关人物：#R\n#B地藏王 #B\n#R任务介绍#R\n找地藏王帮忙 ");
	break;
case 16:
	AddTriggerObj("地藏王", "地藏王府");
	break;
case 17:
	AddTriggerDialog(
		"很遗憾,谛听也分辩不出.建议你去找观音,她认真起来能耐比我大#3",
		"你是说她之前都不认真吗.....",
		"可以这么说，她心情好能耐就大，心情不好能耐就小",
		"#24，还有这种操作",
		"比如说她听到别人夸她好看，她能耐就比较大了",
		"#24好吧！可能是我之前叫她阿姨的缘故",
		"你还活着真是个奇迹#24");
	AddJob("#R任务提示#R：\n#B潮音洞#B\n#R相关人物：#R\n#B观音 #B\n#R任务介绍#R\n求观音找解决之法 ");
	break;
case 18:
	AddTriggerObj("观音姐姐", "潮音洞");
	break;

case 19:
	AddTriggerDialog("你怎么又来了，滚，滚，滚，我不想看见你",
		"#G哎呀，对不起了我美丽、可爱、天生丽质，人见人爱、车间车载、花见花开的观音姐姐帮帮我嘛#103",
		"咦，孺子可教哦，不见3日，应当刮目相看哦！这是他们取经路上的劫数,佛主早就给了我锦囊.我把它交给黑熊怪保管了#1",
		"卧槽，那你之前怎么不对我说",
		"#4鬼叫我之前叫我做阿姨，这就是对你的惩罚，也是你的劫数",
		"那怎么办啊！",
		"我都说这是劫数了#24" );
	AddJob("#R任务提示#R：\n#B普陀山#B\n#R相关人物：#R\n#B黑熊怪 #B\n#R任务介绍#R\n找黑熊要锦囊 ");
	break;

case 20:
	AddTriggerObj("黑熊怪", "普陀山");
	break;

case 21:
	AddTriggerDialog(".......不好,时间太久,我居然忘了这是观音姐姐给我的了.",
		"#G认真想想，放哪里了！#103",
		"龙女宝宝老是吵着要生日礼物,我一烦就把这当生日礼物给她了#17",
		"这个理由很合理#8我去找她吧#3",
		"要你就自己去，送出去的东西我怎么能那么不要脸地要回来！",
		"好吧！只有靠我自己了#24");
	AddJob("#R任务提示#R：\n#B普陀山#B\n#R相关人物：#R\n#B龙女宝宝 #B\n#R任务介绍#R\n找龙女宝宝讨回锦囊 ");
	break;
case 22:
	AddTriggerObj("龙女宝宝", "普陀山");
	break;
case 23:
	AddTriggerDialog("",
		"#G龙女宝宝,这个哈根达斯棒棒糖给你，这个锦囊是黑熊怪替观音姐姐保管的,黑熊怪这脑子不好使忘了才把这当生日礼物的,现在观音姐姐要收回锦囊了.希望你能还回来.",
		"这锦囊现在在本宝宝这儿,就是本宝宝的,谁也别想拿走#90，你的糖我也要了#1",
		"你不要那么调皮好不，黑熊怪说,等下他会拿一个更好的给你,做为补偿#17",
		"让黑熊怪把那个更好的给观音姐姐吧,本宝宝很大方的#3",
		"你这是逼我动手吗#24我从来不打女人,你别让我破戒#3(<--之前不是打过玉面狐狸,万圣公主,花妖等吗#74)");

	break;

case 24:
{
	auto pc = AddEnemy(47000, e小龙女, 75, eMP_普陀山, "龙女妹妹");
	pc->getObj()->say("#17居然敢欺负本宝宝，飘飘拳锤你#2");
	AddEnemy(40000, e蛟龙, 65, eMP_随机, "蛟龙喽啰");
	AddEnemy(40000, e蛟龙, 65, eMP_随机, "蛟龙喽啰");
	AddEnemy(40000, e蛟龙, 65, eMP_随机, "蛟龙喽啰");
	AddEnemy(40000, e蟹将, 65, eMP_输出, "蟹将喽啰");
	AddEnemy(40000, e蛟龙, 65, eMP_随机, "蛟龙喽啰");
	AddEnemy(40000, e龟丞相, 65, eMP_随机, "龟丞相喽啰");
	AddEnemy(40000, e龟丞相, 65, eMP_随机, "龟丞相喽啰");
	AddEnemy(40000, e龟丞相, 65, eMP_随机, "龟丞相喽啰");
	AddEnemy(40000, e虾兵, 65, eMP_随机, "虾兵喽啰");
	g_StateType = STATE_FIGHT;
	AddTriggerFightSuccess(_next);
	break;
}

case 25:
	/////////////////////////////////////////////////////////////////////////////
	
	if (r >6)//奖励代码段
	{

		if (r >= 0 && r <1)//10%
		{
			g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
		

		}
		else if (r >= 1 && r<2)//10%
		{
			g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
	

		}
		else if (r >= 2 && r<4)
		{
			g_pMainState->awardItem(23, rand() % 9, 1, true);
		
		}
		else if (r >= 4 && r <= 7)
		{
			g_pMainState->awardItem(23, rand() % 9, 1, true);
		}
	}

	else if (r>7)
	{
		g_pMainState->awardk(100, 100);//10W经验，10W钱
		g_pHeroObj->say("#15我不要当非洲人");;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	AddTriggerDialog("你这人怎么这么暴力,这个给你吧#15诅咒你孤独一辈子#71",
		"#G对付熊孩纸专用#103",
		"拿着快滚吧！不想看见你了#17",
		"厉害了，我的小公举#3",
		"以大欺小！真不要脸",
		"说得对#24");
	AddJob("#R任务提示#R：\n#B潮音洞#B\n#R相关人物：#R\n#B观音 #B\n#R任务介绍#R\n得到锦囊，回普陀山。将锦囊直接给予观音姐姐。 ");
	break;

case 26:
	AddTriggerObj("观音姐姐", "潮音洞");
	break;

case 27:

	AddTriggerDialog("少年，你怎么又来了，是不是贪恋我的美色啊#71",
		"#17才没有呢，我把你给黑熊怪的锦囊拿回来了",
		"哦，原来是这样，你附耳过来我告诉你怎么对付这个假猴王，******这个东西带去，切莫伤了那猴子性命。#17",
		"好的，谢谢了，我马上就去收了这猴头#3");
	AddJob("#R任务提示#R：\n#B水帘洞#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n根据锦囊提示分辨假冒伪劣的孙悟空（洞里那个） ");
	break;

case 28:
	AddTriggerObj("美猴王", "水帘洞");
	break;


case 29:	
	g_pHeroObj->say("***********");
	g_pMainState->FindObjByName("美猴王")->say("卧槽！卧槽！痛死我了，哪个蠢货在念紧箍咒");
	AddJob("#R任务提示#R：\n#B花果山 40 240#B\n#R相关人物：#R\n#B侯医仙 #B\n#R任务介绍#R\n#R#B向#R为辨认真假，去找猴医仙确认#B" + g_strNeedBattle);
	AddTriggerObj("侯医仙", "花果山", _next );
	break;

case 30:

	AddTriggerDialog("",
		"#17老猴子，你们大王可是在洞中休息",
		"说话注意点，我可是这方圆十里有名的神医#G（庸医），我们大王是在动力休息，你有事找他？我给你去禀告。#G",
		"不用了，不用了，谢谢了#G（让它知道是我念的紧箍咒，我还有命么）#G#3");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n确认这只猴子是假扮的，找美猴王在花果山78,108那只对话开打 ");
	break;

case 31:
	AddTriggerObj("美猴王", "花果山");
	break;
case 32:
	AddTriggerDialog("死扑街，又是你，看来你是不见棺材不流泪啊！",
		"#17六耳灵猴，明天今天就是你的忌日",
		"#G哟，居然识破我了，了不起，点赞，666，老铁没毛病，转发，送飞机，送轮船。#G",
		"#4妈的，我最讨厌那些傻逼说这些话了，吃我一招降狗十八掌");
	AddJob("#R任务提示#R：\n#B花果山#B\n#R相关人物：#R\n#B美猴王 #B\n#R任务介绍#R\n确认这只猴子是假扮的，找美猴王在花果山78,108那只对话开打 ");
	break;

case 33:
{

	auto pc = AddEnemy(50000, e孙悟空, 120, eMP_大唐官府, "六耳灵猴");
	g_pMainState->SetRanse(10, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->getObj()->say("#G#18#G");
	pc->DmgPercent.d2 += 100;//给怪物的防御和攻击
	pc->Pierce刺穿.d1 += 90;
	pc->DmgPercentOfMagic.d1 += 18;
	pc->DmgPercentOfMagic.d2 += 44;
	pc->Pierce刺穿OfMagic.d1 += 100;
	pc->Pierce刺穿OfMagic.d2 += 126;



	pc = AddEnemy(40000, 87, 120, eMP_普陀山, "猴医仙");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(11, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->LiveHp = 500;//每回合回血
	pc->DmgPercent.d2 += 29;//物理
	pc->Pierce刺穿.d2 += 29;//物理
	pc->DmgPercentOfMagic.d1 += 28;//灵力
	pc->DmgPercentOfMagic.d2 += 24;//灵力
	pc->Pierce刺穿OfMagic.d2 += 99;
	pc->DmgPercentOfFix.d2 -= 32;//怕固伤


	pc = AddEnemy(40000, 87, 160, eMP_化生寺, "老马猴");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(12, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->LiveHp = 5000;//每回合回血
	pc->DmgPercentOfMagic.d1 += 30;//+灵力
	pc->DmgPercent.d2 += 20;//物抗
	pc->Pierce刺穿.d2 += 20;//物抗
	pc->DmgPercentOfMagic.d2 += 29;//法抗
	pc->Pierce刺穿OfMagic.d2 += 29;//法抗
	pc->DmgPercentOfFix.d2 -= 35;//怕固伤




	pc = AddEnemy(30000, e巡游天神, 160, eMP_阴曹地府, "花果山土地");

	pc->SetJinJie(3);
	g_pMainState->SetRanse(13, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->DmgPercent.d2 += 20;
	pc->Pierce刺穿.d2 -= 16;
	pc->Ghost.d1 += 5;
	pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(30);
	pc->applyXL();


	pc = AddEnemy(30000, e巡游天神, 160, eMP_方寸山, "马猴");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(14, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->ParryRateOfMaigc.d1 += 5;
	pc->LiveHp = 50;//每回合回血
	pc->_isWeakSeal = false;
	pc->DmgPercent.d2 += 20;
	pc->Pierce刺穿.d2 -= 20;
	pc->Pierce刺穿OfMagic.d2 -= 70;
	pc->HitRate.d2 += 50;
	pc->Evade.AddDataAddPercent(800);
	pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
	pc->applyXL();

	pc = AddEnemy(40000, e吸血鬼, 160, eMP_大唐官府, "路过的吸血鬼");//数据很好
	pc->SetJinJie(3);
	pc->CriRate.d1 += 20;
	g_pMainState->SetRanse(15, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->LiveHp = 500;//每回合回血
	pc->_isWeakSeal = false;
	pc->DmgPercent.d2 += 10;//给怪物的防御和攻击
	pc->Pierce刺穿.d1 += 10;
	pc->HitRate.d2 += 10;
	pc->Evade.AddDataAddPercent(100);
	pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
	pc->applyXL();


	pc = AddEnemy(30000, e巨力神猿, 120, eMP_大唐官府, "猴先锋");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(16, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->_isWeakSeal = false;
	pc->DmgPercent.d2 += 30;//给怪物的防御和攻击
	pc->Pierce刺穿.d1 += 30;
	pc->HitRate.d2 += 30;
	pc->Evade.AddDataAddPercent(30);
	pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(23);
	pc->applyXL();

	pc = AddEnemy(30000, e雾中仙, 120, eMP_东海龙宫, "猴法师");
	pc->SetJinJie(3);
	pc->DmgAdd.d1 += 50;//每回合回血
	g_pMainState->SetRanse(17, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->Pierce刺穿.d2 -= 29;
	pc->DmgPercent.d2 += 20;
	pc->DmgPercentOfMagic.d2 += 29;
	pc->DmgPercentOfMagic.d1 += 30;
	pc->DmgPercentOfMagic.d2 += 24;
	pc->Pierce刺穿OfMagic.d1 += 10;
	pc->Pierce刺穿OfMagic.d2 += 24;

	pc = AddEnemy(30000, e雨师, 160, eMP_魔王寨, "猴军师");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(18, rand() % 2, rand() % 3, rand() % 4, rand() % 5);
	pc->StabPercent.d1 += 50;//每回合回血

	pc->DmgPercentOfMagic.d2 += 29;
	pc->DmgPercentOfMagic.d1 += 28;
	pc->DmgPercentOfMagic.d2 += 24;
	pc->Pierce刺穿OfMagic.d1 += 20;
	pc->Pierce刺穿OfMagic.d2 += 24;

	pc = AddEnemy(30000, e律法女娲, 160, eMP_凌波城, "猴打手");
	pc->SetJinJie(3);
	g_pMainState->SetRanse(19, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	pc->HitRate.d2 += 60;//每回合回血
	pc->DmgPercent.d2 += 39;
	pc->Pierce刺穿.d1 += 20;
	pc->DmgPercentOfMagic.d2 += 29;
	pc->DmgPercentOfMagic.d2 += 24;//灵力
	pc->Pierce刺穿OfMagic.d2 += 29;
	pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(35);
	pc->applyXL();


	int c = 0;
	for (int i = 10; i < 15; ++i)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			++c;
		}
	}
	if (c >= 3)
	{
		g_pMainState->m_InterfaceTeam.SetFormation(eFormation(1 + rand() % 10), true);
	}
	g_StateType = STATE_FIGHT;

	AddTriggerFightSuccess(34);//跳转蚩尤奖励
}
	return true;

case 34:
	/////////////////////////////////////////////////////////////////////////////
	if (r < 10)//奖励代码段
	{

		if (r < 5)
		{
			g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
			

		}
		else if (r > 5)
		{
			g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
			
		}
		else if (r <2)
		{
			g_pMainState->awardBook(160);//书
			g_pMainState->awardIron(160);//铁
			g_pMainState->awardk(666, 6666);//60W经验，100W钱
		}
	}
	else if (r < 20)
	{
		if (!g_pMainState->awardBookIron(10 * rand() % 6))
		{
		
			g_pMainState->awardShouJue1();
			
			g_pMainState->awardk(600, 1000);//60W经验，100W钱
		}
	}
	else if (r < 30)
	{
		g_pMainState->awardEquip(80);
		g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);
		g_pMainState->awardk(600, 1000);//60W经验，100W钱
	}
	else if (r <90)
	{
		g_pMainState->awardk(600, 1000);//60W经验，100W钱
		g_pHeroObj->say("#15运气太差了");;
	}
	else if (r > 90)
	{
		g_pHeroObj->say("#15今天倒了血霉，啥也没得到");
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	AddTag("完成<真假美猴王>剧情");
//	AddJob("#R任务提示#R：剧情任务到此结束，请耐心等待更新");
	g_pMainState->m_Job.ReMoveJob(this);
	break;
case 35:
	AddTag("完成<真假美猴王>剧情");
	break;


case 36:
	RemoveTriggerObj();
	g_pMainState->m_Job.ReMoveJob(this);

	g_pHeroObj->say("#24下个剧情找 东莞市东城 楷大电子-小草#18启动");
	break;


#if 0
	case 0:
		g_GlobalValues[4] = 50;
		g_GlobalValues[6] = 12;
		g_GlobalValues[5] = 10;
		SetChapter(7);
		g_pMainState->SetDialogListPet(m_Textlist[1], e猪八戒);
		TalkList(0, 6, 3, 7, 3); break;
		break;
	case 3:
		g_pMainState->m_DialogList.clear();
		TalkList(3, 8, 3, 9, next); break;//火焰山土地
	case 4:TalkList(4, 10, 11, 12, next); break;//云里雾
	case 5:AddTriggerDialog2(5, 6); break;//铁扇公主
	case 6:
	{
		g_pMainState->m_Map.LoadMap(21, 46, m_Textlist[13].c_str(), 0);
		g_pHeroObj->Set(POS_DEAD, 0);
		TalkList(6, 14, 15, 16, next);


		AddTriggerObjMap2(35, 15, e观音姐姐, 14, 15, 3, 7);
		AddTriggerObjMap2(33, 15, e空度禅师, 10, 14, 3, 7);
		AddTriggerObjMap2(34, 15, e菩提祖师, 28, 8, 7, 7);
	}
		break;//疥癞和尚
	case 7://镇元大仙
		if (CheckINT(12, 3))
		{
			g_pMainState->SetDialogListPC(m_Textlist[32], 9);
			AddTriggerDialog2(7, -7);
		}
		else
			AddTriggerDialog2(28, -7);
		break;
	case -7://超级泡泡

	{
		g_pMainState->ClearDialogList();
		cPropertyData* pPet;
		pPet = Add变身Enemy2(3000, e镇元大仙, 60, eMP_五庄观);
		pPet->HitRateOfSeal.d1 += 50;
		pPet->HitRateOfSeal.d2 += 50;
		pPet->DmgPercent.d2 += 9990;
		pPet->DmgPercentOfMagic.d2 += 9990;
		pPet->DmgPercentOfArm.d2 += 99;
		pPet->DmgPercentOfFix.d2 += 90;
		pPet->m_XiuLian.Set(30, 30, 30, 30);
		pPet = Add变身Enemy2(3000, e菩提祖师, 60, eMP_方寸山);
		pPet->HitRateOfSeal.d1 += 50;
		pPet->HitRateOfSeal.d2 += 50;
		pPet->DmgPercent.d2 += 9990;
		pPet->DmgPercentOfMagic.d2 += 9990;
		pPet->DmgPercentOfArm.d2 += 99;
		pPet->DmgPercentOfFix.d2 += 90;
		pPet->m_XiuLian.Set(30, 30, 30, 30);
		pPet = Add变身Enemy2(3000, e空度禅师, 60, eMP_化生寺, 33);
		pPet->DmgPercentOfCure.d1 += 50;
		pPet->DmgPercent.d2 += 9990;
		pPet->DmgPercentOfMagic.d2 += 9990;
		pPet->DmgPercentOfArm.d2 += 99;
		pPet->DmgPercentOfFix.d2 += 90;
		pPet->m_XiuLian.Set(30, 30, 30, 30);
		pPet = Add变身Enemy2(3000, e观音姐姐, 60, eMP_普陀山);
		pPet->DmgPercentOfCure.d1 += 50;
		pPet->DmgPercent.d2 += 9990;
		pPet->DmgPercentOfMagic.d2 += 9990;
		pPet->DmgPercentOfArm.d2 += 99;
		pPet->DmgPercentOfFix.d2 += 90;
		pPet->m_XiuLian.Set(30, 30, 30, 30);
		if (CheckINT(12, 3))
		{
			AddPCEnemy2(30000, 9, 0, 120, eMP_五庄观, 32);
		}
		pPet = AddPetEnemy2(8000, e超级泡泡, 100);
		pPet->RelifeRate.d1 = 130;
		pPet = AddPetEnemy2(8000, e超级人参娃娃, 100);
		pPet->RelifeRate.d1 += 90;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e金身罗汉; break;
			case 1:petid = e灵符女娲; break;
			default:petid = e葫芦宝贝; break;
			}
			Add变身Enemy2(8000, petid, 100);
		}
		SetMusic("Lacrimosa");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(-6);
	}
		return true;
	case -6:

	{

		RemoveTriggerObjMap();
		g_pMainState->m_Map.RemoveAllNpc();
		SetJiangLi2(2000000, 500000, 500000, 2000000);

		TalkList(23, 10, 11, 12, 8);
		////////////////////////////////////////////////////////////////////////// 呵呵哒 奖励加成
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
//		g_pCharacter->m_PcData.GetShangPinPet(1);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		// 			g_pCharacter->m_PCData.AddHpZZ(800);
		// 			g_pCharacter->m_PCData.AddAtkZZ(200);
		// 			g_pCharacter->m_PCData.AddAvoidZZ(200);
		//			g_pMainState->LockLv(132);
	}
		return true;

	case 8:AddTriggerDialog2(8, next); break;//铁扇公主
	case 9:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(50000, e地涌夫人, 148, eMP_魔王寨, 10);
		pPet->DmgPercent.d2 += 10;
		ePetID petid;
		for (int i = 0; i < 7; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e红萼仙子; break;
			case 1:petid = e龙龟; break;
			case 2:petid = e修罗傀儡鬼; break;
			default:petid = e修罗傀儡妖; break;
			}
			Add变身Enemy2(20000, petid, 129);
		}
		SetMusic("镜影命缘");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 10:

	{
		SetJiangLi2(2100000, 500000, 500000, 2100000);

		TalkList(9, 6, 3, 7, next);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(135);
	}
		return true;
	case 11:TalkList(10, 17, 18, 19, next); break;//土地公公
	case 12:AddTriggerDialog2(11, next); break;//铁扇公主
	case 13:

	{
		AddTriggerDialog2(29);
		Add变身Enemy2(50000, e超级神牛, 148, eMP_魔王寨, 17);
		AddPCEnemy2(50000, 2005, 0, 148, eMP_魔王寨, 52);
		ePetID petid;
		for (int i = 0; i < 6; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e机关人; break;
			case 1:petid = e炎魔神; break;
			case 2:petid = e踏云兽; break;
			default:petid = e混沌兽; break;
			}
			Add变身Enemy2(20000, petid, 138);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 14:

	{

		SetJiangLi2(2200000, 9999999, 600000, 2200000);

		TalkList(12, 20, 21, 22, next);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(140);
	}
		return true;
	case 15://觉岸

	{
		TalkList(13, 10, 11, 12, next);
		g_pCharacter->UseCard(133);
	}
		break;
	case 16:TalkList(14, 6, 3, 7, next); break;//铁扇公主
	case 17://火焰山土地

	{
		g_pCharacter->UseCard(-1);
		TalkList(15, 10, 11, 12, next);
	}
		break;
	case 18:TalkList(16, 23, 3, 24, next); break;//铁扇公主
	case 19:TalkList(17, 25, 26, 27, next); break;//牛将军
	case 20:
		SetDialogList(25);
		TalkList(18, 17, 18, 19, next); break;//玉面公主
	case 21:AddTriggerDialog2(19, next); break;//牛魔王
	case 22:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(50000, e牛魔王, 159, eMP_魔王寨);
		pPet->MagicFire.d2 += 30;
		pPet = Add变身Enemy2(50000, e狐狸精, 148, eMP_盘丝岭, 25);
		pPet->AddSkill(ePS_法术连击);
		ePetID petid;
		for (int i = 0; i < 6; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e炎魔神; break;
			case 1:petid = e踏云兽; break;
			case 2:petid = e葫芦宝贝; break;
			default:petid = e混沌兽; break;
			}
			Add变身Enemy2(20000, petid, 138);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 23:

	{
		AddTriggerDialog2(20, next);
	}
		break;
	case 24:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(50000, e超级灵狐, 148, eMP_盘丝岭, 25);
		pPet->AddSkill(ePS_高级法术连击);
		pPet = Add变身Enemy2(50000, e九色鹿, 159, eMP_大唐官府);
		pPet->AddSkill(ePS_高级鬼魂术);
		ePetID petid;
		for (int i = 0; i < 8; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e猫灵; break;
			case 1:petid = e狂豹; break;
			case 2:petid = e猫灵人; break;
			default:petid = e狂豹人; break;
			}
			Add变身Enemy2(30000, petid, 138);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 25:

	{
		SetJiangLi2(2500000, 600000, 800000, 2500000);

		TalkList(21, 10, 11, 12, next);
		g_pMainState->ClearDialogList();
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		// 			g_pCharacter->m_PCData.AddMagZZ(150);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		// 			g_pCharacter->m_PCData.AddHpZZ(500);
		g_pMainState->LockLv(145);
	}
		return true;
	case 26:
		g_pMainState->SetDialogListPet(m_Textlist[1], e猪八戒);
		TalkList(22, -1, -1, -1, -1, -26); break;//铁扇公主
	case -26:
		g_pMainState->m_DialogList.clear();
		//Process9(0);
		g_pMainState->m_TaskHuoDong.Start(门派闯关);
		g_pMainState->m_TaskHuoDong.SetTrigger(this, 27, 12);
		return true;
	case 27:
		g_pMainState->LockLv(155);
		TalkList(24, 36, 37, 38, 28, -27);
		return true;
	case -27:

	{
		//			int id;
		Un邀请(m_Textlist[39]);
		Un邀请(m_Textlist[40]);
		// 			id = g_pMainState->m_Friend.FindFriend("燕子");
		// 			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "燕子3";
		// 			id = g_pMainState->m_Friend.FindFriend("傻妞");
		// 			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "傻妞2";
		Invite(m_Textlist[41]);
		Invite(m_Textlist[42]);
	}
		return true;
	case 28:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(80000, e蚩尤, 169, eMP_狮驼岭);
		pPet->SetJinJie(0);
		pPet->LiveRestoreRate += 100;
		pPet->HitRateOfSeal.d2 += 30;
		pPet->ParryRate.d1 += 20;
		pPet->CriRate.d1 += 20;
		pPet->DmgPercent.d1 += 30;
		pPet->SuckBloodPercent.d1 += 30;
		pPet->CounterRate.d1 += 100;
		pPet->StabRate.d1 += 100;
		pPet->StabPercent.d1 += 20;
		pPet->StabRateOfMagic.d1 += 100;
		pPet->StabPercentOfMagic.d1 += 50;
		ePetID petid;
		eMengPai e;
		for (int i = 0; i < 7; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e修罗傀儡鬼; e = eMP_阴曹地府; break;
			case 1:petid = e持国巡守; e = eMP_化生寺; break;
			case 2:petid = e毗舍童子; e = eMP_普陀山; break;
			default:petid = e真陀护法; e = eMP_随机; break;
			}
			Add变身Enemy2(30000, petid, 159, e);
		}
		SetMusic("战斗BOSS");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 29:

	{
		SetJiangLi2(2800000, 800000, 1000000, 2800000);

		TalkList(25, -1, -1, -1, -1, 30);
		// 			g_pCharacter->m_PCData.AddGrowing(5);
		// 			g_pCharacter->m_PCData.AddAtkZZ(200);
		// 			g_pCharacter->m_PCData.AddDefZZ(100);
		// 			g_pCharacter->m_PCData.AddMagZZ(200);
		// 			g_pCharacter->m_PCData.AddHpZZ(1000);
		// 			g_pCharacter->m_PCData.AddSpdZZ(100);
		// 			g_pCharacter->m_PCData.AddAvoidZZ(100);

		//			g_pMainState->LockLv(160);
	}
		return true;
	case 30:

	{
		Un邀请(m_Textlist[41]);
		Un邀请(m_Textlist[42]);
		Un邀请(m_Textlist[43]);
		Un邀请(m_Textlist[44]);
		AddTriggerObjMap2(46, 45, 2000, 17, 13, 3);
		AddTriggerObjMap2(39, 45, 2010, 24, 12, 9);
		AddTriggerObjMap2(47, 45, 2001, 30, 10, 8);
		g_pMainState->m_Map.LoadMap(29, 12, m_Textlist[45].c_str(), 0);
		g_pHeroObj->Set(POS_DEAD, 0);
		TalkList(26, -1, -1, 51, -1, 31);
	}
		return true;
	case 31:

	{
		g_pMainState->m_Map.RemoveAllNpc();
		RemoveTriggerObjMap();
		Invite(m_Textlist[46]);
		Invite(m_Textlist[47]);
		g_pMainState->FindObj();
		AddTriggerObjMap2(49, 50, 2013, 84, 37, 7, 32);
		AddTriggerObjMap2(48, 50, 2008, 79, 41, 3, 32);
	}
		return true;
	case 32:

	{
		TalkList(27, -1, -1, -1, -1, 33);
		RemoveNpc(48);
		RemoveNpc(49, true);
		// 			int id = g_pMainState->m_Friend.FindFriend("清风");
		// 			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "清风2";
		Invite(m_Textlist[48]);
		Invite(m_Textlist[49]);
		g_pMainState->FindObj();
	}
		return true;
	case 33:
		Process9(0);
		return true;
#endif
	default:
		ERRBOX2(stage);
		break;
	}


	return true;
}

