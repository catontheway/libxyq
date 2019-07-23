#include "txtEasy.h"

ccc_txt_instance_cpp(txtEasy)

void txtEasy::initIdx()
{
	_idx = -1;
}

void txtEasy::insert(sTable& table, ulong uid)
{
	table.insert(std::make_pair(++_idx, uid));
}

const txtEasy::sTable& txtEasy::getChats()
{
	if (_tableChat.empty())
	{
		initIdx();
		insertChat(0x4D3D1188);
		insertChat(0x6E7A8E8F);
		insertChat(0x403105F2);
		insertChat(0xD3C23894);
		insertChat(0xEDD63AB1);
		insertChat(0xC8AA7848);
		insertChat(0xA5D718B1);
		insertChat(0xE0C6F0D3);
		insertChat(0x572F2A4D);
		insertChat(0xA1E13E27);
		insertChat(0xB2F4A198);
		insertChat(0xEDEBCFCF);
		insertChat(0x3B3D19C0);
		insertChat(0x9EEC6DE4);
		insertChat(0x1B1B8326);
		insertChat(0x525FCCF9);
		insertChat(0xAD9E8BAD);
		insertChat(0xE9A1E271);
		insertChat(0x1C7C95C4);
		insertChat(0x1500E768);
		insertChat(0x30615DBC);
		insertChat(0x3694C64F);
		insertChat(0xFD438646);
		insertChat(0x4FAD347C);
		insertChat(0x743AF90F);
		insertChat(0x853F3BC9);
		insertChat(0xD6436048);
		insertChat(0x74E0F5FA);
		insertChat(0x8E0063E2);
		insertChat(0x5BA9CF5E);
		insertChat(0xE8E08FA9);
		insertChat(0x888536BF);
		insertChat(0xBEDE7D41);
		insertChat(0xF06B6B9E);
		insertChat(0x58FAA400);
		insertChat(0x270D5C71);
		insertChat(0xACE9C474);
		insertChat(0xBE3150EE);
		insertChat(0x11C5EA40);
		insertChat(0x73F3BF9D);
		insertChat(0xCCD6B7E8);
		insertChat(0x66D0E07C);
		insertChat(0x9A8BFB91);
		insertChat(0xCA47B474);
		insertChat(0x590CAA9B);
		insertChat(0x4E20C2E6);
		insertChat(0x44B657A9);
		insertChat(0x978F8F8A);
		insertChat(0x522BC68F);
		insertChat(0xA8A9B15D);
		insertChat(0xE53DE56A);
		insertChat(0xE88B5354);
		insertChat(0x0417C932);
		insertChat(0xC699AB3E);
		insertChat(0x19CA9706);
		insertChat(0xFCD58523);
		insertChat(0xCD8F0AD6);
		insertChat(0x978B9123);
		insertChat(0x0E658C4C);
		insertChat(0x12BE1C3E);
		insertChat(0x85AC8CCB);
		insertChat(0x707ABF50);
		insertChat(0x58C9FAB0);
		insertChat(0xAA7B3B42);
		insertChat(0xF2FBDA6E);
		insertChat(0xFC4215EC);
		insertChat(0xD086F684);
		insertChat(0xFCCAA9B5);
		insertChat(0xE5FF2DE2);
		insertChat(0x87621B9F);
		insertChat(0xCDC95381);
		insertChat(0x396C4E03);
		insertChat(0xB06B70C0);
		insertChat(0xADE1576E);
		insertChat(0xFB472367);
		insertChat(0xEDA67286);
		insertChat(0x15CA26D9);
		insertChat(0xDC9C1E87);
		insertChat(0xB5786848);
		insertChat(0xC2A7A47D);
		insertChat(0x7EEB3422);
		insertChat(0x8F20BE2E);
		insertChat(0xA1E7B566);
		insertChat(0x11729962);
		insertChat(0xEF498C25);
		insertChat(0xF95512DC);
		insertChat(0xF5509B1C);
		insertChat(0x7F869E1E);
		insertChat(0x107CF5F3);
		insertChat(0xF45DCF6A);
		insertChat(0x99AFED62);
		insertChat(0xC8BBEEA3);
		insertChat(0x225ECF82);
		insertChat(0xD5C14B62);
		insertChat(0xA8BC861D);
		insertChat(0x7229A70C);
		insertChat(0x4FF6E07A);
		insertChat(0xDF1F56AC);
		insertChat(0x488EBBD6);
		insertChat(0x4806AE3B);
		insertChat(0x09574327);
		insertChat(0x7A9F28C7);
		insertChat(0xB7E060C1);
		insertChat(0x5887677B);
		insertChat(0x1C0BCE22);
		insertChat(0xAAFBD630);
		insertChat(0xE4994B6A);
		insertChat(0xACA32B8F);
		insertChat(0xED5B5996);
		insertChat(0x65D48DBF);
		insertChat(0x91EAD158);
		insertChat(0x50BF3749);
		insertChat(0x383F3815);
		insertChat(0x445A8BA0);
		insertChat(0xD6252D94);
		insertChat(0x247121AF);
		insertChat(0x64A8BD13);
		insertChat(0x79C2D9F2);
		insertChat(0xD753949E);
		insertChat(0x57648A83);
	}
	return _tableChat;
}


