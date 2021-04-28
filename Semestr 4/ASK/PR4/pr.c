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
        .globl  cubef
        .type   cubef, @function

/*
 * W moim rozwiązaniu używam następującej techniki: ____ ____ ____ ____
 */

cubef:
        mov %rdi, %rsi
        mov %rdi, %r9
        mov %rdi, %rax
        shr $31, %rsi # w rsi sam znak
        mov $0x7F800000, %r8
        and %r8, %r9 # w r9 exponent
        shr $23, %r9
        mov $0x7FFFFF, %r8
        and %r8, %rax # w rax mantysa
#-- -- -- -- -- -- --->(9)
        sub $127, %r9
        imul $3, %r9
        add $127, %r9
#-- -- -- -- -- -- --->3 exp(2)
        mov %rax, %r8
        imul %r8, %r8
        mul %r8
#-- -- -- -- -- -- --->wymnożenie mantysy(3) #GIT 
        mov $0, %rcx
        mov %rdx, %r8
        shr $6, %r8
        and $1, %r8
        cmp $1, %r8
        jne .L1
        mov $1, %rcx
.L1:    mov %rdx, %r8
        shr $7, %r8
        and $1, %r8
        cmp $1, %r8
        jne .L2
        mov $2, %rcx
#-- -- -- -- -- -- --> normalizacja(? ? ?)(16)
.L2:     add %rcx, %r9
#-- -- -- -- -- --->dodanie do expa(1)
        mov %rax, %rdi
        shr $47, %rdi
        shr %rcx, %rdi
        and $1, %rdi # guard(???)
        mov %rax, %r8
        shl $15, %r8
        shl %rcx, %r8 
        cmp $0, %r8
        mov $0, %r8
        setnz %r8b # sticky(???)
        or %rdi, %r8
        mov %rax, %rdi
        shr $48, %rdi
        shr %rcx, %rdi
        and $1, %rdi # round(???)
        and %r8, %rdi # wynik predykatu
#-- -- -- -- -- -- ---> 
        shr $47, %rax
        shr %rcx, %rax
        shl $6, %rdx
        shl %rcx, %rdx
        or %rdx, %rax
#-- -- -- -- -- -- --->
        cmp $0, %rdi
        setnz %dil
        shl $31, %rsi
        add %rdi, %rax
        mov %r9, %r8 # kopia expa
        add $127, %r8
        cmp $255, %r8
        jle .L3
        mov $0x7F800000, %rcx
        or %rcx, %rsi
        mov %rsi, %rax
        ret
.L3:    cmp $0, %r8 # popraw
        jge .L4
        or $0, %rsi
        mov %rsi, %rax
        ret
.L4:     
        shl $23, %r9
        or %rsi, %rax
        or %r9, %rax
        ret 

        .size   cubef, .-cubef
