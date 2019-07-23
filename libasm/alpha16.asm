;
;                ..;;;;,                     ;;;,    
;            ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
;      ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
;      ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
;     .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
;    ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
;    ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
;   :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
; .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
;;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
;""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
;
;                       Windsoul++
;
;               by 云风 (Cloud Wu)  1999-2001
;
;       http://member.netease.com/~cloudwu 
;		mailto:cloudwu@263.net
; 
;		请阅读 readme.txt 中的版权信息
;		See readme.txt for copyright information.
;
;		Description:		16位Alpha位图 Blit
;		Original Author:	云风
;		Authors:
;		Create Time:		2001/3/10
;		Modify Time:
;
;:*W*:._.:*I*:_.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:

[bits 32]

%include "c32.mac"
%include "wpp.inc"
%include "bmpclip.mac"

[section .text class=code use32]

; 把 16 位 Alpha 位图 bmp BLIT 到 this 位图上
;WSERR _stdcall _alpha_blit16(WBmpStruct *,const WAlphaBmpStruct *);
function _alpha_blit16
proc __alpha_blit16@8
	saveesi
	saveedi
	saveebx
	saveebp
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp 指针
	mov ecx,var(%$this)		; 保存 this 指针
	mov ebp,[ebx+WBmpStruct.ptr]	; ebp 为源图指针
	bmpclip	16			; 剪裁处理(16 bit)
					; ebx=bmp(目标)指针,ecx=this(源)指针
					; esi=源地址, edi=目标地址
.blit:
	pcmpeqd mm6,mm6
	sub ebp,esi
	mov edx,[ecx+WBmpStruct.pitch]	; 目标图 pitch
	neg ebp
	mov eax,var(%$w)
	shr ebp,1
	sub eax,4
	xor ecx,ecx
	mov var(%$w4),eax
	and eax,3
	add ebp,[ebx+WAlphaBmpStruct.channel]
	shl eax,4
	mov ebx,[ebx+WBmpStruct.pitch]	; 源图 pitch
	movd mm5,eax
	sar ebx,1
	psllq mm6,mm5
	cld
	align 4
.loop:	
	mov eax,0x20202020
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add ebp,ebx
	lea esi,[esi+ebx*2]
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
.skip4pixel:
	add ecx,4
	jmp .loop
.loop_pixel:
	sub eax,[ebp+ecx]		; 32-alpha 值
	jz .4pixel
	cmp eax,0x20202020
	jz .skip4pixel
	pxor mm4,mm4
	movd mm7,eax
	movq mm0,[edi+ecx*2]		; 目标像素
	punpcklbw mm7,mm4		; mm7 = 32-alpha 通道
	movq mm1,mm0
	movq mm4,mm0
	movq mm2,[mask_b]
	psrlw mm0,11			; mm0 = red
	pand mm2,mm4			; mm2 = blue
	pand mm1,[mask_g]		; mm1 = green
	pmullw mm0,mm7
	psrlw mm1,5
	pmullw mm2,mm7
	psllw mm0,6
	pmullw mm1,mm7
	psrlw mm2,5
;	psrlw mm1,3
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	cmp ecx,var(%$w4)
	paddw mm0,[esi+ecx*2]
	jle .not_tail
.clip:
	pand mm4,mm6
	psubusw mm0,mm6
	por mm0,mm4
	movq [edi+ecx*2],mm0
	jmp .nextline
.4pixel:
	cmp ecx,var(%$w4)
	movq mm0,[esi+ecx*2]
	jle .neednotclip
	movq mm4,[edi+ecx*2]
	jmp .clip
.neednotclip:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.not_tail:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; 返回 this 指针
endproc

function _alpha_trans_blit16
proc __alpha_trans_blit16@8
	saveesi
	saveedi
	saveebx
	saveebp
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp 指针
	movd mm7,[ebx+WBmpStruct.data]
	mov ecx,var(%$this)		; this 指针
	psrlw mm7,3
	mov ebp,[ebx+WBmpStruct.ptr]	; ebp 为源图指针
	bmpclip	16			; 剪裁处理(16 bit)
					; ebx=bmp(目标)指针,ecx=this(源)指针
					; esi=源地址, edi=目标地址
.blit:
	punpcklwd mm7,mm7
	pcmpeqd mm6,mm6
	punpckldq mm7,mm7		; mm7=alpha
	sub ebp,esi
	mov edx,[ecx+WBmpStruct.pitch]	; 目标图 pitch
	neg ebp
	mov eax,var(%$w)
	shr ebp,1
	sub eax,4
	xor ecx,ecx
	mov var(%$w4),eax
	and eax,3
	add ebp,[ebx+WAlphaBmpStruct.channel]
	shl eax,4
	mov ebx,[ebx+WBmpStruct.pitch]	; 源图 pitch
	movd mm5,eax
	sar ebx,1
	psllq mm6,mm5
	cld
	movq [mask],mm6
	align 4
.loop:	
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add ebp,ebx
	lea esi,[esi+ebx*2]
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
.skip4pixel:
	add ecx,4
	jmp .loop
.loop_pixel:
	mov eax,[ebp+ecx]		; alpha 值
	test eax,eax
	jz .skip4pixel

	movd mm6,eax
	movq mm4,[solid]
	movq mm3,[edi+ecx*2]
	punpcklbw mm6,mm4
	movq mm0,[esi+ecx*2]		; 目标像素
	pcmpeqw mm6,mm4
	movq mm4,mm3
	pand mm6,mm7			; mm6 = alpha
	movq mm5,mm3

	psrlw mm3,5
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,5
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	psubw mm0,mm3
	psubw mm1,mm4
	pmullw mm0,mm6
	movq mm3,[edi+ecx*2]
	psubw mm2,mm5
	pmullw mm1,mm6
	paddw mm0,mm3
	pmullw mm2,mm6
	psrlw mm1,5
	psrlw mm2,5
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	por mm0,mm2

	cmp ecx,var(%$w4)
	jle .not_tail
	pand mm3,[mask]
	psubusw mm0,[mask]
	por mm0,mm3
	movq [edi+ecx*2],mm0
	jmp .nextline
.not_tail:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.end:	
	xor eax,eax
endproc

[section .data class=data use32]
mask_r	dd	0xf800f800,0xf800f800
mask_g	dd	0x07e007e0,0x07e007e0
mask_b	dd	0x001f001f,0x001f001f
solid	dd	0x20202020,0x20202020

[section .bss class=bss use32]
mask	resq	1