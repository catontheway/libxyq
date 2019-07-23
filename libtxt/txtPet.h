#pragma once
#include "_txtinc.h"
#include "eMod.h"
#include "txtAction.h"

ccc_txt_class_begin(txtPet);

txtPet();
struct sPoint
{
	int offx;
	std::array<std::array<int, 2>, 2> atks;
	int magic;
};

struct sPet
{
	std::string name;
	std::vector<txtAction::sAction> heads;
	std::vector<txtAction::sAction> sounds;
	std::vector<sPoint> points;
	std::vector<std::vector<int>> jinjies;
	std::vector<ulong> colors;
	std::vector<txtAction::sAction> actionMaps;
	std::vector<txtAction::sAction> actions;
};

public:
	static const int cJinjie4 = 4;
	static const int cJinjie2 = cJinjie4 / 2;
private:
	void init(eMod pet, const std::string& name);
	void insert(const ulong& small, const ulong&  big, const ulong&  dialog);
	void insert(const ulong&  atk, const ulong&  atk2, const ulong&  suffer, const ulong&  magic, const ulong&  def, const ulong&  dead);
	void insert(int offx, int atk1, int tak2, int atk3, int atk4, int magic);
	void insert(const std::vector<int>& jj);
	void insert(const std::vector<int>& jj1, const std::vector<int>& jj2);
	void insert(const std::vector<int>& jj1, const std::vector<int>& jj2, const std::vector<int>& jj3, const std::vector<int>& jj4);
	void insert(const ulong& color, const ulong& stand, const ulong&  walk, const ulong&  fight, const ulong&  go, const ulong&  atk, const ulong&  atk2, const ulong&  magic, const ulong&  def, const ulong&  suffer, const ulong&  dead, const ulong&  back);

	sPet* _pet;
	sPoint _point;
	txtAction::sAction _action;

ccc_txt_class_end(eMod, sPet);