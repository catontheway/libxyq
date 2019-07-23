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

		Description:		风魂++ 画布管理
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/23
		Modify Time:		2002/2/27

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include <assert.h>
#include "windsoul.h"
#include "wscanvas.h"
#include "canvasin.h"
#include "wsstring.h"
#include "textint.h"
#define new debug_new

WCanvas::WCanvas(int width,int height)
	: WBitmap((width+2*WCANVASBLOCKW-1)/WCANVASBLOCKW*WCANVASBLOCKW,(height+2*WCANVASBLOCKH-1)/WCANVASBLOCKH*WCANVASBLOCKH), 
	block_x(0), block_y(0), data(new WCanvasInternalData(width,height))
{
	int i,j,id;
	m_FrameTime=0;
	WCanvasBlock *pblock;
	width=(width+2*WCANVASBLOCKW-1)/WCANVASBLOCKW*WCANVASBLOCKW;
	height=(height+2*WCANVASBLOCKH-1)/WCANVASBLOCKH*WCANVASBLOCKH;
	row=height/WCANVASBLOCKH;
	col=width/WCANVASBLOCKW;
	pblock=block=new WCanvasBlock[row*col];
	data->rect_link.next=0;
 	for (id=i=0;i<row;i++)
		for (j=0;j<col;j++,++pblock,++id) {
			pblock->Create(*(WBitmap*)this,j*WCANVASBLOCKW,i*WCANVASBLOCKH,WCANVASBLOCKW,WCANVASBLOCKH);
			pblock->link.next=0;
			pblock->change=0;
			pblock->m_IsTrans=false;
			pblock->m_IsOvl=false;
			pblock->offset=j*WCANVASBLOCKW;
		}
}

void WCanvas::Reset(int f)
{
	if (f==0) m_FrameTime=0;
	else m_FrameTime=10000/f;
	m_Timer.Reset();
}

void WCanvas::Laptop(bool Set)
{
	data->laptop=Set;
}

#ifdef _RECORD_CANVAS

static void record_bmp(WBitmap &buffer,WCanvasRecorder *block,WBitmap *bmp,int row,int col)
{
	int i,j,x,y;
	WCanvasRecorder::Block *blocks=block->blocks;
	for (;blocks->bmp.IsValid() && blocks->next!=0;) {
		WCanvasRecorder::Block *p=blocks->next;
		bmp[blocks->id].Draw(blocks->bmp,0);
		delete blocks;
		blocks=p;
	}
	delete blocks;
	for (i=0;i<row;i++) {
		y=i-block->block_y;
		if (y<0) y+=row;
		for (j=0;j<col;j++) {
			x=j-block->block_x;													
			if (x<0) x+=col;
			buffer(x*WCANVASBLOCKW-block->offset_x,y*WCANVASBLOCKH-block->offset_y).Draw(bmp[i*col+j],0);
		}
	}
}

#include "wsstring.h"

void WCanvas::Record(const char *path)
{
 	if (data->recorder_head==0) {
		data->recorder_head=new WCanvasRecorder;
		data->recorder_head->blocks=0;
		data->recorder_p=data->recorder_head;
	}
	else {
		// 关闭
		int i;
		WBitmap buffer(GetW(),GetH());
		WBitmap *bmp=new WBitmap[row*col];
		for (i=0;i<row*col;i++)
			bmp[i].Create(WCANVASBLOCKW,WCANVASBLOCKH);
		WCanvasRecorder	*r;
		int n=0;
		for (r=data->recorder_head;r->next!=0 && r->blocks!=0;++n) {
			WCanvasRecorder	*p=r->next;
			record_bmp(buffer,r,bmp,row,col);
			delete r;
			r=p;
			WString name;
			name.Format("%s/%08d.bmp",path,n);
			buffer.Save(name);
		}
		delete r;
		data->recorder_head=0;
	}
}

#endif

bool WCanvas::IsMoved() const 
{ 
	return data->moved; 
}


