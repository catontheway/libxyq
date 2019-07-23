#include "txtSkill.h"

ccc_txt_instance_cpp(txtSkill);


void txtSkill::insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiType type /* = eSkiType::BattleOther */, eBuff buff /* = eBuff::None */, eSkiPos pos /* =  */)
{
	_skill.act = act;
	_skill.state = state;
	_skill.sound = sound;
	_skill.type = type;
	_skill.buff = buff;
	_skill.pos = pos;
	_tables.insert(std::make_pair(skill, _skill));
}

void txtSkill::insert(ulong act, ulong state, ulong sound, eSkill skill, eBuff buff, eSkiPos pos)
{
	insert(act, state, sound, skill, eSkiType::BattleOther, buff, pos);
}

void txtSkill::insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiType type, eSkiPos pos)
{
	insert(act, state, sound, skill, type, eBuff::None, pos);
}

void txtSkill::insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiPos pos)
{
	insert(act, state, sound, skill, eSkiType::BattleOther, eBuff::None, pos);
}

void txtSkill::insert(ulong act, ulong state, ulong sound, eSkill skill, eBuff buff)
{
	insert(act, state, sound, skill, eSkiType::BattleOther, buff);
}


void txtSkill::insertCost(eSkill e, const std::string& descCost)
{
	if (descCost.empty())
	{
		return;
	}
	sCost c;
	if (e >= eSkill::eSpecial0 && e <= eSkill::eSpecialEnd)
	{
		c.ap = std::atoi(descCost.c_str());
		c.desc = descCost + "µã·ßÅ­";
		_costs.insert(std::make_pair(e, c));
		return;
	}
	std::vector<std::string> strs;
	cc::split(descCost, "_", strs);
	if (strs.front() == "ignore")
	{
		c.ignore = true;
		strs.erase(strs.begin());
	}
	int costvalue = std::atoi(strs[1].c_str());
	const std::string& costhpmp = strs.front();

	if (costhpmp == "HpMax")
	{
		c.hpmaxper = costvalue;
		c.desc = toString("%d%%×î´óÆøÑª", costvalue);
		if (e == eSkill::ÓÉ¼º¶ÉÈË)
		{
			c.mp = 50;
			c.desc += "50µãÄ§·¨";
		}
	}
	else if (costhpmp == "HpFix")
	{
		c.hp = costvalue;
		c.desc = toString("%dµãÆøÑª", costvalue);
	}
	else if (costhpmp == "Hp")
	{
		c.hpper = costvalue;
		c.desc = toString("%d%%µ±Ç°ÆøÑª", costvalue);
	}
	else if (costhpmp == "Lv")
	{
		c.lv = costvalue;
		c.mp = std::atoi(strs[2].c_str());
		c.desc = "µÈ¼¶";
		if (costvalue > 1)
		{
			c.desc += toString("/%d", costvalue);
		}
		c.desc += "+" + strs[2] + "µãÄ§·¨";
	}
	else if (costhpmp == "Mps")
	{
		c.desc = toString("%dµãÄ§·¨*Ä¿±êÊý", costvalue);
		c.mps = costvalue;
	}
	else if (costhpmp == "Mp")
	{
		c.desc = toString("%dµãÄ§·¨", costvalue);
		c.mp = costvalue;
	}

	if (e == eSkill::¶ÏÔÀÊÆ || e == eSkill::¾ªÌÎÅ­)
	{
		c.desc += ",1µãÕ½Òâ";
		c.zy = 1;
	}
	else if (e == eSkill::Ìì±ÀµØÁÑ)
	{
		c.desc += ",2µãÕ½Òâ";
		c.zy = 2;
	}
	else if (e == eSkill::·­½­½Áº£)
	{
		c.desc += ",3µãÕ½Òâ";
		c.zy = 3;
	}
	_costs.insert(std::make_pair(e, c));
}


void txtSkill::insertAct(eSkill e, ulong a1, ulong a2 /*= 0*/, ulong a3 /*= 0*/)
{
	_uids.clear();
	_uids.push_back(a1);
	if (a2 > 0)
	{
		_uids.push_back(a2);
	}
	if (a3 > 0)
	{
		_uids.push_back(a3);
	}
	_acts.insert(std::make_pair(e, _uids));
}

void txtSkill::insertHit(eSkill e, ulong a1, ulong a2 /*= 0*/, ulong a3 /*= 0*/)
{
	_uids.clear();
	_uids.push_back(a1);
	if (a2 > 0)
	{
		_uids.push_back(a2);
	}
	if (a3 > 0)
	{
		_uids.push_back(a3);
	}
	_hits.insert(std::make_pair(e, _uids));
}


void txtSkill::insertEffect(eSkill e, eSkiPos pos /*= eSkiPos::Mid*/, bool zTop /*= false*/)
{
	_effect.pos = pos;
	_effect.zTop = zTop;
	_effects.insert(std::make_pair(e, _effect));
}

void txtSkill::insertEffect(eSkill e, bool zTop)
{
	insertEffect(e, eSkiPos::Mid, zTop);
}



void txtSkill::initFushi()
{
	//////////////////////////////////////////////////////////////////////////
	_fushis.push_back(eSkill::½ð¸Õ»¤·¨);
	_fushis.push_back(eSkill::ÄæÁÛ);
	_fushis.push_back(eSkill::Á¶Æø»¯Éñ);
	_fushis.push_back(eSkill::ÆÕ¶ÉÖÚÉú);
	_fushis.push_back(eSkill::ÓÄÚ¤¹íÑÛ);
	_fushis.push_back(eSkill::ÐÞÂÞÒþÉí);
	_fushis.push_back(eSkill::Ä§Íõ»ØÊ×);
	_fushis.push_back(eSkill::¶¨ÐÄÊõ);
	_fushis.push_back(eSkill::ÅÌË¿Õó);
	_fushis.push_back(eSkill::ËéÐÇ¾÷);
	_fushis.push_back(eSkill::Ã÷¹â±¦Öò);

	//////////////////////////////////////////////////////////////////////////
	_zhuijias.push_back(eSkill::ºáÉ¨Ç§¾ü);
	_zhuijias.push_back(eSkill::ÂäÀ×·û);
	_zhuijias.push_back(eSkill::ßóßóÍáÍá);
	_zhuijias.push_back(eSkill::ÂúÌì»¨Óê);
	_zhuijias.push_back(eSkill::ÁúÌÚ);
	_zhuijias.push_back(eSkill::Áú¾íÓê»÷);
	_zhuijias.push_back(eSkill::ÁúÒ÷);

	_zhuijias.push_back(eSkill::½ô¹¿Öä);
	_zhuijias.push_back(eSkill::ÈÕ¹â»ª);
	_zhuijias.push_back(eSkill::µå²×º£);
	_zhuijias.push_back(eSkill::¾ÞÑÒÆÆ);
	_zhuijias.push_back(eSkill::²ÔÃ£Ê÷);
	_zhuijias.push_back(eSkill::µØÁÑ»ð);

	_zhuijias.push_back(eSkill::ÑÖÂÞÁî);
	_zhuijias.push_back(eSkill::ÅÐ¹ÙÁî);
	_zhuijias.push_back(eSkill::Ê¬¸¯¶¾);

	_zhuijias.push_back(eSkill::·ÉÉ°×ßÊ¯);
	_zhuijias.push_back(eSkill::ÈýÃÁÕæ»ð);
	_zhuijias.push_back(eSkill::ÎÞµÐÅ£Ê­);

	_zhuijias.push_back(eSkill::¹´»ê);
	_zhuijias.push_back(eSkill::ÉãÆÇ);

	_zhuijias.push_back(eSkill::ÀËÓ¿);

	_zhuijias.push_back(eSkill::¶áÃüÖä);

	_zhuijias.push_back(eSkill::ÂäÒ¶ÏôÏô);
	_zhuijias.push_back(eSkill::¾£¼¬Îè);
	_zhuijias.push_back(eSkill::³¾ÍÁÈÐ);
	_zhuijias.push_back(eSkill::±ù´¨Å­);


	_zhuijias.push_back(eSkill::À×»÷);
	_zhuijias.push_back(eSkill::±¼À×Öä);
	_zhuijias.push_back(eSkill::ÂäÑÒ);
	_zhuijias.push_back(eSkill::Ì©É½Ñ¹¶¥);
	_zhuijias.push_back(eSkill::Ë®¹¥);
	_zhuijias.push_back(eSkill::Ë®Âþ½ðÉ½);
	_zhuijias.push_back(eSkill::ÁÒ»ð);
	_zhuijias.push_back(eSkill::µØÓüÁÒ»ð);
	_zhuijias.push_back(eSkill::¾ªÐÄÒ»½£);
	_zhuijias.push_back(eSkill::Ò¹ÎèÇã³Ç);
	_zhuijias.push_back(eSkill::ËÀÍöÕÙ»½);
	_zhuijias.push_back(eSkill::Á¦Åü»ªÉ½);
	_zhuijias.push_back(eSkill::ÉÆ¶ñÓÐ±¨);
	_zhuijias.push_back(eSkill::±ÚÀÝ»÷ÆÆ);

	_zhuijias.push_back(eSkill::Ìì½µÁéºù);
	_zhuijias.push_back(eSkill::ÔÂ¹â);

	_zhuijias.push_back(eSkill::½£µ´ËÄ·½);
}



