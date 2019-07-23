#include "txtZuoqi.h"

ccc_txt_instance_cpp(txtZuoqi);


// bool txtZuoqi::isZuoqi(eZuoqi zq, int shuangshi)
// {
// 	return shuangshi >= 0 && shuangshi < _zhuangshis.size() && (shuangshi / 3) == (int)zq;
// }


void txtZuoqi::init(eZuoqi e, const ulong& stand,const ulong& walk,const ulong& color,const std::string& name)
{
	auto& zuoqi = _tables.at(e);
	zuoqi.stand = stand;
	zuoqi.walk = walk;
	zuoqi.color = color;
	zuoqi.name = name;
	_masters = &zuoqi.masters;
}

void txtZuoqi::init(int id, const ulong& stand,const ulong& walk,const ulong& color)
{
	auto& zuoqi = _zhuangshis.at(id);
	zuoqi.stand = stand;
	zuoqi.walk = walk;
	zuoqi.color = color;
	_masters = &zuoqi.masters;
}
void txtZuoqi::insert(eMod master,const ulong& stand,const ulong& walk)
{
	_standwalk.stand = stand;
	_standwalk.walk = walk;
	_masters->insert(std::make_pair(master, _standwalk));
	if (_index < 0)
	{
		txtXiangrui::getInstance()->_masterStands.at(master).push_back(stand);
		txtXiangrui::getInstance()->_masterWalks.at(master).push_back(walk);
	}
}

// void txtZuoqi::insert(const ulong& stand, const ulong& walk, const ulong& stand2 /*= 0*/, const ulong& walk2 /*= 0*/)
// {
// 	_xiangrui.stand = stand;
// 	_xiangrui.walk = walk;
// 	_xiangrui.stand2 = stand2;
// 	_xiangrui.walk2 = walk2;
// 	_xiangruis.insert(std::make_pair(_index, _xiangrui));
// 	++_index;
// }

