#include "_global.h"
#include "_txt.h"


//////////////////////////////////////////////////////////////////////////
static const sPetData& getPetData(int& idx, int& id)
{
	static map<int, vector<int>> s_petMap;
	static vector<int> s_tlvs = { 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 125, 135, 145, 155, 165, 175 };
	int size = s_tlvs.size();
	const auto& ps = g_pMainState->m_PetDataManager.m_PetList;
	if (s_petMap.empty())
	{
		for (const auto& e : s_tlvs)
		{
			s_petMap.insert(make_pair(e, vector<int>()));
		}
		forv(ps, i)
		{
			if (std::find(s_tlvs.begin(), s_tlvs.end(), ps[i].m_LvTake) == s_tlvs.end())
			{
				continue;
			}
			s_petMap.find(ps[i].m_LvTake)->second.push_back(ps[i].m_ID);
		}
	}

	const auto& ids = s_petMap.at(s_tlvs[idx %= size]);
	return ps[ids[id %= ids.size()]];
}

static const cPet* getPet(int& idx)
{
	const auto& ps = g_pMainState->m_InterFaceBuyPet.m_Item;
	if (ps.empty())
	{
		return nullptr;
	}
	return ps[idx %= ps.size()];
}

static int comzz(int z1, int z2)
{
	if (z1 == z2)
	{
		return z1;
	}
	int z = (z1 + z2) / 2;
	int zmin = min(z1, z2);
	int zmax = max(z1, z2);
	return z + (rand() % (zmax - z + 1)) - (rand() % (z - zmin + 1));
}

static sZiZhi comzz(const sZiZhi& z1, const sZiZhi& z2)
{
	sZiZhi z;
	z.atk = comzz(z1.atk, z2.atk);
	z.def = comzz(z1.def, z2.def);
	z.hp = comzz(z1.hp, z2.hp);
	z.mag = comzz(z1.mag, z2.mag);
	z.speed = comzz(z1.speed, z2.speed);
	z.avoid = comzz(z1.avoid, z2.avoid);
	z.grow = comzz(z1.grow, z2.grow);
	return z;
}


static cPet* comPet(cPet* p1, cPet* p2)
{
	cPet* pet = new cPet;
	auto& p = pet->m_PetData;
	for (int i = p1->m_PetData.m_NumofBBSkill - 1; i >= 0; --i)
	{
		p.AddSkill(p1->m_PetData.m_petSkills[i]->m_Id);
	}
	for (int i = p2->m_PetData.m_NumofBBSkill - 1; i >= 0; --i)
	{
		p.AddSkill(p2->m_PetData.m_petSkills[i]->m_Id);
	}

	vector<sSkill*> sks;
	for (int i = p.m_NumofBBSkill - 1; i >= 0; --i)
	{
		sks.push_back(p.m_petSkills[i]);
	}

	forr(sks, i)
	{
		int size = sks.size();
		if (rand() % 100 < (45 + size))
		{
			sks.erase(sks.begin() + (rand() % size));
		}
	}

	forr(sks, i)
	{
		p.m_petSkills[i] = sks[i];
	}
	p.m_NumofBBSkill = sks.size();
	p.m_ZiZhi = comzz(p1->m_PetData.m_ZiZhi, p2->m_PetData.m_ZiZhi);
	return pet;
}

