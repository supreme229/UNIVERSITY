	.file	"z3.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	""
.LC1:
	.string	"%u"
	.text
	.p2align 4
	.globl	printBits
	.type	printBits, @function
printBits:
.LFB27:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leal	-1(%rdi), %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movslq	%r12d, %rax
	leaq	.LC1(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	leaq	(%rsi,%rax), %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	testl	%r12d, %r12d
	js	.L5
	.p2align 4,,10
	.p2align 3
.L4:
	movl	$7, %r13d
	.p2align 4,,10
	.p2align 3
.L3:
	movzbl	(%rbx), %edx
	movl	%r13d, %ecx
	movq	%rbp, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	subl	$1, %r13d
	sarl	%cl, %edx
	andl	$1, %edx
	call	__printf_chk@PLT
	cmpl	$-1, %r13d
	jne	.L3
	subl	$1, %r12d
	subq	$1, %rbx
	cmpl	$-1, %r12d
	jne	.L4
.L5:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	leaq	.LC0(%rip), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	puts@PLT
	.cfi_endproc
.LFE27:
	.size	printBits, .-printBits
	.p2align 4
	.globl	test
	.type	test, @function
test:
.LFB28:
	.cfi_startproc
	endbr64
	movabsq	$6148914691236517205, %rdx
	movq	%rdi, %rax
	shrq	%rdi
	movabsq	$3689348814741910323, %rcx
	andq	%rdx, %rax
	andq	%rdx, %rdi
	leaq	(%rax,%rdi), %rdx
	movq	%rdx, %rax
	shrq	$2, %rdx
	andq	%rcx, %rax
	andq	%rcx, %rdx
	movabsq	$1085102592571150095, %rcx
	addq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$4, %rdx
	andq	%rcx, %rax
	andq	%rcx, %rdx
	movabsq	$71777214294589695, %rcx
	addq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$8, %rdx
	andq	%rcx, %rax
	andq	%rcx, %rdx
	movabsq	$281470681808895, %rcx
	addq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$16, %rdx
	andq	%rcx, %rdx
	andq	%rcx, %rax
	addq	%rdx, %rax
	movabsq	$-4294967296, %rdx
	andq	%rdx, %rax
	ret
	.cfi_endproc
.LFE28:
	.size	test, .-test
	.p2align 4
	.globl	nlz
	.type	nlz, @function
nlz:
.LFB29:
	.cfi_startproc
	endbr64
	movl	$6, %edx
	movl	$32, %ecx
	movl	$64, %eax
	.p2align 4,,10
	.p2align 3
.L15:
	movq	%rdi, %rsi
	shrq	%cl, %rsi
	testq	%rsi, %rsi
	je	.L14
	subq	%rcx, %rax
	movq	%rsi, %rdi
.L14:
	sarq	%rcx
	subl	$1, %edx
	jne	.L15
	subl	%edi, %eax
	ret
	.cfi_endproc
.LFE29:
	.size	nlz, .-nlz
	.p2align 4
	.globl	zeroer
	.type	zeroer, @function
zeroer:
.LFB30:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
	movq	%rdi, %rdx
	shrq	%rdi
	movq	%rax, %rcx
	shrq	$32, %rdx
	shrq	$2, %rcx
	orq	%rcx, %rdi
	movq	%rax, %rcx
	orq	%rax, %rdi
	shrq	$4, %rcx
	orq	%rcx, %rdi
	movq	%rax, %rcx
	shrq	$16, %rax
	shrq	$8, %rcx
	orq	%rcx, %rdi
	movabsq	$1085102592571150095, %rcx
	orq	%rax, %rdi
	movabsq	$6148914691236517205, %rax
	orq	%rdx, %rdi
	movq	%rdi, %rdx
	shrq	%rdi
	andq	%rax, %rdx
	andq	%rax, %rdi
	leaq	(%rdx,%rdi), %rax
	movabsq	$3689348814741910323, %rdi
	movq	%rax, %rdx
	shrq	$2, %rax
	andq	%rdi, %rdx
	andq	%rdi, %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	shrq	$4, %rax
	andq	%rcx, %rdx
	andq	%rcx, %rax
	movabsq	$71777214294589695, %rcx
	addq	%rdx, %rax
	movq	%rax, %rdx
	shrq	$8, %rax
	andq	%rcx, %rdx
	andq	%rcx, %rax
	movabsq	$281470681808895, %rcx
	addq	%rdx, %rax
	movq	%rax, %rdx
	shrq	$16, %rax
	andq	%rcx, %rdx
	andq	%rcx, %rax
	addq	%rdx, %rax
	movl	%eax, %edx
	shrq	$32, %rax
	addq	%rax, %rdx
	movl	$64, %eax
	subq	%rdx, %rax
	ret
	.cfi_endproc
.LFE30:
	.size	zeroer, .-zeroer
	.section	.rodata.str1.1
.LC2:
	.string	"%lu"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB31:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$11, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	leaq	.LC2(%rip), %rsi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE31:
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
