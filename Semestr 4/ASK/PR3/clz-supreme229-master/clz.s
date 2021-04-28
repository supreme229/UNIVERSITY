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
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
 
 Generalnie całe rozwiązanie ma dwa proste etapy.
 
 Pierwszy nazwałbym wypełnieniem "dziur" w liczbie.
 
 Gdy natrafiamy na pierwszą najbardziej znaczącą jedynkę to nie interesuje nas co jest na mniej znaczących bitach.
 Na potrzeby drugiego kroku, dokonuje tutaj w takim razie wypełnienia tych mniej znaczących bitów jedynkami.

 Potem jeszcze małym krokiem jest negacja naszego wyniku. Za chwile okaże się po co.
 
 Drugim etapem jest zliczenie jedynek w naszej liczbie. Zauważmy, że te najbardziej znaczące zera to teraz jedynki (po 1 kroku reszta
 była jedynkami a wiodące zera zerami, ale to nam załatwia tutaj właśnie negacja) więc to da nam rozwiązanie. Zrobiłem  to za pomocą
 popcounta, który pisałem już (Lista 2) z drobną modyfikacją dla liczb 64 bitowych. Dokonałem tez pewnych prostych optymalizacji, by zmieścić się
 w 50 instrukcjach.
 
 Wydaje mnie się, że da się jeszcze zejść kilka instrukcji jednak z uwagi na zadowalające IPC, CPI i spełniony wymóg 50 instrukcji, 
 nie dokonywałem już większych zmian.
 */

clz:
	mov	%rdi, %rax
	shr 	$1, %rdi
	orq     %rdi, %rax
	mov     %rax, %rdi
	shrq    $2, %rdi
	orq     %rdi, %rax
	mov     %rax, %rdi
	shrq    $4, %rdi
	orq     %rdi, %rax
	mov     %rax, %rdi
	shrq    $8, %rdi
	orq     %rdi, %rax
	mov     %rax, %rdi
	shrq    $16, %rdi
	orq     %rdi, %rax
	mov     %rax, %rdi
	shrq    $32, %rdi
	orq     %rdi, %rax
	# ------------------> wypełniamy wszystkie "dziury" czyli zera, które znalazły się po pierwszej najbardziej znaczącej jedynce
	not     %rax
	# ------------------> negujemy by leading zeroes były jedynkami a reszta zerami
	mov     %rax, %rcx
	mov     $0x5555555555555555, %rdx
	shrq    $1, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# -------------------> krok popcounta #1
	mov     %rax, %rcx
	mov     $0x3333333333333333, %rdx
	shrq    $2, %rcx
	and     %rdx, %rcx
	and     %rdx, %rax
	add     %rcx, %rax
	# -------------------> krok popcounta #2
	mov     %rax, %rcx
	mov     $0x0F0F0F0F0F0F0F0F, %rdx
	shrq    $4, %rcx
	add     %rcx, %rax
	and     %rdx, %rax
	# -------------------> krok popcounta #3
	mov     %rax, %rcx
	shrq    $8, %rcx
	add     %rcx, %rax
	# -------------------> krok popcounta #4
	mov     %rax, %rcx
	shrq    $16, %rcx
	add     %rcx, %rax
	# -------------------> krok popcounta #5
	mov     %rax, %rcx
	shrq    $32, %rcx
	add     %ecx, %eax      
	and     $0x7F, %rax  
	# -------------------> krok popcounta #6
	ret

        .size   clz, .-clz