void WCanvas::MoveTo(int x,int y)
{
	int bx,by,i,j,from,to;
	WCanvasBlock *pblock;
	if (data->viewport.x==x && data->viewport.y==y) {
		data->moved=false;
		UnChange();
		return;
	}
	data->moved=true,
	data->viewport.x-=data->offset.x;
	data->viewport.y-=data->offset.y;
	data->offset.x=MOD(x,WCANVASBLOCKW),data->offset.y=MOD(y,WCANVASBLOCKH);
	bx=DIV(x-data->offset.x-data->viewport.x,WCANVASBLOCKW);
	by=DIV(y-data->offset.y-data->viewport.y,WCANVASBLOCKH);
	data->viewport.x=x,
	data->viewport.y=y;

	if (bx==0 && by==0) return;

	if (bx>=col || by>=row || bx<=-col || by<=-row) {
		for (pblock=block,i=0;i<row;i++)
			for (j=0;j<col;j++,++pblock)
				pblock->last=0;
		return;
	}

	if (block_x==0) pblock=block+col-1;
	else pblock=block+block_x-1;
	for (i=0;i<row;i++,pblock+=col)
		pblock->last=0;

	pblock=block+block_x;
	for (i=0;i<row;i++,pblock+=col)
		pblock->last=0;

	if (block_y==0) pblock=block+(row-1)*col;
	else pblock=block+(block_y-1)*col;
	for (i=0;i<col;i++,pblock++)
		pblock->last=0;

	pblock=block+block_y*col;
	for (i=0;i<col;i++,pblock++)
		pblock->last=0;

// 失效区域标记

	if (by>0) {
		from=block_y,to=block_y+by;
		for (i=from;i<to;i++) {
			pblock=block+(i-(i>=row?row:0))*col;
			for (j=0;j<col;j++,++pblock)
				pblock->last=0;
		}
	}
	else {
		from=block_y+by,to=block_y;
		for (i=from;i<to;i++) {
			pblock=block+(i+(i<0?row:0))*col;
			for (j=0;j<col;j++,++pblock)
				pblock->last=0;
		}
	}
	if (bx>0) {
		from=block_x,to=block_x+bx;
		for (i=from;i<to;i++) {
			pblock=block+i-(i>=col?col:0);
			for (j=0;j<row;j++,pblock+=col)
				pblock->last=0;
		}
	}
	else {
		from=block_x+bx,to=block_x;
		for (i=from;i<to;i++) {
			pblock=block+i+(i<0?col:0);
			for (j=0;j<row;j++,pblock+=col)
				pblock->last=0;
		}
	}

// 重组图块坐标
	block_x+=bx,block_y+=by;
	if (block_x<0) block_x+=col;
	else if (block_x>=col) block_x-=col;
	if (block_y<0) block_y+=row;
	else if (block_y>=row) block_y-=row;
	Change();
}

void WCanvas::Move(int x,int y)
{
	MoveTo(data->viewport.x+x,data->viewport.y+y);
}

int WCanvas::GetX() const 
{ 
	return WBitmap::GetX()+data->viewport.x-data->offset.x; 
}

int WCanvas::GetY() const
{ 
	return WBitmap::GetY()+data->viewport.y-data->offset.y;
}

int WCanvas::GetW() const
{ 
	return data->viewport.w;
}	

int WCanvas::GetH() const
{
	return data->viewport.h; 
}

WPoint WCanvas::GetViewPort(int x,int y) const 
{
	return WPoint(x+data->viewport.x,y+data->viewport.y);
}

WCanvas& WCanvas::SetPos(int x,int y)
{
	WBitmap::SetPos(x-data->viewport.x+data->offset.x,y-data->viewport.y+data->offset.y); 
	return *this; 
}	

WCanvas& WCanvas::AddPos(int x,int y)
{
	int kx=WBitmap::GetX();
	int ky=WBitmap::GetY();
	WBitmap::SetPos(kx+x,ky+y); 
	return *this; 
}	

WCanvas& WCanvas::ViewPort(int x,int y)
{
	WBitmap::SetPos(x+data->offset.x,y+data->offset.y); 
	return *this; 
}

#ifdef _DEBUG_CANVAS 

#include "wsgeo.h"
extern "C" void _stdcall _draw_ascii(WBmpStruct *bmp,char c);

void WCanvas::Update()
{
	int i,s=col*row;
	CANVAS_LINK *p;
	for (i=0;i<s;i++)
		if (block[i].last!=block[i].obj) {
			int n=0;
			block[i](0,0);
			p=block[i].link.next;
			while(p) {
				p->blit_func((DWORD)block[i].objdata,p->param);
				p=p->next;
				++n;
			}
			block[i].m_IsMasked=false;
			char c=(n<10)?('0'+n):('A'+n-10);
			WBmpStruct *bmp=(WBmpStruct*)block[i].objdata;
			bmp->userdata=WPixel((block[i].last==0)?0xff00:0x8000).color;
			_draw_ascii(bmp,c);
		}
		else if (block[i].change!=0) {
			int n=0;
			block[i](0,0);
			p=block[i].change;
			while(p) {
				p->blit_func((DWORD)block[i].objdata,p->param);
				p=p->next;
				++n;
			}
			block[i].m_IsMasked=false;
			char c=(n<10)?('0'+n):('A'+n-10);
			WBmpStruct *bmp=(WBmpStruct*)block[i].objdata;
			bmp->userdata=WPixel(0xff0000).color;
			_draw_ascii(bmp,c);
		}
		else if (!block[i].m_IsMasked) {
			block[i].m_IsMasked=true;
			WBox _debug_mask(WCANVASBLOCKW,WCANVASBLOCKH,0xff);
			_debug_mask(64).DrawFunc(BLIT_TRANS)((DWORD)block[i].objdata,(DWORD)_debug_mask.GetData());
		}
}