bool uiComPet::Init()
{
	if (!cInterfaceFather::Init())
	{
		return false;
	}
	loadBack(0xA47BE3B8);

	sChild blv1(&g_pMainState->m_Button2, " ", 10, 250);
	sChild blv2(&g_pMainState->m_Button2, " ", 225, 250);
	sChild bname1(&g_pMainState->m_Button4, " ", 10 + 50, 250);
	sChild bname2(&g_pMainState->m_Button4, " ", 225 + 50, 250);

	sChild b301(&g_pMainState->m_Button4, " ", 55, 10);
	sChild b302(&g_pMainState->m_Button4, " ", 230, 10);

	blv1.tag = bname1.tag = b301.tag = 0;
	blv2.tag = bname2.tag = b302.tag = 1;
	blv1.onClick = blv2.onClick = [&](const sChild* c)
	{
		if (_isBB30s[c->tag])
		{
			++_takelvs[c->tag];
			initShow();
		}
	};
	bname1.onClick = bname2.onClick = [&](const sChild* c)
	{
		if (_isBB30s[c->tag])
		{
			++_idxs[c->tag];
		}
		else
		{
			++_idx2s[c->tag];
		}
		initShow();
	};

	b301.onClick = b302.onClick = [&](const sChild* c)
	{
		_isBB30s[c->tag] = !_isBB30s[c->tag];
		initShow();
	};


	_tLvs[0] = (cText*)blv1.ptr2;
	_tLvs[1] = (cText*)blv2.ptr2;
	_tNames[0] = (cText*)bname1.ptr2;
	_tNames[1] = (cText*)bname2.ptr2;
	_tBB30s[0] = (cText*)b301.ptr2;
	_tBB30s[1] = (cText*)b302.ptr2;
	_idxs[0] = _idxs[1] = _takelvs[0] = _takelvs[1] = _idx2s[0] = _idx2s[1] = 0;
	_isBB30s[0] = _isBB30s[1] = true;

	sChild shadow1(g_pMainState->m_Shadow.m_NowID, 85, 200);
	sChild shadow2(g_pMainState->m_Shadow.m_NowID, 270, 200);
	shadow1.checkon = shadow2.checkon = false;
	addChild(shadow1);
	addChild(shadow2);
	for (int i = 0; i < 4; ++i)
	{
		sChild was1(g_pMainState->m_Button2.m_NowID, 85, 200);
		sChild was2(g_pMainState->m_Button2.m_NowID, 270, 200);
		_wass[0][i] = (cWasFile*)was1.ptr;
		_wass[1][i] = (cWasFile*)was2.ptr;
		_wass[0][i]->SetStatic(false);
		_wass[1][i]->SetStatic(false);
		was1.checkon = was2.checkon = false;
		addChild(was1);
		addChild(was2);
	}

	// 	sChild was1(g_pMainState->m_Button2.m_NowID, 85, 200);
	// 	sChild was2(g_pMainState->m_Button2.m_NowID, 270, 200);
	// 	_wass[0] = (cWasFile*)was1.ptr;
	// 	_wass[1] = (cWasFile*)was2.ptr;
	// 	was1.checkon = was2.checkon = false;
	// 	_wass[0]->SetStatic(false);
	// 	_wass[1]->SetStatic(false);



	addChild(blv1);
	addChild(blv2);
	addChild(bname1);
	addChild(bname2);
	addChild(b301);
	addChild(b302);
	// 	addChild(was1);
	// 	addChild(was2);

	sChild btn(&g_pMainState->m_Button2, "合", 155, 250);
	btn.onClick = [&](const sChild* c)
	{
		forv(_pets, i)
		{
			if (_pets[i].GetData()->m_LvTake == 0 || _pets[i].GetData()->m_LvTake == 115)
			{
				g_pMainState->m_Tags.Add("不可以");
				return;
			}
		}
		if (_isBB30s[0] && _isBB30s[1] && _takelvs[0] == _takelvs[1] && _idxs[0] == _idxs[1])
		{
			g_pMainState->m_Tags.Add("不可以");
			return;
		}

		if (!_isBB30s[0] && !_isBB30s[1] && _idx2s[0] == _idx2s[1])
		{
			g_pMainState->m_Tags.Add("不可以");
			return;
		}

		auto& ps = g_pMainState->m_InterFaceBuyPet.m_Item;
		if (_isBB30s[0] && _isBB30s[1] && ps.size() >= 20)
		{
			g_pMainState->m_Tags.Add("仓库已满");
			return;
		}

		cPet* pet = comPet(&_pets[0], &_pets[1]);
		pet->SetData(_pets[(rand() % 100 < 50) ? 0 : 1].GetData());

		auto& p = pet->m_PetData;
		p.modeid = pet->GetData()->m_ID;
		p.m_Name = pet->GetData()->m_Name;
		p.m_Lv = 0;
		p.PointRemain = cct::PointRemian;
		p.setPointAfterLv(sAddPoint(), false);
		p.apply();
		p.FillHpMp();

		if (!_isBB30s[0] && (!_isBB30s[1]))
		{
			int imin = min(_idx2s[0], _idx2s[1]);
			int imax = max(_idx2s[0], _idx2s[1]);
			SAFE_DELETE(ps[imax]);
			ps.erase(ps.begin() + imax);

			SAFE_DELETE(ps[imin]);
			ps.erase(ps.begin() + imin);
		}
		else
		{
			forr(_pets, i)
			{
				if (!_isBB30s[i])
				{
					SAFE_DELETE(ps[_idx2s[i]]);
					ps.erase(ps.begin() + _idx2s[i]);
				}
			}
		}
		g_pMainState->m_InterFaceBuyPet.addPet(pet);
		g_pMainState->m_ChaKan.Set(pet);
		g_pMainState->m_ChaKan.OnOff(true);
		g_pMainState->m_Tags.Add("存入仓库");
		initShow();
		cct::autoSave();
	};
	addChild(btn);

	forr(_petSkills, i)
	{
		_petSkills[i].Init();
	}
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool uiComPet::initShow()
{
	int kkk = 0;
	if (!getPet(kkk))
	{
		_isBB30s[0] = _isBB30s[1] = true;
	}
	forr(_pets, i)
	{
		if (_isBB30s[i])
		{
			_pets[i].SetData((sPetData*)&getPetData(_takelvs[i], _idxs[i]));
			cPetData* pd = &_pets[i].m_PetData;
			pd->m_Name.clear();
			pd->Load(_pets[i].GetData()->m_ID, true, true);
			_tBB30s[i]->SetString(toString("胚子%d", _pets[i].GetData()->m_LvTake));
			//			_tNames[i]->SetString(_pets[i].m_PetData.m_Name);
		}
		else
		{
			_pets[i] = *(cPet*)getPet(_idx2s[i]);
			_tBB30s[i]->SetString(toString("仓库%d", _idx2s[i]));
			//			_tNames[i]->SetString(_pets[i].m_PetData.m_Name);
		}
		_tNames[i]->SetString(_pets[i].GetData()->m_Name);
		const auto& pd = _pets[i].GetData();
		_tLvs[i]->SetString(pd->m_LvTake);
		_petSkills[i].UpdateData(&_pets[i].m_PetData, false);


		//		_wass[i]->Load(pd->m_ModelActs[0].m_fstand);

		vector<ulong> picid;
		array<sChangeColorData*, 4> pranse;
		_pets[i].GetID(POS_STAND, picid);
		_pets[i].GetRanse(pranse);

		for (int k = 0; k < 4; ++k)
		{
			_wass[i][k]->Free();
		}

		for (int k = 0; k < picid.size(); ++k)
		{
			_wass[i][k]->Load(picid[k], pranse[k]);
		}
	}
	return true;
}

bool uiComPet::Move(int x, int y)
{
	_petSkills[0].Move(x - 207, y - 80);
	_petSkills[1].Move(x + m_Back.GetWidth(), y - 80);
	return cInterfaceFather::Move(x, y);
}

bool uiComPet::Show(cCanvas* pCanvas)
{
	forr(_petSkills, i)
	{
		_petSkills[i].Show(pCanvas);
	}
	return cInterfaceFather::Show(pCanvas);
}