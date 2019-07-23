#pragma  once
#include "_inc.h"

class cWdf : public cWas
{
public:

	static cWdf* getColor();
	static cWdf* getMp3();
	static cWdf* getWav();

	bool loadRoot(const std::string &filename);
};



enum class eBlend { normal, light, blink, };
struct sSpDecode
{
	int w, h;
	uchar* palIdxs = nullptr;
	uchar* alphas = nullptr;

	sSpDecode();
	~sSpDecode();
	const bool isValid()const;
	void decode(int w, int h, const uchar* ptrHead, ulong offs);
	const cAlphaBmp* getBitmap(const s565* palettes, eBlend e, uchar opacity);
};

struct sSpBitmaps
{
	typedef std::map<uchar, const cAlphaBmp*> sOps;
	std::map<eBlend, sOps> bmps;

	sSpBitmaps();
	~sSpBitmaps();

	void insert(eBlend e, uchar opacity, const cAlphaBmp* bitmap);
	const cAlphaBmp* getBitmap(eBlend e, uchar opacity);
};

struct sMatrix9 { ushort r1, r2, r3, g1, g2, g3, b1, b2, b3; };
struct sMatrix { sMatrix9 matrix;  ushort start, end; };
typedef std::vector<sMatrix> sMatrixs;
struct sSpDecoder
{
	sSpInfo info;
	const s565* palette = nullptr;
	const ulong* offsets = nullptr;
	sSpDecode* decodes = nullptr;


	int matrixid = 0;
	// 2<<16Ö¡ ×ã¹»ÁË°É
	static const int cMatrixFlag = 16;
	std::map<int, const s565*> palettes;
	std::map<int, sSpBitmaps*> bitmaps;

	sSpDecoder();
	~sSpDecoder();
	const bool isValid()const;
	void load(const char* ptr);
	void decode(int frame);
	int getMatrix(const sMatrixs* matrixs);
	bool removeMatrix(int mid);
	const cAlphaBmp* getBitmap(int mid, int iframe, eBlend e, uchar opacity);
};



class cSp : public cWdf
{
public:
	static const ulong c0 = 0;

	~cSp();

	static void toPalette(s565* palette, const sMatrixs* matrixs);

	const sSpDecoder* getDecoder(ulong uid);

	bool freeDecoder(ulong uid);

private:
	struct sRef 
	{ 
		const char* ptr;
		sSpDecoder decoder;
		int ref; 
	};
	std::map<ulong, sRef> _refs;
};

struct sSp
{
	ulong uid = cSp::c0;
	sMatrixs matrixs;
};
typedef std::vector<sSp> sSps;

class cSps
{
public:
	~cSps();
	static cSps* getInstance();
	cSp* loadRoot(const std::string &filenameWithoutRoot);
	cSp* getSp(const std::string &filenameWithoutRoot);
private:
	std::map<std::string, cSp*> _sps;
};