#else

void WCanvas::Update()
{
	int i,s=col*row;
	CANVAS_LINK *p;
#ifdef _RECORD_CANVAS
	WCanvasRecorder::Block *blocks;
	if (data->recorder_head) {
		blocks=data->recorder_p->blocks=new WCanvasRecorder::Block;
		data->recorder_p->block_x=block_x,data->recorder_p->block_y=block_y;
		data->recorder_p->offset_x=data->offset.x;
		data->recorder_p->offset_y=data->offset.y;
		data->recorder_p->next=new WCanvasRecorder;
		data->recorder_p=data->recorder_p->next;
		data->recorder_p->blocks=0;
		data->recorder_p->next=0;
	}
#endif
	for (i=0;i<s;i++) {
		if (block[i].last!=block[i].obj) {
			block[i](0,0);
			p=block[i].link.next;
			while(p) {
				p->blit_func((DWORD)block[i].objdata,p->param);
				p=p->next;
			}
#ifdef _RECORD_CANVAS
			if (data->recorder_head) {
				blocks->bmp.Create(WCANVASBLOCKW,WCANVASBLOCKH);
				blocks->bmp.Draw(block[i],0);
				blocks->id=i;
				blocks->next=new WCanvasRecorder::Block;
				blocks=blocks->next;
			}
#endif
		}
		else if (block[i].change!=0) {
			block[i](0,0);
			p=block[i].change;
			while(p) {
				p->blit_func((DWORD)block[i].objdata,p->param);
				p=p->next;
			}
#ifdef _RECORD_CANVAS
			if (data->recorder_head) {
				blocks->bmp.Create(WCANVASBLOCKW,WCANVASBLOCKH);
				blocks->bmp.Draw(block[i],0);
				blocks->id=i;
				blocks->next=new WCanvasRecorder::Block;
				blocks=blocks->next;
			}
#endif
		}
	}
}

#endif

void WCanvas::NextFrame()
{
	int i,s=col*row;
	for (i=0;i<s;i++) {
		block[i].last=block[i].obj,
		block[i].m_IsTrans=false,
		block[i].m_IsOvl=false,
		block[i].obj=0,
		block[i].link.next=0,
		block[i].change=0;
	}
	data->rect_link.next=0,
	data->moved=false;
	data->object_mem.clearobj(data->heap);
	data->rect_mem.clear();
}

void WCanvas::SkipFrame()
{
	int i,s=col*row;
	for (i=0;i<s;i++) {
		block[i].last=0,block[i].change=0;
		block[i].obj=0,
		block[i].m_IsTrans=false,
		block[i].m_IsOvl=false,
		block[i].link.next=0;
	}
	data->rect_link.next=0;
	data->object_mem.clearobj(data->heap);
	data->rect_mem.clear();
}

void WCanvas::Clear()
{
	int i,s=col*row;
	for (i=0;i<s;i++) {
		block[i].last=0,block[i].change=0;
		block[i].obj=0,
		block[i].m_IsTrans=false,
		block[i].m_IsOvl=false,
		block[i].link.next=0;
	}
	data->rect_link.next=0;
	data->object_mem.clearobj(data->heap);
	data->rect_mem.clear();
}