void txtSkill::initActs()
{
	insertAct(eSkill::À×»÷, 0x3200B6CC);
	insertAct(eSkill::±¼À×Öä, 0x3200B6CC, 0x279AF873);
	insertAct(eSkill::ÂäÑÒ, 0xFDF34F35, 0x05391F73);
	insertAct(eSkill::Ì©É½Ñ¹¶¥, 0x4E86F9B3);
	insertAct(eSkill::Ë®¹¥, 0xCE33E201);
//	insertAct(eSkill::Ë®Âþ½ðÉ½, 0x4CE1ACB6);	// 0x439692DE, 0xC9BCA454, 0x60EB2F76, 
	insertAct(eSkill::ÁÒ»ð, 0x22A3D764);
	insertAct(eSkill::µØÓüÁÒ»ð, 0xDED2253F);

	insertAct(eSkill::Ò¹ÎèÇã³Ç, 0x68E51BB6);

//  {eSkill::ºáÉ¨Ç§¾ü}
	insertAct(eSkill::ºó·¢ÖÆÈË, 0x1EDD5D74, 0xBED8962A, 0x22DFD2EA);	// A5C6BDFB

};



void txtSkill::initEffect()
{
//	insertEffect(eSkill::¾ªÐÄÒ»½£:
	insertEffect(eSkill::Ò¹ÎèÇã³Ç, eSkiPos::Top, true);
	insertEffect(eSkill::ËÀÍöÕÙ»½, eSkiPos::Bottom);
//	insertEffect(eSkill::Á¦Åü»ªÉ½:
	insertEffect(eSkill::·¨Êõ·ÀÓù, true);
	insertEffect(eSkill::ÎÞÎ·²¼Ê©, true);
	insertEffect(eSkill::ÎÞÎ·²¼Ê©2, eSkiPos::Top, true);

//	insertEffect(eSkill::¾ø»ÃÄ§Òô:
	insertEffect(eSkill::Ì«¼«»¤·¨, eSkiPos::Bottom);
	insertEffect(eSkill::ÂÞºº½ðÖÓ, eSkiPos::Bottom);
//	insertEffect(eSkill::ÐÞÂÞÖä:
	insertEffect(eSkill::ÌìÒÂÎÞ·ì, eSkiPos::Top, true);
	insertEffect(eSkill::ÐÄÈçÃ÷¾µ, eSkiPos::Top, true);


	insertEffect(eSkill::ºáÉ¨Ç§¾ü, eSkiPos::Bottom, true);
	insertEffect(eSkill::ºó·¢ÖÆÈË, eSkiPos::Bottom);
	insertEffect(eSkill::É±Æø¾÷, eSkiPos::Bottom);
//	insertEffect(eSkill::·´¼äÖ®¼Æ:
	insertEffect(eSkill::ÆÆ¸ª³ÁÖÛ, eSkiPos::Bottom, true);
	insertEffect(eSkill::°²Éñ¾÷, eSkiPos::Top, true);

	insertEffect(eSkill::´ßÃß·û, eSkiPos::Bottom);
	insertEffect(eSkill::Ê§ÐÄ·û, eSkiPos::Bottom);
	insertEffect(eSkill::ÂäÆÇ·û, eSkiPos::Bottom);
	insertEffect(eSkill::Ê§Òä·û, eSkiPos::Bottom);
	insertEffect(eSkill::×·»ê·û, eSkiPos::Bottom);
	insertEffect(eSkill::Àë»ê·û, eSkiPos::Bottom);
	insertEffect(eSkill::Ê§»ê·û, eSkiPos::Bottom);
	insertEffect(eSkill::¶¨Éí·û, eSkiPos::Bottom);
//	insertEffect(eSkill::ÄýÉñÊõ:
//	insertEffect(eSkill::·ÖÉíÊõ:
	insertEffect(eSkill::Ëé¼×·û, eSkiPos::Top, true);
//	insertEffect(eSkill::ÂäÀ×·û:

//	insertEffect(eSkill::´ïÄ¦»¤Ìå:
	insertEffect(eSkill::½ð¸Õ»¤·¨, eSkiPos::Bottom);
	insertEffect(eSkill::Î¤ÍÓ»¤·¨, eSkiPos::Bottom);
	insertEffect(eSkill::½ð¸Õ»¤Ìå, true);
	insertEffect(eSkill::½ð¸Õ»¤Ìå1, eSkiPos::Bottom);
	insertEffect(eSkill::½ð¸Õ»¤Ìå2, eSkiPos::Bottom, true);
	insertEffect(eSkill::Ò»Î­¶É½­, true);
	insertEffect(eSkill::·ð·¨ÎÞ±ß, eSkiPos::Bottom, true);

//	insertEffect(eSkill::Äé»¨ÃîÖ¸:
//	insertEffect(eSkill::ºìÐäÌíÏã:
	insertEffect(eSkill::³þ³þ¿ÉÁ¯, eSkiPos::Bottom, true);
	insertEffect(eSkill::ÂúÌì»¨Óê, eSkiPos::Bottom, true);
//	insertEffect(eSkill::ÇéÌìºÞº£:
	insertEffect(eSkill::Á«²½ÇáÎè, eSkiPos::Bottom);
	insertEffect(eSkill::Èç»¨½âÓï, eSkiPos::Bottom);
	insertEffect(eSkill::ËÆÓñÉúÏã, eSkiPos::Bottom);
// 	insertEffect(eSkill::æ³æÃ‹ØÄÈ:
// 	insertEffect(eSkill::ÇáÈçºèÃ«:
// 	insertEffect(eSkill::°Ù¶¾²»ÇÖ:
// 	insertEffect(eSkill::ÒÆÐÎ»»Ó°:
	insertEffect(eSkill::Ò»Ð¦Çã³Ç, eSkiPos::Bottom);
// 	insertEffect(eSkill::·É»¨ÕªÒ¶:
// 	insertEffect(eSkill::ÓêÂäº®É³:

	insertEffect(eSkill::ÌìÉñ»¤Ìå, eSkiPos::Top, true);
// 	insertEffect(eSkill::ÌìÉñ»¤·¨:
// 	insertEffect(eSkill::ÌìÖïµØÃð:
// 	insertEffect(eSkill::Öª¼ºÖª±Ë:
// 	insertEffect(eSkill::ÄþÐÄ:
	insertEffect(eSkill::ÕòÑý, eSkiPos::Bottom);
	insertEffect(eSkill::´íÂÒ, eSkiPos::Bottom, true);
	insertEffect(eSkill::°ÙÍòÉñ±ø, eSkiPos::Bottom);
//	insertEffect(eSkill::½ð¸Õïí:
// 	insertEffect(eSkill::À×öªÍò¾û:
// 	insertEffect(eSkill::ºÆÈ»ÕýÆø:
// 	insertEffect(eSkill::ÕÆÐÄÀ×:

	insertEffect(eSkill::ÄæÁÛ, eSkiPos::Bottom);
// 	insertEffect(eSkill::³Ë·çÆÆÀË:
// 	insertEffect(eSkill::ÁúÐ¥¾ÅÌì:
	insertEffect(eSkill::ÉñÁú°ÚÎ², eSkiPos::Bottom, true);

	insertEffect(eSkill::ÈÕÔÂÇ¬À¤, eSkiPos::Bottom, true);
	insertEffect(eSkill::Á¶Æø»¯Éñ, eSkiPos::Top, true);
	insertEffect(eSkill::ÉúÃüÖ®Èª, eSkiPos::Top, true);
//	insertEffect(eSkill::ÇýÄ§:
//	insertEffect(eSkill::ÌìµØÍ¬ÊÙ:
//	insertEffect(eSkill::Ç¬À¤Ãî·¨:
//	insertEffect(eSkill::Ò»Æø»¯ÈýÇå:

	insertEffect(eSkill::ÆÕ¶ÉÖÚÉú, eSkiPos::Top, true);
	insertEffect(eSkill::½ô¹¿Öä, eSkiPos::Top, true);
	insertEffect(eSkill::ÑîÁø¸ÊÂ¶, eSkiPos::Top, true);
// 	insertEffect(eSkill::ÈÕ¹â»ª:
// 	insertEffect(eSkill::µå²×º£:
// 	insertEffect(eSkill::¾ÞÑÒÆÆ:
// 	insertEffect(eSkill::²ÔÃ£Ê÷:
// 	insertEffect(eSkill::µØÁÑ»ð:
//	insertEffect(eSkill::ÎåÐÐ´íÎ»:
	insertEffect(eSkill::Áé¶¯¾ÅÌì, eSkiPos::Top, true);
	insertEffect(eSkill::µßµ¹ÎåÐÐ, eSkiPos::Bottom);
//	insertEffect(eSkill::Á«»ªÃî·¨:

//	insertEffect(eSkill::¹ÑÓûÁî:
	insertEffect(eSkill::ÓÄÚ¤¹íÑÛ, true);
//	insertEffect(eSkill::Ô©»ê²»É¢:
	insertEffect(eSkill::Ê¬¸¯¶¾, eSkiPos::Bottom, true);
//	insertEffect(eSkill::ÐÞÂÞÒþÉí:
//	insertEffect(eSkill::»¹ÑôÊõ:
	insertEffect(eSkill::»ÆÈªÖ®Ï¢, eSkiPos::Bottom, true);
//	insertEffect(eSkill::»ê·ÉÆÇÉ¢:
	insertEffect(eSkill::ïÀ»êÊõ, true);

	insertEffect(eSkill::Å£¾¢, true);
//	insertEffect(eSkill::Ì¤É½ÁÑÊ¯:
	insertEffect(eSkill::Ä§Íõ»ØÊ×, true);
//	insertEffect(eSkill::»ð¼×Êõ:
//	insertEffect(eSkill::Ò¡Í·°ÚÎ²:

	insertEffect(eSkill::ÏóÐÎ, eSkiPos::Bottom);
	insertEffect(eSkill::Ó¥»÷, eSkiPos::Bottom, true);
	insertEffect(eSkill::ÍþÉå, eSkiPos::Bottom, true);
	insertEffect(eSkill::±äÉí, true);
//	insertEffect(eSkill::Ä§ÊÞÐ¥Ìì:
	insertEffect(eSkill::¶¨ÐÄÊõ, true);
	insertEffect(eSkill::¼«¶È·è¿ñ, true);
//	insertEffect(eSkill::ÌìÄ§½âÌå:

	insertEffect(eSkill::Ä§ÒôÉã»ê, eSkiPos::Bottom);
// 	insertEffect(eSkill::ÅÌË¿Îè:
// 	insertEffect(eSkill::¶áÃüÖëË¿:
	insertEffect(eSkill::º¬ÇéÂöÂö, eSkiPos::Bottom);
	insertEffect(eSkill::ÅÌË¿Õó, true);
//	insertEffect(eSkill::¸´ËÕ:
	insertEffect(eSkill::ÌìÂÞµØÍø, eSkiPos::Bottom);
// 	insertEffect(eSkill::½ãÃÃÍ¬ÐÄ:
// 	insertEffect(eSkill::ÕÎÆø:
	insertEffect(eSkill::»Ã¾µÊõ, true);

// 	insertEffect(eSkill::ÁÑÊ¯:
// 	insertEffect(eSkill::¶ÏÔÀÊÆ:
// 	insertEffect(eSkill::Ìì±ÀµØÁÑ:
// 	insertEffect(eSkill::ÀËÓ¿:
// 	insertEffect(eSkill::¾ªÌÎÅ­:
// 	insertEffect(eSkill::·­½­½Áº£:
// 	insertEffect(eSkill::ÌÚÀ×:
// 	insertEffect(eSkill::Ö¸µØ³É¸Ö:
// 	insertEffect(eSkill::²»¶¯ÈçÉ½:
	insertEffect(eSkill::Õ½Òâ1, eSkiPos::Top, true);
	insertEffect(eSkill::ËéÐÇ¾÷, eSkiPos::Top, true);
	insertEffect(eSkill::Õò»ê¾÷, eSkiPos::Top, true);
// 	insertEffect(eSkill::´©ÔÆÆÆ¿Õ:
// 	insertEffect(eSkill::ÎÞÇîÃîµÀ:
// 	insertEffect(eSkill::×ÝµØ½ð¹â:

	insertEffect(eSkill::ÒÆ»ê»¯¹Ç, eSkiPos::Top, true);
	insertEffect(eSkill::¶áÆÇÁî, eSkiPos::Bottom);
// 	insertEffect(eSkill::É·Æø¾÷:
// 	insertEffect(eSkill::¾ª»êÕÆ:
	insertEffect(eSkill::´ÝÐÄÊõ, eSkiPos::Bottom, true);
	insertEffect(eSkill::Ã÷¹â±¦Öò, eSkiPos::Top, true);
	insertEffect(eSkill::½ðÉíÉáÀû, true);
//	insertEffect(eSkill::ÍòÄ¾µò¿Ý:
//	insertEffect(eSkill::ÔªÑô»¤Ìå:
//	insertEffect(eSkill::ÓÉ¼º¶ÉÈË:

// 	insertEffect(eSkill::¾£¼¬Îè:
// 	insertEffect(eSkill::³¾ÍÁÈÐ:
// 	insertEffect(eSkill::±ù´¨Å­:
	insertEffect(eSkill::ÎíÉ±, eSkiPos::Top, true);
	insertEffect(eSkill::ÑªÓê, eSkiPos::Bottom);
	insertEffect(eSkill::Ñ×»¤, eSkiPos::Top, true);
//	insertEffect(eSkill::ÉñÄ¾ß½Óï:
	insertEffect(eSkill::ÃÜÈó, eSkiPos::Top, true);
//	insertEffect(eSkill::ò÷ÒÏÊ´Ìì:
}