const txtEasy::sTable& txtEasy::getTops()
{
	if (_tableTop.empty())
	{
		initIdx();
	//	insertTop(0x3D3AA29E); // 战斗
		insertTop(0xB77BBE55);
	//	insertTop(0xA7B20C0F); // 任务
		insertTop(0x6C27FCF1);
		insertTop(0x474F2EE1);
		insertTop(0xD379BEFA);
		insertTop(0xA7E1ABEA);
	}
	return _tableTop;
}



const txtEasy::sTable& txtEasy::getTransmits()
{
	if (_tableTransmit.empty())
	{
		initIdx();
		insertTransmit(0x70274B36);
		insertTransmit(0x176A564C);
		insertTransmit(0xACFC4A18);
		insertTransmit(0x1544B91F);
		insertTransmit(0x03313AA0);
		insertTransmit(0xF37C270D);
		insertTransmit(0xE2C2C735);
		insertTransmit(0x90D8195A);
		insertTransmit(0x4EE48F77);
		insertTransmit(0xE633635B);
		insertTransmit(0x3D302BBC);
		insertTransmit(0x8B739012);
		insertTransmit(0xD35327B8);
		insertTransmit(0xCFCA19E0);
		insertTransmit(0xB43AF865);
	}
	return _tableTransmit;
}



const txtEasy::sTable& txtEasy::getDazzles()
{
	if (_tableDazzle.empty())
	{
		std::vector<ulong> dazzlMap
		{
			0x6F1A7860,
			0x35522533,
			// 大的
			0xE328B499,
			0x654EAD9E,
		};
		for (int k = 0; k < dazzlMap.size(); ++k)
		{
			_tableDazzle.insert(std::make_pair(k, dazzlMap[k]));
		}
	}
	return _tableDazzle;
}


const txtEasy::sTable& txtEasy::getFoots()
{
	if (_tableFoot.empty())
	{
		std::vector<ulong> footMap =
		{
			0x1B62DAF4, 
			0xF2848531, 
			0x15D8A5CC, 
			0xFFED8401, 
			0xE7B37A0B, 
			0x27235A2C, 
			0xE7B85C54, 
		};
		for (int k = 0; k < footMap.size(); ++k)
		{
			_tableFoot.insert(std::make_pair(k, footMap[k]));
		}
	}
	return _tableFoot;
}





