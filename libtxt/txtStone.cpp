#include "txtStone.h"

ccc_txt_instance_cpp(txtStone);


std::string txtStone::sStone::toString(const std::string& str /*= " "*/)const
{
	return txtStone::toString(pro) + str + cc::toString(value);
}


std::string txtStone::toString(eProPerty pro)
{
	switch (pro)
	{
	case eProPerty::伤害: return "伤害";
	case eProPerty::命中: return "命中";
	case eProPerty::防御: return "防御";
	case eProPerty::魔法: return "魔法";
	case eProPerty::灵力: return "灵力";
	case eProPerty::速度: return "速度";
	case eProPerty::气血: return "气血";
	case eProPerty::力量: return "力量";
	case eProPerty::敏捷: return "敏捷";
	case eProPerty::体质: return "体质";
	case eProPerty::魔力: return "魔力";
	case eProPerty::耐力: return "耐力";
	case eProPerty::火抗: return "火抗";
	case eProPerty::雷抗: return "雷抗";
	case eProPerty::土抗: return "土抗";
	case eProPerty::水抗: return "水抗";
	case eProPerty::躲避: return "躲避";
	case eProPerty::法伤: return "法伤";
	case eProPerty::法防: return "法防";
	case eProPerty::法结: return "法术结果";
	case eProPerty::物结: return "物理结果";
	case eProPerty::回复: return "气血回复";
	case eProPerty::愤怒: return "愤怒";
	case eProPerty::命率: return "命中率";
	}
	return "error";
}
