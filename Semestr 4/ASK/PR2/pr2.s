/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: __________ __________, ______
 */

        .text
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki: ____ ____ ____ ____
 */

clz:
	mov     %rdi, %r8
	mov		%rdi, %rax
	shr 	$2, %rax
	shr 	$1, %rdi
	orq     %rdi, %rax
	shrq    $3, %rdi
	orq     %rdi, %rax
	shrq    $4, %rdi
	orq     %rdi, %rax
	shrq    $8, %rdi
	orq     %rdi, %rax
	shrq    $16, %rdi
	orq     %rdi, %rax
	orq     %r8, %rax
	not     %rax
	# ------------------>
	mov     %rax, %rcx
	mov     $0x5555555555555555, %rdx
	shrq    $1, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# ------------------->
	mov     %rax, %rcx
	mov     $0x3333333333333333, %rdx
	shrq    $2, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# ------------------->
	mov     %rax, %rcx
	mov     $0x0F0F0F0F0F0F0F0F, %rdx
	shrq    $4, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# ------------------->
	mov     %rax, %rcx
	mov     $0x00FF00FF00FF00FF, %rdx
	shrq    $8, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# ------------------->
	mov     %rax, %rcx
	mov     $0x0000FFFF0000FFFF, %rdx
	shrq    $16, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# ------------------->
	mov     %rax, %rcx
	shrq    $32, %rcx
	or      %ecx, %ecx
	add     %rcx, %eax
	ret

        .size   clz, .-clz