// 添加一个覆盖矩形
void WCanvas::SetOvlRect(int w,int h)
{
	CANVAS_RECTLINK *p,*last;
	WRect rect(GetX(),GetY(),w,h);
	if (rect.IsOut(data->viewport)) return;

// 对覆盖矩形记数
	int i,j;																	
	int left,right,top,bottom;													
	WCanvasBlock *b;															

	left=MAX(0,(rect.x-data->viewport.x+data->offset.x)/WCANVASBLOCKW);						
	right=MIN(col-1,(rect.x-data->viewport.x+data->offset.x+rect.w)/WCANVASBLOCKW);
	top=MAX(0,(rect.y-data->viewport.y+data->offset.y)/WCANVASBLOCKH);
	bottom=MIN(row-1,(rect.y-data->viewport.y+data->offset.y+rect.h)/WCANVASBLOCKH);

	for (i=top;i<=bottom;i++) {	
		b=block+(i+block_y-(i+block_y>=row?row:0))*col;
/*
		if (i==top || i==bottom) {
			for (j=left;j<=right;j++) {
				int num=j+block_x;
				if (num>=col) num-=col;
				b[num].last=0;
			}
		}
		else {
			int num=left+block_x;
			if (num>=col) num-=col;
			b[num].last=0;
			num=right+block_x;
			if (num>=col) num-=col;
			b[num].last=0;
		}
*/
		for (j=left;j<=right;j++) {
			int num=j+block_x;
			if (num>=col) num-=col;
			b[num].obj+=0x10000;
		}
	}

	for (i=top;i<=bottom;i++) {	
		b=block+(i+block_y-(i+block_y>=row?row:0))*col;							
		for (j=left;j<=right;j++) {
			int num=j+block_x;													
			if (num>=col) num-=col;
			b[num].obj+=0x10000;
		}																		
	}

// 如果链表里的矩形在这个矩形内,删掉链表中的矩形
// 如果这个矩形在链表中某个矩形内, 忽略这个矩形
	for (last=&data->rect_link,p=data->rect_link.next;p;last=p,p=p->next) {
		if (rect.IsIn(p->rect))
			return;
		else if (p->rect.IsIn(rect))	
			last->next=p->next;	
	}

// 添加入链表
	p=data->rect_mem.alloc();
	p->rect=rect;
	p->next=data->rect_link.next;
	data->rect_link.next=p;

	left=MAX(0,((rect.x-data->viewport.x+data->offset.x)+WCANVASBLOCKW-1)/WCANVASBLOCKW);						
	right=MIN(col-1,((rect.x-data->viewport.x+data->offset.x+rect.w)-WCANVASBLOCKW+1)/WCANVASBLOCKW);
	top=MAX(0,((rect.y-data->viewport.y+data->offset.y)+WCANVASBLOCKH-1)/WCANVASBLOCKH);
	bottom=MIN(row-1,((rect.y-data->viewport.y+data->offset.y+rect.h)-WCANVASBLOCKH+1)/WCANVASBLOCKH);

	for (i=top;i<bottom;i++) {	
		b=block+(i+block_y-(i+block_y>=row?row:0))*col;							
		for (j=left;j<right;j++) {
			int num=j+block_x;													
			if (num>=col) num-=col;
			b[num].m_IsOvl=true;
		}																		
	}

// 如果这个矩形和链表中某个矩形相交, 添加相交部分
	for (p=p->next;p;p=p->next) {
		if (!rect.IsOut(p->rect)) {
			if (!((rect.x<=p->rect.x && rect.x+rect.w>=p->rect.x+p->rect.w) ||
				(rect.x>=p->rect.x && rect.x+rect.w<=p->rect.x+p->rect.w)))
				SetOvlRect(rect.HorRect(p->rect));
			if (!((rect.y<=p->rect.y && rect.y+rect.h>=p->rect.y+p->rect.h) ||
				(rect.y>=p->rect.y && rect.y+rect.h<=p->rect.y+p->rect.h)))
				SetOvlRect(rect.VerRect(p->rect));
		}
	}
}

WSERR WCanvas::Draw(const WObject &bmp,DWORD style)
{
	if (!bmp.IsValid()) return WS_NULLBITMAP;
	BLIT_FUNC blit_func=bmp.DrawFunc(style);
	if (!blit_func) return WS_UNSUPPORTBLITTYPE;
	int i,j;																	
	int left,right,top,bottom;													
	WCanvasBlock *b;															
	CANVAS_LINK *p;																
	CANVAS_RECTLINK *prect;														
	int x,y;		
	int bmp_x=bmp.GetX(),bmp_y=bmp.GetY();
	WRect rect(GetX()-bmp_x,GetY()-bmp_y,bmp.GetW(),bmp.GetH());		
	if (rect.w==0) return WS_OK;
	WRect viewrect(data->viewport.x-data->offset.x,data->viewport.y-data->offset.y,WBitmap::GetW(),WBitmap::GetH());
	if (rect.IsOut(viewrect)) return WS_OK;
//	if (rect.IsOut(data->viewport)) return WS_OK;
	for (prect=data->rect_link.next;prect;prect=prect->next)							
		if (rect.IsIn(prect->rect)) return WS_OK;
	left=MAX(0,(WBitmap::GetX()-bmp_x)/WCANVASBLOCKW);						
	right=MIN(col-1,(WBitmap::GetX()-bmp_x+rect.w-1)/WCANVASBLOCKW);			
	top=MAX(0,(WBitmap::GetY()-bmp_y)/WCANVASBLOCKH);						
	bottom=MIN(row-1,(WBitmap::GetY()-bmp_y+rect.h-1)/WCANVASBLOCKH);			
	x=WBitmap::GetX()-left*WCANVASBLOCKW-bmp_x;								
	y=WBitmap::GetY()-top*WCANVASBLOCKH-bmp_y;								
	if (style!=BLIT_COPY && style!=(BLIT_MASK|BLIT_COPY) && changed==change_self) 
		changed=change_full;
	for (i=top;i<=bottom;i++,y-=WCANVASBLOCKH,x+=(right-left+1)*WCANVASBLOCKW) {	
		b=block+(i+block_y-(i+block_y>=row?row:0))*col;							
		for (j=left;j<=right;j++,x-=WCANVASBLOCKW) {								
			int num=j+block_x;													
			WObjStruct *os;
			if (num>=col) num-=col;
			if (b[num].m_IsOvl) continue;
			p=data->object_mem.alloc();												
			p->param=(DWORD)(os=bmp.Duplicate(&data->heap));
			os->kx=-x,os->ky=-y;
			p->blit_func=blit_func;
			p->next=b[num].link.next;											
			b[num].link.next=p;													
			if (style!=BLIT_COPY && style!=(BLIT_MASK|BLIT_COPY)) b[num].m_IsTrans=true;										
			if (changed==change_full) b[num].last=0;
			else if (changed==change_self) {
				if (b[num].m_IsTrans==false) {
					b[num].change=p;		
				}
				else {
					b[num].last=0;
				}
			}
			++b[num].obj;														
		}																		
	}
	return WS_OK;
}

