#include <stdlib.h>
#include <string.h>
#include "jpegint.h"
#pragma warning(disable:4996) 
struct {
	PACKFILE *f;
	unsigned char *buf;
	int freq;
} filebuffer[FILEBUFFERNUM]={{NULL,NULL,0}};

DATAFILE *datafile=NULL;
char virtualpath[PATHMAXLEN]="/\0";

//矫正目录(去掉.., 将\改为/, 全部换成小写, 只支持两个 . 返回上层目录)
void adjust_path(char *s)
{
	int i;
	char tmp[PATHMAXLEN],*p;
	strlwr(s);
	for (i=0,p=s;*p;++p,++i) {
		if (*p=='\\') *p='/';
		else if (*p=='.' && *(p-1)=='/') {
			if (*(p+1)=='.' && (*(p+2)=='/' || *(p+2)=='\\' || *(p+2)==0)) {
				// 处理 '..'
				for (i-=2;i>=0;i--) 
					if (tmp[i]=='/') break;
				if (i<0) i+=2;
				p+=2;
			}
		}
		else tmp[i]=*p;
	}
	tmp[i]=0;
	strcpy(s,tmp);
}

// 矫正文件名
void adjust_filename(char *s)
{
	char tmp[PATHMAXLEN];
	if (s[0]=='/' || s[0]=='\\') strcpy(tmp,s);
	else {
		strcpy(tmp,virtualpath);
		strcat(tmp,s);
	}
	strcpy(s,tmp);
	adjust_path(tmp);
	strcpy(s,tmp+1);
}

// 获得一个可用的缓冲区地址
unsigned char *get_buffer(PACKFILE *f)
{
	int i,s,*freq,buf,p=0;
	if (f->buf) {
		freq=&filebuffer[(f->buf-filebuffer[0].buf)>>16].freq;
		for (s=i=0;i<FILEBUFFERNUM;i++)
			if (filebuffer[i].f && filebuffer[i].freq>*freq) --filebuffer[i].freq,++s;
		*freq+=s;
		return f->buf;
	}
	for (s=i=0;i<FILEBUFFERNUM;i++)
		if (filebuffer[i].f) ++s;
		else buf=i;
		if (s<FILEBUFFERNUM) {
			filebuffer[buf].f=f;
			filebuffer[buf].freq=s;
			return (f->buf=filebuffer[buf].buf);
		}
		for (i=0;i<FILEBUFFERNUM;i++)
			if (filebuffer[i].freq==0 && p==0) 
				filebuffer[i].freq=FILEBUFFERNUM-1,
				filebuffer[i].f=f,
				f->buf=filebuffer[i].buf,
				p=1;
			else if (filebuffer[i].freq!=0) --filebuffer[i].freq;
			return f->buf;
}

PACKFILE *pack_fopen(char *filename)
{
	PACKFILE *f;
	FILE *file;
	//CW 4.12e
	int b=0,e,m;
	//CW 4.12
	char name[PATHMAXLEN];
	unsigned id,sid;
	strcpy(name,filename);
//	adjust_filename(name);

	file=fopen(name,"rb");
	if (file) { // 包外存在同名文件
		f=malloc(sizeof(*f)-sizeof(unsigned short)-sizeof(unsigned));
		f->datafile=file;
		fseek(file,0,SEEK_END);
		f->len=ftell(file);
		f->offset=0;
		f->buf=NULL;
		fseek(file,0,SEEK_SET);
	}
	else {
		//CW 4.12a
		if (!datafile) return NULL;
		e=datafile->filenum-1;
		//CW
		id=filename2id(name);
		while(b<=e) {
			m=(b+e)/2,sid=datafile->block[m].id;
			if (id==sid) goto _found_id;
			if (id<sid) e=m-1;
			else b=m+1;
		}
		return NULL;
_found_id:
		f=malloc(sizeof(*f)+((b=(datafile->block[m].len+0xffff)>>16)-1)*sizeof(unsigned short));
		f->datafile=datafile->file;
		f->offset=datafile->block[m].offset+b*sizeof(unsigned short);
		f->len=datafile->block[m].len;
		fseek(datafile->file,datafile->block[m].offset,SEEK_SET);
		fread(f->block,sizeof(unsigned short),b,datafile->file);
		f->datapos=ftell(datafile->file);
		f->buf=NULL;
	}
	f->pos=0;
	return f;
}

void readblock(unsigned char *buf,int block,PACKFILE *f)
{
	static unsigned char compressbuf[0x10000];
	fseek(f->datafile,f->datapos,SEEK_SET);
	if (f->block[block]==0) {
		fread(buf,0x10000,1,f->datafile);
		return;
	}
	fread(compressbuf,f->block[block],1,f->datafile);
	decompress (compressbuf , f->block[block], buf);
}

unsigned pack_fread(void *buffer, unsigned size, PACKFILE *f)
{
	int block,readsize;
	unsigned short blockpos;
	unsigned char *buf;
	buf=buffer;

	if (f->offset==0)
		return (unsigned)fread(buf,1,size,f->datafile);
	if (f->pos+size>f->len) readsize=size=f->len-f->pos;
	else readsize=size;
	block=f->pos>>16;
	blockpos=f->pos&0xffff;

	if (blockpos) { //以前读过数据
		if (f->buf==0) { //若缓冲区丢失则恢复
			get_buffer(f);
			readblock(f->buf,block,f);
		}
		if (blockpos+size<=0x10000) {
			memcpy(buf,f->buf+blockpos,size);
			f->pos+=size;
			if (((f->pos)&(0xffff))==0) f->datapos+=f->block[block];
			return (unsigned)size;
		}
		memcpy(buf,f->buf+blockpos,0x10000-blockpos);
		buf+=0x10000-blockpos;
		f->datapos+=f->block[block];
		f->pos=(++block)<<16;
		size-=(0x10000-blockpos);
	}

	while (size>0xffff) {
		readblock(buf,block,f);
		buf+=0x10000;
		f->datapos+=f->block[block];
		f->pos=(++block)<<16;
		size-=0x10000;
	}

	if (size==0) return (unsigned)readsize;

	get_buffer(f);
	readblock(f->buf,block,f);
	memcpy(buf,f->buf,size);

	f->pos+=size;

	return (unsigned)readsize;
}

void pack_fclose(PACKFILE *pf)
{
	if (!pf) return;
	if (pf->buf)			// 释放占用着的缓冲区
		filebuffer[(pf->buf-filebuffer[0].buf)>>16].f=NULL;
	if (pf->offset==0) fclose(pf->datafile); // 如果是真实文件就需要关闭
	free(pf);
}

// 文件名转换成 32bit ID 
unsigned filename2id(char *name)
{
	unsigned int s;
	int i;
	for (s=i=0;name[i];i++)
		s=(s+(i+1)*name[i])%0x8000000bu*0xffffffefu;
	return s^0x12345678;
}