/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by 云风 (Cloud Wu)  1999-2001
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		文字输出
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/11
		Modify Time:		2002/2/25

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>  
#include <malloc.h>
#include "windsoul.h"
#include "wsfont.h"
#include "fontint.h"

WObjStruct* WChar::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WCharStruct(*GetCharStruct());
}

#define new debug_new

static int BMPINFO16[13]={
	sizeof(BITMAPINFOHEADER),
	0,	// 宽度
	0,	// 高度
	0x100001,BI_BITFIELDS,0,0,0,0,0,
	0xf800,0x7e0,0x1f
};

 ///	字体
/////////////////////////

WSERR WFont::Create(HFONT font,int alpha,int cachesize)
{
	if (m_CacheSize!=0) Destroy();
	TEXTMETRIC tm;
	m_FontDC=CreateCompatibleDC(NULL);
	if (font!=0) SelectObject(m_FontDC, font);

	m_Data=(Data*)WAlloc(cachesize*sizeof(Data));
	m_FontData=(WFontData*)WAlloc(cachesize*sizeof(WFontData));
	if (m_Data==0 || m_FontData==0) return WS_CANTCREATEFONT;

	GetTextMetrics(m_FontDC,&tm);
	m_Height=tm.tmHeight;//-tm.tmInternalLeading;
	m_Ascent=tm.tmAscent;//-tm.tmInternalLeading;

	m_CacheSize=cachesize;
	m_CacheNum=0;
	m_Locked=0;
	m_Alpha=alpha;
	if (alpha==0) {
		m_MaxWidth=(tm.tmMaxCharWidth+3)&-4;
		BMPINFO16[1]=m_MaxWidth,BMPINFO16[2]=-m_Height;
		m_FontBmp=CreateDIBSection(m_FontDC,(BITMAPINFO*)&(BMPINFO16[0]),DIB_RGB_COLORS,(void**)&m_Buffer,0,0);
		SelectObject(m_FontDC,m_FontBmp);
		SetTextColor(m_FontDC,0xffffff);
		SetBkColor(m_FontDC,0);
	}
	return WS_OK;
}

void WFont::Destroy()
{
	int i;
	if (m_CacheSize==0) return;
	for (i=0;i<m_CacheNum;i++) {
		WFree(m_FontData[i].data);
	}
	WFree(m_Data);
	WFree(m_FontData);
	DeleteDC(m_FontDC);
	m_CacheNum=m_CacheSize=0;
	m_Freq=0;
	if (m_Alpha==0) {
		DeleteObject(m_FontBmp);
	}
}

void WFont::ExpandCacheSize(int newsize)
{
	Data *newbuf;
	WFontData *new_font_buf;
	newbuf=(Data*)WAlloc(newsize*sizeof(Data));
	new_font_buf=(WFontData*)WAlloc(newsize*sizeof(WFontData));
	WMemCpy(newbuf,m_Data,m_CacheSize*sizeof(Data));
	WMemCpy(new_font_buf,m_FontData,m_CacheSize*sizeof(WFontData));
	WFree(m_Data);
	WFree(m_FontData);
	m_CacheSize=newsize;
	m_Data=newbuf;
	m_FontData=new_font_buf;
}

int WFont::SearchChar(unsigned int c) const
{
	int begin,end,middle;
	unsigned int Char;
	begin=0,end=m_CacheNum-1;
	while(begin<=end) {
		middle=(begin+end)/2;
		Char=m_Data[middle].c;
		if (c==Char)
			return middle;
		else if (c<Char) 
			end=middle-1;
		else begin=middle+1;
	}
	return -begin-1;
}