WSERR WCanvas::DrawEx(const WObject &bmp,DWORD style)
{
	BLIT_FUNC blit_func=bmp.DrawFunc(style);
	if (!blit_func) return WS_UNSUPPORTBLITTYPE;
	int i,j;																	
	int left,right,top,bottom;													
	WCanvasBlock *b;															
	CANVAS_LINK *p;																
	CANVAS_RECTLINK *prect;														
	int x,y;		
	int bmp_x=bmp.GetX(),bmp_y=bmp.GetY();
	WRect rect(GetX()-bmp_x,GetY()-bmp_y,bmp.GetW(),bmp.GetH());		
	if (rect.w==0) return WS_OK;
	WRect viewrect(data->viewport.x-data->offset.x,data->viewport.y-data->offset.y,WBitmap::GetW(),WBitmap::GetH());
	if (rect.IsOut(viewrect)) return WS_OK;
//	if (rect.IsOut(data->viewport)) return WS_OK;
	for (prect=data->rect_link.next;prect;prect=prect->next)							
		if (rect.IsIn(prect->rect)) return WS_OK;
	left=MAX(0,(WBitmap::GetX()-bmp_x)/WCANVASBLOCKW);						
	right=MIN(col-1,(WBitmap::GetX()-bmp_x+rect.w-1)/WCANVASBLOCKW);			
	top=MAX(0,(WBitmap::GetY()-bmp_y)/WCANVASBLOCKH);						
	bottom=MIN(row-1,(WBitmap::GetY()-bmp_y+rect.h-1)/WCANVASBLOCKH);			
	x=WBitmap::GetX()-left*WCANVASBLOCKW-bmp_x;								
	y=WBitmap::GetY()-top*WCANVASBLOCKH-bmp_y;								
	if (style!=BLIT_COPY && style!=(BLIT_MASK|BLIT_COPY) && changed==change_self) 
		changed=change_full;						
	for (i=top;i<=bottom;i++,y-=WCANVASBLOCKH,x+=(right-left+1)*WCANVASBLOCKW) {	
		b=block+(i+block_y-(i+block_y>=row?row:0))*col;							
		for (j=left;j<=right;j++,x-=WCANVASBLOCKW) {								
			int num=j+block_x;													
			WObjStruct *os;
			if (num>=col) num-=col;
			if (b[num].m_IsOvl) continue;
			if (!bmp.Affect(x,y)) continue;
			p=data->object_mem.alloc();												
		
			p->param=(DWORD)(os=bmp.Duplicate(&data->heap));
			os->kx=-x,os->ky=-y;

			p->blit_func=blit_func;
			p->next=b[num].link.next;											
			b[num].link.next=p;													
			if (style!=BLIT_COPY && style!=(BLIT_MASK|BLIT_COPY)) b[num].m_IsTrans=true;										
			if (changed==change_full) b[num].last=0;							
			else if (changed==change_self) {
				if (b[num].m_IsTrans==false) {
					b[num].change=p;		
				}
				else {
					b[num].last=0;
				}
			}
			++b[num].obj;														
		}																		
	}
	return WS_OK;
}

void WCanvas::Clear(WPixel color)
{
	int i,s=col*row;
	CANVAS_LINK *p;
	ASSERT(data!=0);
	for (i=0;i<s;i++) {
		if (block[i].m_IsOvl) continue;
		++block[i].obj;
		p=data->object_mem.alloc();
		p->param=color.color;
		p->blit_func=WBitmap::ClearFunc();
		p->next=block[i].link.next;
		block[i].link.next=p;
	}
	if (changed!=change_null)
		for (i=0;i<s;i++) {
			block[i].last=0;
		}
//	设置最大覆盖矩形 (一般不需要)
//	operator()(-0x1000000,-0x10000000);
//	SetOvlRect(0x2000000,0x20000000);
}

