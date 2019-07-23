#include "_global.h"


bool TaskZhuXian::Process8(int stage)
{
	int next = stage + 1;
	setJobTitle("智取芭蕉扇");
	int i = 10;
	int r = rand() % 100;

	static int s_hadG;
	switch (stage)
	{
	case 0:
		AddTriggerDialog("热死个人的这鬼天气", "#G是啊！我都热的头冒大汗，浑身湿透了，你这什么鬼地方啊？这么热#G#103"
			, "现在我都热得喉咙干痒，你去找瓶女儿红来，我慢慢给你细说？",
			"什么个情况啊！现在的剧情人物要求都这么多么，草#17#4");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B张猎户 #B\n#R任务介绍#R\n找女儿红给张猎户解渴，烹饪，可以各地酒店看看 ");
		break;
	case 1:
		AddTriggerGive("张猎户", 23, 4, _next);
		break;
	case 2:

		AddTriggerDialog("你这小子真够意思哈！我就告诉你吧"
			, "废话少说，赶紧的，做完任务我还的去组队开黑呢",
			"四五百年前天上掉下火球，使得这里变成了火焰山，而当地出产的庄稼，都是得铁扇公主帮助降雨才能生长，具体的我也不太清楚，那边有个胖嘟嘟的老爷爷，好像很高深的样子，你不妨去问问#17#4");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B土地公 #B\n#R任务介绍#R\n找火焰山土地公公 ");
		break;
	case 3:
		AddTriggerObj("火焰山土地");
		break;
	case 4:
		AddTriggerDialog(
			"哎哟喂，热热热热热热热热热热热热热热热热热热热热热热热热热热",
			"土地老头，这是怎么回事啊！这地方热死个人的",
			"铁扇公主就是牛魔王的妻子，但要她降雨必须要有足够的贡品，今年的供奉不够，因此铁扇不肯降雨#4",
			"哦，为什么这地方会是这个样子啊。",
			"这里的火乃当年齐天大圣大闹天宫时打翻炼丹炉所掉下，需要一个有缘人去熄灭，而当然的，你就是那个有缘人，要你去问铁扇借芭蕉扇，把火焰山的火熄灭#4",
			"我都成万事通了#2");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云里雾 #B\n#R任务介绍#R\n找一下云里雾 ");
		break;
	case 5:
		AddTriggerObj("云里雾");
		break;
	case 6:
		AddTriggerDialog("我知道你来找我想问什么，但是我是不会白白告诉你的，你得给我找个避水珠来才行，只有这个我才能带你去找她",
			"#G好吧！我都习惯了要送东西了#103"
			, "没办法的哦，敲诈勒索乃是我的看家本领");
		g_pHeroObj->say("#24");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云里雾 #B\n#R任务介绍#R\n找避水珠给云里雾 ");
		break;
	case 7:
		AddTriggerGive("云里雾", 27, 10, _next);
		break;
	case 8:
		g_pMainState->awardk(0, 90);
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("云里雾");
		AddTriggerDialog("铁扇公主到了长寿郊外修炼", "#68哦，知道了那咱们启程吧", "启程？NO,NO ,NO，我才不去那泼妇.随时性命难保啊！", "卧槽！你这是不讲信用啊！就如说好的一起到白头，你却偷偷焗了油");
		break;
	case 9:	
	{

		auto pc = AddEnemy(47000, e兔子怪, 80, eMP_魔王寨, "云里雾");
		pc->getObj()->say("#17老子说不去就不去#24#2");
		AddEnemy(25000, e牛妖, 60, eMP_随机);
		AddEnemy(25000, e黑熊精, 60, eMP_随机);
		AddEnemy(25000, e雷鸟人, 60, eMP_随机);
		AddEnemy(25000, e蛤蟆精, 60, eMP_随机);
		AddEnemy(25000, e花妖, 60, eMP_随机);
		AddEnemy(25000, e蜘蛛精, 60, eMP_随机);
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}
		
	case 10:
		SetJiangLiItem(6 + rand() % 5, 27);
		g_pMainState->awardk(600, 1000);//60W经验，100W钱
		AddTriggerDialog("虽然你打败了我但是我还是不会跟你去的",
			"#G好吧！也就这个了#G");
		AddJob("#R任务提示#R：\n#B长寿郊外#B\n#R相关人物：#R\n#B铁扇公主 #B\n#R任务介绍#R\n去找铁扇公主 ");
		break;
	case 11:
		AddTriggerObj("铁扇公主", "长寿郊外");
		break;
	case 12:
		g_pMainState->m_TriggerDialog.AddSelect(this, "你看我美不美", "铁扇公主", -1, "太美了，天下竟然有如此绝色没人", 13, "太丑了，简直无法直视，长得太对不起观众了", 14);
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B云里雾 #B\n#R任务介绍#R\n找避水珠给云里雾 ");
		break;
	case 13:
		AddTriggerDialogList({ "你这话是捂着良心说的吧！哼！", "#4不是啊", "骗子，看我把你扇到九霄云外", "#4" }, next+2);
		
		AddJob("#R任务提示#R：\n#B化生寺#B\n#R相关人物：#R\n#B疥癞和尚 #B\n#R任务介绍#R\n疥癞和尚有办法帮你灭火 ");
		break;

	case 14:
		AddTriggerDialog(
			"#G你居然敢说我丑，不教训你，你是不知道老娘的厉害#103",
			"还有这种操作？");	
		AddJob("#R任务提示#R：\n#B地藏王府#B\n#R相关人物：#R\n#B地藏王 #B\n#R任务介绍#R\n找地藏王帮忙 ");
		break;
	case 15:
	{
	
		auto pc = AddEnemy(990000, 41, 80, eMP_东海龙宫, "铁扇公主");
		pc->getObj()->say("#17说我丑的一般见不到明天的太阳#2");
		pc->DmgAddOfMagic.d1 += 0x2fff;
		pc->DmgAdd.d1 += 0x2fff;
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		AddTriggerFightFalse(_next);
		break;
		AddTriggerFightEscape(_next);
		g_pHeroObj->Set(POS_DEAD, 0);
		g_pMainState->m_Map.LoadMap(21, 46, "化生寺");
	}
	case 16:
		g_pMainState->m_Map.LoadMap(21, 46, "化生寺");
		AddTriggerObj("疥癞和尚", "化生寺");
		break;
	case 17:
		AddTriggerDialog(
			"施主，你是从何而来，又归何去啊#3",
			".....这是哪里....我怎么跑这里来了",
			"施主，你是不是跟别人打架打坏了脑子？",
			"#24哦，我想起来了，是铁扇公主那个贱人把我扇飞了",
			"哦，知道了，你是第9999个被她扇飞到这里的人了",
			"#24她居然这么厉害？有何解救之法啊？",
			"还别说，还真有的,说到定风的话,五庄观的门派法宝就是这个,你可以找镇元大仙借个定风珠#3#24");
		AddJob("#R任务提示#R：\n#B乾坤殿#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n求个定风珠 ");
		break;
	case 18:
		AddTriggerObj("镇元大仙", "乾坤殿");
	
		break;
	case 19:
	{
		sNpc npc;
		npc.Set("观音姐姐", "乾坤殿", e观音姐姐, 13, 14, DIRECTION_LEFT);
		AddTriggerObjMap(&npc, _next, false);

		npc.Set("法明长老", "乾坤殿", e空度禅师, 17, 16, DIRECTION_RIGHT);
		AddTriggerObjMap(&npc, _next, false);

		npc.Set("菩提祖师", "乾坤殿", e菩提祖师, 20, 17, DIRECTION_RIGHT);
		AddTriggerObjMap(&npc, _next, false);
	}

		break;

	case 20:
		AddTriggerDialog("你是何人，到这里是来拜师学艺的么？",
			"#G我已经有门派和师傅了，这次来这里是求道长给我一颗定风珠，我好去对付铁扇公主#103",
			"你居然想要去打女人，这是我绝不答应#4",
			"我只想问铁扇公主接把扇子灭火而已，但是她不肯，还吧我扇飞了#3",
			"你自己修行不够那没办法的事情啊！",
			"难道你忍心看着黎民百姓遭受苦难么？#24",
			"旁边这几位道友好像有话要说哦");
		AddJob("#R任务提示#R：\n#B乾坤殿#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n求个定风珠 ");
		break;

	case 21:
		g_pMainState->FindObjByName("观音姐姐")->say("虽然我对她没什么仇,但看三位都对她不满,我也来帮下忙吧#18#52");
		g_pMainState->FindObjByName("法明长老")->say("就是这人,两次打伤我的徒弟!#54");
		g_pMainState->FindObjByName("菩提祖师")->say("法明长老,你这还算好的,我徒弟张小陵下山去斩妖除魔,受伤后被她给杀了,事后她居然还恶意骗走觉明的仙药,实在是罪无可恕#78");
		g_pMainState->FindObjByName("镇元大仙")->say(".诸位的意见是很大啊！");
		AddTriggerObj("镇元大仙", "乾坤殿");
		break;
	case 22:
		AddTriggerDialog("你这恶心，看我不教训教训你",
			"#G一群老顽固，真是难搞。。。",
			"还敢出言不逊，看招#4"
			);
		AddJob("#R任务提示#R：\n#B乾坤殿#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n求个定风珠 ");
		break;
	
	case 23:
	{

		auto pc = AddEnemy(70000, e镇元大仙, 90, eMP_五庄观, "老道士");
		pc->getObj()->say("#17恶人，居然口出狂言#24#2");
		auto pc1 = AddEnemy(70000, e观音姐姐, 90, eMP_五庄观, "观音阿姨");
		pc1->getObj()->say("#17我只是路过#2");
		auto pc2 = AddEnemy(70000, e空度禅师, 90, eMP_五庄观, "老秃驴");
		pc2->getObj()->say("#17专治各种狂#2");
		auto pc3 = AddEnemy(70000, e菩提祖师, 90, eMP_五庄观, "菩提大爷");
		pc3->getObj()->say("#17我要为徒弟报仇#2");
		AddEnemy(35000, e老虎, 80, eMP_随机);
		AddEnemy(35000, e花妖, 80, eMP_随机);
		AddEnemy(35000, e蜘蛛精, 80, eMP_随机);
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}

	case 24:
		AddTriggerDialog("罢了罢了，这是定风珠拿去吧",
			"那多谢了",
			"技不如人没办法#4"
			);
		break;
		AddJob("#R任务提示#R：\n#B乾坤殿#B\n#R相关人物：#R\n#B镇元大仙 #B\n#R任务介绍#R\n求个定风珠 ");
		break;
	case 25:
		AddTag("剧情任务到此结束，请耐心等待更新");
		g_pMainState->m_Job.ReMoveJob(this);
		RemoveTriggerObj();
		break;
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
				g_pMainState->awardk(666, 6666.666);//60W经验，100W钱
			}
		}
		else if (r < 20)
		{
			if (!g_pMainState->awardBookIron(10 * rand() % 16))
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
		AddTriggerObj("侯医仙", "花果山", _next);
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
				
			}
		}
		else if (r < 20)
		{
			if (!g_pMainState->awardBookIron(10 * rand() % 16))
			{
				
				g_pMainState->awardShouJue1();
			
				g_pMainState->awardk(600, 1000);//60W经验，100W钱
			}
		}
		else if (r < 30)
		{
			g_pMainState->awardEquip(80);
		
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
		AddJob("#R任务提示#R：剧情任务到此结束，请耐心等待更新");
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

//	switch (stage)
//	{
#if 0
	case 0:

	{
		SetChapter(8);
		g_GlobalValues[5] = 3;
		g_pMainState->SetDialogListPet(m_Textlist[1], e沙和尚);
		TalkList(0, 2, 3, 4, next); break;
	}
		break;
	case 1:
		g_pMainState->m_DialogList.clear();
		TalkList(2, 8, 9, 10, 3); break;//西门将军
	case 3:TalkList(3, 11, 9, 12, next); break;//姜国师
	case 4:AddTriggerDialog2(4, next); break;//美美
	case 5:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(10000, e蚌精, 69, eMP_东海龙宫, 11);
		pPet->MagicWater.d2 += 20;
		for (int i = 0; i < 4; i++)
		{
			pPet = Add变身Enemy2(8000, e蚌精, 60);
			pPet->MagicWater.d2 += 20;
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 6:

	{
		SetJiangLi2(600000, 100000, 50000, 600000);

		sNpc npc;
		npc.Reset();
		npc.Set(m_Textlist[13], m_Textlist[14], 82, 41, 73, 3);
		AddTriggerObjMap(&npc, -1);
		npc.Set(m_Textlist[16], m_Textlist[14], 1074, 32, 75, 3);
		AddTriggerObjMap(&npc, -1, false);
		TalkList(5, 13, 14, 15, next);
		AddTriggerObj2(8, 9, 106, false);
		// 			g_pCharacter->m_PCData.AddDefZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(64);
	}
		return true;
	case 106:
		AddTriggerDialog2(16);
		return true;
	case 7:AddTriggerDialog2(6, next); break;//蝎子精
	case 8:

	{
		Un邀请(m_Textlist[27]);
		cPropertyData* pPet;
		pPet = Add变身Enemy2(20000, e蝎子精, 79, eMP_女儿村);
		pPet->HitRateOfPoison.d1 += 20;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e犀牛将军; break;
			case 1:petid = e犀牛将军人; break;
			case 2:petid = e百足将军; break;
			default:petid = e野猪精; break;
			}
			Add变身Enemy2(10000, petid, 69);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 9:

	{
		RemoveNpc(13, true);
		RemoveTriggerObjMap(7);
		SetJiangLi2(650000, 100000, 50000, 650000);

		sNpc npc;
		npc.Set(m_Textlist[13], m_Textlist[14], 82, 50, 50, 0);
		TalkList(7, 16, 14, 17, next, 109);
		// 			g_pCharacter->m_PCData.AddHpZZ(300);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(75);
	}
		return true;
	case 109:
		Un邀请(m_Textlist[28]);
		Un邀请(m_Textlist[29]);

		break;
	case 10:TalkList(8, 18, 6, 19, next); break;//玄奘
	case 11:
		g_pMainState->SetDialogListNpc(m_Textlist[16], 1074);
		TalkList(9, 20, 21, 22, next);
		RemoveTriggerObjMap();
		break;//西梁女国国王
	case 12:
		g_pMainState->ClearDialogList();
		TalkList(10, 23, 24, 25, next); break;//月老
	case 13:
		Invite(m_Textlist[28]);
		Invite(m_Textlist[29]);
		Invite(m_Textlist[27]);

		TalkList(11, 20, 21, 22, next);
		break;//青莲仙女
	case 14:AddTriggerDialog2(12, next); break;//玄藏幻影
	case 15:

	{
		AddTriggerDialog2(17);
		cPropertyData* pPet;
		pPet = AddPCEnemy2(20000, 1, 0, 79, eMP_化生寺, 26/*, 0, 6*/);;
		pPet->CriRateOfCure.d1 += 20;
		ePetID petid;
		for (int i = 0; i < 9; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e蚌精; break;
			case 1:petid = e鲛人; break;
			case 2:petid = e碧水夜叉; break;
			default:petid = e蛟龙; break;
			}
			Add变身Enemy2(8000, petid, 60);
		}
		SetMusic("白色相簿深爱");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		return true;
	case 16:
	{
		SetJiangLi2(700000, 100000, 50000, 700000);

		TalkList(13, 18, 6, 19, next);
		// 			g_pCharacter->m_PCData.AddSpdZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(66);
	}
		return true;
	case 17:TalkList(14, 20, 21, 22, next); break;//西梁女国国王
	case 18:
		TalkList(15, -1, -1, -1, -1, 19);
		break;//月老
	case 19:
		//		g_pCharacter->m_PCData.AddGrowing(5);
		SetJiangLiItem(16, 24);
		return Process3(0);
#endif
	default:
		ERRBOX2(stage);
		break;
	}


	return true;
}
