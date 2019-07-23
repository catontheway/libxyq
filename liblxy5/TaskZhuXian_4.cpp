#include "_global.h"


bool TaskZhuXian::Process4(int stage)
{
	int r = rand() % 10;
 	int next = stage + 1;
	setJobTitle("寻找四琉璃");
	int i = 10;
	switch (stage)
	{
	case 0:
		AddTriggerDialog("#G孽臣#G#103，#G你打破琉璃盏，犯下大错，搞到老子要在这里陪你受罚#G，#B玉帝命我每七天睡你媳妇、打你儿子，将飞剑穿你胸胁百下，今日，又到虐你之日，看剑！#B#18"
			, "住手！睡人媳妇，打人娃这种事你也干的出来#4，还TM不叫上我#118，该打", "兄弟有话好说好说，这叔打破了琉璃盏，已被相关部门以#R临时工#R的身份清出党的队伍，我劝你少管闲事#2", "我今天非要管管了#53",
		"敬酒不吃，吃罚酒，小的们给我上。");
			
			break;
	case 1:
	{		
		auto p = AddEnemy(35000, e天兵, 50, eMP_物理, "天兵飞剑");
		p->SetJinJie(2);
		g_pMainState->SetRanse(i, 1);//给召唤兽加颜色代码

		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(20000, e天兵, 45, eMP_随机, "看守人员");
		}

		for (int i = 0; i < 5; ++i)
		{
			AddEnemy(10000, e护卫, 45, eMP_输出, "临时工");
			
		}
		
		g_pMainState->m_FightWorkList[15 + rand() % 5].m_pObj->say("#G作为一名临时工，我内心其实是拒绝的#G#17");

		if (g_pMainState->m_InterfaceTeam.getLeaveBegin() == 5)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
		}
		auto pc = AddEnemy(0, e沙和尚, 60, eMP_狮驼岭, "卷帘大将", nullptr, -1, -1, true);
		if (pc)
		{
			pc->PointRemain = cct::PointRemian;
			pc->setPointAfterLv(g_pMainState->getAddpointFromMp(eMP_狮驼岭, true), true);
			pc->autoEquip(false);
			pc->autoData(false, true, true);
			pc->apply();
			pc->m_Controler.Set(0);
			g_pMainState->m_pFightState->m_FightMenu.SetControl(pc->m_IDinFightWorkList, false);

			g_pMainState->setNowSelect(pc->getObj());
		}
		g_pMainState->FindObjByName("天兵飞剑")->say("#R想劫走犯人，得先问问我手中的斧头同不同意#965#R", 0xFFFF);
		g_pMainState->FindObjByName("卷帘大将")->say("#R我河流之王今天非要把你这看门狗打一顿不可#4#R", 0xFFFF);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B卷帘大将 #B\n#R任务介绍#R\n看下卷帘大将的情况 ");
		readyFightAndSucces();
	}
		break;
	case 2:
		g_pMainState->awardEquip(50);
		g_pMainState->awardk(120, 100);//
		AddTriggerObj("卷帘大将");
		break;
	case 3:	 
		AddTriggerDialog("大哥在上,今日承蒙大哥搭救,无以为报....#52",
			"不用谢!得了得了,说那么多废话干嘛，无非是想要我帮你找回其他的琉璃碎片#24",
			"少侠神机妙算，我的想法都让你给知道了",
			"没办法，谁叫跑剧情给钱又给经验，还有意想不到的惊喜呢！");
			AddJob("#R任务提示#R：#B女儿村#B\n#R相关人物：#R#B粟粟娘 #B\n#R任务介绍#R\n她应该知道琉璃碎片的下落");
	case 4:
		g_pMainState->FindObjByName("天兵飞剑")->say("尼玛，整天在这里守着个抠脚大汉难受死了", 0xFFFF);
		g_pMainState->FindObjByName("卷帘大将")->say("#G前面有条狗守着,搞得老子没办法出去泡妞#2#G");
		 AddTriggerObj("栗栗娘", "女儿村");
		break;
	case 5:
		g_pMainState->setNowSelect();
		AddTriggerDialog("女儿村最近有许多女孩失踪了,听说是被盘丝的女妖抓走了#15,少侠能不能帮忙找找#52",
		"可以，没问题，话说事成之后给介绍对象不#2",
		"当然，必须的啊！但是前提得有车子有房子存款上百万！","#24");
		AddJob("#R任务提示#R：\n#G盘丝岭#G\n人物坐标：\n#B女妖#B \n#R任务介绍#R\n去打听是不是女妖捉走了小孩");
		break;
	case 6:
		AddTriggerObj("女妖","盘丝岭");
		break;
	case 7:
		AddTriggerDialog("哟嗬！好久不见哦！还打LOL不，带我，我宫本贼6","听说你干起了贩卖人口的勾当？","我有这么无聊么，去干这种违法的事情","绝对有#71，女人什么的最无聊了");
		break;
	case 8:
	{
		auto pc = AddEnemy(30000, e芙蓉仙子, 60, eMP_盘丝岭, "女妖");
		pc->getObj()->say("#G居然说我无聊，诅咒你单身一辈子#G#99");
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(20000, e兔子怪, 45, eMP_随机);
		}
		g_pMainState->m_FightWorkList[15 + rand() % 5].m_pObj->say("#G保护大姐大，顺便今晚去金琉璃那里吃小孩##G#47");
		g_pHeroObj->say("我凭本事单的身，还怕这种诅咒#24");
		g_StateType = STATE_FIGHT;
		readyFightAndSucces();
	}
		break;
	case 9:
		g_pMainState->awardEquip(60);
		g_pMainState->awardk(130, 120);//
		getTag("琉璃的碎片");
		g_pMainState->FindObjByName("女妖")->say("#65说了不是我，居然怀疑我，友谊的小船说翻就翻");
		AddJob("#R任务提示#R：\n#G盘丝岭#G\n人物坐标：\n#B金琉璃 凉亭里面 #B \n任务介绍：\n应该是塔姐姐金琉璃干的");
		RemoveTriggerObj();
		AddTriggerObj("金琉璃");
		break;

	case 10:
		AddTriggerDialog("没错,小孩确实是我掳走的.我身为妖,吃人.有错吗?这和大鱼吃小鱼一样,你把妖都杀了,你这是破坏食物链,懂吗？",
			"#24，我还没问你呢！你这是恶人先告状么？",
			"我不管，我就要");
		break;
	case 11:
	{
		auto pc = AddEnemy(20000, e如意仙子, 65, eMP_盘丝岭, "金琉璃");
		pc->getObj()->say("#G看我九阳神功把你打飞#G#17"); 
		AddEnemy(18000, e星灵仙子, 60, eMP_随机);
		AddEnemy(18000, e星灵仙子, 60, eMP_随机);
		AddEnemy(18000, e芙蓉仙子, 60, eMP_输出);
		AddEnemy(18000, e芙蓉仙子, 60, eMP_随机);
		AddEnemy(18000, e芙蓉仙子, 60, eMP_随机);
		AddEnemy(18000, e芙蓉仙子, 60, eMP_输出);
		AddEnemy(18000, e芙蓉仙子, 60, eMP_输出);
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#G老大，是九阴真经#G#17");
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#118");
		readyFightAndSucces();
	}
		break;
	
	case 12:
		getTag("金琉璃的碎片");
		g_pMainState->m_Map.RemoveNpc("金琉璃", true);
		g_pMainState->awardEquip(60);
		g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);//阵书
		g_pMainState->awardk(130, 120);//
		g_pMainState->FindObjByName("栗栗儿")->say("#G#1谢谢你，救了我#G");
		AddJob("#R任务提示#R：#B女儿村#B\n#R相关人物：#R#B栗栗娘 #B\n#R任务介绍#R\n她应该知道其他琉璃碎片的下落");
		AddTriggerObj("栗栗娘", "女儿村");
		break;
	case 13:
		AddTriggerDialog("感谢少侠救了我们女儿村的村民，少侠不是要介绍对象么，请问车子、房子、存款准备得怎么样了？我村的如花姑娘说对少侠已经仰慕已久。。",
			"#17，这。。。。这。。。。我有心上人了所以就不用你操心了。。（#95#G其实就是给不起钱#G）？",
			"哦，原来是这样，好吧！前段时间，有个青女侠为了收伏做恶多端的翻天怪,去北俱芦州了,到现在还没回来,希望少侠能帮忙找她.",
			"#R英雄救美#100#R这种事，我是最积极的了，等我好消息吧！");
		break;
	case 14:
		AddTriggerObj("青琉璃", "北俱芦洲");
		AddJob("#R任务提示#R：#B北俱芦洲#B\n#R相关人物：#R#B青琉璃 #B\n#R任务介绍#R\n去北俱芦洲英雄救美");
		break;
	case 15:
		g_pMainState->FindObjByName("青琉璃")->say("#G我的白马王子，你在哪里#37#2#G");
		AddTriggerDialog("我被翻天怪变的白马王子骗财骗色#97，我打不过它，受伤了，谁帮我教训教训他！",
			"靓女，你没事吧！要不要我扶你到宾馆休息一晚，用双修之术为你疗伤#80","#90你个色狼#90，先别管我,翻天怪就要跑了,先制服翻天怪吧，它是个很#R卑鄙、无耻、下流、贱格#R的家伙。",
			"#117，看我现在就去取它狗命，为姑娘你出口恶气。");	
		break;
	case 16:
	
		AddJob("#R任务提示#R：#B北俱芦洲#B\n#R相关人物：#R#B翻天怪 #B\n#R任务介绍#R\n去教训骗财骗色的翻天怪");
		AddTriggerObj("翻天怪", "北俱芦洲", _next + 1);
		break;
	case 17:
		break;
	case 18:	
		AddTriggerDialog("站住！在这里鬼鬼祟祟想干嘛#4，一看就知道不是什么好人#113，是来帮青琉璃找我麻烦的吧！",
			"#24现在的剧情怪都有预知能力了#117",
			"那是自然，得跟紧社会潮流，我们剧情怪也是要进化的嘛！#114", "#111你是要乖乖投降呢!还是让我教教你怎么做人",
			"扯什么犊子！放马过来", "#17好吧！我开始放马了");
		break;
	case 19:
	{
		auto pc = AddEnemy(40000, e地狱战神, 65, eMP_随机, "翻天怪");
		pc->getObj()->say("#G我翻天怪纵横江湖几十年，还没怕过谁#G#17");
		AddEnemy(18000, e黑山老妖, 60, eMP_随机);
		AddEnemy(18000, e黑山老妖, 60, eMP_随机);
		AddEnemy(18000, e黑山老妖, 60, eMP_输出);
		AddEnemy(18000, e黑山老妖, 60, eMP_随机);
		g_pMainState->SetRanse(i, 1);//给召唤兽加颜色代码
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#G出来搞事情了#18#");
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#18");
		readyFightAndSucces();
	}
		break;
	case 20:
		AddTriggerDialog("可恶，居然这样就输了....我不要。。。我不要。。。。",
			"早叫你投降得了，非要犯贱跟我SOLO",
			"我不服，再来一盘",
			"滚，没空跟你玩，看我降狗十八掌");
		g_pMainState->awardEquip(50);
		g_pMainState->awardk(210, 200);//60W经验，100W钱
		AddTriggerObj("翻天怪");
		g_pMainState->FindObjByName("翻天怪")->say("求...求你...别杀我...#R啊。。啊。#R...呃~");
		AddJob("#R任务提示#R：#B北俱芦洲#B\n#R相关人物：#R#B青琉璃 #B\n#R任务介绍#R\n去看看青琉璃的伤势");
		break;
	case 21:
		AddTriggerObj("青琉璃");
		break;
	case 22:
		AddTriggerDialog("我这伤势,看到只能靠燕窝鱼翅加神仙饮来治了",
			"#36，你根本没啥大碍，这是想骗吃骗喝",
			"#28居然被你发现了，你必须得给，不然你别想拿到琉璃碎片",
			"。。。#43。。我要抗议",
			"#51抗议无效");
		AddJob("#R任务提示#R：#B北俱芦洲#B\n#R相关人物：#R#B青琉璃 #B\n#R任务介绍#R\n找神仙饮治疗青琉璃的伤势，好像江湖奸商那里有卖");
		break;
	case 23:
		AddTriggerGive("青琉璃", 22, 52, _next);
		break;
	case 24:
		g_pMainState->awardk(0, 50);
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("青琉璃");
	    AddTriggerDialog("谢谢你，我好多了","#68吃完该上路了","谢谢你,现在我心愿已了,我知道你来找我是为了什么,我跟你走.","找到了两片了,先交给卷帘大将吧！");
	    break;
	case 25:
		getTag("青琉璃的碎片");
		g_pMainState->m_Map.RemoveNpc("青琉璃", true);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：\n#B#卷帘大将 #B\n#R任务介绍#R\n把2片琉璃盏碎片交还给卷帘大将");
		AddTriggerObj("卷帘大将", "大唐境外", _next + 1);
		break;
	case 26:
	
		break;
	case 27:
		AddTriggerDialog("我真是太崇拜你了,办事速度真不是一般的快，再有一片我就能回天庭了#1",
			"#3，那是当然，现在办事没点速度，还怎么在这个地球上生存。",
			"#28剩下的一片就拜托你了",
			"放心吧！我做事绝不忽悠！");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B阿紫 #B\n#R任务介绍#R\n小紫是最后一片琉璃碎片");
		break;
	case 28:
		AddTriggerObj("阿紫", "大唐境外");
		break;
	case 29:
		AddTriggerDialog("我知道你来的目的,你能帮我把这个送给卷帘大将吗？",
			"#3，当然可以，你到底喜欢他哪里#3",
			"喜欢一个人,不需要理由#17",
			"还是做我的单身狗实在！");
		g_pMainState->FindObjByName("阿紫")->say("问世间情为何物，直叫人生死相许。#8~");
		break;
	case 30:
		g_pMainState->awardk(0, 50);
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B卷帘大将 #B\n#R任务介绍#R\n把小紫的情书交给卷帘大将");
		getTag("阿紫的情书");
		AddTriggerObj("卷帘大将", "大唐境外");
		break;
	case 31:
		AddTriggerDialog("#24找到了？",
			"这是阿紫给你的,她的心意你应该懂的吧#3",
			"以我现在的样子,我们还是不要见面为好#74",
			"活该你单身！");
		g_pMainState->FindObjByName("卷帘大将")->say("问世间情为何物#108~");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B阿紫 #B\n#R任务介绍#R\n告诉小紫卷帘大将心如死灰,不过得先打跑姚太尉");
		break;
	case 32:
		AddTriggerObj("姚太尉");
		break;
	case 33:
		AddTriggerDialog("#28阿紫小姐,我们家二郎神#37派我来迎亲.",
			"住手,竟敢强抢民女,我得好好教训教训你#44#3",
			"哪来的单身狗，居然档我的道#4挡我者死#74",
			"看来最近练的吸星大法有地方施展了#18！");
		break;
	case 34:
	{
		auto pc = AddEnemy(40000, e天兵, 65, eMP_天宫, "姚太尉");
		pc->getObj()->say("#G专业抢亲几十年，头一回遇到不怕死的#G#17");
		pc->SetJinJie(2);
		AddEnemy(28000, e天兵, 60, eMP_随机);
		AddEnemy(28000, e天兵, 60, eMP_随机);
		AddEnemy(28000, e天兵, 60, eMP_输出);
		AddEnemy(28000, e天兵, 60, eMP_随机);
		g_pMainState->SetRanse(i, 1);//给召唤兽加颜色代码
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#G专业抢女子#18#");
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#18");
		readyFightAndSucces();
	}
		break;
	case 35:
		g_pMainState->FindObjByName("姚太尉")->say("我主人二郎神叫我来迎亲，乖乖跟我走吧#108~");
		g_pMainState->FindObjByName("阿紫")->say("我不要，我不要，我不要嫁给三眼怪，我不要吃狗粮#15~");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B姚太尉 #B\n#R任务介绍#R\n姚太尉好像有话要说");
		AddTriggerObj("姚太尉", "大唐境外", _next + 1);
		break;
	//case 36:

	//{
	//	int lnum = g_pMainState->GetLiveNum(10, 20);
	//	if (lnum == 1)
	//	{
	//		g_pMainState->m_pFightState->SuccessFight();
	//		break;
	//	}
	//	if (lnum != 2)
	//	{
	//		break;
	//	}

	//	cPcData* lb = g_pMainState->m_FightWorkList[11].m_pObj->getPcData();
	//	cPcData* lh = g_pMainState->m_FightWorkList[10].m_pObj->getPcData();
	//	lh->DmgAdd.d2 -= 1000000;
	//	lb->Hit.AddDataAdd(1000000);

	//	auto& list = g_pMainState->m_FightWorkList[11];
	//	list.m_pObj->ReMoveState(eBuffType封印);
	//	auto& ski = list.m_SkillSelect;

	//	list.m_WorkType = WORKTYPE_ATTACK;
	//	list.targetID = ski.TargetID = 10;
	//	ski.SkillID = 1000;

	//	lb->getObj()->say("哼,没用的废物!");
	//	lh->getObj()->say("老婆大人，我错了!");
	//}
	//	break;
	case 37:
		AddTriggerObj("姚太尉");
		break;
	case 38:
		AddTriggerDialog("我还会回来的！.");
		break;
	case 39:
		g_pMainState->FindObjByName("姚太尉")->say("十八年后又是一条好汉~");	
		g_pMainState->awardEquip(60);
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
				g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
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
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B阿紫 #B\n#R任务介绍#R\n告诉阿紫卷帘的心意");
		g_pMainState->m_Map.RemoveNpc("姚太尉", true);
		AddTriggerObj("阿紫");
		break;
	case 40:
		AddTriggerDialog("少侠，卷帘他怎么说",
			"阿紫,卷帘大将觉的他现在的样貌太丑,配不上你，不愿见你#78",
			"哎,既然如此,我就成全他",
			"活该他单身！#75");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B卷帘大将 #B\n#R任务介绍#R\n去吧碎片交给卷帘大将");
		break;
	case 41:
		getTag("紫琉璃的碎片");
		g_pMainState->m_Map.RemoveNpc("阿紫", true);
		AddTriggerObj("卷帘大将");
		break;
	case 42:
		AddTriggerDialog("太好了,麻烦你把这个琉璃盏交给王母娘娘,她说过,只要我修好了琉璃盏就让我官复原职的#1",
			"你这种人，就不配活在这世上");
		AddJob("#R任务提示#R：#B凌霄宝殿#B\n#R相关人物：#R#B王母娘娘 #B\n#R任务介绍#R\n去把碎片交给王母娘娘");
		break;
	case 43:
		g_pMainState->awardk(0, 50);
		AddTriggerObj("王母娘娘", "凌宵宝殿");
		break;
	case 44:
		AddTriggerObj("王母娘娘", "凌宵宝殿");
		break;
	case 45:
		AddTriggerDialog("来着何人，姓什名谁，家在何方，年龄大小，是否婚配，家中是否有党中央关系户，家境是否富裕，到此所为何事.",
			"#24卧槽，你这是查家宅，还是相亲，还是攀关系#78",
			"#28都有点吧！说吧，找我有啥事，是不是叫我去做广场舞的领队啊！#56",
			"#24脑洞出奇的清新#24这是琉璃盏,希望王母娘娘能恢复卷帘大将的官位",
			"天庭的官位岂是说换就换的, 我不过逗他一下而已, 不必当真#24",
			"什么#4我最讨厌这种说话不算话的人了.",
			"怎么遭，你藐视本女王是吧！来人，给我拿下");

		break;
	case 46:
	{
		auto pc = AddEnemy(100000, e蛟龙, 60, eMP_东海龙宫, "玉皇大帝");
		pc->LiveHp = 100000;
		pc->getObj()->say("#G我草，我怎么加入战斗了#G#24");
		pc = AddEnemy(150000, e凤凰, 60, eMP_阴曹地府, "王母娘娘");
		pc->getObj()->say("#G我拉的，正所谓夫妻同心，其利断金#G#28");
		pc->LiveHp = 100000;
		pc->Speed.AddDataAdd(8000);
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(15000, e天将, 45, eMP_随机);
		}

		for (int i = 0; i < 3; ++i)
		{
			AddEnemy(15000, e天兵, 45, eMP_输出);
		}

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
	}
		break;
	case 47:
	{
		int lnum = g_pMainState->GetLiveNum(10, 20);
		if (lnum == 1)
		{
			g_pMainState->m_pFightState->SuccessFight();
			break;
		}
		if (lnum != 2)
		{
			break;
		}

		cPcData* lb = g_pMainState->m_FightWorkList[11].m_pObj->getPcData();
		cPcData* lh = g_pMainState->m_FightWorkList[10].m_pObj->getPcData();
		lh->DmgAdd.d2 -= 1000000;
		lb->Hit.AddDataAdd(1000000);

		auto& list = g_pMainState->m_FightWorkList[11];
		list.m_pObj->ReMoveState(eBuffType封印);
		auto& ski = list.m_SkillSelect;

		list.m_WorkType = WORKTYPE_ATTACK;
		list.targetID = ski.TargetID = 10;
		ski.SkillID = 1000;

		lb->getObj()->say("哼,没用的废物!");
		lh->getObj()->say("老婆大人，我错了!");
	}
		break;

	case 48:

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
		AddTriggerObj("王母娘娘");
		g_pMainState->FindObjByName("王母娘娘")->say("不跟你们玩了，我跳广场舞去了#36~");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B卷帘大将 #B\n#R任务介绍#R\n告诉卷帘大将真相");
		break;
	case 49:
		AddTriggerObj("卷帘大将", "大唐境外");
		break;
	case 50:
		AddTriggerDialog("事情进展得怎么样了，王母娘娘怎么说？#47",
			"卷帘大将,王母一直都在骗你.#17",
			"好吧,我已看破一切,看来我的使命就是送玄藏去西天取经.");

		break;

	case 51:
		AddTag("完成<四琉璃>剧情");
		g_pMainState->m_Job.ReMoveJob(this);
		g_pMainState->awardEquip(50);//奖励装备语句
		break;
	case 52:
		RemoveTriggerObj();
		g_pMainState->m_Job.ReMoveJob(this);

		g_pHeroObj->say("#24下个剧情找天宫大力神灵启动");
		break;