void WCanvas::Draw (WCanvas &canvas,DWORD style)
{
	canvas.Update();
	int sx=WBitmap::GetX(),sy=WBitmap::GetY(),s,i,j;
	WPoint canvas_offset_pos=canvas.data->offset;
	int width=MIN((canvas.col-canvas.block_x)*WCANVASBLOCKW-canvas_offset_pos.x,canvas.GetW());
	int height=MIN(((canvas.row-canvas.block_y)*WCANVASBLOCKH-canvas_offset_pos.y),canvas.GetH());
	int split_x=canvas.block_x*WCANVASBLOCKW+canvas_offset_pos.x;
	int split_y=canvas.block_y*WCANVASBLOCKH+canvas_offset_pos.y;
/*
	if (changed!=change_full) {
		for (s=i=0;i<canvas.col*canvas.row;i++) {
			if (canvas.block[i].last!=canvas.block[i].obj || canvas.block[i].change!=0)
				++s;
		}
		if (s==0) changed=change_null;
		else if (canvas.GetW()<WCANVASBLOCKW || canvas.GetH()<WCANVASBLOCKH || s>canvas.col*canvas.row*3/4) 
			changed=change_full;	// 如果有 3/4 的块改变, 整个覆盖
	}
	if (s==0 || canvas.IsMoved() || changed==change_full) {
*/
	WCanvasChangedTag tag;
	if (style==BLIT_COPY || style==BLIT_MASK) tag=change_self;
	else tag=change_full;

	bool canvas_move=canvas.IsMoved();

	if (canvas_move) changed=tag;

	if (changed==change_full || canvas_move) {
		if (height>0) {
			if (width>0) {
				Draw(canvas(split_x,split_y,width,height),style);
			}
			if (canvas.GetW()>width) {
				WBitmap::SetPos(sx+canvas.WBitmap::GetW()-split_x,sy);
				Draw(canvas(0,split_y,canvas.GetW()-width,height),style);
			}
		}
		if (canvas.GetH()>height) {
			if (width>0) {
				WBitmap::SetPos(sx,sy+canvas.WBitmap::GetH()-split_y);
				Draw(canvas(split_x,0,width,canvas.GetH()-height),style);
			}
			if (canvas.GetW()>width) {
				WBitmap::SetPos(sx+canvas.WBitmap::GetW()-split_x,sy+canvas.WBitmap::GetH()-split_y);
				Draw(canvas(0,0,canvas.GetW()-width,canvas.GetH()-height),style);
			}
		}
	}
	else {
		DWORD userdata=canvas.GetBmpStruct()->userdata;
		int xx=sx-canvas_offset_pos.x,yy=sy-canvas_offset_pos.y;
		int canvas_w=canvas.GetW(),canvas_h=canvas.GetH();

		for (s=canvas.block_y*canvas.col+canvas.block_x,i=canvas.block_y;i<canvas.row;i++,yy+=WCANVASBLOCKH,xx=sx-canvas_offset_pos.x) {
			for (j=canvas.block_x;j<canvas.col;j++,s++,xx+=WCANVASBLOCKW) {
				if (canvas.block[s].last!=canvas.block[s].obj || canvas.block[s].change!=0) 
					changed=tag;
				else UnChange();
				int dx=0,dy=0,dw=WCANVASBLOCKW,dh=WCANVASBLOCKH;
				if (xx-sx<0) dx=sx-xx;
				if (yy-sy<0) dy=sy-yy;
				if (xx-sx+WCANVASBLOCKW>canvas_w) dw-=xx-sx+WCANVASBLOCKW-canvas_w;
				if (yy-sy+WCANVASBLOCKH>canvas_h) dh-=yy-sy+WCANVASBLOCKH-canvas_h;
				dw-=dx,dh-=dy;
				if (dw==WCANVASBLOCKW && dh==WCANVASBLOCKH) {
					WBitmap::SetPos(xx,yy);
					Draw(canvas.block[s](userdata),style);
				}
				else {
					WBitmap::SetPos(xx+dx,yy+dy);
					Draw(canvas.block[s](dx,dy,dw,dh)(userdata),style);
				}
			}
			s-=canvas.col;
			for (j=0;j<canvas.block_x;j++,s++,xx+=WCANVASBLOCKW) {
				if (canvas.block[s].last!=canvas.block[s].obj || canvas.block[s].change!=0) 
					changed=tag;
				else UnChange(); 
				int dx=0,dy=0,dw=WCANVASBLOCKW,dh=WCANVASBLOCKH;
				if (xx-sx<0) dx=sx-xx;
				if (yy-sy<0) dy=sy-yy;
				if (xx-sx+WCANVASBLOCKW>canvas_w) dw-=xx-sx+WCANVASBLOCKW-canvas_w;
				if (yy-sy+WCANVASBLOCKH>canvas_h) dh-=yy-sy+WCANVASBLOCKH-canvas_h;
				dw-=dx,dh-=dy;
				if (dw==WCANVASBLOCKW && dh==WCANVASBLOCKH) {
					WBitmap::SetPos(xx,yy);
					Draw(canvas.block[s](userdata),style);
				}
				else {
					WBitmap::SetPos(xx+dx,yy+dy);
					Draw(canvas.block[s](dx,dy,dw,dh)(userdata),style);
				}
			}
			s+=canvas.col;
		}
		for (s=canvas.block_x,i=0;i<canvas.block_y;i++,yy+=WCANVASBLOCKH,xx=sx-canvas_offset_pos.x) {
			for (j=canvas.block_x;j<canvas.col;j++,s++,xx+=WCANVASBLOCKW) {
				if (canvas.block[s].last!=canvas.block[s].obj || canvas.block[s].change!=0)  
					changed=tag;
				else UnChange();
				int dx=0,dy=0,dw=WCANVASBLOCKW,dh=WCANVASBLOCKH;
				if (xx-sx<0) dx=sx-xx;
				if (yy-sy<0) dy=sy-yy;
				if (xx-sx+WCANVASBLOCKW>canvas_w) dw-=xx-sx+WCANVASBLOCKW-canvas_w;
				if (yy-sy+WCANVASBLOCKH>canvas_h) dh-=yy-sy+WCANVASBLOCKH-canvas_h;
				dw-=dx,dh-=dy;
				if (dw==WCANVASBLOCKW && dh==WCANVASBLOCKH) {
					WBitmap::SetPos(xx,yy);
					Draw(canvas.block[s](userdata),style);
				}
				else {
					WBitmap::SetPos(xx+dx,yy+dy);
					Draw(canvas.block[s](dx,dy,dw,dh)(userdata),style);
				}
			}
			s-=canvas.col;
			for (j=0;j<canvas.block_x;j++,s++,xx+=WCANVASBLOCKW) {
				if (canvas.block[s].last!=canvas.block[s].obj || canvas.block[s].change!=0) 
					changed=tag;
				else UnChange();
				int dx=0,dy=0,dw=WCANVASBLOCKW,dh=WCANVASBLOCKH;
				if (xx-sx<0) dx=sx-xx;
				if (yy-sy<0) dy=sy-yy;
				if (xx-sx+WCANVASBLOCKW>canvas_w) dw-=xx-sx+WCANVASBLOCKW-canvas_w;
				if (yy-sy+WCANVASBLOCKH>canvas_h) dh-=yy-sy+WCANVASBLOCKH-canvas_h;
				dw-=dx,dh-=dy;
				if (dw==WCANVASBLOCKW && dh==WCANVASBLOCKH) {
					WBitmap::SetPos(xx,yy);
					Draw(canvas.block[s](userdata),style);
				}
				else {
					WBitmap::SetPos(xx+dx,yy+dy);
					Draw(canvas.block[s](dx,dy,dw,dh)(userdata),style);
				}
			}
			s+=canvas.col;
		}
	}

	canvas.NextFrame();
	WBitmap::SetPos(sx,sy);
	if (style==BLIT_COPY) SetOvlRect(canvas.GetW(),canvas.GetH());
}

