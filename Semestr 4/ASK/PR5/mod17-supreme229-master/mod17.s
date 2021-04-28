/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: Bartosz Janikowski, 315489
 */
        .data
        mask1: .quad 0x0F0F0F0F0F0F0F0F
        number1: .quad 136
        mask2: .quad 0x0F
        number2: .quad 17

        .text
        .globl  mod17
        .type   mod17, @function

/*
 * W moim rozwiązaniu używam następującej techniki: ____ ____ ____ ____
*/

mod17:
        mov     %rdi, %rax

        and     mask1, %rax
        mov     %rax, %rcx
	shrq    $8, %rcx
	add     %rcx, %rax
	mov     %rax, %rcx
	shrq    $16, %rcx
	add     %rcx, %rax
	mov     %rax, %rcx
	shrq    $32, %rcx
	add     %ecx, %eax      

        shr     $4, %rdi
        and     mask1, %rdi
        mov     %rdi, %rcx
	shrq    $8, %rcx
	add     %rcx, %rdi
	mov     %rdi, %rcx
	shrq    $16, %rcx
	add     %rcx, %rdi
	mov     %rdi, %rcx
	shrq    $32, %rcx
	add     %ecx, %edi   

        sub     %dil, %al

        mov     $0, %r9b
        cmovs   number1, %r9
        add     %r9b, %al

        mov     %al, %r10b
        and     mask2, %rax
        shr     $4, %r10b
        sub     %r10b, %al

        mov     $0, %r9b
        cmovs   number2, %r9
        add     %r9b, %al

        ret

        .size   mod17, .-mod17