bool txtSkill::isEd(eSkill e)
{
	return e >= eSkill::eSkied0 && e <= eSkill::eSkiedEnd;
}

bool txtSkill::isMenpai(eSkill e)
{
	return e >= eSkill::eMain0 && e <= eSkill::eMainEnd;
}

bool txtSkill::isF1(eSkill e)
{
	switch (e)
	{
	case eSkill::Ç§ÀïÉñÐÐ:
	case eSkill::ÒÒÄ¾ÏÉ¶Ý:
	case eSkill::·ðÃÅÆÕ¶É:
	case eSkill::ÒÆÐÎ»»Ó°:
	case eSkill::ÌÚÔÆ¼ÝÎí:
	case eSkill::Ë®¶Ý:
	case eSkill::¶·×ªÐÇÒÆ:
	case eSkill::×øÁ«:
	case eSkill::èÃÎÞÒôÑ¶:
	case eSkill::Å£Êº¶Ý:
	case eSkill::Õñ³áÇ§Àï:
	case eSkill::Ìì²ÏË¿:
	case eSkill::×ÝµØ½ð¹â:
	case eSkill::¶ÝµØÊõ:
	case eSkill::Ò¶Òþ:
		return true;
	}
	return false;
}

bool txtSkill::isPet(eSkill e)
{
	return e >= eSkill::ePetSki0 && e <= eSkill::ePetSkiEnd;
}

bool txtSkill::isSpecial(eSkill e)
{
	return e >= eSkill::eSpecial0 && e <= eSkill::eSpecialEnd;
}