void WCanvas::BlitTo(WBitmap &bmp)
{
	int x=bmp.GetX(),y=bmp.GetY();
	WPoint offset_pos=data->offset;
	int width=MIN((col-block_x)*WCANVASBLOCKW-offset_pos.x,GetW());
	int height=MIN(((row-block_y)*WCANVASBLOCKH-offset_pos.y),GetH());
	int split_x=block_x*WCANVASBLOCKW+offset_pos.x;
	int split_y=block_y*WCANVASBLOCKH+offset_pos.y;
	if (height>0) {
		if (width>0) {
			bmp(x,y).Draw((*(WBitmap*)this)(split_x,split_y,width,height),0);
		}
		if (GetW()>width) {
			bmp(WBitmap::GetW()-split_x+x,y).Draw((*(WBitmap*)this)(0,split_y,GetW()-width,height),0);
		}
	}
	if (GetH()>height) {
		if (width>0) {
			bmp(x,WBitmap::GetH()-split_y+y).Draw((*(WBitmap*)this)(split_x,0,width,GetH()-height),0);
		}
		if (GetW()>width) {
			bmp(WBitmap::GetW()+x-split_x,WBitmap::GetH()+y-split_y).Draw((*(WBitmap*)this)(0,0,GetW()-width,GetH()-height),0);
		}
	}
	bmp(x,y);
}

