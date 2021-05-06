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
        mask1: .quad 0x7F800000
        mask2: .quad 0x0000000000800000
        mask3: .quad 0x7FFFFF
        mask4: .long 0x80000000
        number1: .quad 1
        number2: .quad 2
        

        
        .text
        .globl  cubef
        .type   cubef, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
 Lista kroków:
 
 1. Zapisanie do rejestrów osobno mantysy, wykładnika i znaku. Robię to wykorzystując maski i przesunięcia.
 
 2. Z wykorzystaniem maski wstawiam dodatkowe 1 do mantysy (to jest 1,xxxx. czyli jakby część całkowita)
 
 3. Wyznaczenie wykładnika z wykorzystaniem biasu.
 
 4. Wymnożenie mantysy. Zapisana ona po całym wymnożeniu będzie w RDX:RAX
 
 5. Normalizacja, a dokładnie wyznaczenie ile będzie trzeba przesunąć przecinek i zapisanie tego w %rcx.
 
 6. Dodanie do wykładnika przesunięcia, które dokonałem.
 
 7. Wyznaczenie bitu sticky, potrzebne do znalezienia zaokrąglenia.
 
 8. I kolejno guard
 
 9. I round
 
 10. Złączenie rdx i rax by miec mantyse w rax
 
 11. Dodanie ewentualnego zaokrąglenia #wynik predykatu to oczywiście
 jak na wykładzie. Gdy round = 1 i guard = 1 lub round = 1 i sticky = 1
 
 12. Ucięcie (1,) które dodałem w kroku 2.
 
 13. Generalnie jest to krok wyznaczający naszą liczbę, ale bez znaku
 znak robię niżej a to zostało wymuszone przez podejście jakie miałem do sprawdzenia
 infów. Gdybym tu już ustawił znak to wywali mi się sprawdzenie -inf. Bo
 korzystam tam z maski, która ma 0 na znaku i sobie go zmieniam tam na miejscu. 
 Zauważmy, że jak zmieniam tam to odrazu też zmieniam znak gdy inf nie zachodzi, więc
 wszystko działa poprawnie. 

 14. Sprawdzenie wszystkich warunków dla +- inf i +-0

 15. Zwrócenie wyniku :)
*/

cubef:
        mov %edi, %esi
        mov %edi, %r9d
        mov %edi, %eax
        and mask4, %rsi # w rsi znak
        and mask1, %r9 # w r9 exponent
        shr $23, %r9
        and mask3, %rax # w rax mantysa
        # ---------------> krok 1
        or mask2, %rax
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
        and $0x40, %r8
        cmp $0x40, %r8
        cmove number1, %rcx
        mov %rdx, %r8
        and $0x80, %r8
        cmp $0x80, %r8
        cmove number2, %rcx
        # --------------> krok 5
        add %rcx, %r9
        # -------------> krok 6
        mov %rax, %r8
        mov %rcx, %r10
        mov $19, %rcx
        sub %r10, %rcx
        shl %cl, %r8
        mov %r10, %rcx 
        cmp $0, %r8
        mov $0, %r8
        setnz %r8b # sticky
        # --------------> krok 7
        mov %rax, %r10
        shr $46, %r10
        shr %cl, %r10
        and $1, %r10 # guard
        # --------------> krok 8
        or %r10, %r8
        mov %rax, %r10
        shr $45, %r10
        shr %cl, %r10
        and $1, %r10 # round
        # ---------------> krok 9
        and %r8, %r10 # wynik predykatu
        shr $46, %rax
        shr %cl, %rax 
        shl $18, %rdx  
        shr %cl, %rdx
        or %rdx, %rax
        # ---------------> krok 10
        add %r10, %rax
        # ---------------> krok 11
        and mask3, %rax
        mov %r9, %r8 
        # ---------------> krok 12
        shl $23, %r9
        or %r9, %rax
        # ---------------> krok 13
        cmp $255, %r8
        cmovge mask1, %eax
        or %esi, %eax
        cmp $0, %r8 
        cmovl %esi, %eax
        # -----------------> krok 14
        ret 

        .size   cubef, .-cubef
