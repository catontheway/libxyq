#include "_global.h"
#include "_txt.h"


vector<int> cAI::finds(int user, int start, int end, eFindType e /* = eFindType::None */, const function<bool(int)>& condition /* = nullptr */, int checkState /* = -1 */, bool checkDie /* = true */, bool checkHide /* = true */)
{
	auto con = condition ? condition : [](int){return true; };
	vector<int> ids;
	for (int i = start; i < end; ++i)
	{
		auto& list = g_pMainState->m_FightWorkList[i];
		if (!list.isExist)
		{
			continue;
		}
		if (checkDie && !(e == eFindType::Dying || e == eFindType::Relifeable) && list.CheckDie())
		{
			continue;
		}
		if (checkState >= 0 && list.m_pObj->CheckHaveState(checkState))
		{
			continue;
		}
		if (checkHide &&  e != eFindType::Hide && !See(user, i))
		{
			continue;
		}
		if (!con(i))
		{
			continue;
		}
		if (e == eFindType::Hp30)
		{
			cPropertyData* data = list.m_pObj->getPropertyData();
			if (!isHpLessThan(data, 30))
			{
				continue;
			}
			if (data->Ghost.d1 > 0)
			{
				continue;
			}
		}
		if (e == eFindType::Hp70)
		{
			cPropertyData* data = list.m_pObj->getPropertyData();
			if (!isHpLessThan(data, 70))
			{
				continue;
			}
			if (data->Ghost.d1 > 0)
			{
				continue;
			}
		}
		else if (e == eFindType::HpNotFull)
		{
			cPropertyData* data = list.m_pObj->getPropertyData();
			if (data->m_HP == data->HPMax.GetData())
			{
				continue;
			}
		}
		else if (e == eFindType::Mp0)
		{
			cPropertyData* data = list.m_pObj->getPropertyData();
			if (data->m_MP > 0)
			{
				continue;
			}
			if (data->isHadPetSkill((int)eSkillPassive::冥思ms) || data->isHadPetSkill((int)eSkillPassive::高级冥思ms))
			{
				continue;
			}
		}
		else if (e == eFindType::MpSeal)
		{
			if (list.m_pObj->getPetData())
			{
				continue;
			}
		//	const auto& mp = list.m_pObj->getPcData()->m_MengPaiID;
			if (!isMpSeal(list.m_pObj->getPcData()))
			{
				continue;
			}
		}
		else if (e == eFindType::MpCure)
		{
			if (list.m_pObj->getPetData())
			{
				continue;
			}
		//	const auto& mp = list.m_pObj->getPcData()->m_MengPaiID;
			if (!isMpCure(list.m_pObj->getPcData()))
			{
				continue;
			}
		}
		else if (e == eFindType::MpPhy)
		{
			if (list.m_pObj->getPetData())
			{
				if (!isAtkFromPoint(list.m_pObj->getPetData()))
				{
					continue;
				}
			}
			if (list.m_pObj->getPcData())
			{
			//	const auto& mp = list.m_pObj->getPcData()->m_MengPaiID;
				if (!isMpPhy(list.m_pObj->getPcData()))
				{
					continue;
				}
			}

		}
		else if (e == eFindType::MpMag)
		{
			if (list.m_pObj->getPetData())
			{
				if (!isMagFromPoint(list.m_pObj->getPetData()))
				{
					continue;
				}
			}
			if (list.m_pObj->getPcData())
			{
			//	const auto& mp = list.m_pObj->getPcData()->m_MengPaiID;
				if (!isMpMag(list.m_pObj->getPcData()))
				{
					continue;
				}
			}

		}
		else if (e == eFindType::Dying)
		{
			if (!list.CheckDie())
			{
				continue;
			}
		}
		else if (e == eFindType::Relifeable)
		{
			if (!list.CheckDie())
			{
				continue;
			}
			if (list.m_pObj->getPetData())
			{
				continue;
			}
			cPropertyData* data = list.m_pObj->getPropertyData();
			if (data->Ghost.d1 > 0)
			{
				continue;
			}
			if (list.m_pObj->CheckHaveState((int)eSkill::锢魂术))
			{
				continue;
			}
			if (list.m_pObj->CheckHaveState((int)eSkill::死亡召唤))
			{
				continue;
			}
		}
		else if (e == eFindType::Sealable)
		{
			cPropertyData* d = list.m_pObj->getPropertyData();
			if (d->LiveRestoreRate > 0x40 ||
				d->HitRateOfSeal.d2 > 0x80 ||
				d->Ghost.d1 > 0)
			{
				continue;
			}
			const auto& fd = d->m_FightData;
			if (/*fd.cannotAll ||*/
				fd.chaos混乱反间 ||
				fd.cannotMagic || 			
				fd.cannotAttack
				)
			{
				continue;
			}
		}
		else if (e == eFindType::UnSeal)
		{
			cPropertyData* d = list.m_pObj->getPropertyData();
			if (d->LiveRestoreRate > 0x40 ||
				d->HitRateOfSeal.d2 > 0x80 ||
				d->Ghost.d1 > 0)
			{
				continue;
			}

			const auto& fd = list.m_pObj->getPropertyData()->m_FightData;
			const auto& pet = list.m_pObj->getPetData();
			if (pet && fd.cannotMagic && isAtkFromPoint(pet))
			{
				continue;
			}
			if (pet && fd.cannotAttack && isMagFromPoint(pet))
			{
				continue;
			}
// 			vector<int> ms, m2s, ps, bs;
// 			bool phySkill = g_pMainState->m_AI.isHadPetSkill(list.m_pObj->getPetData(), bs, ps, ms, m2s);
			if (fd.chaos混乱反间 || fd.cannotMagic)
			{
				if (fd.cannotMagic == 1 && isState(list.m_pObj, { 0, 7, 142 }))
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else if (e == eFindType::UnSealAndPosion)
		{
			cPropertyData* d = list.m_pObj->getPropertyData();
			if (d->LiveRestoreRate > 0x40 ||
				d->HitRateOfSeal.d2 > 0x80 ||
				d->Ghost.d1 > 0)
			{
				continue;
			}

			const auto& fd = list.m_pObj->getPropertyData()->m_FightData;
			const auto& pet = list.m_pObj->getPetData();
			if (pet && fd.cannotMagic && isAtkFromPoint(pet))
			{
				continue;
			}
			if (pet && fd.cannotAttack && isMagFromPoint(pet))
			{
				continue;
			}
			if (isState(list.m_pObj, { 50, 103, 122, 198 }) ||
			//	fd.cannotAll ||
				fd.chaos混乱反间 ||
				fd.cannotMagic
			//	|| fd.cannotAttack
				)
			{
				if (fd.cannotMagic == 1 && isState(list.m_pObj, { 0, 7, 142 }))
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else if (e == eFindType::Hide)
		{
			if (list.m_pObj->getPropertyData()->Hide.d1 == 0)
			{
				continue;
			}
		}
		ids.push_back(i);
	}

	function<bool(int, int)> cb = nullptr;
	switch (e)
	{
		// 	case cAI::eFindType::None:
		// 		break;
	case eFindType::Hp30:
	case eFindType::Hp70:
	case eFindType::HpNotFull:
	case eFindType::HpRateMin:
		cb = [&](int a, int b)
		{
			setData(a, b);
			return s_data1->m_HP * 100 / s_data1->HPMax.GetData() < s_data2->m_HP * 100 / s_data2->HPMax.GetData();
		};
		break;
	case eFindType::Mp0:
	case eFindType::MpMin:
		cb = [&](int a, int b)
		{
			setData(a, b);
			return s_data1->m_MP * 100 / s_data1->MPMax.GetData() < s_data2->m_MP * 100 / s_data2->MPMax.GetData();
		};
		break;
	case eFindType::ManaMin:
		cb = [&](int a, int b)
		{
			setData(a, b);
			return s_data1->Mana.GetData() < s_data2->Mana.GetData();
		};
		break;
		// 	case cAI::eFindType::MpSeal:
		// 		break;
		// 	case cAI::eFindType::MpCure:
		// 		break;
		// 	case cAI::eFindType::MpPhy:
		// 		break;
		// 	case cAI::eFindType::MpMag:
		// 		break;
		// 	case cAI::eFindType::Dying:
		// 		break;
		// 	case cAI::eFindType::Sealable:
		// 		break;
		// 	case cAI::eFindType::Hide:
		// 		break;
	default:
		cb = [](int a, int b)
		{
			return g_pMainState->m_FightWorkList[a]._turnOfSpeed < g_pMainState->m_FightWorkList[a]._turnOfSpeed;
		};
		break;
	}

	if (cb)
	{
		std::sort(ids.begin(), ids.end(), cb);
	}
	return ids;
}