#if 0
	case 0:
		g_GlobalValues[5] = 6;
		SetChapter(4);
		TalkList(0, 1, 2, 3, 1, 100);
		break;
	case 100:
		Un邀请(m_Textlist[44]);
		break;
	case 1:
		g_pMainState->m_DialogList.clear();
		TalkList(1, 4, 2, 5, 2); break;//猪八戒
	case 2:TalkList(2, 6, 7, 8, 3); break;//土地公公
	case 3:TalkList(3, 9, 10, 11, 4); break;//高翠兰
	case 4:TalkList(4, 6, 7, 8, 5); break;//月老
	case 5:TalkList(5, 1, 2, 3, 6); break;//高翠兰
	case 6:TalkList(6, 4, 2, 5, 7); break;//猪八戒
	case 7:TalkList(7, 12, 13, 14, 8); break;//土地公公
	case 8:TalkList(8, 15, 13, 14, 9); break;//月香侍女
	case 9://康太尉
		AddTriggerDialog2(9, 10);
		break;
	case 10:
	{
		cPropertyData* ppet = Add变身Enemy2(20000, e巡游天神, 79, eMP_天宫, 15);
		ppet->SetJinJie(2);
		ppet = Add变身Enemy2(20000, e天兵, 79, eMP_天宫, 65);
		ppet->SetJinJie(2);
		ppet = Add变身Enemy2(20000, e风伯, 79, eMP_天宫, 66);
		ppet->SetJinJie(2);
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e天将; break;
			case 1:petid = e天兵; break;
			case 2:petid = e雨师; break;
			default:petid = e风伯; break;
			}
			Add变身Enemy2(10000, petid, 69);
		}
		SetMusic();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(11);
	}
		return true;
	case 11:
	{
		SetJiangLi2(900000, 100000, 100000, 900000);

		TalkList(10, 16, 17, 18, 12);
		// 			g_pCharacter->m_PCData.AddAtkZZ(200);
		// 			g_pCharacter->m_PCData.AddGrowing(5);
		//			g_pMainState->LockLv(75);
	}
		return true;
	case 12:TalkList(11, 19, 20, 21, 13); break;//嫦娥
	case 13://杨戟
		AddTriggerDialog2(12, 14);
		break;
	case 14:
	{
		if (g_GlobalValues[0]>50)
			AddTriggerDialog2(38);
		Add变身Enemy2(20000, e二郎神, 89, eMP_大唐官府);
		cPropertyData* pPet = Add变身Enemy2(20000, e啸天犬, 89, eMP_狮驼岭);
		pPet->SuckBloodPercent.d1 += 10;
		pPet->SetJinJie(3);
		ePetID petid;
		for (int i = 0; i < 6; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e巡游天神; break;
			case 1:petid = e天将; break;
			case 2:petid = e雨师; break;
			default:petid = e风伯; break;
			}
			Add变身Enemy2(15000, petid, 69);
		}
		SetMusic("stonecoldFictionJunction");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(15);
	}
		return true;
	case 15:
	{
		SetJiangLi2(1000000, 150000, 150000, 1000000);

		TalkList(13, 22, 23, 24, 16);
		// 			g_pCharacter->m_PCData.AddDefZZ(100);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(80);
	}
		return true;
	case 16:TalkList(14, 16, 17, 18, 115); break;//慧觉
	case 115:
	{

		sTaskMapObj obj;
		obj.m_Npc.Set(m_Textlist[52], m_Textlist[13], e超级神兔, 72, 72);
		obj.m_pTask = this;
		obj.m_Stage = -1;
		AddTriggerObjMap(&obj);
		TalkList(31, 52, 13, 53, 116); break;//嫦娥
	}
		break;
	case 116://超级神兔
	{
		AddTriggerDialog2(39);
		auto p = AddPetEnemy2(66666, e超级玉兔, 66);
		p->MPMax.SetData(6666);
		p->FillHpMp();
		for (int i = 0; i < 6; i++)
		{
			Add变身Enemy2(20000, e超级神兔, 35);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(118);
	}
		return true;
	case 118:

	{
		RemoveTriggerObjMap();
		RemoveTriggerObj();
		RemoveNpc(52, true);
		SetJiangLi2(1080000, 150000, 150000, 1080000);
		AddChannel2(67);
		TalkList(32, 16, 17, 18, 17, -118);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		// 			g_pCharacter->m_PCData.AddAvoidZZ(200);
		// 			g_pCharacter->m_PCData.AddHpZZ(100);
		//			g_pMainState->LockLv(85);

		sShangPinPet sppet;
		sAddPoint addpoint;
		addpoint.Set(0, 0, 4, 1, 0);
		sppet.Set(e超级玉兔, &addpoint, 100, true);
		GetPet(m_Textlist[57], &sppet, 100);
	}
		break;
	case -118:
		AddTriggerDialog2(40);
		break;
	case 17:TalkList(15, 1, 2, 3, 18); break;//嫦娥
	case 18:TalkList(16, 4, 2, 5, 19); break;//天蓬元帅
	case 19:TalkList(17, 25, 26, 27, 20); break;//土地公公
	case 20:TalkList(18, 28, 26, 29, 21); break;//春三十娘
	case 21:TalkList(19, 30, 2, 31, 22); break;//白晶晶
	case 22:TalkList(20, 32, 2, 33, 23); break;//至尊宝
	case 23:TalkList(21, 34, 35, 36, 24); break;//二当家
	case 24:TalkList(22, 37, 38, 39, 25); break;//江湖奸商
	case 25://龙神

	{
		sNpc npc;
		int x, y;
		g_pMainState->m_Map.AutoGetPos(x, y, m_Textlist[41]);
		npc.Set(m_Textlist[40], m_Textlist[41], 123, x, y, 0);
		AddTriggerObjMap(&npc, -1);
		TalkList(23, 40, 41, 42, 26);
	}
		break;
	case 26://超级神龙
		AddTriggerDialog2(24, 27);
		break;
	case 27:

	{
		AddPetEnemy2(30000, e超级神龙, 99/*, eMP_魔王寨*/);
		for (int i = 0; i < 6; i++)
		{
			Add变身Enemy2(8000, e蛟龙, 69);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(28);
	}
		return true;
	case 28:

	{
		SetJiangLi2(1120000, 200000, 200000, 1120000);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		RemoveTriggerObjMap();
		TalkList(25, 37, 38, 39, 29);
		// 			g_pCharacter->m_PCData.AddDefZZ(100);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(95);
	}
		return true;
	case 29: TalkList(26, 59, 60, 58, 133);
		break;//龙神
	case 133://去地府找六道轮回
		g_pMainState->m_Friend.AddFriend(m_Textlist[61]);
		TalkList(33, -1, -1, 64, -1, 134);
		//AddRangeMap(63, 95, 57, 10, 135);
		break;
	case 134:
		Invite(m_Textlist[61]);
		{
			sShangPinPet sppet;
			sAddPoint addpoint;
			addpoint.Set(0, 0, 4, 1, 0);
			sppet.Set(e超级海豚, &addpoint, 100, true);
			GetPet(m_Textlist[61], &sppet, 100);
		}
		AddTriggerObj2(62, 63, 135);
		break;
	case 135://千年怨鬼
		AddTriggerDialog2(34, 136);
		break;
	case 136:

	{
		cPropertyData* Pet = Add变身Enemy2(24000, e幽灵, 89, eMP_阴曹地府, 62);
		Pet->AddSkill(ePS_反震);
		Pet->SetJinJie(3);
		ePetID petid;
		for (int i = 0; i < 9; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e僵尸; break;
			case 1:petid = e鬼将; break;
			case 2:petid = e吸血鬼; break;
			default:petid = e幽灵; break;
			}
			Add变身Enemy2(12000, petid, 79);
		}
		SetMusic("OneLight");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(137);
		//AddTriggerFightEscape(-137);
	}
		return true;
		//case -137:
		//	AddTriggerObj2(62, 63, 135);
		//	return true;
	case 137:

	{
		SetJiangLi2(1200000, 200000, 200000, 1200000);

		RemoveTriggerObjMap();
		TalkList(35, 32, 2, 33, 138);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(95);
	}
		return true;
	case 138:
		AddTriggerDialog2(36, 139);
		UpdateJob2(-1);
		////////////////////////////////////////////////////////////////////////// 呵呵哒 不要副本
		return true;
	case 139:
		g_pMainState->m_TaskFB.Start(3);
		g_pMainState->m_TaskFB.SetTask(this, 140);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.Process(3);
		return true;
	case 140:
		TalkList(37, 30, 2, 31, 30);
		return true;
	case 30: TalkList(27, 28, 26, 29, 31);
		SetJiangLiItem(11, 24);
		break;//至尊宝
	case 31:TalkList(28, 25, 26, 27, 32); break;//白晶晶
	case 32:TalkList(29, 1, 2, 3, 33); break;//春三十娘
	case 33:
		TalkList(30, -1, -1, -1, -1, 34);
		SetJiangLiItem(50, 40);
		g_pMainState->LockLv(105);
		/*	SetChapter(5);
		AddTriggerLv(0, 105);*/
		break;//天蓬元帅
	case 34:
		Process5(0);
		break;
#endif
	default:
		ERRBOX2(stage);
		break;

	}

	return true;
}