txtZuoqi::txtZuoqi()
{
	sZuoqi zuoqi;
	for (int e = (int)eZuoqi::eZuoqi0; e <= (int)eZuoqi::eZuoqiEnd; ++e)
	{
		_tables.insert(std::make_pair((eZuoqi)e, zuoqi));
	}
	for (int e = 0; e < 24; ++e)
	{
		_zhuangshis.insert(std::make_pair(e, zuoqi));
	}
// 	std::vector<ulong> uids;
// 	for (int e = (int)eMod::eJueSe0; e <= (int)eMod::eJueSeEnd; ++e)
// 	{
// 		_masterStands.insert(std::make_pair((eMod)e, uids));
// 		_masterWalks.insert(std::make_pair((eMod)e, uids));
// 	}
// 
// 	_masterStands.at(eMod::eJueSeÙÈÎÞÊ¦).push_back(0xC8FDA195);
// 	_masterStands.at(eMod::eJueSeÌÒØ²Ø²).push_back(0x0C8FDA28);
// 	_masterStands.at(eMod::eJueSe¹íäìäì).push_back(0x094C5BFB);
// 
// 	_masterWalks.at(eMod::eJueSeÙÈÎÞÊ¦).push_back(0xC8FDA428);
// 	_masterWalks.at(eMod::eJueSeÌÒØ²Ø²).push_back(0x0C8FDA70);
// 	_masterWalks.at(eMod::eJueSe¹íäìäì).push_back(0xFE2D2B18);

	_index = 0;

	init(eZuoqi::±¦±´ºùÂ«, 0x63C1AA04, 0x939B6AA2, 0x63999FC7, "±¦±´ºùÂ«");
	insert(eMod::eJueSe½£ÏÀ¿Í, 0x67101CB7, 0x9C8790BA);
	insert(eMod::eJueSeåÐÒ£Éú, 0xA35491C9, 0x49D7C76E);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x4492502E, 0xF6D6D5E6);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xD43912A9, 0xD2D4CAD3);
	insert(eMod::eJueSe»¢Í·¹Ö, 0x99AD84CD, 0x9FA6D533);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x21ED721D, 0x5A05E1C0);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xBEEF3795, 0x3C6BF98F);
	insert(eMod::eJueSeºüÃÀÈË, 0xE3123BDA, 0x956305B5);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x4F27A59F, 0x801F438D);
	insert(eMod::eJueSeÉñÌì±ø, 0x77104303, 0xBC38000F);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x861EE4D9, 0x9F2F9C11);
	insert(eMod::eJueSeÎèÌì¼§, 0x54DB4F4D, 0xCB722714);
	insert(eMod::eJueSeÎ×Âù¶ù, 0xF2BC9369, 0xB11F6642);
	insert(eMod::eJueSeÓðÁéÉñ, 0x7D31F43E, 0x76E4E3D6);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0xE137A55D, 0xDB553291);
	init(eZuoqi::ÉñÆøÐ¡¹ê, 0x00E88353, 0x702610D3, 0x6FFB9A9B, "ÉñÆøÐ¡¹ê");
	insert(eMod::eJueSe½£ÏÀ¿Í, 0x32DA9583, 0xEC9AC961);
	insert(eMod::eJueSeåÐÒ£Éú, 0xB770EAD4, 0x9A1479D8);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xDCB946EC, 0xDCC84D4E);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x70291C50, 0x30CABF19);
	insert(eMod::eJueSe»¢Í·¹Ö, 0xF56603D1, 0x83DBBA94);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x9DFEB143, 0x77C20678);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xE2C1CDE4, 0xBAD0F711);
	insert(eMod::eJueSeºüÃÀÈË, 0xFB798485, 0xD1997415);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x46F4FDF6, 0xC9EF2751);
	insert(eMod::eJueSeÉñÌì±ø, 0xF4EF98B5, 0x7C731501);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x3316877C, 0x31F77503);
	insert(eMod::eJueSeÎèÌì¼§, 0xD92FC3DE, 0x809F42FE);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x9B73C75F, 0xDA0A8B06);
	insert(eMod::eJueSeÓðÁéÉñ, 0x7B86A5F4, 0xE496A2D7);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x8BEA762D, 0x14EE7109);
	init(eZuoqi::ººÑª±¦Âí, 0x7B49FA9A, 0x3F76F5B2, 0x365DD585, "ººÑª±¦Âí");
	insert(eMod::eJueSe½£ÏÀ¿Í, 0x0766731D, 0x8C50358A);
	insert(eMod::eJueSeåÐÒ£Éú, 0x76D629EA, 0xFB50C58F);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xDF01F29D, 0xA77B55E4);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x726C392E, 0x68FB1969);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x2F5EAD3F, 0x499F9D37);
	init(eZuoqi::»¶Ï²ÑòÑò, 0x8D4DBAAE, 0x2636063C, 0x040C3F, "»¶Ï²ÑòÑò");
	insert(eMod::eJueSe½£ÏÀ¿Í, 0xA95A126D, 0x513DDE6C);
	insert(eMod::eJueSeåÐÒ£Éú, 0x3D392EF4, 0xA5E02A65);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x6E0AD379, 0x87C7A650);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x2474769B, 0xACD868DE);
	insert(eMod::eJueSeÎ×Âù¶ù, 0xCCC0985C, 0xC8F56BA3);
	init(eZuoqi::Ä§Á¦¶·ÊÞ, 0x4B0E16F1, 0x28F7499E, 0x2BC951, "Ä§Á¦¶·ÊÞ");
	insert(eMod::eJueSe»¢Í·¹Ö, 0x37FFB9DF, 0x64426F93);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x1AF61311, 0x6E370D46);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x75B09FA1, 0x5E5736EE);
	insert(eMod::eJueSeºüÃÀÈË, 0x64C21A63, 0xD5D2FA14);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x046A79E5, 0x03CD5444);
	init(eZuoqi::Åû¼×Õ½ÀÇ, 0x003B0CC9, 0xF6B76F79, 0x6B289253, "Åû¼×Õ½ÀÇ");
	insert(eMod::eJueSe»¢Í·¹Ö, 0x95BC0425, 0xC6053278);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xCC1426ED, 0x39FE09DB);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x83DD50D3, 0xB84C7C38);
	insert(eMod::eJueSeºüÃÀÈË, 0xBCD86DDA, 0xF0062006);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x0F974CEB, 0x54A8F096);
	init(eZuoqi::ÏÐÔÆÒ°º×, 0x49CAB729, 0x1544FBAD, 0x03FF92C0, "ÏÐÔÆÒ°º×");
	insert(eMod::eJueSeÁúÌ«×Ó, 0x5B0EDDAD, 0xB227D39F);
	insert(eMod::eJueSeÉñÌì±ø, 0x7F6D09AB, 0x13AD1C23);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x0779A3DF, 0x622664DC);
	insert(eMod::eJueSeÎèÌì¼§, 0x212848A1, 0xAAD7CB93);
	insert(eMod::eJueSeÓðÁéÉñ, 0x8072202A, 0x6528F013);
	init(eZuoqi::ÔÆ÷ÈÏÉÂ¹, 0x621ECF47, 0x098D7DB2, 0x65D2A1A4, "ÔÆ÷ÈÏÉÂ¹");
	insert(eMod::eJueSeÁúÌ«×Ó, 0x643F7DDE, 0xCC8E0921);
	insert(eMod::eJueSeÉñÌì±ø, 0x60A47C21, 0x63930A54);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0xA6FD7850, 0xB9FD9DBD);
	insert(eMod::eJueSeÎèÌì¼§, 0xB44DF735, 0xECA5DB49);
	insert(eMod::eJueSeÓðÁéÉñ, 0x4BBD02E6, 0x694A236B);


	//////////////////////////////////////////////////////////////////////////
	_index = 0;
	init(0x00, 0x2DC16EF4, 0x47A59E6C, 0x834E83B8);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0xB53D5C44, 0xC96AA3DB);
	insert(eMod::eJueSeåÐÒ£Éú, 0x9EE50249, 0x2F9E90BF);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xD9D4DF23, 0x11AE6369);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x08387E6E, 0xDE9D39B2);
	insert(eMod::eJueSe»¢Í·¹Ö, 0x3ED360D9, 0xAB65F5A6);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x3C6E582F, 0xD412204D);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x760F7E30, 0xE4E8FD53);
	insert(eMod::eJueSeºüÃÀÈË, 0x61FA8C5A, 0x2A996DC0);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x42FEAB27, 0x3E8C2715);
	insert(eMod::eJueSeÉñÌì±ø, 0x06C8CD7B, 0x145D2965);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x3DBED35F, 0xBD447357);
	insert(eMod::eJueSeÎèÌì¼§, 0x055833D4, 0x0E3198D2);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x92C873E1, 0x6D7462CB);
	insert(eMod::eJueSeÓðÁéÉñ, 0x0728B84A, 0x023D243C);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x92C873E1, 0xD66C4AE0);

	init(0x01, 0x4FB7A645, 0xC89B8D7B, 0x09B3E018);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0xB3514A6C, 0xFCA1E15D);
	insert(eMod::eJueSeåÐÒ£Éú, 0xC29B17B3, 0x7BA1295E);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x0A648F69, 0x81A1DC67);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xD9665834, 0xD4CE3400);
	insert(eMod::eJueSe»¢Í·¹Ö, 0xE8E4583D, 0x7EDA0BD2);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xC8CD054B, 0x17D34B4E);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x85ACCFE8, 0x24A7DA08);
	insert(eMod::eJueSeºüÃÀÈË, 0x9C3B291E, 0x19D64839);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x5638BBD4, 0x202CFBA6);
	insert(eMod::eJueSeÉñÌì±ø, 0x6C386770, 0x7EE974D8);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0xCE447B5D, 0xBF648097);
	insert(eMod::eJueSeÎèÌì¼§, 0xC8514E80, 0x1B09DC42);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x9795C606, 0x7A1B24A6);
	insert(eMod::eJueSeÓðÁéÉñ, 0x2AC04497, 0x710FE7AE);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0xFC11D6B9, 0xCDE65552);

	init(0x02, 0x8AC5514E, 0xD30116BE, 0x283DFE4A);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x67A36E68, 0x706510E6);
	insert(eMod::eJueSeåÐÒ£Éú, 0x768EDF10, 0xFE8577AF);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x8B7AA812, 0xFDA99F33);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xE57566B9, 0x9C62228A);
	insert(eMod::eJueSe»¢Í·¹Ö, 0x0967F9D7, 0xA8A1F820);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x03E53AEE, 0x7178B819);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x2CEB198B, 0x60F60818);
	insert(eMod::eJueSeºüÃÀÈË, 0xCA4D6280, 0x9397B696);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x535301E9, 0x01040DCF);
	insert(eMod::eJueSeÉñÌì±ø, 0x2B66FF5F, 0xD5265D71);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0xF73B4DFB, 0x94486AE7);
	insert(eMod::eJueSeÎèÌì¼§, 0xF181FCE0, 0x35CE9964);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x202C73C0, 0xAD7E4AA2);
	insert(eMod::eJueSeÓðÁéÉñ, 0x72C2B55B, 0xF154F434);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x5853C81C, 0xE7791076);

	init(0x03, 0xCB41BF07, 0x6D415352, 0x00002203);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x21B355E9, 0xA4E3E70A);
	insert(eMod::eJueSeåÐÒ£Éú, 0xE40D8CCA, 0x239E6F4B);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x9FCF1C80, 0x96CB5DAD);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xBCCF5B9F, 0xF924271F);
	insert(eMod::eJueSe»¢Í·¹Ö, 0x17E1BE56, 0x66199710);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xE606CF44, 0x85C8CB61);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xE1316912, 0x13836C3C);
	insert(eMod::eJueSeºüÃÀÈË, 0xC782279A, 0x85F13C8E);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x3E45D994, 0x45AA3A70);
	insert(eMod::eJueSeÉñÌì±ø, 0xA9273A82, 0x156F458C);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0xBC121DA7, 0x3F1C16AD);
	insert(eMod::eJueSeÎèÌì¼§, 0x648591A2, 0xB7D00874);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x566D1363, 0xBD40D2AA);
	insert(eMod::eJueSeÓðÁéÉñ, 0x3EAF325B, 0xEC330D95);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0xCECE8CCB, 0x0AD3B889);

	init(0x04, 0xE385373B, 0x71FE0155, 0x00002204);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x4F94EE73, 0x311319D4);
	insert(eMod::eJueSeåÐÒ£Éú, 0x59F5D107, 0x9B02DACD);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x7CC4957D, 0xC559F53B);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x533C2E0A, 0x678A0B46);
	insert(eMod::eJueSe»¢Í·¹Ö, 0xFD7DC837, 0x3CFFA8FB);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x214B0F5C, 0x3BCE9496);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xB101BE2C, 0x6A11FF53);
	insert(eMod::eJueSeºüÃÀÈË, 0x4A324D58, 0xC92FC27B);
	insert(eMod::eJueSeÁúÌ«×Ó, 0xEB2058A8, 0x03633E06);
	insert(eMod::eJueSeÉñÌì±ø, 0x0670BDCB, 0xDB9B2AB1);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x8E341679, 0x17BF2927);
	insert(eMod::eJueSeÎèÌì¼§, 0xCD3D730A, 0xCF55E0B7);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x4696C297, 0x4DDA9E16);
	insert(eMod::eJueSeÓðÁéÉñ, 0x4696C297, 0x4DDA9E16);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0xA182DC27, 0x7622A6F7);

	init(0x05, 0x2529E5A5, 0x51C03CD4, 0x00002205);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x931720F6, 0x10018213);
	insert(eMod::eJueSeåÐÒ£Éú, 0x922827BD, 0x56BF79BD);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x24B70479, 0x8D6CB5A3);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xB9086F2F, 0x68A693AB);
	insert(eMod::eJueSe»¢Í·¹Ö, 0x24B70479, 0x87EC3F8C);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xEC7EF5B6, 0x7ACD7927);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x8600A67C, 0x21E13319);
	insert(eMod::eJueSeºüÃÀÈË, 0x70798C6A, 0x8D6CB5A3);
	insert(eMod::eJueSeÁúÌ«×Ó, 0x3EA5725F, 0x557853AC);
	insert(eMod::eJueSeÉñÌì±ø, 0x023E3D96, 0x3BE540B8);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x8AC648C3, 0x1988F2F8);
	insert(eMod::eJueSeÎèÌì¼§, 0x0038AC9B, 0x642D3C0C);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x450A37CF, 0xE811CEFA);
	insert(eMod::eJueSeÓðÁéÉñ, 0xF81315D2, 0x2B6A4EDF);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x817384E9, 0xFBEF9BFD);

	init(0x06, 0xE8B35E96, 0x3949C769, 0x962EF053);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x89EB1142, 0x33C5809B);
	insert(eMod::eJueSeåÐÒ£Éú, 0xEF5DA6CA, 0xA8C6C156);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x6107DE71, 0x3357A656);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xFED4A4E3, 0x49ACB2C4);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x48A09582, 0x7C092E58);

	init(0x07, 0x72489CFD, 0x4D136355, 0x1E638EA4);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0xCC3A545C, 0x2226276D);
	insert(eMod::eJueSeåÐÒ£Éú, 0x19B20056, 0x15626E6B);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xAF692214, 0x51F9E921);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x0BDDE760, 0x9C25A705);
	insert(eMod::eJueSeÎ×Âù¶ù, 0xF1E8A488, 0xAE7C7B6C);

	init(0x08, 0x5BDBA7CB, 0x5CDC5A5E, 0xFE076F18);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x6B5FD57B, 0x33C2161A);
	insert(eMod::eJueSeåÐÒ£Éú, 0x36B75BA8, 0x4BC6AF6C);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x2A63DAA7, 0xAEB71298);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x90DB62B7, 0x2A7A5163);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x2D0F50A4, 0xF74F4B17);

	init(0x09, 0xCCBF24B8, 0xFE4B37F2, 0x00002209);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x55BF3F51, 0x981A3E15);
	insert(eMod::eJueSeåÐÒ£Éú, 0x5883A0AA, 0xF58357F5);
	insert(eMod::eJueSe·ÉÑàÅ®, 0x594370B0, 0xFD62AF1D);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xAC014E6E, 0x8F0501B3);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x85EA00C3, 0x82CFF9EB);

	init(0x0A, 0xEC4C09DF, 0x57B096DF, 0xF3EDF088);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x7836F4B4, 0xF0FF4B97);
	insert(eMod::eJueSeåÐÒ£Éú, 0xC19808D1, 0x068F5707);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xA65CDB93, 0xC9866359);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0xF07920F4, 0x05B30628);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x88C01E50, 0x030A88CA);

	init(0x0B, 0xA6966FD2, 0xCA8864D1, 0x00002211);

	insert(eMod::eJueSe½£ÏÀ¿Í, 0x42704629, 0x37F2D241);
	insert(eMod::eJueSeåÐÒ£Éú, 0x75185EFF, 0x64886829);
	insert(eMod::eJueSe·ÉÑàÅ®, 0xA4EC42DC, 0x70E3FA90);
	insert(eMod::eJueSeÓ¢Å®ÏÀ, 0x7F275D83, 0x6555242D);
	insert(eMod::eJueSeÎ×Âù¶ù, 0x68D6F317, 0x311350B8);

	init(0x0C, 0xBB906984, 0x02549904, 0x00002212);

	insert(eMod::eJueSe»¢Í·¹Ö, 0x2076021F, 0xC8A484B1);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xBB1BF88C, 0xF6C8EAA2);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x762E72D4, 0x11DB6F96);
	insert(eMod::eJueSeºüÃÀÈË, 0x70287479, 0xBCD552E5);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x7DF4E812, 0xD402D51B);

	init(0x0D, 0x742FBF19, 0x103FFB93, 0x00002213);

	insert(eMod::eJueSe»¢Í·¹Ö, 0x7D13F985, 0xE220A573);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x8831EB83, 0xC96B5DA2);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xF744B022, 0xB27B204F);
	insert(eMod::eJueSeºüÃÀÈË, 0x100ED72D, 0x35543AEA);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x979C563C, 0x8A337F9D);

	init(0x0E, 0x7F6FFC35, 0x716B5DC1, 0x00002214);

	insert(eMod::eJueSe»¢Í·¹Ö, 0xD3DEF3EE, 0xEF1CBA57);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xE02317F5, 0xEAD2C5EB);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xE55135E0, 0xA29A3A75);
	insert(eMod::eJueSeºüÃÀÈË, 0xDEB6652E, 0xD86FD443);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x7304B7A8, 0x8A46B173);

	init(0x0F, 0x1FED0CD8, 0xD8EB6880, 0x00002215);

	insert(eMod::eJueSe»¢Í·¹Ö, 0xDB11CCDA, 0x77CC4531);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0xB8D88944, 0xFA338B6F);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x48D5E6E3, 0x9A764074);
	insert(eMod::eJueSeºüÃÀÈË, 0x9365D100, 0xED742A60);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x79A9A8B6, 0x56F9E65B);

	init(0x10, 0xAB007164, 0x2E177381, 0x00002216);

	insert(eMod::eJueSe»¢Í·¹Ö, 0x00DE29E4, 0xD4701A5C);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x754D804C, 0x74616D41);
	insert(eMod::eJueSe¹Ç¾«Áé, 0x88176173, 0x5F689F16);
	insert(eMod::eJueSeºüÃÀÈË, 0x5C976C00, 0xDAC6BCA4);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0x78261D3A, 0xE1BC0656);

	init(0x11, 0xE7CB8205, 0x0E615404, 0x00002217);

	insert(eMod::eJueSe»¢Í·¹Ö, 0x0C2671A8, 0x4D2B29B0);
	insert(eMod::eJueSe¾ÞÄ§Íõ, 0x22DB5CB4, 0x0A8F525D);
	insert(eMod::eJueSe¹Ç¾«Áé, 0xBF7616BA, 0xE2511F44);
	insert(eMod::eJueSeºüÃÀÈË, 0x523E44B7, 0xAC238287);
	insert(eMod::eJueSeÉ±ÆÆÀÇ, 0xC8D54BF6, 0x76845DBD);

	init(0x12, 0xE0CB07C8, 0xD9D958E6, 0x53377FEF);

	insert(eMod::eJueSeÁúÌ«×Ó, 0xEE42F47D, 0x1FD8DE61);
	insert(eMod::eJueSeÉñÌì±ø, 0x5E213259, 0xD1FC1E6A);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0xD555D335, 0x919CFCFA);
	insert(eMod::eJueSeÎèÌì¼§, 0x8EBEFE46, 0x54047874);
	insert(eMod::eJueSeÓðÁéÉñ, 0x7A2FF293, 0xBBB78E1F);

	init(0x13, 0x8ED6D8CC, 0xC5D8F53D, 0x584C55F8);

	insert(eMod::eJueSeÁúÌ«×Ó, 0x857D8C9B, 0xFA34864C);
	insert(eMod::eJueSeÉñÌì±ø, 0x0A5927A6, 0x4F84A6BE);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x08DB9889, 0x6CB4B68A);
	insert(eMod::eJueSeÎèÌì¼§, 0xAD10E450, 0xE2A3A637);
	insert(eMod::eJueSeÓðÁéÉñ, 0x0ACD3305, 0x4C99775C);

	init(0x14, 0x8C575D26, 0x7B15590A, 0x6218BD0D);

	insert(eMod::eJueSeÁúÌ«×Ó, 0x6AEA969F, 0x1307A0C5);
	insert(eMod::eJueSeÉñÌì±ø, 0x18AF8DBF, 0x351E6A34);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x5612BE22, 0x775EFAC1);
	insert(eMod::eJueSeÎèÌì¼§, 0xD61FE699, 0x4672F3F2);
	insert(eMod::eJueSeÓðÁéÉñ, 0xE8317E09, 0xABB8CB82);

	init(0x15, 0x503F394B, 0x23BF657B, 0x00002221);

	insert(eMod::eJueSeÁúÌ«×Ó, 0x858A9444, 0x8B45918C);
	insert(eMod::eJueSeÉñÌì±ø, 0x0536E9A9, 0xFDA8E282);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x65EEA4CE, 0xB694385C);
	insert(eMod::eJueSeÎèÌì¼§, 0xE7FE2C6E, 0x346414D1);
	insert(eMod::eJueSeÓðÁéÉñ, 0x2126017B, 0x16E6F66C);

	init(0x16, 0xC4D118C5, 0xCBC6930A, 0x00002222);

	insert(eMod::eJueSeÁúÌ«×Ó, 0x9A720D2A, 0x594F8AA0);
	insert(eMod::eJueSeÉñÌì±ø, 0xF944D9DD, 0x648BFA3E);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x4C22777B, 0x79488756);
	insert(eMod::eJueSeÎèÌì¼§, 0x1E7D6B47, 0x7B45FCCA);
	insert(eMod::eJueSeÓðÁéÉñ, 0xAF91432D, 0xA3A19095);

	init(0x17, 0x1F01B8BE, 0xBDA4DDAB, 0x00002223);

	insert(eMod::eJueSeÁúÌ«×Ó, 0x6BF39B41, 0x6B2976AD);
	insert(eMod::eJueSeÉñÌì±ø, 0x065C9E27, 0xECFE2605);
	insert(eMod::eJueSeÐþ²Ê¶ð, 0x165F4907, 0xCCA5DB62);
	insert(eMod::eJueSeÎèÌì¼§, 0xDA2DF898, 0x03C81880);
	insert(eMod::eJueSeÓðÁéÉñ, 0x41F34937, 0xE80202D6);


	//////////////////////////////////////////////////////////////////////////
