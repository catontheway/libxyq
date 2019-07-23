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
;		Description:		16位 Font Blit
;		Original Author:	云风
;		Authors:
;		Create Time:		2001/3/12
;		Modify Time:		2001/11/12
;
;:*W*:._.:*I*:_.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:

[bits 32]

%include "c32.mac"
%include "wpp.inc"
%include "fontclip.mac"

[section .data class=data use32]
mask_r	dd	0xf800f800,0xf800f800
mask_g	dd	0x07e007e0,0x07e007e0
mask_b	dd	0x001f001f,0x001f001f

[section .bss class=bss use32]
mask	resq	1

[section .text class=code use32]

;WSERR _stdcall _font16_alpha(WBmpStruct *,const WCharStruct *);
;function _font16_alpha
;proc __font16_alpha@8
function _font16_alpha
proc __font16_alpha@8
	saveesi
	saveedi
	saveebx
%$back	arg
%$c	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$c)		; edx = char 指针
	mov ecx,var(%$back)		; 目标图
	fontclip 16			; 剪裁处理(16 bit)
					; ebx=char(源)指针,ecx=back(目标)指针
					; esi=源地址, edi=目标地址
.blit:
	movd mm7,[ebx+WCharStruct.color]
	pcmpeqd mm6,mm6
	mov edx,[ecx+WBmpStruct.pitch]	; 目标图 pitch
	mov eax,var(%$w)
	punpcklwd mm7,mm7
	sub eax,4
	punpckldq mm7,mm7		; mm7=color
	mov var(%$w4),eax
	and eax,3
	shl eax,4
	mov ebx,[ebx+WCharStruct.w]	; 源图 pitch
	movd mm5,eax
	cld
	psllq mm6,mm5
	xor ecx,ecx
	movq [mask],mm6
	align 4
.loop:	
	mov eax,0x10101010
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add esi,ebx
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
	align 4
.4pixel:
	movq [edi+ecx*2],mm7
.skip4pixel:
	add ecx,4
	jmp .loop
	align 4
.loop_pixel:
	cmp ecx,var(%$w4)
	jle .skip_not_tail
	sub eax,[esi+ecx]
	jmp .begin_draw
.skip_not_tail:
	sub eax,[esi+ecx]		; 16-alpha 值
	jz .4pixel
.begin_draw:
	cmp eax,0x10101010
	jz .skip4pixel
	pxor mm4,mm4
	movd mm6,eax
	movq mm3,mm7
	punpcklbw mm6,mm4		; mm5 = 16-alpha 通道
	movq mm0,[edi+ecx*2]		; 目标像素
	movq mm4,mm3
	movq mm5,mm3
	psrlw mm3,4
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,4
	pand mm1,[mask_g]
	psubw mm0,mm3
	movq mm3,mm2
	pand mm2,[mask_b]
	psubw mm1,mm4
	pmullw mm0,mm6
	psubw mm2,mm5
	pmullw mm1,mm6
	paddw mm0,mm7
	pmullw mm2,mm6
	psrlw mm1,4
	psrlw mm2,4
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	cmp ecx,var(%$w4)
	por mm0,mm2
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

;WSERR _stdcall _font16_noalpha(WBmpStruct *,const WCharStruct *);
function _font16_noalpha
proc __font16_noalpha@8
	saveesi
	saveedi
	saveebx
%$back	arg
%$c	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$c)		; edx = char 指针
	mov ecx,var(%$back)		; 目标图
	fontclip 16			; 剪裁处理(16 bit)
					; ebx=char(源)指针,ecx=back(目标)指针
					; esi=源地址, edi=目标地址
.blit:
	movd mm7,[ebx+WCharStruct.color]
	pcmpeqd mm6,mm6
	mov edx,[ecx+WBmpStruct.pitch]	; 目标图 pitch
	mov eax,var(%$w)
	punpcklwd mm7,mm7
	sub eax,4
	punpckldq mm7,mm7		; mm7=color
	mov var(%$w4),eax
	and eax,3
	mov ecx,0x000c000c
	shl eax,4
	movd mm1,ecx
	mov ebx,[ebx+WCharStruct.w]	; 源图 pitch
	movd mm5,eax
	punpckldq mm1,mm1		; mm1=0x000c000c000c000c
	psllq mm6,mm5
	pxor mm4,mm4
	xor ecx,ecx
	cld
	jmp .loop
	align 4
.4pixel:
	movq [edi+ecx*2],mm7

.skip4pixel:
	add ecx,4
.loop:	
	mov eax,0x10101010
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add esi,ebx
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
	align 4
.loop_pixel:
	cmp ecx,var(%$w4)
	jle .skip_not_tail
	sub eax,[esi+ecx]
	jmp .begin_draw
.skip_not_tail:
	sub eax,[esi+ecx]		; 16-alpha 值
	jz .4pixel
.begin_draw:
	cmp eax,0x10101010
	jz .skip4pixel
	movd mm5,eax
	movq mm2,mm7
	punpcklbw mm5,mm4		; mm5 = 16-alpha 通道
	movq mm0,[edi+ecx*2]		; 目标像素
	pcmpgtw mm5,mm1
	psubusw mm2,mm5
	pand mm5,mm0
	cmp ecx,var(%$w4)
	por mm5,mm2
	jle .not_tail
	pand mm0,mm6
	psubusw mm5,mm6
	por mm0,mm5
	movq [edi+ecx*2],mm0
	jmp .nextline
.not_tail:
	movq [edi+ecx*2],mm5
	jmp .skip4pixel
.end:	
	xor eax,eax
endproc
