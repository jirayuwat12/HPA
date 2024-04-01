	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 3	sdk_version 13, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	stp	x28, x27, [sp, #-32]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	mov	w9, #50896
	movk	w9, #45, lsl #16
Lloh0:
	adrp	x16, ___chkstk_darwin@GOTPAGE
Lloh1:
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	sub	sp, sp, #732, lsl #12           ; =2998272
	sub	sp, sp, #1744
	mov	x8, #0
Lloh2:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh3:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh4:
	ldr	x9, [x9]
	stur	x9, [x29, #-24]
	add	x9, sp, #488, lsl #12           ; =1998848
	add	x9, x9, #1160
	mov	w10, #2000
	add	x11, sp, #8
LBB0_1:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_2 Depth 2
                                        ;       Child Loop BB0_3 Depth 3
	mov	x12, #0
	madd	x13, x8, x10, x11
	add	x14, sp, #244, lsl #12          ; =999424
	add	x14, x14, #584
LBB0_2:                                 ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_3 Depth 3
	mov	x15, #0
	ldr	w16, [x13, x12, lsl #2]
	mov	x17, x14
LBB0_3:                                 ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_2 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	ldr	w0, [x9, x15]
	ldr	w1, [x17]
	madd	w16, w1, w0, w16
	add	x17, x17, #2000
	add	x15, x15, #4
	cmp	x15, #2000
	b.ne	LBB0_3
; %bb.4:                                ;   in Loop: Header=BB0_2 Depth=2
	str	w16, [x13, x12, lsl #2]
	add	x12, x12, #1
	add	x14, x14, #4
	cmp	x12, #500
	b.ne	LBB0_2
; %bb.5:                                ;   in Loop: Header=BB0_1 Depth=1
	add	x8, x8, #1
	add	x9, x9, #2000
	cmp	x8, #500
	b.ne	LBB0_1
; %bb.6:
	ldur	x8, [x29, #-24]
Lloh5:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh6:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh7:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB0_8
; %bb.7:
	mov	w0, #0
	add	sp, sp, #732, lsl #12           ; =2998272
	add	sp, sp, #1744
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #32             ; 16-byte Folded Reload
	ret
LBB0_8:
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh2, Lloh3, Lloh4
	.loh AdrpLdrGot	Lloh0, Lloh1
	.loh AdrpLdrGotLdr	Lloh5, Lloh6, Lloh7
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