// 	insert(0x876E0D2B, 0x6088EDAC, 0x9AF401B2, 0xC541DCEA);
// 	insert(0xB5DFFC71, 0xC5B4FDEF, 0xCA6F2BB0, 0x7E3ADBB8);
// 	insert(0x10E2138C, 0x5CE41EF8);
// 	insert(0xD1A403AF, 0x44477FB0);
// 	insert(0xDDDECE7F, 0x0D060BA5);
// 	insert(0xC01D7558, 0x343087B3);
// 	insert(0x9CEA9EAE, 0xDA83EF16);
// 	insert(0x9BE76E48, 0x87935F6F);
// 	insert(0x089A78C7, 0x43FB6660); // ÔÆ, stand, not sit
// 	insert(0xBE8BCD59, 0x1EE017FE);
// 	insert(0xC745F2D8, 0x5570453A);
// 	insert(0x2283C8E4, 0x256B2E02);
// 	// wd6 ,,,,,,,,
// 	insert(0xF2CA5DC8, 0x5F8820C3);
// 	insert(0x9BDE4F15, 0xC5C3525E);
// 	insert(0x2D5B61B8, 0x366A7D69);
// 	insert(0x2D7948EF, 0xD9195AA8);
// 	insert(0x76C1A8E7, 0x8EF49CF4);
// 	insert(0x7CA62346, 0xF8383911);
// 	insert(0xBCDA9EDE, 0x55DCA86B);
// 	insert(0xC9086441, 0x76C33E92);
// 	insert(0xE814EFEF, 0x86E72B40);
// 	insert(0xEC31AF3B, 0x55E4FB5C);
// 	// ,,,
// 	insert(0x3A0E45CF, 0x6A7FC191); // jump
// 	insert(0xE28B984B, 0xCB8EE213); // jump
// 	insert(0x4BCC4EAD, 0x64C2E6D5); // jump
// 	insert(0xC6FF58F7, 0x989EFF24); // jump
// 	// wd7 ,,,,,,
// 	insert(0x81C7039C, 0x069D19C2);
// 	insert(0x0BBA930C, 0xF5B6264C);
// 	insert(0x81FB5DFA, 0x65FF3621);
// 	insert(0xFF82FDF9, 0xB86E0F22);
// 	insert(0x0EDBD872, 0x50C728CE);
// 	insert(0x5B1D9E29, 0xB8BA3A90);
// 	insert(0x6E344847, 0xA4A3288E);
// 	insert(0x57ADCE36, 0x065822B8);
// 	// ,,,,,,,
// 	insert(0x4E6BB145, 0x075DCD5B);// ½£ºÍ»­²¼
// 	insert(0xDD8A41FB, 0x0912E249);// ½£ºÍ»­²¼
// 	insert(0xD8AFA03F, 0xCA287671);// ½£ºÍ»­²¼
// 	insert(0x24AC4749, 0xF4AA5BF6);// ½£ºÍ»­²¼
// 	insert(0x70B8A5CE, 0xCAF276BE);// ½£ºÍ»­²¼
// 	insert(0xD81B9522, 0x0D4F9957);// ½£ºÍ»­²¼
// 	insert(0xEEB83B53, 0x4931C9EC); // ½£ºÍ»­²¼
// 	insert(0x0FF3F9E2, 0x2D6915E1); // ½£ºÍ»­²¼
// 	// ,
// 	insert(0x50985A64, 0x268E9022); // ÍÃ×Ó Ìø
// 	insert(0xAA0D7A33, 0xE5B94362); // ÍÃ×Ó Ìø
// 	// ,
// 	insert(0x9FA21058, 0xB1868DA4); // Óã Å¤
// 	insert(0xEBCD273D, 0x37196BDB); // Óã Å¤
// 	// wd8 ,,,,,,,
// 	// ,,,,,,,,,,,
// 	insert(0x3D33442E, 0xE8252C7B);
// 	insert(0xC7655C83, 0xAD4889BD);
// 	insert(0x91921EE5, 0xCB07D86C);
// 	insert(0x0773EB94, 0x23C8E5DE);
// 	insert(0x031FA9A3, 0x7AF47E11);
// 	insert(0x66B74D43, 0xBA4BB16F);
// 	insert(0xBB49CBB2, 0x8247EBC3);
// 	insert(0xABCFC98B, 0xF3EF410A);
// 	insert(0x2C490405, 0x61F5973D);
// 	insert(0x1FC05A17, 0x8549F030);
// 	insert(0x5504B0BE, 0xE8DD3341);
// 	insert(0xE5304126, 0xE8DB426B);
// 	insert(0xABA51F5B, 0x4F170FCA);
// 	insert(0x36BC39A8, 0x80C30B8B);
// 	insert(0x43E7BE1F, 0x77C1746C);
// 	insert(0x22FE1F3E, 0xA7A653F9);
// 	insert(0x5BCF5B7B, 0x0A6E3345);
// 	insert(0xB08E7973, 0xE1FC4981);
// 	insert(0xD2AC7841, 0xA8DB37FF);
// 	insert(0x0F74DAF0, 0x9BC89AC8);
// 	insert(0xCFBABB7C, 0x925DA881);
// 	// ,,,
// 	insert(0x9C565325, 0x30B204B2); // Ìø
// 	insert(0xD4CED8F7, 0x4391944D); // Õ¾
// 	insert(0x803D9F96, 0xA09A6760); // Õ¾
// 	insert(0x37D98B57, 0x93871E46); // Õ¾
// 	// ,,,
// 	insert(0xDBC73BA2, 0x0D9F322E, 0x8BC61B52, 0x85646C0B);
// 	insert(0xDBC73BA2, 0x0D9F322E, 0x333E35A3, 0xDC75D547);
// 	insert(0xA18A6B43, 0xF4EA8EA6, 0x8BC61B52, 0x85646C0B);
// 	insert(0xA18A6B43, 0xF4EA8EA6, 0x333E35A3, 0xDC75D547);
// 	insert(0x7F92EFAC, 0x8056E391, 0x35DC3843, 0x0CEBA8DC);
// 	// ,,
// 	insert(0xAB450DF7, 0xF2FA734B, 0x18893426, 0x45EE7F31); // ³µ·ò
// 	insert(0xAB450DF7, 0xF2FA734B, 0xB042878A, 0x7C5EE831); // ³µ·ò
// 	insert(0xAB450DF7, 0xF2FA734B, 0x09773FEB, 0x96AACB05); // ³µ·ò
// 	// ,,
// 	insert(0xD8346A08, 0xE160569F, 0xB042878A, 0x7C5EE831); // ³µ·ò
// 	insert(0xD8346A08, 0xE160569F, 0x18893426, 0x45EE7F31); // ³µ·ò
// 	insert(0xD8346A08, 0xE160569F, 0x09773FEB, 0x96AACB05); // ³µ·ò
// 	// wd9 ,,,,
// 	insert(0x02DDDA57, 0xF7F825D3);
// 	insert(0xF3C7A79F, 0xB9B1B192);
// 	insert(0xD87DC324, 0xE0C82908);
// 	insert(0x0DFEAF25, 0x3460E9A6);
// 	insert(0x32BE003F, 0x32BE003F); // Çò Õ¾
// 	// wdb ,,,,,,,,,,,,,
// 	insert(0x386B9BE9, 0x4C508BC0);
// 	insert(0x3EE240A2, 0xDBC190A1);
// 	insert(0xF0D76857, 0x62735411);
// 	insert(0x6E932BD6, 0xBDF58C53); // ÐÜÃ¨ ºÜ¸ß
// 	insert(0x6944F4CC, 0x3EAB6E78);
// 	insert(0x004C273C, 0x0670275F);
// 	insert(0x2939A157, 0x33E32357);
// 	insert(0xB78E7A06, 0xFC14DF68);
// 	insert(0x7453F531, 0xBC893B6A);
// 	insert(0x24F91023, 0x3D345627);
// 	insert(0x2306AD22, 0xC1FE3DEC);
// 	insert(0xE2C2EC0D, 0x95E724B0);
// 	insert(0xE551B917, 0xDC6D2831);
// 	insert(0xE9121B70, 0x3815C169);
// 	// wdc ,,,,,,
// 	// ,,,,,,,,,,,,,,,,,,,,,
// 	insert(0xC661EA6E, 0xFA419A20);
// 	insert(0x397A8C71, 0x92025504);
// 	insert(0x15521B1F, 0xD47915FB);
// 	insert(0x8E94D66F, 0x6770AAC9);
// 	insert(0x94FD9126, 0xFCB0282F);
// 	insert(0x2EDE08D6, 0x687324BB);
// 	insert(0xF040B821, 0x7E002D8D);
// 	insert(0x33BFF46F, 0x2D7EA2BA);
// 	insert(0xD8E8D600, 0x4771DEA3);
// 	insert(0xBAD36730, 0x429F6014);
// 	insert(0x0181CFC1, 0xC6FED2C7);
// 	insert(0x0492E64D, 0xC5C9968C);
// 	insert(0x6307DC3F, 0xD6CAD3F5);
// 	insert(0x07B8CDD0, 0x76EA6FF7);
// 	insert(0xCB51189B, 0xBB051DE9);
// 	insert(0x1349EE08, 0x0D8BB036);
// 	insert(0x7CC1F74C, 0xC0EF1F6A);
// 	insert(0x33668F97, 0xDD66EE9C);
// 	insert(0x8C542810, 0x31FC26C6);
// 	insert(0x6C70658E, 0x27858783);
// 	insert(0x9EA86797, 0x7B745DE4);
// 	insert(0x31C69560, 0xD3DAA128);
// 	insert(0x0499FDCB, 0x01128FED);
// 	insert(0x420A35DB, 0xF809B4D1);
// 	insert(0xE47361C0, 0xEB15D736);
// 	insert(0xF260474D, 0x804119A2);
// 	insert(0x40FFF86D, 0x1CB3928D);
// 	insert(0xDFE5DB81, 0xF7495B4A);
// 	insert(0x13F76327, 0x3DB2E7AC);
// 	insert(0x0B5E7B2A, 0x1C5C2571, 0x9966DA4E, 0x356C2295);
// 	insert(0x0B5E7B2A, 0x1C5C2571, 0x7BC51FC9, 0x79BA815E);
// 	insert(0x33BFF46F, 0x2D7EA2BA); // ºÉ»¨ Õ¾
// 	insert(0x8640CC00, 0x6B404CD1); // ÇàÍÜ Ìø
// 	insert(0x52282FC2, 0xB19DF18D);
// 	insert(0x1760AFAE, 0x1760AFAE); // ºùÂ« ¸ß
// 	insert(0x7F4B8E3C, 0x06880DBF);
}

const txtZuoqi::sMasterPos& txtZuoqi::getMasterStands()
{
	return txtXiangrui::getInstance()->_masterStands;
}

const txtZuoqi::sMasterPos& txtZuoqi::getMasterWalks()
{
	return txtXiangrui::getInstance()->_masterWalks;
}

