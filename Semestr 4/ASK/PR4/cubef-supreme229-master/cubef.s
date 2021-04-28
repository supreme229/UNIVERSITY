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

        .text
        .globl  cubef
        .type   cubef, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
 Lista kroków:
 
 1. Zapisanie do rejestrów osobno mantysy, wykładnika i znaku. Robię to wykorzystując maski i przesunięcia.
 
 2. Z wykorzystaniem maski wstawiam 1 do mantysy (to jest 1,xxxx. 1 przed x-em)
 
 3. Wyznaczenie wykładnika z wykorzystaniem biasu.
 
 4. Wymnożenie mantysy. Zapisana ona po całym wymnożeniu będzie w RDX:RAX
 
 5. Normalizacja, a dokładnie wyznaczenie ile będzie trzeba przesunąć przecinek i zapisanie tego w %rcx.
 
 6. Dodanie do wykładnika przesunięcia, które dokonałem.
 
 7. Wyznaczenie bitu sticky, potrzebne do znalezienia zaokrąglenia.
 
 8. I kolejno guard
 
 9. I round
 
 10. Złączenie rdx i rax by miec mantyse w rax 
 
 11. Dodanie zaokrąglenia i przesunięcie signa by mieć go na 32 bicie w rsi
 
 12. Wyznaczenie mantysy i ucięcie (1,) które dodałem w kroku 2.
 
 13. Sprawdzenie wszystkich warunków dla +- inf i +-0
 
 14. Zwrócenie wyniku normalnego
 */

cubef:
        mov %rdi, %rdi
        mov %edi, %esi
        mov %edi, %r9d
        mov %edi, %eax
        shr $31, %rsi # w rsi znak
        mov $0x7F800000, %r8
        and %r8, %r9 # w r9 exponent
        shr $23, %r9
        mov $0x7FFFFF, %r8
        and %r8, %rax # w rax mantysa
        # ---------------> krok 1
        mov $0x0000000000800000, %r8
        or %r8, %rax
        # ---------------> krok 2
        sub $127, %r9
        imul $3, %r9
        add $127, %r9
        # ---------------> krok 3
        mov %rax, %r8
        imul %r8, %r8
        mul %r8
        # ---------------> krok 4
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
        # --------------> krok 5
.L2:     add %rcx, %r9
        # -------------> krok 6
        mov %rax, %r8
        mov %rcx, %rdi
        mov $19, %rcx
        sub %rdi, %rcx
        shl %cl, %r8
        mov %rdi, %rcx 
        cmp $0, %r8
        mov $0, %r8
        setnz %r8b # sticky
        # --------------> krok 7
        mov %rax, %rdi
        shr $46, %rdi
        shr %cl, %rdi
        and $1, %rdi # guard
        # --------------> krok 8
        or %rdi, %r8
        mov %rax, %rdi
        shr $45, %rdi
        shr %cl, %rdi
        and $1, %rdi # round(???)
        # ---------------> krok 9
        and %r8, %rdi # wynik predykatu
        shr $46, %rax
        shr %cl, %rax 
        shl $18, %rdx  
        shr %cl, %rdx
        or %rdx, %rax
        # ---------------> krok 10
        shl $31, %esi
        add %rdi, %rax
        # ---------------> krok 11
        mov $0x7FFFFF, %r8
        and %r8, %rax
        mov %r9, %r8 
        # ---------------> krok 12
        cmp $255, %r8
        jl .L3
        mov $0x7F800000, %ecx
        or %ecx, %esi
        mov %esi, %eax
        ret
.L3:    cmp $0, %r8 # popraw
        jge .L4
        or $0, %rsi
        mov %rsi, %rax
        ret
.L4:     
        # -----------------> krok 13
        shl $23, %r9
        or %rsi, %rax
        or %r9, %rax
        # -----------------> krok 14
        ret 

        .size   cubef, .-cubef