void WCanvas::Update2DC(HDC hDC,int x,int y) const
{
	WPoint offset_pos=data->offset;
	int width=MIN((col-block_x)*WCANVASBLOCKW-offset_pos.x,GetW());
	int height=MIN(((row-block_y)*WCANVASBLOCKH-offset_pos.y),GetH());
	int split_x=block_x*WCANVASBLOCKW+offset_pos.x;
	int split_y=block_y*WCANVASBLOCKH+offset_pos.y;
	if (height>0) {
		if (width>0) {
			WBitmap::Blit2DC(hDC,x,y,split_x,split_y,width,height);
		}
		if (GetW()>width) {
			WBitmap::Blit2DC(hDC,WBitmap::GetW()-split_x+x,y,0,split_y,GetW()-width,height);
		}
	}
	if (GetH()>height) {
		if (width>0) {
			WBitmap::Blit2DC(hDC,x,WBitmap::GetH()-split_y+y,split_x,0,width,GetH()-height);
		}
		if (GetW()>width) {
			WBitmap::Blit2DC(hDC,WBitmap::GetW()+x-split_x,WBitmap::GetH()+y-split_y,0,0,GetW()-width,GetH()-height);
		}
	}
}

void WCanvas::SleepFrame()
{
	if (m_FrameTime>0) {
		int lastframe;
/*
		if (lastframe>frame) {
			SkipFrame();
			WTimer::Reset(lastframe-frame);
			return;
		}
*/
		bool sleep=!(data->laptop);
		while ((lastframe=m_Timer.GetTime())<m_FrameTime-data->timer) {
			if (sleep) 
				Sleep(5);
		}
		lastframe-=m_FrameTime;
		data->timer=lastframe/2;
		if (lastframe>10000) m_Timer.Reset();
		else m_Timer.Reset(-lastframe);
	}

}

void WCanvas::Blit(HDC hDC,int x,int y)
{
#ifdef _DEBUG_CANVAS
	Update2DC(hDC,x,y);
#else
	int i,j,s;
	WPoint offset_pos=data->offset;
	int width=MIN((col-block_x)*WCANVASBLOCKW-offset_pos.x,GetW());
	int height=MIN(((row-block_y)*WCANVASBLOCKH-offset_pos.y),GetH());
	int split_x=block_x*WCANVASBLOCKW+offset_pos.x;
	int split_y=block_y*WCANVASBLOCKH+offset_pos.y;
	if (data->moved) {
		if (height>0) {
			if (width>0) {
				WBitmap::Blit2DC(hDC,x,y,split_x,split_y,width,height);
			}
			if (GetW()>width) {
    			WBitmap::Blit2DC(hDC,WBitmap::GetW()-split_x+x,y,0,split_y,GetW()-width,height);
			}
		}
		if (GetH()>height) {
			if (width>0) {
    			WBitmap::Blit2DC(hDC,x,WBitmap::GetH()-split_y+y,split_x,0,width,GetH()-height);
			}
			if (GetW()>width) {
    			WBitmap::Blit2DC(hDC,WBitmap::GetW()+x-split_x,WBitmap::GetH()+y-split_y,0,0,GetW()-width,GetH()-height);
			}
		}
	}
	else {
		int xx=x-offset_pos.x,yy=y-offset_pos.y;
		SaveDC(hDC);
		IntersectClipRect(hDC,x,y,x+GetW(),y+GetH());
		for (s=block_y*col+block_x,i=block_y;i<row;i++,yy+=WCANVASBLOCKH,xx=x-offset_pos.x) {
			for (j=block_x;j<col;j++,s++,xx+=WCANVASBLOCKW)
				if (block[s].last!=block[s].obj || block[s].change!=0)
					block[s].Blit2DC(hDC,xx,yy,block[s].offset);
			s-=col;
			for (j=0;j<block_x;j++,s++,xx+=WCANVASBLOCKW)
				if (block[s].last!=block[s].obj || block[s].change!=0)
					block[s].Blit2DC(hDC,xx,yy,block[s].offset);
			s+=col;
		}
		for (s=block_x,i=0;i<block_y;i++,yy+=WCANVASBLOCKH,xx=x-offset_pos.x) {
			for (j=block_x;j<col;j++,s++,xx+=WCANVASBLOCKW)
				if (block[s].last!=block[s].obj || block[s].change!=0) 
					block[s].Blit2DC(hDC,xx,yy,block[s].offset);
			s-=col;
			for (j=0;j<block_x;j++,s++,xx+=WCANVASBLOCKW)
				if (block[s].last!=block[s].obj || block[s].change!=0) 
					block[s].Blit2DC(hDC,xx,yy,block[s].offset);
			s+=col;
		}
		RestoreDC(hDC,1);
	}
#endif
}

void WCanvas::Blit2DC(HDC hDC,int x,int y)
{
	SleepFrame();
	Update();
	Blit(hDC,x,y);
	NextFrame();
}

// 写 ASCII String
void WCanvas::Draw(const char *str, WPixel color)
{
	WText tmp(str);
	WPoint t=WPoint(GetX(),GetY());
	WTextStruct *data=tmp.GetTextStruct();
	data->color=color;
	Draw(tmp,0);
	SetPos(t);
}

WCanvas::~WCanvas()
{
	delete data;
	delete [](block);
}
