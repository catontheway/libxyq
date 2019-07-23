#include "_global.h"



bool TaskZhuXian::Process6(int stage)
{
	int next = stage + 1;
	setJobTitle("三打白骨精");
	int i = 10;
	int r = rand() % 20;

	static int s_hadG;
	switch (stage)
	{
	case 0:
		AddTriggerDialog("#G嘿，少侠，可等到你来了，有件事想劳烦你走一趟#17#G#103"
			, "嚯~吓死我了,你怎么也加我好友了，我特么成万金油了？", "向师弟那要的，我昨晚做了个梦,梦见高老庄面临大难,而我又肩负取经重任,无法抽身,所以有劳少侠替我去确认一下.#17#4", "今天刚好有空，看在你这么有诚意的份上我就帮你跑一趟吧#1",
			"那太谢谢你！你真是我的好兄弟。");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云游僧 #B\n#R任务介绍#R\n大唐境外（351，29）云游僧似乎每天都在念经敲打不停，去看看吧 ");
		break;
	case 1:
		AddTriggerObj("云游僧");
		break;
	case 2:

		AddTriggerDialog("南无阿尼陀佛，C喱C喱，自雷自雷 自雷自雷 饿类个尔米磊米磊 米磊米磊 米乐喷买单"
			, "大师#24你是在唱歌么",
			"#2少年，看来你是个可造之才，是否有兴趣跟我学习音乐啊。",
			"我才不当秃驴，我是来问你关于高老庄最近发生了啥事。",
			"哦，原来是这样，我只知道有妖怪在横行，你去问高老先生吧，他知道得比较清楚。",
			"好吧，你慢慢唱，我先走了。。。。");
		g_pMainState->m_Mp3.Load("C哩C哩");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B高老先生 #B\n#R任务介绍#R\n在高老庄大厅向高老先生打听情况 ");
		break;

	case 3:
		AddTriggerObj("高老先生", "高老庄大厅");
		break;
	
	case 4:
		AddTriggerDialog("最近高老庄天天丢动物，丢了一半牲口，而且在这庄外也发现了许多野兽的尸体，尸体支离破碎，全身血被吸干，半个月前，我们庄的家丁和佣人也开始失踪了",
			"#3，卧槽！这么可怕！我还是不要管这闲事算了）",
			"站住！#4，作者可发话了，不帮忙你往下的剧情无法做，各种限制#28，跟共产党斗，你还是太嫩！", "#24这作者相当可恶啊！", "必须的，听说水云仙见多识广，你去问问她吧！"
			, "哎，尼玛，现在跑个剧情都要受到各种不公平待遇#65！");
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B水云仙 #B\n#R任务介绍#R\n向水云仙打探消息");
		break;
		
	case 5:
		AddTriggerObj("水云仙", "大唐境外", _next);
		break;
	case 6:

		AddTriggerDialog("#98",
			"#3，这世上怎么会有这样的绝世美女#80",
			"呵呵，你这小伙子嘴巴可真甜。", "嘴巴甜有个毛用，可惜！我还是单身", "哈哈，你会找到心上人的！我知道你想问啥！其实我也不知道，你去狮驼岭问下三大王吧！"
			,"好的，谢谢！");
		AddJob("#R任务提示#R：#B狮驼岭#B\n#R相关人物：#R#B三大王 #B\n#R任务介绍#R\n去狮驼岭问下三大王妖怪吃人的事");
		break;
	case 7:
		AddTriggerObj("三大王", "老雕洞");
		break;
	case 8:
		AddTriggerDialog("哎呀,什么时候能再吃一次唐僧肉啊.吃一次就完全停不下来啊#80"
			, "妖孽,一看就是你吃的高老庄的人,受死#4",
			"#24这尼玛什么情况？");
		break;
	case 9:
	{
	
		auto pc = AddEnemy(30000, e牛妖, 65, eMP_狮驼岭, "三大王");
		pc->getObj()->say("#17吃包零食-<唐憎肉>居然引发一场斗殴#24#2");
		AddEnemy(15000, e牛妖, 60, eMP_随机);
		AddEnemy(15000, e黑熊精, 60, eMP_随机);
		AddEnemy(15000, e雷鸟人, 60, eMP_随机);
		AddEnemy(15000, e蛤蟆精, 60, eMP_随机);
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}
	case 10:
		AddTriggerDialog("大哥，高老庄的血案并非我所为，你找错人了#115",
			"那是谁所为，你都说吃唐憎肉了，还不是你？",
			"你没有童年么？唐憎肉这个零食都不知道，我又不是吃真的唐憎！",
			"说的好有道理，我居然无言以对！那你有啥有价值的消息不！", "盘丝岭的女妖知道的事情很多，值得前去探查一番", "好吧,你的作用就到这里，可以滚了#3",
			"少侠，可否帮我找一条银腰带送给我好友野猪王",
			"#103又一个买东西不给钱，还要包邮的要求，不用问，又是作者安排的了！#B（心里几十万个草泥马跑过。。。)#B#3");
		g_pMainState->awardk(400, 150);
		AddJob("#R任务提示#R：#B大唐境外#B\n#R相关人物：#R#B野猪王 #B\n#R任务介绍#R\n大唐境外（483，7）买一张神兽变身卡（神马）带给野猪王");
		break;
	case 11:
		AddTriggerObj("野猪王", "大唐境外");
		break;
	case 12:
		AddTriggerDialog("没有 神兽变身卡(神马) 我是什么都不会说的");
		break;
	case 13:
		AddTriggerGive("野猪王", 26, 153 , _next);
		//AddTriggerObj("野猪王", "大唐境外");
		break;
	case 14:
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("野猪王");
		AddTriggerDialog("哇，这不是我梦寐以求的神兽变身卡么，哈哈有了它我就可以称霸大唐境外了",
			"#17你就这点出息？废物不多说，我是来问高老庄血案的事情的？",
			"哦，这件事啊！我这几天都是提心吊胆的活着，我亲眼见过那作乱的妖怪——妖怪喜穿一身白衣，走动时带着点点鳞火和一阵腥风",
			"居然这么强大", "具体的情况你找盘丝岭的女妖问问吧！#3");
		g_pMainState->awardEquip(60);
		AddTriggerObj("野猪王");
		g_pMainState->FindObjByName("野猪王")->say("称霸大唐境外指日可待");
		AddJob("#R任务提示#R：\n#B盘丝岭#B\n#R相关人物：#R\n#B女妖 #B\n#R任务介绍#R\n去盘丝岭问女妖一些事情");
		break;
	case 15:
		AddTriggerObj("女妖", "盘丝岭");
		break;
	case 16:
		AddTriggerDialog("#4骂我无聊的人居然还敢来见我？",
			"是罗，我错了行不？我想向你打听一件事？",
			"不知道，滚.",
			"。。。。。。。。#17");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B山贼头子 #B\n#R任务介绍#R\n山贼头子（大唐境外94，90）也在打听吸血的妖怪，可能有些线索。");
	case 17:
		AddTriggerObj("山贼头子", "大唐境外");
		break;
	case 18:
		AddTriggerDialog("#96",
			"怎么了？",
			"我的兄弟竟被妖怪打伤了，危在旦夕。只有九转回魂丹才能为我兄弟续命",
			"我认识的江湖奸商好像有卖。");
		AddJob("#R任务提示#R：\n#B江南野外#B\n#R相关人物：#R\n#B江湖奸商 #B\n#R任务介绍#R\n找江湖奸商要九转还魂单");
		break;

	case 19:
		AddTriggerObj("江湖奸商", "江南野外");
		break;
	case 20:
		AddTriggerDialog("哟，老客户到，有什么需要尽管跟我说？打个九点九八折给你#1",
			"最近比较穷，没啥钱买药了，先赊个九转还魂丹来用用#28",
			"没钱？不好意思，我这里九转还魂丹没货了，下次请早#98",
			"非要我使用武力才肯交出来是吧。");
		break;
		

	case 21:
	{
		auto pc = AddEnemy(30000, e山贼, 65, eMP_随机, "江湖奸商");
		pc->getObj()->say("#17打劫我，少做梦了，小的们上#24#2");
		AddEnemy(15000, e强盗, 60, eMP_随机);
		AddEnemy(15000, e赌徒, 60, eMP_随机);
		AddEnemy(15000, e羊头怪, 60, eMP_随机);
		AddEnemy(15000, e蛤蟆精, 60, eMP_随机);
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}
		
	case 22:
		AddTriggerDialog("求，求你，别打了，我认怂这是九转还魂丹你拿去吧！#1",
			"早知如此，何必当初咧，乖乖交出来不就好了#2",
			"我又不是公益组织的，我是红十字会人员#98",
			"#24");
		g_pMainState->awardItem(22, 45, 1, true);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B山贼头子 #B\n#R任务介绍#R\n得到的九转还魂丹给山贼头子（先点击再给予）");
		break;
	case 23:

		AddTriggerObj("山贼头子", "大唐境外");
		break;
	case 24:
		AddTriggerDialog("少侠，是否找到九转还魂丹了");
		break;

	case 25:

		AddTriggerGive("山贼头子", 22, 45, _next);
		break;

	case 26:
	g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("山贼头子");
	AddTriggerDialog("太感谢你了，我的兄弟有救了。#1",
		"小事一桩，你知道高老庄最近吃人妖怪的事情吗？#2",
			"这个我知道，我亲眼看见过，那妖怪身穿白衣，穿着和你听说的妖怪很象，而且带着一股恶臭，眼神还非常凶恶。#98",
			"好的，我在四处去寻找一下线索。");
		g_pMainState->awardItem(22, 45, 1, true);
		g_pCharacter->m_PcData.AddMoney(100000);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B白衣人 #B\n#R任务介绍#R\n去大唐境外（233，7）探查一下");
	break;
	case 27:
	AddTriggerObj("白衣人", "大唐境外");
		break;
	case 28:
		g_pHeroObj->say("这货身上散发着恶臭！熏死我了，我还是快点走吧#24");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云游僧 #B\n#R任务介绍#R\n去大唐境外（350，30）和云游僧汇合讨论情况");
		AddTriggerObj("云游僧", "大唐境外", _next + 1);
		break;
	case 29:
		AddTriggerObj("云游僧", "大唐境外");
		break;
	case 30:
		AddTriggerDialog("","大师，刚才我碰到一个穿白色衣服浑身散发这恶臭的人，他该不会是妖怪吧？",
			"#G没错，就是他，白衣人身上占满血迹在高老庄附近打探，肯定是他了。", "#G好，我马上去替天行道#4。");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B白衣人 #B\n#R任务介绍#R\n去大唐境外（233，7）打败妖怪-白衣人");
		break;

	case 31:
		AddTriggerObj("白衣人");
		break;
	case 32:
		g_pMainState->FindObjByName("白衣人")->say("#R#这几天没洗澡了，浑身臭熏熏的，难受死了");
		g_pHeroObj->say("受死吧#4吃我一招降狗十八掌#28");
		AddTriggerObj("白衣人", "大唐境外", _next);
		break;
	case 33:
	{
		auto objSelect = g_pMainState->m_pNowSelect;
		if (1)
		{
			auto pc = AddEnemy(30000, 2001, 75, eMP_五庄观, objSelect->m_TrueName.GetString(), nullptr, 160);
			pc->m_XiuLian.AddXiuLianLv(30, eXLATK);
			pc->m_RanSe.m_ranse[0].Set(4, 3, 3, 3); //人物染色
			pc->getObj()->say("#17虽然我长得帅，但是也没帅到被打的程度吧#24");
			g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
		}

		{
		cPropertyData* Pet;
		Pet = AddPCEnemyF(25000, 2001, 0, 70, eMP_大唐官府, "黑衣人", 2, 22);
		Pet->m_XiuLian.AddXiuLianLv(20, eXLATK);
		//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
		g_pMainState->SetRanse(11, 5, 2, 1, 3);
		g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
	}
{
	cPropertyData* Pet;
	Pet = AddPCEnemyF(25000, 2001, 0, 70, eMP_化生寺, "绿衣人", 2, 22);
	Pet->m_XiuLian.AddXiuLianLv(20, eXLATK);
	//Pet->m_RanSe.m_ranse[3].Set(0, 3, 3, 3); //人物染色
	g_pMainState->SetRanse(12, 4, 2, 3, 3);
	g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
}
	{
		auto pc = AddEnemy(20000, 2002, 65, eMP_凌波城, "", nullptr, 160);
		pc->m_XiuLian.AddXiuLianLv(10, eXLATK);
		pc->m_RanSe.m_ranse[0].Set(4, 3, 3, 3); //人物染色
		pc->getObj()->say("#24");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}
	{
		auto pc = AddEnemy(20000, 2003, 65, eMP_狮驼岭, "", nullptr, 160);
		pc->m_XiuLian.AddXiuLianLv(10, eXLATK);
		pc->m_RanSe.m_ranse[0].Set(4, 3, 3, 3); //人物染色
		pc->getObj()->say("#17");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}
		AddTriggerObj("白衣人");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(34);
	}
		break;
	case 34:
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B白衣人 #B\n#R任务介绍#R\n看看白衣人");
		AddTriggerObj("白衣人","大唐境外");
		break;
	case 35:
		
		AddTriggerDialog("啊，要不是受了严重的内伤，我怎么会败给你这黄毛小子#1",
			"妖孽，受死吧！#2",
			"我不是妖孽，我乃五庄观弟子张小陵，奉师尊之令下山降妖伏魔，我身上的臭气是昨日与妖怪打斗时被妖怪用尸气击伤所至。你误伤了我，我命不久矣#98",
			"#24不好意思，我冲动了，有什么办法能治好你？",
			"去五庄观找我师傅镇元大仙求一味红雪散#98我才能好转","好，我马上去给你找来" );
		
		//////////////////////////////////////////////////////////////////////////////
	
		if (r >6)//奖励代码段
		{

			if (r >= 0 && r <1)//10%
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->award5bao();//五宝

			}
			else if (r >= 1 && r<2)//10%
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
				g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石

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
		////////		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AddJob("#R任务提示#R：\n#B五庄观#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n找镇元大仙求一味红雪散");
		break;
	case 36:
		AddTriggerObj("镇元大仙", "乾坤殿");
		break;
	case 37:
		AddTriggerDialog("什么#4你居然伤了吾爱徒？",
			"这其中存在这误会，一时半会说不清楚，现在只有红雪散能救他了#4",
			"这是红雪散，你赶紧拿去给他服下吧！#15.",
			"#32好，马上就去#18",
			"但愿我的弟子能挺过来。.");
		g_pMainState->awardItem(22, 11, 1, true);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B白衣人 #B\n#R任务介绍#R\n拿红雪散给张小陵食用");
		break;
	case 38:
		AddTriggerGive("白衣人", 22, 11, _next);
		break;
	case 39:	
		AddTriggerDialog("你赶回大唐境外（233，7），白衣人竟又被人偷袭过，伤势已经到了无力回天的地步。赶紧让白衣人服下灵药，");
		AddTriggerObj("白衣人", "大唐境外");
		break;
	case 40:	
		
		AddTriggerDialog("你赶回大唐境外（233，7），白衣人竟又被人偷袭过，伤势已经到了无力回天的地步。赶紧让白衣人服下灵药，");
		AddTriggerDialog("高老庄前那个云游僧，其实是妖怪的心腹，他在你回来之前偷袭过我","这秃驴居然隐藏得那么深，把我给骗了#4",
			"那作乱的妖怪本身乃一千年骷髅成精，会诸多变化，或变为少女，或变为老妪，将人骗至无人处吞食。你如果遇到麻烦，可以去五庄观找镇元大仙寻求帮助","");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云游僧 #B\n#R任务介绍#R\n高老庄前那个云游僧，其实是妖怪的心腹，他还偷袭过白衣人");
		break;

	case 41:
		AddTriggerObj("云游僧", "大唐境外");
		break;

	case 42:
		AddTriggerDialog("少侠是否查到什么线索?#4",
			"是的,有线索了，你把耳朵凑过来点,我告诉你#1", "什么啊,搞这么神秘#24");
		
		break;
	case 43:
		{
		auto pc = AddEnemy(30000, e空度禅师, 70, eMP_化生寺, "云游僧");
		pc->getObj()->say("#少侠你这是何意#24");
		AddEnemy(15000, e花妖, 60, eMP_随机);
		AddEnemy(15000, e黑熊精, 60, eMP_随机);
		AddEnemy(15000, e老虎, 60, eMP_随机);
		AddEnemy(15000, e蛤蟆精, 60, eMP_随机);
		g_pMainState->m_FightWorkList[0].m_pObj->say("#G死秃驴，还敢骗我，我已经识破你的诡计了！#G#118");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}


	case 44:
		
		g_pMainState->awardEquip(50);
		AddTriggerObj("云游僧");
		g_pMainState->FindObjByName("云游僧")->say("啊...卧槽...救我...#R主人救救我...呃~");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云游僧 #B\n#R任务介绍#R\n看看云游僧");
		break;

	case 45:
		g_pMainState->awardk(600, 200);
		AddTriggerDialog("啊...卧槽...救我...#R主人救救我...呃~");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云游僧 #B\n#R任务介绍#R\n看看云游僧" + g_strNeedBattle);
		break;
	case 46:
		g_pMainState->FindObjByName("云游僧")->m_ShowTime = 0;
		g_pMainState->m_Map.RemoveNpc("云游僧", true);
		g_pHeroObj->say("接下该是白骨精了#24");
		g_pMainState->m_FightWorkList[0].m_pObj->say("隐隐听到那边有少女的哭泣声,过去看看吧#3");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B少女 #B\n#R任务介绍#R\n你继续在大唐境外寻找妖怪，途中听到少女（大唐境外559，104）在哭泣#3");
		AddTriggerObj("少女");
		break;
	case 47:
		AddTriggerDialog("", "美女,你怎么了?#1", "我不小心摔了一跤,现在无法走路了#15?#1", 
			"没关系,你告诉我你家住哪,我背你回家吧#1", 
			"多谢少侠.我家就在高老庄.#1", 
			"", "我肚子饿了，你想吃东西了！");
		break;
	case 48:
	{
		auto pc = AddEnemy(45000, e花妖, 65, eMP_盘丝岭, "妖精少女");
		pc->getObj()->say("#17我肚子饿了#17，你就当我的点心吧#2");
		AddEnemy(10000, e兔子怪, 60, eMP_随机, "兔子怪喽啰");
		AddEnemy(10000, e树怪, 60, eMP_随机, "树怪喽啰");
		AddEnemy(10000, e兔子怪, 60, eMP_随机, "兔子怪喽啰");
		AddEnemy(10000, e树怪, 60, eMP_随机, "树怪喽啰");
		AddEnemy(10000, e羊头怪, 60, eMP_输出, "羊头怪怪喽啰");
		AddEnemy(10000, e蜘蛛精, 60, eMP_输出, "蜘蛛精怪喽啰");
		AddEnemy(10000, e蜘蛛精, 60, eMP_输出, "蜘蛛精怪喽啰");
		g_pMainState->m_FightWorkList[0].m_pObj->say("#G幸好老子早有准备，不然被你吃了！#G#118");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}
	case 49:

		AddTriggerDialog("打不过你，我跑。。（妖怪化作一股青烟，，消失得无影无踪）");
		g_pMainState->FindObjByName("少女")->m_ShowTime = 0;
		g_pMainState->m_Map.RemoveNpc("少女", true);
		
		//////////////////////////////////////////////////////////////////////////////
		
		if (r >6)//jiutou奖励代码段
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
		////////		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AddJob("#R任务提示#R：\n#B大唐境外536，30#B\n#R相关人物：#R\n#B老太婆、老太爷 #B\n#R任务介绍#R\n在大唐境外一路巡视，遇着老太婆、老太爷，但你无法分辨妖怪");
		break;
	case 50:
		AddTriggerObj("老太婆", "大唐境外", _next);
		break;
	case 51:
		g_pMainState->FindObjByName("老太婆")->say("呵呵！不过那食物的味道实在是太诱人了#52");
		g_pHeroObj->say("这人说话比较可疑，该不会是妖怪变的吧！还是先找镇元大仙问问吧！#28");
		AddJob("#R任务提示#R：\n#B乾坤殿#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n找镇元大仙问问");
		AddTriggerObj("镇元大仙", "乾坤殿", _next + 1);
		break;
	case 52:
		AddTriggerObj("镇元大仙", "乾坤殿");
		break;
	case 53:
		AddTriggerDialog("","道长，你可知道高老庄妖怪的来历","我知道，欲除此妖，需要请李天王帮忙。");
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B李靖 #B\n#R任务介绍#R\n请李靖帮忙降服此妖怪");
		break;
	case 54:
		AddTriggerObj("李靖", "凌宵宝殿");
		break;
	case 55:
		AddTriggerDialog("", "李天王，你可知道高老庄妖怪的来历", "我掐指算出了妖怪的来历，这个照妖镜给你，助你降妖。");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B老太婆 #B\n#R任务介绍#R\n对老太婆使用照妖镜");
		getTag("你得到了照妖镜");
		break;
	case 56:
		AddTriggerObj("老太婆", "大唐境外", _next);
		break;
	case 57:
		AddTriggerDialog("","妖怪现身吧！（你对老太婆使用了照妖镜）", "哎呀，被你识破了，没办法了看我吃了你", "想太多");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B老太婆 #B\n#R任务介绍#R\n对老太婆使用照妖镜");
		break;

	case 58:
	{
		auto pc = AddEnemy(47000, e骷髅怪, 65, eMP_阴曹地府, "白骨精");
		pc->getObj()->say("#17拿命来吧，小子#2");
		AddEnemy(10000, e兔子怪, 60, eMP_随机, "兔子怪喽啰");
		AddEnemy(10000, e树怪, 60, eMP_随机, "树怪喽啰");
		AddEnemy(10000, e羊头怪, 60, eMP_随机, "羊头怪喽啰");
		AddEnemy(10000, e老虎, 60, eMP_随机, "老虎喽啰");
		AddEnemy(10000, e僵尸, 60, eMP_输出, "僵尸喽啰");
		AddEnemy(10000, e野鬼, 60, eMP_输出, "野鬼怪喽啰");
		AddEnemy(10000, e蜘蛛精, 60, eMP_输出, "蜘蛛精怪喽啰");
		g_pMainState->m_FightWorkList[0].m_pObj->say("#G不要白日做梦#G#118");
		g_pMainState->m_FightWorkList[1].m_pObj->say("#G我们也不是吃素的#G#4");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}
		
	case 59:
		AddTriggerDialog("打不过你，但是逃跑我是最在行的，哈哈，有缘再会", "卧槽，又给她逃掉了，早知道给她装个北斗定位系统了，可惜了");
		g_pMainState->m_FightWorkList[1 + rand() % 3].m_pObj->say("#G这货的逃跑技能点满了吧.看来得再找李天王要点宝物了#3#G#77");
		g_pHeroObj->say("附近有个老太爷，该不会又是妖怪变的吧？不管了先照照再说#24");
		/////////////////////////////////////////////////////////////////////////////
		
	
		if (r >6)//奖励代码段
		{

			if (r >= 0 && r <1)//10%
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->award5bao();//五宝

			}
			else if (r >= 1 && r<2)//10%
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
				g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石

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
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B老大爷 #B\n#R任务介绍#R\n对老太爷使用照妖镜");
		break;

	case 60:
		AddTriggerObj("老太爷", "大唐境外");
		break;
	case 61:
		g_pMainState->FindObjByName("老太爷")->say("#R照你妹的照，一拐杖怼死你");
		g_pHeroObj->say("#24居然毫无反应");
		g_pMainState->m_FightWorkList[1+rand()%3].m_pObj->say("#G我想笑#G#77");
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B李靖 #B\n#R任务介绍#R\n照妖镜对老太爷没反应，请李靖帮忙看看");
		AddTriggerObj("李靖", "凌宵宝殿", _next + 1);
		break;
	case 62:
		AddTriggerObj("李靖", "凌宵宝殿");
	case 63:
		AddTriggerDialog("有这种事？看来我照妖镜的技术落后了啊！近期得更新一波才行，不然群友意见很大。", "那我现在怎么办才好，总不能立马就去杀死那老太爷吧？而且他特么穿了滑板鞋，溜得特别快，万一不是妖怪，遇上个碰瓷的，倾家荡产都是有可能的",
			"这样吧！你去我儿那里借个混天绫那妖怪就跑不了，我先改进下照妖镜");
		getTag("失去照妖镜");
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B哪吒 #B\n#R任务介绍#R\n向哪吒借照妖镜");
		break;
	case 64:
		AddTriggerObj("哪吒", "凌宵宝殿");
		break;
	case 65:
		AddTriggerDialog("", "三大爷，能不能借你的狗链子我用一下", "什么狗链子#24", "就你手上的混天绫啊！",
			"。。。。好吧！本来作者是想在这里加个扣钱的选项的，但是想到挺麻烦，没耐心所以就不加了", "感谢作者，感谢上天给了我生活的信心#24");
		getTag("得到改进后的照妖镜");
		getTag("得到混天绫（狗链子）");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B老大爷 #B\n#R任务介绍#R\n对老太爷使用照妖镜");
		break;
	case 66:
		AddTriggerObj("老太爷", "大唐境外");
		break;

	case 67:
		AddTriggerDialog("草泥马，又来照我，还有完没完了，就你那破镜子还想照出我的原型来，搞笑么", "（你用镜子对着老太爷照了照）", "啊！啊！这镜子好耀眼。。我要显出原形了", "哈哈，更新后的镜子果然不错",
			"哇，这镜子出现的美女实在是太漂亮了#", "你是唯一一个连自己都骗都要怪#24");
		break;

	case 68:
	{
		auto pc = AddEnemy(47000, e骷髅怪, 45, eMP_阴曹地府, "白骨精");
		pc->getObj()->say("今天不是你死，就是我亡#2");
		g_pMainState->SetRanse(10, 1, 3, 2);
		AddEnemy(15000, e僵尸, 45, eMP_随机, "僵尸叔叔");
		AddEnemy(15000, e野鬼, 45, eMP_随机, "野鬼妹妹");
		AddEnemy(15000, e牛头, 45, eMP_随机, "牛头哥哥");
		AddEnemy(15000, e马面, 45, eMP_随机, "马面弟弟");
		AddEnemy(10000, e地狱战神, 45, eMP_输出, "地狱战神喽啰");
		AddEnemy(10000, e狐狸精, 45, eMP_输出, "狐狸精喽啰");
		AddEnemy(10000, e蜘蛛精, 45, eMP_输出, "白骨精喽啰");
		g_pMainState->m_FightWorkList[13 + rand() % 5].m_pObj->say("#G开战了#G#18");
		g_pMainState->m_FightWorkList[0].m_pObj->say("#G肯定是你亡啊#G#118");
		g_pMainState->m_FightWorkList[3].m_pObj->say("#G必须是你亡啊#G#4");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
		s_hadG = 0;
		break;
	}
	case 69:
	{
		int idG = -1;
		int num = 0;
		const sFightWork* fw = nullptr;
		for (int i = 10; i < 20; ++i)
		{
			const sFightWork& l = g_pMainState->m_FightWorkList[i];
			if (!l.isExist)
			{
				continue;
			}
			if (num == 0)
			{
				fw = &l;
			}
			if (l.m_pObj->m_TrueName.GetString() == "白骨精分身")
			{
				idG = i;
				break;
			}
			++num;
		}
		if (idG < 0 && num < 2 && fw && !s_hadG)
		{
			int bbmode = g_pMainState->m_Map.m_EnemyList[rand() % g_pMainState->m_Map.m_NumOfEmemyType];
			sPetData* pm = g_pMainState->m_PetDataManager.GetPetData(bbmode);
			auto ppp = AddEnemy(47000, e骷髅怪, 50, eMP_东海龙宫, "白骨精分身");
			g_pMainState->SetRanse(11, 1, 1, 2);
			int cid = ppp->m_IDinFightWorkList;
			g_pMainState->m_pFightState->PrePareToFight(12);
			ppp->FillHpMp();
			cObj* obj = ppp->getObj();
			obj->SetXY(g_pMainState->m_pFightState->m_战斗坐标xs[12], g_pMainState->m_pFightState->m_战斗坐标ys[12]);
			obj->MoveShadow();
			obj->MoveDialog();
			obj->MoveHpLine();
			obj->UpdateHpLine();
			obj->MoveName();
			g_pMainState->FindObj();
			fw->m_pObj->say("分身术");
			s_hadG = 1;

			auto bbb = AddEnemy(47000, e骷髅怪, 50, eMP_东海龙宫, "白骨精分身");
			g_pMainState->SetRanse(12, 3, 1, 2);
			int abc = bbb->m_IDinFightWorkList;
			g_pMainState->m_pFightState->PrePareToFight(abc);
			bbb->FillHpMp();
			obj->SetXY(g_pMainState->m_pFightState->m_战斗坐标ys[abc], g_pMainState->m_pFightState->m_战斗坐标ys[abc]);
			obj->MoveShadow();
			obj->MoveDialog();
			obj->MoveHpLine();
			obj->UpdateHpLine();
			obj->MoveName();
			g_pMainState->FindObj();
			s_hadG = 3;
		}
		else if (idG >= 0 && g_pMainState->m_FightWorkList[idG]._myTurn == 1)
		{
			g_pMainState->m_FightWorkList[idG].m_pObj->say("少年#2难度又增加了哦！");
		}
		
	}
		break;
		
	case 70:
		
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
		AddTriggerDialog("我还会回来的", "你回不来了，我砍草除根", "啊！啊！。。。。。我会记住你的。。做鬼也不会放过你", "#24");
		g_pMainState->m_Map.RemoveNpc("老太爷", true);
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B哪吒 #B\n#R任务介绍#R\n把照妖镜和混天绫还给哪吒");
		break;

	case 71:
		AddTriggerObj("哪吒", "凌宵宝殿");
		break;

	case 72:
		getTag("失去改进后的照妖镜");
		getTag("失去混天绫（狗链子）");
		AddTriggerDialog("", "感谢你的宝物，我将那逃跑大王白骨精一举铲除了", "哈哈，你客气了，以后有啥需要帮忙的尽管找我！");
		AddJob("#R任务提示#R：\n#B高老庄#B\n#R相关人物：#R\n#B高老先生 #B\n#R任务介绍#R\n告诉高老先生妖怪已经消灭");
		break;

	case 73:
		AddTriggerObj("高老先生", "高老庄大厅");
		break;

	case 74:
		AddTriggerDialog("",
			"高老庄吃人妖怪已经被我铲除了，你们可以过太平日子了",
			"太感谢少侠了，我们村准备颁个#R诺贝尔和平奖#R给你，感谢你为村子作的贡献！", "你太客气了，真不难为情啊#39！什么时候颁奖啊？#77", "#27奖杯。。。制作中。。。！"
			, "好吧！做好了给我快递过来，记得用顺丰快递哦！其他快递我拒收的");
		
		break;

	case 75:
		AddTag("完成<三打白骨精剧情>剧情");
		AddJob("#R任务提示#R：剧情任务到此结束，请耐心等待更新");
		g_pMainState->m_Job.ReMoveJob(this);
	
		
	
		break;
	case 76:
		AddTag("完成<三打白骨精剧情>剧情");
		break;


	case 77:
		RemoveTriggerObj();
		g_pMainState->m_Job.ReMoveJob(this);

		g_pHeroObj->say("#24下个剧情找 东莞市东城 楷大电子-小草#18启动");
		break;

//#if 0
//	case 0:
//		g_GlobalValues[5] = 8;
//		SetChapter(6);
//		g_pMainState->SetDialogListPet(m_Textlist[1], e猪八戒);
//		TalkList(0, 2, 3, 4, next); break;//猪八戒
//		break;
//	case 1:
//		g_pMainState->m_DialogList.clear();
//		TalkList(1, 5, 26, 6, next); break;//云游僧
//	case 2:TalkList(2, 9, 10, 11, next); break;//高老先生
//	case 3:AddTriggerDialog2(3, next); break;//三大王
//	case 4:
//
//	{
//		cPropertyData* pPet;
//		pPet = Add变身Enemy2(30000, e超级大鹏, 138, eMP_狮驼岭, 9);
//		pPet = Add变身Enemy2(30000, e超级麒麟, 138, eMP_狮驼岭, 28);
//		pPet = Add变身Enemy2(30000, e超级大象, 138, eMP_狮驼岭, 29);
//		ePetID petid;
//		for (int i = 0; i < 5; i++)
//		{
//			switch (rand() % 2)
//			{
//			case 0:petid = e雷鸟人; break;
//			default:petid = e蝴蝶仙子; break;
//			}
//			Add变身Enemy2(20000, petid, 109);
//		}
//		g_pMainState->m_InterfaceTeam.SetFormation(sky, true);
//		SetMusic("Magia");
//		g_StateType = STATE_FIGHT;
//		AddTriggerFightSuccess(next);
//	}
//		return true;
//	case 5:
//
//	{
//		SetJiangLi2(1500000, 250000, 300000, 1500000);
//
//		TalkList(4, 7, 3, 8, next);
//		g_GlobalValues[14] += 200;
//		g_GlobalValues[15] += 200;
//		// 			g_pCharacter->m_PCData.AddHpZZ(500);
//		// 			g_pCharacter->m_PCData.AddSpdZZ(100);
//		// 			g_pCharacter->m_PCData.AddGrowing(1);
//		//			g_pMainState->LockLv(109);
//	}
//		return true;
//	case 6:TalkList(5, 12, 3, 13, next); break;//野猪王
//	case 7:AddTriggerDialog2(6, next); break;//白衣人
//	case 8:
//
//	{
//		sZiZhi zizhi;
//		zizhi.Set(1400, 1200, 2000, 6000, 1200, 1200, 120);
//		AddPCEnemy2(30000, 1, &zizhi, 129, eMP_方寸山, 12);
//		ePetID petid;
//		for (int i = 0; i < 4; i++)
//		{
//			switch (rand() % 2)
//			{
//			case 0:petid = e牛头; break;
//			default:petid = e马面; break;
//			}
//			Add变身Enemy2(20000, petid, 129);
//		}
//		SetMusic();
//		g_StateType = STATE_FIGHT;
//		AddTriggerFightSuccess(next);
//	}
//		return true;
//	case 9:
//	{
//		SetJiangLi2(1550000, 250000, 350000, 1550000);
//
//		TalkList(7, 14, 15, 16, next);
//		//			g_pCharacter->m_PCData.AddGrowing(1);
//		//			g_pMainState->LockLv(125);
//	}
//		return true;
//	case 10:TalkList(8, 12, 3, 13, next); break;//觉明
//	case 11:TalkList(9, 2, 3, 4, next); break;//白衣人
//	case 12:TalkList(10, 17, 3, 18, next); break;//云游僧
//	case 13:AddTriggerDialog2(11, next); break;//少女
//	case 14:
//	{
//		cPropertyData* pPet;
//		pPet = Add变身Enemy2(30000, e修罗傀儡妖, 129, eMP_盘丝岭, 27);
//		pPet->SuckBloodPercent.d1 += 20;
//		ePetID petid;
//		for (int i = 0; i < 7; i++)
//		{
//			switch (rand() % 4)
//			{
//			case 0:petid = e画魂; break;
//			case 1:petid = e鬼将; break;
//			case 2:petid = e吸血鬼; break;
//			default:petid = e幽灵; break;
//			}
//			eMengPai e = petid == e幽灵 ? eMP_大唐官府 : eMP_随机;
//			pPet = Add变身Enemy2(10000, petid, 129, e);
//			pPet->SuckBloodPercent.d1 += 30;
//		}
//		SetMusic();
//		g_StateType = STATE_FIGHT;
//		AddTriggerFightSuccess(next);
//	}
//		return true;
//	case 15:
//	{
//		SetJiangLi2(1600000, 250000, 400000, 1600000);
//
//		TalkList(12, 19, 20, 21, next);
//		// 			g_pCharacter->m_PCData.AddDefZZ(50);
//		// 			g_pCharacter->m_PCData.AddGrowing(1);
//		//			g_pMainState->LockLv(118);
//	}
//		return true;
//	case 16:TalkList(13, 22, 3, 23, next); break;//李靖
//	case 17:AddTriggerDialog2(14, next); break;//老太婆
//	case 18:
//	{
//		cPropertyData* pPet;
//		pPet = Add变身Enemy2(30000, e孙婆婆, 129, eMP_盘丝岭, 27);
//		pPet->HitRateOfPoison.d1 += 50;
//		pPet->SuckBloodPercent.d1 += 20;
//		ePetID petid;
//		for (int i = 0; i < 7; i++)
//		{
//			switch (rand() % 4)
//			{
//			case 0:petid = e画魂; break;
//			case 1:petid = e鬼将; break;
//			case 2:petid = e吸血鬼; break;
//			default:petid = e幽灵; break;
//			}
//			eMengPai e = petid == e幽灵 ? eMP_大唐官府 : eMP_随机;
//			Add变身Enemy2(20000, petid, 129, e);
//		}
//		SetMusic();
//		g_StateType = STATE_FIGHT;
//		AddTriggerFightSuccess(next);
//	}
//		return true;
//	case 19:
//	{
//		SetJiangLi2(1700000, 250000, 400000, 1700000);
//
//		TalkList(15, 19, 20, 21, next);
//		// 			g_pCharacter->m_PCData.AddDefZZ(100);
//		// 			g_pCharacter->m_PCData.AddGrowing(1);
//		//			g_pMainState->LockLv(125);
//	}
//		return true;
//	case 20:TalkList(16, 24, 3, 25, next); break;//李靖
//	case 21:AddTriggerDialog2(17, next); break;//老太爷
//	case 22:
//	{
//		cPropertyData* pPet;
//		pPet = Add变身Enemy2(30000, e白晶晶, 138, eMP_盘丝岭, 27);
//		pPet->SuckBloodPercent.d1 += 20;
////		pPet->m_AtkDownDef.d1 = 2;
//		ePetID petid;
//		for (int i = 0; i < 9; i++)
//		{
//			switch (rand() % 4)
//			{
//			case 0:petid = e修罗傀儡妖; break;
//			case 1:petid = e炎魔神; break;
//			case 2:petid = e修罗傀儡鬼; break;
//			default:petid = e蝎子精; break;
//			}
//			Add变身Enemy2(30000, petid, 129);
//		}
//		SetMusic();
//		g_StateType = STATE_FIGHT;
//		AddTriggerFightSuccess(next);
//	}
//		return true;
//	case 23:
//	{
//		SetJiangLi2(1800000, 300000, 400000, 1800000);
//
//		TalkList(18, 19, 20, 21, next);
//		// 			g_pCharacter->m_PCData.AddDefZZ(150);
//		// 			g_pCharacter->m_PCData.AddGrowing(1);
//		g_pMainState->LockLv(135);
//	}
//		return true;
//	case 24:TalkList(19, 5, 26, 6, next); break;//李靖
//	case 25:
//		TalkList(20, -1, -1, -1, -1, next);
//		break;
//	case 26:
//		Process7(0);
//		break;//高老先生
//#endif
	default:
		ERRBOX2(stage);
		break;

	}

	
	return true;
}