WFontData * WFont::GetChar(unsigned int c)
{
	int i,j,pos;
	WFontData *temp;
	if (m_CacheSize==0) return 0;
	++m_Freq;

	pos=SearchChar(c);
	if (pos>=0) {
		m_Data[pos].freq=m_Freq;
		return &m_FontData[m_Data[pos].id];
	}
// Cache 不命中
	pos=-pos-1;

	if (m_CacheNum>=m_CacheSize) {
// Cache 满, 删掉最早进 Cache 的
		int min=m_Freq+1,min_id=-1;
		for (i=0;i<m_CacheNum;i++) {
			if (m_Data[i].freq==1) {
				min=1;
				min_id=i;
				break;
			}
			if (m_Data[i].freq<min) {
				min=m_Data[i].freq;
				min_id=i;
			}
		}
		if (m_Locked!=0 && min>=m_Locked) {
			if (m_CacheSize<1024) ExpandCacheSize(m_CacheSize*2);
			else ExpandCacheSize(m_CacheSize+1024);
			for (i=m_CacheNum;i>pos;i--)
				m_Data[i]=m_Data[i-1];
			temp=&m_FontData[m_CacheNum];
			temp->data=0;
			m_Data[pos].freq=m_Freq;
			m_Data[pos].c=c;
			m_Data[pos].id=m_CacheNum;
			++m_CacheNum;
		}
		else {
			int id=m_Data[min_id].id;
			temp=&m_FontData[id];

			if (pos==m_CacheNum) {
// 替代最后一个
				--pos;
			}

			if (pos>min_id) {
//				插入位置在删除点的后面
				for (i=min_id;i<pos;i++) {
					m_Data[i]=m_Data[i+1];
				}
				m_Data[pos].freq=m_Freq;
				m_Data[pos].c=c;
				m_Data[pos].id=id;
			}
			else {
//				插入位置在删除点的前面
				for (i=min_id;i>pos;i--) {
					m_Data[i]=m_Data[i-1];
				}
				m_Data[pos].freq=m_Freq;
				m_Data[pos].c=c;
				m_Data[pos].id=id;
			}
			m_Freq-=min;
			if (m_Locked>0) m_Locked-=min;
			for (i=0;i<m_CacheNum;i++)
				m_Data[i].freq-=min;
		}
	}
	else {
// Cache 不满, 添加
		temp=&m_FontData[m_CacheNum];
		temp->data=0;
		for (i=m_CacheNum;i>pos;i--)
			m_Data[i]=m_Data[i-1];
		m_Data[pos].freq=m_Freq;
		m_Data[pos].c=c;
		m_Data[pos].id=m_CacheNum;
		++m_CacheNum;
	}

// 计算字符数据到 temp->data;
	if (m_Alpha==0) {
		// 从 DC 取 (无反混淆)
		static RECT rect;
		static char str[3]={0,0,0};
		SIZE si;

		rect.top=0,rect.left=0,rect.right=m_MaxWidth,rect.bottom=m_Height;
		if (c<256) {
			str[0]=c,str[1]=0;
			DrawText(m_FontDC,str,1,&rect,DT_LEFT|DT_NOPREFIX);
			GetTextExtentPoint(m_FontDC,str,1,&si);
		}
		else {
			str[0]=c>>8,str[1]=c&0xff;
			DrawText(m_FontDC,str,2,&rect,DT_LEFT|DT_NOPREFIX);
			GetTextExtentPoint(m_FontDC,str,2,&si);
		}
		WORD *line=m_Buffer;
		int from;
		for (i=0;i<si.cy;i++,line+=m_MaxWidth) {
			for (j=0;j<si.cx;j++) {
				if (line[j]!=0) goto _find;
			}
		}
_find:
		from=i;
		si.cy-=from;
		int ox=si.cx;
//		si.cx=(si.cx+3)&-4;
		if (si.cx>m_MaxWidth) si.cx=m_MaxWidth;
		if (si.cy>m_Height) si.cy=m_Height;
		int size=si.cx*si.cy+8;
		if (!temp->data) {
			temp->size=size;
			temp->data=(BYTE *)WAlloc(size);
		}
		else if (size>temp->size) {
			temp->size=size;
			WFree(temp->data);
			temp->data=(BYTE *)WAlloc(size);
		}
		temp->w=si.cx;
		temp->h=si.cy;
		temp->width=si.cx;
		temp->kx=0;
		temp->ky=-from;
		line=m_Buffer+from*m_MaxWidth;
		BYTE *des=temp->data;
		for (i=0;i<si.cy;i++,line+=m_MaxWidth,des+=si.cx) {
			for (j=0;j<ox;j++) {
				des[j]=(line[j]==0)?0:0x10;
			}
			for (;j<si.cx;j++) {
				des[j]=0;
			}
		}
	}
	else {

		int size;
		static MAT2 mat2={{0,1},{0,0},{0,0},{0,1}};
		GLYPHMETRICS gm;

		size=GetGlyphOutline(
			m_FontDC,
			c,
			GGO_GRAY4_BITMAP,
			&gm,
			0,
			NULL,
			&mat2
			);

		int size8=size+8;
		if (!temp->data) {
			temp->size=size8;
			temp->data=(BYTE *)WAlloc(size8);
		}
		else if (size8>temp->size) {
			temp->size=size8;
			WFree(temp->data);
			temp->data=(BYTE *)WAlloc(size8);
		}
		if (size>0) {
			if ( GetGlyphOutline(
			m_FontDC,
			c,
			GGO_GRAY4_BITMAP,
			&gm,
			size,
			(LPVOID)temp->data,
			&mat2
			) == GDI_ERROR) return 0;
		}

		temp->w=(gm.gmBlackBoxX+3)&0xfffffffc;
		temp->h=gm.gmBlackBoxY;
		temp->width=gm.gmCellIncX;
		temp->kx=-gm.gmptGlyphOrigin.x;
		temp->ky=-m_Ascent+gm.gmptGlyphOrigin.y;
		if (size==0) {
			temp->w=0;
			temp->h=0;
		}
	}

	return temp;
}

 ///	字符对象
