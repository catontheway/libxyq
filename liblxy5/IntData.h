#pragma once
#include "_asert.h"

struct sInt2
{
	int d1 = 0;
	int d2 = 0;
	void Save(ofstream& File)
	{
		File << d1 << " ";
		File << d2 << " ";
	}
	void Load(ifstream& File)
	{
		File >> d1;
		File >> d2;
	}
	void Reset()
	{
		d1 = 0;
		d2 = 0;
	}

	int operator-(const sInt2& s2)
	{
		return d1 - s2.d2;
	}
};


struct sInt3
{
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Reset()
	{
		m_Data = 0;
		add = 0;
		precent = 0;
		origin = 0;
	}
	void InitAll(int DataOriginal, int Percent, int Add)
	{
		origin = DataOriginal;
		add = Add;
		precent = Percent;
		Update();
	}
	void SetDataAdd(int num)
	{
		add = num;
		Update();
	};
	void AddDataAdd(int num)
	{
		if (!num)return;
		add += num;
		Update();
	}
	void SetDataOriginal(int num)
	{
		origin = num;
		Update();
	};
	void AddDataOriginal(int num)
	{
		origin += num;
		Update();
	}
	void SetDataAddPercent(int num)
	{
		if (!num)return;
		precent = num;
		Update();
	};
	void AddDataAddPercent(int num)
	{
		if (!num)return;
		precent += num;
		Update();
	}
	int* GetDatap(){ return &m_Data; }
	int* GetPercentp(){ return &precent; }
	int* GetOriginalp(){ return &origin; }
	int* GetAddp(){ return &add; }


	const int GetData()const{ return m_Data; }
	const int GetPercent()const{ return precent; }
	const int GetOriginal()const{ return origin; }
	const int GetAdd()const{ return add; }
	void SetData(int k){ m_Data = k; }
	void SetPercent(int k){ precent = k; }
	void SetOriginal(int k){ origin = k; }
	void SetAdd(int k){ add = k; }

	void operator=(sInt3& k)
	{
		m_Data = k.GetData();
		add = k.GetAdd();
		precent = k.GetPercent();
	}

	operator int()
	{
		return (origin*(100 + precent)) / 100 + add;
	}

private:
	void Update()
	{
		m_Data = (origin*(100 + precent)) / 100 + add;
	}

	int m_Data = 0;
	int precent = 0;
	int origin = 0;
	int add = 0;
};