const txtEasy::sTable& txtEasy::getMagicWhat()
{
	if (_tableMagicWhat.empty())
	{
		std::vector<ulong> temps =
		{
			0xE5F52524, 
			0x53E46986, 
			0x0B8C9232, 
			0x5AE22A40, 
			0x6D4CCE5A, 
			0x53A253C7, 
			0xFB90D9B1, 
			0xA114D468, 
			0x139AF9A1, 
			0xE99401D7, 
			0xF2822C9D, 
			0x14E3155E, 
			0x6697B50E, 
			0xD69CAE82, 
			0xF66070DF, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicWhat.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicWhat;
}

// const txtEasy::sTable& txtEasy::getMagicFont()
// {
// 	if (_tableMagicFont.empty())
// 	{
// 		std::vector<ulong> temps =
// 		{
// 			0xC13CB3DD, 0xF08C56E8, 0x0F28E2DC, 0x3DD71DF3
// 		};
// 		for (int k = 0, size = temps.size(); k < size; ++k)
// 		{
// 			_tableMagicFont.insert(std::make_pair(k, temps[k]));
// 		}
// 	}
// 	return _tableMagicFont;
// }

const txtEasy::sTable& txtEasy::get_magic()
{
	if (_table_magic.empty())
	{
		std::vector<ulong> temps =
		{
			0x2F02120B, 
			0x2BAFA21D, 
			0xF001A7B5, 
			0xCE33E201, 
			0xDA312397, 
			0x057B7209, 
			0x2698E079, 
			0xE241D087, 
			0xC9BCA454, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_table_magic.insert(std::make_pair(k, temps[k]));
		}
	}
	return _table_magic;
}

const txtEasy::sTable& txtEasy::getMagic()
{
	if (_tableMagic.empty())
	{
		std::vector<ulong> temps =
		{
			0x734BBB81, 
			0x7CD9C342, 
			0x5D294555, 
			0x87AE3947, 
			0x80D1CFB9, 
			0xEFDFC9DD, 
			0xDB00E6D8, 
			0x3B86B284, 
			0xDDDEC47C, 
			0xDBBD355B, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagic.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagic;
}

const txtEasy::sTable& txtEasy::getMagicMove()
{
	if (_tableMagicMove.empty())
	{
		std::vector<ulong> temps =
		{
			0xDBC405D9, 
			0x9E4E9755, 
			0x63AD9368, 
			0x3D0C6FF1, 
			0x697E01E6, 
			0xC4FABE4C, 
			0x9F9F85EF, 
			0x83F5033C, 
			0x0BE97E00, 
			0x6044E21A, 
			0xCE4013A9, 
			0xA04039FD, 
			0x154CD236, 
			0xC481FD16
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicMove.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicMove;
}

const txtEasy::sTable& txtEasy::getMagicImpact()
{
	if (_tableMagicImpact.empty())
	{
		std::vector<ulong> temps =
		{
			0xB1822745, 
			0x83020DAE, 
			0x21FAE73F, 
			0x82C9074A, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicImpact.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicImpact;
}

const txtEasy::sTable& txtEasy::getMagicState()
{
	if (_tableMagicState.empty())
	{
		std::vector<ulong> temps =
		{
			0x09DA386B, 
			0xB512CBEB, 
			0xCB9CBB52, 
			0x56E05B32, 
			0x20FCCE94, 
			0x1FDF16A3, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicState.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicState;
}

const txtEasy::sTable& txtEasy::getMagicStateUnkown()
{
	if (_tableMagicStateUnkown.empty())
	{
		std::vector<ulong> temps =
		{
			0x3EA6C9EB, 
			0xEC3149BB, 
			0x619B686C, 
			0x155C6908, 
			0x61CB13B5, 
			0x1350671F, 
			0xCDE5D209, 
			0x0ACA5045, 
			0x69180378, 
			0xE447F922, 
			0xE3BB9D50, 
			0xDCCB25E2, 
			0xD2578505, 
			0x0EEC978E, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicStateUnkown.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicStateUnkown;
}

// const txtEasy::sTable& txtEasy::getMagicGiveup()
// {
// 	if (_tableMagicGiveup.empty())
// 	{
// 		std::vector<ulong> temps =
// 		{
// 			0x191D824A, 0x42566D0B, 0x9A408957, 0x9F9BEB7D, 0x22A50569, 0xA68B3211, 0x98300C2D, 0xE23E4B51, 0x48EF4031, 0x133F8E31,
// 			0x4644255B, 0x17E6C3AC, 0x17E3437D, 0x426DAB66, 0x7C16ADC9, 0xA9FA2CB4, 0xB4895150
// 		};
// 		for (int k = 0, size = temps.size(); k < size; ++k)
// 		{
// 			_tableMagicGiveup.insert(std::make_pair(k, temps[k]));
// 		}
// 	}
// 	return _tableMagicGiveup;
// }

const txtEasy::sTable& txtEasy::getMagicIter()
{
	if (_tableMagicIter.empty())
	{
		std::vector<ulong> temps =
		{
			0x7FE3C5D8, 
			0x91109049, 
			0xDFC4A4F2, 
			0xDCD7A875, 
			0x8D302CE0, 
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicIter.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicIter;
}

const txtEasy::sTable& txtEasy::getMagicUnkown()
{
	if (_tableMagicUnkown.empty())
	{
		std::vector<ulong> temps =
		{
			0x4683E91D, 0x7D5C2E05, 0xFD5737BF, 0x15AB76A0, 0x33DD2829, 0x937302F8, 0x24F5813C, 0xF0A5E9B6, 0x5927908D, 0xA1450F98,
			0x8E7DA7BF, 0x247E5D2A, 0x4C652A39, 0xF7103C1D, 0xF2C7BC8E
		};
		for (int k = 0, size = temps.size(); k < size; ++k)
		{
			_tableMagicUnkown.insert(std::make_pair(k, temps[k]));
		}
	}
	return _tableMagicUnkown;
}