/////////////////////////

WSERR WChar::Create(WFont &font,unsigned int c,WPixel color)
{
	WCharStruct *data=GetCharStruct();
	WFontData *font_data;
	font_data=font.GetChar(c);
	if (font_data==0) return WS_CANTCREATECHAR;
	if (data!=0) delete data;
	data=new WCharStruct;
	data->w=font_data->w,data->h=font_data->h,
	data->data=font_data->data,
	data->kx=font_data->kx,data->ky=font_data->ky,
	data->width=font_data->width,
	data->color=color;
	SetData(data);
	return WS_OK;
}

int WChar::GetW() const
{
	WCharStruct *data=GetCharStruct();
	ASSERT(data!=0);
    return data->w;
}

int WChar::GetH() const
{
	WCharStruct *data=GetCharStruct();
	ASSERT(data!=0);
    return data->h;
}

int WChar::GetWidth() const
{
	WCharStruct *data=GetCharStruct();
	ASSERT(data!=0);
    return data->width;
}

void WChar::Destroy()
{
	WCharStruct *data=GetCharStruct();
	if (data) {
		delete data;
		SetData(0);
	}
}

extern "C" {
	WSERR _stdcall _font16_noalpha(WBmpStruct *,const WCharStruct *);
	WSERR _stdcall _font16_alpha(WBmpStruct *,const WCharStruct *);
}

static BLIT_FUNC _font_func[2]={
	(BLIT_FUNC)_font16_alpha,			// 带 65 级 Alpha 的画字函数
	(BLIT_FUNC)_font16_noalpha			// 不带 Alpha 的画字函数
};		

BLIT_FUNC WChar::DrawFunc(DWORD style) const
{
	WCharStruct *data=GetCharStruct();
	ASSERT(data!=0);
	return _font_func[style];
}

DWORD WFont::GetLength(const char *str)
{
	DWORD len=0;
	WChar tmp;
	int i;
	for (i=0;str[i];i++) {
		unsigned a,b;
		a=(unsigned char)str[i];
		if (a>0x80) {
			++i;
			b=(unsigned char)str[i];
			if (b==0) break;
			a=a*256+b;
		}

		tmp.Create(*this,a,0);
		len+=tmp.GetWidth();
	}
	return len;
}

void WFont::Draw(WBitmap &buffer,const char *str, WPixel color, DWORD style)
{
//	LPWSTR ws;
//	size_t len;
//	unsigned i;
	if (m_Alpha==0) style=FONT_NOALPHA;
	int x,y;
	y=buffer.GetY();
	x=buffer.GetX();
	WChar tmp;
/*
	len=MultiByteToWideChar(CP_ACP,0,str,-1,0,0);
	ws=(LPWSTR)_alloca(len*2);
	MultiByteToWideChar(CP_ACP,0,str,-1,ws,len);
	for (i=0;i<len;i++) {
		tmp.Create(*this,ws[i],color);
		buffer(x,y).Draw(tmp,style);
		x+=tmp.GetWidth();
	}
*/
	int i;
	for (i=0;str[i];i++) {
		unsigned a,b;
		a=(unsigned char)str[i];
		if (a>0x80) {
			++i;
			b=(unsigned char)str[i];
			if (b==0) break;
			a=a*256+b;
		}

		if (tmp.Create(*this,a,color)==WS_OK) {
			if (a>32) buffer(x,y).Draw(tmp,style);
			x+=tmp.GetWidth();
		}
	}
}