int txtSkill::getTargetsCount(eSkill e)
{
	switch (e)
	{
	case eSkill::ÆÆÑª¿ñ¹¥:
		return 2;
	case eSkill::±¼À×Öä:
	case eSkill::Ì©É½Ñ¹¶¥:
	case eSkill::Ë®Âþ½ðÉ½:
	case eSkill::µØÓüÁÒ»ð:
	case eSkill::½£µ´ËÄ·½:
		return 3;
	case eSkill::ÔÂ¹â:
		return 4;
	case eSkill::Ìì½µÁéºù:
		return 5;
	case eSkill::ÎüÐÇ´ó·¨:
		return 9;
	case eSkill::ËÄº£ÉýÆ½:
	case eSkill::ÓñÇå¾÷:
	case eSkill::¾§Çå¾÷:
	case eSkill::¾ø»ÃÄ§Òô:
	case eSkill::Ä§ÊÞÖ®Ó¡:
	case eSkill::Ê¥ÁéÖ®¼×:
	case eSkill::Ð¥·ç¾÷:
	case eSkill::ÂÞºº½ðÖÓ:
	case eSkill::ºÓ¶«Ê¨ºð:
	case eSkill::Ëé¼×Êõ:
	case eSkill::Í£ÏÝÊõ:
	case eSkill::´Èº½ÆÕ¶É:
		return 10;
	}
	return 1;
}


bool txtSkill::isTargetAtked(eSkill e)
{
	switch (e)
	{
	case eSkill::ºáÉ¨Ç§¾ü:
	case eSkill::ºó·¢ÖÆÈË:
	case eSkill::ÆÆ¸ª³ÁÖÛ:
	case eSkill::ÆÆ¸ª³ÁÖÛ2:
	case eSkill::ÎåÀ×Öä:
	case eSkill::ÂäÀ×·û:

	case eSkill::ßóßóÍáÍá:

	case eSkill::ÌìÀ×Õ¶:
	case eSkill::ÎåÀ×ºä¶¥:
	case eSkill::À×öªÍò¾û:

	case eSkill::ÁúÌÚ:
	case eSkill::Áú¾íÓê»÷:
	case eSkill::ÁúÒ÷:
	case eSkill::¶þÁúÏ·Öé:

	case eSkill::ÑÌÓê½£·¨:
	case eSkill::Æ®ÃìÊ½:

	case eSkill::ÈÕ¹â»ª:
	case eSkill::µå²×º£:
	case eSkill::¾ÞÑÒÆÆ:
	case eSkill::²ÔÃ£Ê÷:
	case eSkill::µØÁÑ»ð:

	case eSkill::ÑÖÂÞÁî:
	case eSkill::ÅÐ¹ÙÁî:
	case eSkill::Ê¬¸¯¶¾:
	case eSkill::»ÆÈªÖ®Ï¢:

	case eSkill::·ÉÉ°×ßÊ¯:
	case eSkill::ÈýÃÁÕæ»ð:

	case eSkill::ÏóÐÎ:
	case eSkill::Ó¥»÷:
	case eSkill::Ê¨²«:
	case eSkill::Á¬»·»÷:

	case eSkill::¹´»ê:
	case eSkill::ÉãÆÇ:
	case eSkill::ÌìÂÞµØÍø:

	case eSkill::ÁÑÊ¯:
	case eSkill::¶ÏÔÀÊÆ:
	case eSkill::Ìì±ÀµØÁÑ:
	case eSkill::¾ªÌÎÅ­2:
	case eSkill::·­½­½Áº£2:

	case eSkill::¾ª»êÕÆ:
	case eSkill::¶áÃüÖä:

	case eSkill::ÂäÒ¶ÏôÏô:
	case eSkill::¾£¼¬Îè:
	case eSkill::³¾ÍÁÈÐ:
	case eSkill::±ù´¨Å­:
	case eSkill::ÎíÉ±:
	case eSkill::ÑªÓê:

	case eSkill::À×»÷:
	case eSkill::±¼À×Öä:
	case eSkill::ÂäÑÒ:
	case eSkill::Ì©É½Ñ¹¶¥:
	case eSkill::Ë®¹¥:
	case eSkill::Ë®Âþ½ðÉ½:
	case eSkill::ÁÒ»ð:
	case eSkill::µØÓüÁÒ»ð:

	case eSkill::¾ªÐÄÒ»½£:
	case eSkill::Ò¹ÎèÇã³Ç:
	case eSkill::ËÀÍöÕÙ»½:
	case eSkill::ÉÆ¶ñÓÐ±¨:
	case eSkill::±ÚÀÝ»÷ÆÆ:
	case eSkill::½£µ´ËÄ·½:
	case eSkill::Ìì½µÁéºù:
	case eSkill::ÔÂ¹â:
	case eSkill::ÎüÐÇ´ó·¨:

	case eSkill::ÆÆÑª¿ñ¹¥:
	case eSkill::Èõµã»÷ÆÆ:
	case eSkill::ÆÆËéÎÞË«:
		return true;
	}
	return false;
}

bool txtSkill::isTargetsTeam(eSkill e)
{
	switch (e)
	{
	case eSkill::¾ÈËÀ·öÉË:
	case eSkill::À×öªÍò¾û:
	case eSkill::Áú¾íÓê»÷:
	case eSkill::ÁúÒ÷:
	case eSkill::¶þÁúÏ·Öé:
	case eSkill::·ÉÉ°×ßÊ¯:
	case eSkill::·­½­½Áº£:
	case eSkill::ÂäÒ¶ÏôÏô:
	case eSkill::Ì©É½Ñ¹¶¥:
	case eSkill::Ë®Âþ½ðÉ½:
	case eSkill::µØÓüÁÒ»ð:
	case eSkill::ÎüÐÇ´ó·¨:
		return true;
	}
	return false;
}


void txtSkill::applyIterPos(ulong actid, eSkiPos& pos)
{
	switch (actid)
	{
	case 0xB073119D: // 14 ´ßÃß
	case 0x2406DA40: // 15 Ê§ÐÄ
	case 0x5BCBB64F: // 28 ÂäÀ×

	case 0xF71DEAF7: // 31ß´ß´ÍáÍá
//	case 0x9E4E9755: // 35 »¤Ìå

	case 0x2C2DA419: // 89 ÈÕÔÂÇ¬À¤
	case 0x1CFE70FA: // 90 À¶µÆ
	case 0x7C7D67A6: // 91 ºìµÆ
	case 0x46038131: // 105 ÈÕ¹â»ª
	case 0x2DEE722A: // 108 ²ÔÃ£
	case 0x09CCB0F3: // 112 Áé¶¯
	case 0xD6BF55AD: // 115 ×ÔÔÚÐÄ·¨
	case 0x2711A4A3: // 117 ÅÐ¹ÙÁî
	case 0xB0FDC1B2: // 154 ¹´»ê
	case 0x1C57DA8A: // 154 ¹´»ê
	case 0x0E1DCDB9: // 187 Ã÷¹â±¦ »¹ÊÇÆ«
	case 0xADF90980: // 201 Ñ×»¤
	case 0x3200B6CC: // 2084 2085 À×»÷ 
		pos = eSkiPos::Bottom;
		break;
	case 0x0116C932: // 27 Ëé¼×
	case 0x9A94D461: // 68 ´íÂÒ
	case 0x6044E21A: // ÎåÀ×
//	case 0xCEAF0E44: // 159 º¬ÇéÂöÂö
		pos = eSkiPos::Mid;
		break;
	}
}


void txtSkill::applyAtkedDelta(ulong atkid, int& delta)
{
	switch (atkid)
	{
	case 0xF71DEAF7: // 31ß´ß´ÍáÍá
	case 0x774B7CEF: // 132 ÈýÃÁÕæ»ð
		delta /= 2;
		break;
	case 0xC4FABE4C: // 107 ¾ÞÑÒÆÆ
	case 0x2DEE722A: // 108 ²ÔÃ£Ê÷
		delta /= 3;
		break;
	default:
		if (delta <= 8)
		{
			delta = 1;
		}
		else if (delta <= 12)
		{
			delta = 2;
		}
		else
		{
			delta = 5;
		}
	}
}




