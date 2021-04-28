	.file	"z3.c"
	.text
	.globl	swapper
	.type	swapper, @function
swapper:
.LFB27:
	.cfi_startproc
	endbr64
	movq 	%rdi, %rdx
	rolq    $32, %rdx
	roll 	$16, %edi
	roll 	$16, %edx
	rolq 	$32, %rdi
	orq 	%rdx, %rdi
	movq	%rdi, %rax
	shrq	$8, %rax
	movq	$71777214294589695, %rcx
	andq	%rcx, %rax
	salq	$8, %rdi
	movq	$-71777214294589696, %rcx
	andq	%rcx, %rdi
	orq		%rdi, %rax
	movq	%rax, %rcx
	shrq	$4, %rcx
	movq	$1085102592571150095, %rdx
	andq	%rdx, %rcx
	salq	$4, %rax
	movq	$-1085102592571150096, %rdx
	andq	%rdx, %rax
	orq	%rax, %rcx
	movq	%rcx, %rdx
	shrq	$2, %rdx
	movq	$3689348814741910323, %rax
	andq	%rax, %rdx
	salq	$2, %rcx
	movq	$-3689348814741910324, %rax
	andq	%rax, %rcx
	orq	%rcx, %rdx
	movq	%rdx, %rax
	shrq	%rax
	movq	$6148914691236517205, %rcx
	andq	%rcx, %rax
	addq	%rdx, %rdx
	movq	$-6148914691236517206, %rcx
	andq	%rcx, %rdx
	orq	%rdx, %rax
	ret
	.cfi_endproc
.LFE27:
	.size	swapper, .-swapper
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%lu"
	.text
	.globl	main
	.type	main, @function
main:
.LFB28:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movabsq	$-4768904339974520832, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE28:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