txtSkill::txtSkill()
{
	insert(0x0E30CD44, 0x00000000, 0xDDD270F5, eSkill::À×»÷);
	insert(0xF54C4025, 0x00000000, 0x040584F3, eSkill::±¼À×Öä, eSkiPos::Bottom);
	insert(0x0AC30DE6, 0x00000000, 0x564F1090, eSkill::ÂäÑÒ, eSkiPos::Bottom);
	insert(0x783F9D20, 0x00000000, 0x22FEF25E, eSkill::Ì©É½Ñ¹¶¥);
	insert(0xF933209B, 0x00000000, 0x0071B681, eSkill::Ë®¹¥, eSkiPos::Bottom);
	// 
	insert(0x97311BAD, 0x00000000, 0x4F09C15D, eSkill::Ë®Âþ½ðÉ½);
	insert(0xD112913D, 0x00000000, 0x3E2A375C, eSkill::ÁÒ»ð, eSkiPos::Bottom);
	insert(0x139426B5, 0x00000000, 0x2E88DCF4, eSkill::µØÓüÁÒ»ð);
	insert(0x3BA4B993, 0x00000000, 0x675E4E20, eSkill::¾ªÐÄÒ»½£);
	// ¹·×¦Ó¡×´Ì¬,ÎÞÎ·²¼Ê©2Ò²ÊÇ
	insert(0xF18C76DD, 0x5525C5FB, 0x9609FDF4, eSkill::Ò¹ÎèÇã³Ç, eSkiPos::Bottom);
	// 0x19182964
	insert(0x4E02EC44, 0x2C6223D4, 0x739A0BAB, eSkill::ËÀÍöÕÙ»½);
	insert(0xFF33B0EE, 0x00000000, 0x00000000, eSkill::Á¦Åü»ªÉ½, eSkiPos::Bottom);
	insert(0x729ADE62, 0x00000000, 0x0504D379, eSkill::½£µ´ËÄ·½);
	insert(0x00000000, 0xDEDEE983, 0x00000000, eSkill::·¨Êõ·ÀÓù, eSkiType::BattleSelf);
	insert(0x8D8A818D, 0x00000000, 0x2174467F, eSkill::ÉÆ¶ñÓÐ±¨);
	insert(0x99DDC32A, 0x00000000, 0x0504D379, eSkill::±ÚÀÝ»÷ÆÆ);

	insert(0xFB90D9B1, 0x2F3E4271, 0x1353874F, eSkill::ÎÞÎ·²¼Ê©, eSkiType::BattleOwnerButSelf, eSkiPos::Top);
	insert(0xDCD7A875, 0x00000000, 0x00000000, eSkill::Ìì½µÁéºù, eSkiPos::Bottom);
	insert(0x28DC0E4B, 0x00000000, 0x9609FDF4, eSkill::ÔÂ¹â, eSkiPos::Bottom);
//	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÉÏ¹ÅÁé·û, eSkiPos::Bottom);
	insert(0x35AA81A7, 0x00000000, 0x00000000, eSkill::ÎüÐÇ´ó·¨);

	insert(0xF3B31E4E, 0x00000000, 0x53E82E61, eSkill::ÆøÁÆÊõ, eSkiType::BattleOwner);
	insert(0xFBF89980, 0x00000000, 0xE6339003, eSkill::ÐÄÁÆÊõ, eSkiType::BattleOwner);
	insert(0xF3B31E4E, 0x00000000, 0x53E82E61, eSkill::ÃüÁÆÊõ, eSkiType::BattleOwner);
	// 0x3240F0D4 ºÃ³ó
	insert(0x899241C3, 0x00000000, 0x4B800708, eSkill::ÄýÆø¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x7EE33126, 0x00000000, 0x4B800708, eSkill::ÄýÉñ¾÷, eSkiType::BattleOwner);
	insert(0xD077C3A0, 0x00000000, 0x53E82E61, eSkill::Æø¹éÊõ, eSkiType::BattleSelf);
	insert(0x30F2B60C, 0x00000000, 0x53E82E61, eSkill::Ãü¹éÊõ, eSkiType::BattleSelf);
	insert(0xD077C3A0, 0x00000000, 0x04E42236, eSkill::ËÄº£ÉýÆ½, eSkiType::BattleOwner);
	insert(0x8E92AE82, 0x00000000, 0x97283C40, eSkill::»Ø»êÖä, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x8E92AE82, 0x00000000, 0x97283C40, eSkill::ÆðËÀ»ØÉú, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x17238B9F, 0x00000000, 0xE6339003, eSkill::Ë®Çå¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x17238B9F, 0x00000000, 0xE6339003, eSkill::±ùÇå¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x17238B9F, 0x00000000, 0xFBD946FB, eSkill::ÓñÇå¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x66150076, 0x00000000, 0xFBD946FB, eSkill::¾§Çå¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0xA0F588C2, eSkill::¿ÕÎ»1);
	insert(0x00000000, 0x00000000, 0xA0F588C2, eSkill::¿ÕÎ»2);
//  insert(0x00000000, 0x00000000, 0xA0F588C2, eSkill::×çÖäÖ®ÉË, eSkillUse::BattleOther);
//  insert(0x00000000, 0x00000000, 0xA0F588C2, eSkill::×çÖäÖ®Íö, eSkillUse::BattleOther);

	insert(0x5DE57BA4, 0x00000000, 0xCE582B31, eSkill::Ð¦Àï²Øµ¶);
	insert(0x5DE57BA4, 0x00000000, 0x245321A8, eSkill::¾ø»ÃÄ§Òô);
	insert(0x203B8C75, 0x00000000, 0x019B0A72, eSkill::Ò°ÊÞÖ®Á¦, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x203B8C75, 0x00000000, 0x019B0A72, eSkill::Ä§ÊÞÖ®Ó¡, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x38FD76EA, 0x00000000, 0x245321A8, eSkill::¹â»ÔÖ®¼×, eSkiType::BattleOwner);
	insert(0x38FD76EA, 0x00000000, 0x245321A8, eSkill::Ê¥ÁéÖ®¼×, eSkiType::BattleOwner);
	insert(0xFE27EBCF, 0x00000000, 0xBF36842D, eSkill::Á÷ÔÆ¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0xFE27EBCF, 0x00000000, 0xBF36842D, eSkill::Ð¥·ç¾÷, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x9B23F38E, 0x5C5C1544, 0x3BF3590C, eSkill::Ì«¼«»¤·¨, eSkiType::BattleSelf);
	insert(0x9B23F38E, 0x5C5C1544, 0x3BF3590C, eSkill::ÂÞºº½ðÖÓ, eSkiType::BattleOwner);
	insert(0x95065313, 0x547C4B68, 0x1A67E919, eSkill::ÐÞÂÞÖä, eSkiType::BattleOwner);
	insert(0xC183DB1E, 0xFAF4A2D4, 0x40701F91, eSkill::ÌìÒÂÎÞ·ì, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x81B4599F, 0x00000000, 0x426F46C8, eSkill::·ÅÏÂÍÀµ¶, eSkiPos::Bottom);
	insert(0x81B4599F, 0x00000000, 0x426F46C8, eSkill::ºÓ¶«Ê¨ºð, eSkiPos::Bottom);
	insert(0xD0EEC915, 0x00000000, 0x70F1E396, eSkill::ÆÆ¼×Êõ);
	insert(0xD0EEC915, 0x00000000, 0x70F1E396, eSkill::Ëé¼×Êõ);
	insert(0xD1E593CE, 0x00000000, 0x70F1E396, eSkill::ÄýÖÍÊõ, eSkiPos::Bottom);
	insert(0xD1E593CE, 0x00000000, 0x70F1E396, eSkill::Í£ÏÝÊõ, eSkiPos::Bottom);
	insert(0x171544B2, 0x00000000, 0x4B800708, eSkill::ÆÆÑª¿ñ¹¥);
	insert(0xB1822745, 0x00000000, 0x4B800708, eSkill::Èõµã»÷ÆÆ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¿ÕÎ»3);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¿ÕÎ»4);
	insert(0x33084AA4, 0x00000000, 0x00000000, eSkill::ÐÇ±­Ê¥Óò, eSkiType::BattleOwner);
	insert(0x4F116543, 0x00000000, 0x00000000, eSkill::ÃüÁÆÊõEX, eSkiType::BattleOwner);
	insert(0x21FAE73F, 0x00000000, 0x00000000, eSkill::ÆÆËéÎÞË«);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¿ÕÎ»5);
	insert(0x00000000, 0x00000000, 0x4B800708, eSkill::ÆÆÑª¿ñ¹¥2);
	insert(0x00000000, 0x00000000, 0x4B800708, eSkill::Èõµã»÷ÆÆEX);
	insert(0x00000000, 0x00000000, 0x4B800708, eSkill::ÆÆÑª¿ñ¹¥EX);
	insert(0x00000000, 0x00000000, 0x104B1B46, eSkill::¿ÕÎ»6);
	insert(0xF224F08A, 0x00000000, 0x00000000, eSkill::´óµØÖ®Ç½, eSkiType::BattleOwner);
	insert(0x1ADABFA6, 0xE43459EB, 0x40701F91, eSkill::ÐÄÈçÃ÷¾µ, eSkiType::BattleSelf);
	insert(0xE1084D39, 0x00000000, 0x00000000, eSkill::´Èº½ÆÕ¶É, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x95473D14, 0x00000000, 0x00000000, eSkill::Ñ¸¼²Èç·ç, eSkiType::BattleOwner);

	// ÐÝÏ¢ 0xD9463A0C
	insert(0x19C102D1, 0x56E05B32, 0x30D78CEF, eSkill::ºáÉ¨Ç§¾ü);
	insert(968268166, 0x2A2A0663, 0x39D047A5, eSkill::ºó·¢ÖÆÈË);
	insert(0x00000000, 0x00000000, 0xED520CA0, eSkill::±øÆ÷Æ×);
	insert(0x00000000, 0x00000000, 0x04E0F4C5, eSkill::Ç§ÀïÉñÐÐ);
	insert(0x94A5BEEC, 0x85B3D6F1, 0x00000000, eSkill::É±Æø¾÷, eSkiType::BattleOwner, eBuff::Good);
	insert(0x19C102D1, 0x00000000, 0x00000000, eSkill::Õ¶Áú¾÷, eSkiPos::Bottom);
	insert(0x6B934898, 0x00000000, 0x0B2ED764, eSkill::·´¼äÖ®¼Æ, eBuff::Seal);
	insert(0x559C8ECF, 0x56E05B32, 0x795E59BA, eSkill::ÆÆ¸ª³ÁÖÛ);
	insert(0x25F14A5E, 0x34999043, 0x095B5FC6, eSkill::°²Éñ¾÷, eSkiType::BattleSelf, eBuff::Good, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÊÈÑª);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÈýÐÇÃðÄ§, eSkiPos::Bottom);
	insert(0x387C1EEB, 0x00000000, 0xDDD270F5, eSkill::ÎåÀ×Öä, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::·ÉÐÐ·û);
	insert(0x00000000, 0x00000000, 0xA309D8A4, eSkill::±ø½â·û, eSkiType::BattleSelf);
	insert(0x9EC0624E, 3398426285, 0xAEABE4AC, eSkill::´ßÃß·û, eBuff::Seal);
	insert(0x091ADDC7, 3635978625, 0x9A1A2884, eSkill::Ê§ÐÄ·û, eBuff::Seal);
	insert(0x4FB56243, 0x8B43833D, 0xF6BED451, eSkill::ÂäÆÇ·û, eBuff::Seal);
	insert(0xD4AA2F8A, 3946646209, 0xF6BED451, eSkill::Ê§Òä·û, eBuff::Seal);
	insert(0xD4024676, 3655438388, 0xF6BED451, eSkill::×·»ê·û, eBuff::Seal);
	insert(0x1919B112, 1214058823, 0xF6BED451, eSkill::Àë»ê·û, eBuff::Seal);
	insert(0x7BCD8BC0, 2336457533, 0xF6BED451, eSkill::Ê§»ê·û, eBuff::Seal);
	insert(0xDE4E3A84, 2461182746, 0xF6BED451, eSkill::¶¨Éí·û, eBuff::Seal);
	insert(0x517656E2, 0x00000000, 0x04E42236, eSkill::¹éÔªÖä, eSkiType::BattleSelf);
	insert(0x517656E2, 0x00000000, 0x04E42236, eSkill::ÄýÉñÊõ, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ç¬Ììî¸Æø);
	insert(0x00000000, 0x00000000, 0xA309D8A4, eSkill::ÒÒÄ¾ÏÉ¶Ý);
	insert(0x4B9ACA92, 0x00000000, 0x4644FF98, eSkill::·ÖÉíÊõ, eSkiType::BattleSelf, eBuff::Good);
	// 0x84FA9FA5 ·û,²»ÊÇ¼× ×´Ì¬0x5525C5FB
	insert(0xCB3B68B8, 0xA5D7B0F7, 0xAEABE4AC, eSkill::Ëé¼×·û, eBuff::Bad, eSkiPos::Bottom);
	insert(0xC1731A60, 0x00000000, 0xDDD270F5, eSkill::ÂäÀ×·û);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Éñ±ø»¤·¨);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::×ÏÆø¶«À´);
	insert(0xC12C2663, 0x00000000, 0xDBB88662, eSkill::ßóßóÍáÍá);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::´ïÄ¦»¤Ìå);
	insert(0x04DB6C0A, 0x00000000, 0xC0A21592, eSkill::½ð¸Õ»¤·¨, eSkiType::BattleOwner, eBuff::Good);
	insert(0x434750DE, 0x85B3D6F1, 0xBF36842D, eSkill::Î¤ÍÓ»¤·¨, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	// 0x38C2146B ×´Ì¬ 916220457 
	insert(0x9E4E9755, 0x369C6A29, 0xC0A21592, eSkill::½ð¸Õ»¤Ìå, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	// 0xF354CCB8
	insert(0x93CFD0AF, 0x061869D7, 0xBF36842D, eSkill::Ò»Î­¶É½­, eSkiType::BattleOwner, eBuff::Good);
	insert(0x203B8773, 0x00000000, 0x97283C40, eSkill::ÎÒ·ð´È±¯, eSkiType::BattleOwner);
	insert(0x573F92CA, 0x00000000, 0x04E42236, eSkill::ÍÆÄÃ, eSkiType::BattleSelf);
	insert(0x03139F50, 0x00000000, 0x04E42236, eSkill::»îÑª, eSkiType::BattleOwner);
	insert(0xEF9691F3, 0x00000000, 0x04E42236, eSkill::ÍÆÆø¹ý¹¬, eSkiType::BattleOwner);
	insert(0xE869B98A, 0x00000000, 0x04E42236, eSkill::ÃîÊÖ»Ø´º, eSkiType::BattleOwner);
	// 0x28E639AA
	insert(0x7EEC276B, 0x00000000, 0x04E42236, eSkill::¾ÈËÀ·öÉË, eSkiType::BattleOwner);
	insert(0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::½â¶¾, eSkiType::BattleOwner);
	insert(0x00000000, 0x00000000, 0x084168D9, eSkill::·ðÃÅÆÕ¶É);
	insert(0xF0CE9045, 0x00000000, 0xCE259E8C, eSkill::ÉáÉúÈ¡Òå, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0xC8011EF1, 3930943562, 0x3E128ADA, eSkill::·ð·¨ÎÞ±ß, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Äé»¨ÃîÖ¸);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ºìÐäÌíÏã);
	insert(0x182CE63B, 0x72AD6DBA, 0xBDCD9588, eSkill::³þ³þ¿ÉÁ¯, eSkiType::BattleSelf, eBuff::Good, eSkiPos::Bottom);
	insert(0x9D5F7277, 0xDBCEE32C, 0xC99B2900, eSkill::ÂúÌì»¨Óê, eBuff::Poison, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÇéÌìºÞº£);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Á«²½ÇáÎè);
	insert(0x8A39B79F, 0x00000000, 0xBDCD9588, eSkill::Èç»¨½âÓï);
	insert(0x46C7B776, 0x59D77EF9, 0xBDCD9588, eSkill::ËÆÓñÉúÏã, eBuff::Seal, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::æ³æÃ‹ØÄÈ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÇáÈçºèÃ«);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::°Ù¶¾²»ÇÖ);
	insert(0x00000000, 0x00000000, 0xFE189BCC, eSkill::ÒÆÐÎ»»Ó°);
	insert(0x8A39B79F, 0x00000000, 0x51F82D7D, eSkill::Ò»Ð¦Çã³Ç, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::·É»¨ÕªÒ¶);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÓêÂäº®É³);

	insert(0x00000000, 0x66CC7A29, 0x00000000, eSkill::ÌìÉñ»¤Ìå, eSkiType::BattleSelf, eBuff::Good, eSkiPos::Top);
	insert(0x73604A57, 0x00000000, 0x00000000, eSkill::ÌìÉñ»¤·¨, eSkiType::BattleOwner, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÌìÖïµØÃð);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Öª¼ºÖª±Ë);
	insert(0xDC756B6F, 0x00000000, 0x57726FFB, eSkill::ÄþÐÄ, eSkiType::BattleOwner);
	insert(0x1EB0026B, 0x98753F94, 0x318685B7, eSkill::ÕòÑý, eBuff::Seal, eSkiPos::Bottom);
	insert(0xD35FC051, 0x2F78C46E, 0x5703EB56, eSkill::´íÂÒ, eBuff::Seal, eSkiPos::Bottom);
	insert(0x8B8516F1, 0xC48ABA7B, 0x318685B7, eSkill::°ÙÍòÉñ±ø, eBuff::Seal, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0xA12CF973, eSkill::ÌÚÔÆ¼ÝÎí);
	insert(0x4C117B7C, 0x00000000, 0x251670FB, eSkill::ÌìÀ×Õ¶, eSkiPos::Bottom);
	insert(0xFFD64CCA, 0x00000000, 0xDB4F9338, eSkill::ÎåÀ×ºä¶¥, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::½ð¸Õïí);
	insert(0x911E3921, 0x00000000, 0x040584F3, eSkill::À×öªÍò¾û);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ºÆÈ»ÕýÆø);
	insert(0x752464D7, 0x00000000, 0x318685B7, eSkill::ÕÆÐÄÀ×, eBuff::Good);

	insert(0xDC756B6F, 0x00000000, 0x57726FFB, eSkill::½â·â, eSkiType::BattleOwner);
	insert(0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::ÇåÐÄ, eSkiType::BattleOwner);
	insert(0x7367AF0F, 0x00000000, 0x5505BC3C, eSkill::ÁúÌÚ, eSkiPos::Bottom);
	insert(0xA19EAB31, 0x00000000, 0xA39B4CA3, eSkill::Áú¾íÓê»÷);
	insert(0x04DB6C0A, 0x00000000, 0xC0A21592, eSkill::ÄæÁÛ, eSkiType::BattleSelf, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::³Ë·çÆÆÀË);
	insert(0x00000000, 0x00000000, 0x64AAF170, eSkill::Ë®¶Ý);
	insert(0x48639CF5, 0x00000000, 0xA08D7D31, eSkill::ÁúÒ÷);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÁúÐ¥¾ÅÌì);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Áú¸½);
	insert(0xF483EB13, 0x4CCDACCB, 0x00000000, eSkill::ÉñÁú°ÚÎ², eSkiType::BattleSelf, eBuff::Good, eSkiPos::Bottom);
	insert(0xA680A821, 0x00000000, 0x6F872F79, eSkill::¶þÁúÏ·Öé);

	insert(0xA70D1263, 0x313BCC79, 0xA7B1C535, eSkill::ÈÕÔÂÇ¬À¤, eBuff::Seal, eSkiPos::Bottom);
	insert(0x3648247E, 0x719D767F, 0x24A434E5, eSkill::Á¶Æø»¯Éñ, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Top);
	insert(0xD2DC9AD3, 0xF8EE853A, 0x24A434E5, eSkill::ÉúÃüÖ®Èª, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Top);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ì«¼«Éú»¯);
	insert(0x00000000, 0x00000000, 0x9197B5A6, eSkill::¶·×ªÐÇÒÆ);
	insert(0x775FD2E3, 0x00000000, 0x24A434E5, eSkill::Èý»¨¾Û¶¥, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÇýÄ§);
	insert(0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::ÇýÊ¬, eSkiType::BattleOwner);
	// »÷´ò¶¯»­ 0xD06119B3 0xC29A0737
	insert(0xA3FD9577, 0x00000000, 0x30D78CEF, eSkill::ÑÌÓê½£·¨);
	insert(0x66BEBCBA, 0x00000000, 0x00000000, eSkill::Æ®ÃìÊ½);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÌìµØÍ¬ÊÙ, eSkiType::BattleOwner, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ç¬À¤Ãî·¨);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ò»Æø»¯ÈýÇå);

	insert(0x2FF74578, 0xD8857128, 0x2550B4D0, eSkill::ÆÕ¶ÉÖÚÉú, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	// 0x5480C749
	insert(0x1EA5FACC, 0xEFE73EB9, 0xD00F519D, eSkill::½ô¹¿Öä, eBuff::Bad, eSkiPos::Bottom);
	insert(0x380337C1, 0xD8857128, 0xA4B9B11E, eSkill::ÑîÁø¸ÊÂ¶, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x45CA9913, 0x00000000, 0xCE259E8C, eSkill::ÈÕ¹â»ª);
	insert(0x6C5F8376, 0x00000000, 0xE957CD44, eSkill::µå²×º£, eSkiPos::Bottom);
	insert(0xDF4C3BE3, 0x00000000, 0x52BA8E8D, eSkill::¾ÞÑÒÆÆ, eSkiPos::Bottom);
	insert(0x9CCB6E84, 0x00000000, 0x251670FB, eSkill::²ÔÃ£Ê÷);
	insert(0x18E13BE9, 0x00000000, 0x1366C86B, eSkill::µØÁÑ»ð, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0xEFB621F4, eSkill::×øÁ«);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÎåÐÐ´íÎ»);
	insert(0xAB5DAE52, 0x95FF4460, 0x2550B4D0, eSkill::Áé¶¯¾ÅÌì, eSkiType::BattleOwner, eBuff::Good);
	// 0x5A07D50A ×´Ì¬0x4DDF5690
	insert(0x88F19652, 0x2D1E688F, 0xA37E8B19, eSkill::µßµ¹ÎåÐÐ, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Á«»ªÃî·¨);
	insert(0x77592664, 0x00000000, 0x00000000, eSkill::×ÔÔÚÐÄ·¨, eSkiType::BattleOwner);

	insert(0x9EB11259, 0x00000000, 0x12A308C0, eSkill::ÑÖÂÞÁî, eSkiPos::Bottom);
	insert(0x241C668A, 0x00000000, 0xB6A8CB18, eSkill::ÅÐ¹ÙÁî);;
	insert(0x00000000, 0x00000000, 0xED520CA0, eSkill::¿±²ìÁî);
	insert(0xDC756B6F, 0x00000000, 0x00000000, eSkill::¹ÑÓûÁî, eSkiType::BattleOwner);
	insert(0x07DF52CA, 0x21435203, 0xFBA099F0, eSkill::ÓÄÚ¤¹íÑÛ, eSkiType::BattleOwner, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ô©»ê²»É¢);
	insert(0x849E48FB, 0x839CC29A, 0x98BDEC63, eSkill::Ê¬¸¯¶¾, eBuff::Poison, eSkiPos::Bottom);
	insert(0xBA7D5CD7, 0x00000000, 0x00000000, eSkill::ÐÞÂÞÒþÉí, eSkiType::BattleOwner);
	insert(0x00000000, 0x00000000, 0xBB1E59E8, eSkill::èÃÎÞÒôÑ¶);
	insert(0x380337C1, 0x00000000, 0x97283C40, eSkill::»¹ÑôÊõ, eSkiType::BattleOwner, eSkiPos::Bottom);
	// ×´Ì¬ 0x5ECEBEDD
	insert(0x2611E02E, 0x69180378, 0xBF36842D, eSkill::»ÆÈªÖ®Ï¢, eBuff::Bad, eSkiPos::Bottom);
	insert(0x057B7209, 0x00000000, 0x814AE8F4, eSkill::»ê·ÉÆÇÉ¢, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ê¬ÆøÂþÌì);
	insert(0x5C0073EE, 0xE02F2E6D, 0x7FDACB76, eSkill::ïÀ»êÊõ);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ä§Íõ»¤³Ö);
	insert(0x4DB67680, 0x00000000, 0x550EEC3F, eSkill::·ÉÉ°×ßÊ¯);
	insert(0xFCDCCCEC, 0x00000000, 0xF4A86696, eSkill::ÈýÃÁÕæ»ð, eSkiPos::Bottom);
	insert(0x6EA4246E, 0xA168E26F, 0xED47E570, eSkill::Å£¾¢, eSkiType::BattleSelf, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ì¤É½ÁÑÊ¯);
	insert(0x00000000, 0x00000000, 0x40E67E07, eSkill::ÎÞµÐÅ£Ê­, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x40E67E07, eSkill::ÎÞµÐÅ£Ñý, eSkiType::BattleSelf);
	insert(0x16B27FFC, 0xBBEA83F4, 0x00000000, eSkill::Ä§Íõ»ØÊ×, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x14E55AF2, eSkill::Å£Êº¶Ý);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::»ð¼×Êõ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ò¡Í·°ÚÎ²);

	insert(0xBE127823, 0x3646A4D9, 0x7CFA5491, eSkill::ÏóÐÎ);
	insert(2194212682, 0x58628406, 0x61688718, eSkill::Ó¥»÷);
	insert(0x718754A2, 0x00000000, 0xF3626BEC, eSkill::Ê¨²«);
	insert(0x8476181B, 0x20FCCE94, 0x019B0A72, eSkill::ÍþÉå, eBuff::Seal);
	insert(0x29D819DF, 0x85C9AF08, 0xB90610BF, eSkill::±äÉí, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ä§ÊÞÐ¥Ìì);
	insert(755485932, 0x566DC0F3, 0x40701F91, eSkill::¶¨ÐÄÊõ, eSkiType::BattleSelf, eBuff::Good);
	insert(0x55EBCA6C, 0x58628406, 0x2FFC7F8A, eSkill::Á¬»·»÷);
	insert(0x00000000, 0x00000000, 0x35B1FE83, eSkill::Õñ³áÇ§Àï);
	insert(0x16B27FFC, 0xBBEA83F4, 0x6961CB02, eSkill::¼«¶È·è¿ñ, eSkiType::BattleSelf, eBuff::Good);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ä§Ï¢Êõ);
	insert(0x3105A01B, 0x3D3FA597, 0x1C7EE63E, eSkill::ÌìÄ§½âÌå, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÉñÁ¦ÎÞÇî);

	insert(0x1B472F2F, 0x00000000, 0xC0942A07, eSkill::¹´»ê);
	insert(0x59BD69F1, 0x00000000, 0xC0942A07, eSkill::ÉãÆÇ);
	insert(0x78246FE4, 0xC4AA8E18, 0xE6F9B619, eSkill::Ä§ÒôÉã»ê, eBuff::Seal);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÅÌË¿Îè);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¶áÃüÖëË¿);
	insert(0x5363AF2D, 0x8103AFD2, 0x7F5FD02A, eSkill::º¬ÇéÂöÂö, eBuff::Seal, eSkiPos::Bottom);
	insert(0x7CD9C342, 0x369C6A29, 0xA37E8B19, eSkill::ÅÌË¿Õó, eSkiType::BattleSelf, eBuff::Good);
	insert(0xDC756B6F, 0x00000000, 0x5007BB0C, eSkill::¸´ËÕ, eSkiType::BattleSelf);
	insert(0x8F3E73D5, 0xD671B65E, 0x13848F75, eSkill::ÌìÂÞµØÍø, eBuff::Seal, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x95C06373, eSkill::Ìì²ÏË¿);
	insert(0x00000000, 0x00000000, 0xC0942A07, eSkill::½ãÃÃÍ¬ÐÄ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÕÎÆø);
	insert(0x0732894C, 0xCDE5D209, 0x245321A8, eSkill::»Ã¾µÊõ, eSkiType::BattleSelf, eBuff::Good);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÁÑÊ¯);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¶ÏÔÀÊÆ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ìì±ÀµØÁÑ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÀËÓ¿);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¾ªÌÎÅ­, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::·­½­½Áº£);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÌÚÀ×);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ö¸µØ³É¸Ö);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::²»¶¯ÈçÉ½, eSkiType::BattleSelf, eBuff::Good, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ËéÐÇ¾÷, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Top);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Õò»ê¾÷, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Top);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::´©ÔÆÆÆ¿Õ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÎÞÇîÃîµÀ, eSkiType::BattleOwner);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::×ÝµØ½ð¹â);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÒÆ»ê»¯¹Ç, eSkiType::BattleOwner, eBuff::Good, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¶áÆÇÁî, eBuff::Seal, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::É·Æø¾÷);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¾ª»êÕÆ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::´ÝÐÄÊõ, eBuff::Bad);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¶áÃüÖä, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ã÷¹â±¦Öò, eSkiType::BattleOwner);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::½ðÉíÉáÀû, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::µØÓ¿½ðÁ«, eSkiType::BattleOwner, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÍòÄ¾µò¿Ý);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÔªÑô»¤Ìå);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¶ÝµØÊõ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÓÉ¼º¶ÉÈË, eSkiType::BattleOwner, eSkiPos::Bottom);

	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÂäÒ¶ÏôÏô);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::¾£¼¬Îè, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::³¾ÍÁÈÐ, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::±ù´¨Å­, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÎíÉ±, eBuff::Bad, eSkiPos::Bottom);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÑªÓê);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÐÇÔÂÖ®»Ý, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ñ×»¤, eSkiType::BattleSelf);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::Ò¶Òþ);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÉñÄ¾ß½Óï);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ÃÜÈó, eSkiType::BattleOwner, eSkiPos::Top);
	insert(0x00000000, 0x00000000, 0x00000000, eSkill::ò÷ÒÏÊ´Ìì);





	initActs();
	//////////////////////////////////////////////////////////////////////////
	insertHit(eSkill::ºáÉ¨Ç§¾ü, 0xACA4A54A, 0x3C45D282, 0xD862FBE7);
	// 0x19C102D1 ??? ÕâÊÇ??? ÐÝÏ¢??
	insertHit(eSkill::ºó·¢ÖÆÈË2, 0x958FAC37);
	insertHit(eSkill::ÆÆ¸ª³ÁÖÛ2, 0x301F9E4A, 0x6AD55205);
	
	insertHit(eSkill::ÌìÀ×Õ¶, 0xB6141EB9, 0xF17168C5, 0x885ACBE1);
	
	insertHit(eSkill::ÑÌÓê½£·¨, 0x4F8312F6, 0x9215D669, 0xD06119B3);
	insertHit(eSkill::Æ®ÃìÊ½, 0x3426ACE0);
	
	insertHit(eSkill::ÏóÐÎ, 0x73DA1CCF, 0x89302F40);
	insertHit(eSkill::Ó¥»÷, 0xA463C055, 0x86FE2BC1, 0x83020DAE);
	insertHit(eSkill::Ê¨²«, 0x42F0386F, 0x096766A8);
	
	insertHit(eSkill::ÁÑÊ¯, 0x958FAC37);
	insertHit(eSkill::¶ÏÔÀÊÆ, 0x958FAC37);
	insertHit(eSkill::Ìì±ÀµØÁÑ, 0x958FAC37);
	insertHit(eSkill::ÀËÓ¿, 0xD53A25EB);
	insertHit(eSkill::¾ªÌÎÅ­2, 0xB94D0B94);
	insertHit(eSkill::·­½­½Áº£2, 0xB94D0B94);
	//////////////////////////////////////////////////////////////////////////
	initFushi();
	//////////////////////////////////////////////////////////////////////////

	_stateExs.insert(std::make_pair(eSkill::ÎÞÎ·²¼Ê©2, 0x5525C5FB));
	_stateExs.insert(std::make_pair(eSkill::½ð¸Õ»¤Ìå1, 0x592EBD89));
	_stateExs.insert(std::make_pair(eSkill::½ð¸Õ»¤Ìå2, 0x2F45B9F0));
	_stateExs.insert(std::make_pair(eSkill::Õ½Òâ1, 0xC4FE8E3F));
	_stateExs.insert(std::make_pair(eSkill::Õ½Òâ2, 0x3D3C8D10));
	_stateExs.insert(std::make_pair(eSkill::Õ½Òâ3, 0xD1C3B611));
	//////////////////////////////////////////////////////////////////////////
	initEffect();
};



