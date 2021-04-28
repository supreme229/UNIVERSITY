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
        .globl  addsb
        .type   addsb, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
 Moje rozwiązanie opiszę w postaci listy kroków.
 
 1. Zwykłe dodawanie liczb z ignorowaniem ewentualnego wystąpienia nadmiaru.  (koniec kroku w #1 w kodzie)
 
 Krok ten jest dość istotny i od niego zaczynam rozwiązanie. Polega on na dodaniu osobno parzystych i nieparzystych ósemek bajtów
 czyli dodajemy osobno bajty 1, 3, 5, 7 liczb a i b, oraz osobno 2, 4 ,6, 8. 
 
 Gdy dodajemy parzyste bajty to nieparzyste są równe 0 by nie powodowały przesunięcia a zbierały ewentualny nadmiar.
 Nastepnie w wyniku dodawania nieparzystych zeruję parzyste i odwrotnie przy dodawaniu parzystych i scalam wyniki.
 Teraz mam zwykłe dodawanie bez nasycenia co kończy pierwszy punkt rozwiązania.
 
 2. Sprawdzenie wystąpienia nadmiaru przy dodawaniu. (#2 w kodzie)
 
 W tym kroku sprawdzam gdzie wystąpił nadmiar za pomocą operacji z ćwiczeń (L2Z3). Wynik wystąpienia nadmiaru przechowuję w 64 bitowej
 liczbie, która zawiera 1 na bicie znaku jeżeli nadmiar wystąpił i 0 jeżeli nie. 
 
 3. Utworzenie wektora znaków (#3 w kodzie)
 
 W rejestrze przechowuję sobię znaki wyników dodawania z kroku 1.
 
 4. Tworzę dodatkowy wektor nadmiarów 1/2 (#4 w kodzie)
 
 W kolejnym rejestrze zachowam maskę, która będzie zawierała 1 na bicie znaku gdy dodawanie odpowiednich liczb dało nam
 nadmiar oraz wynik dodawania jest ujemny.
 
 5. Tworzę dodatkowy wektor nadmiarów 2/2 (#5 w kodzie)
 
 Tymrazem w rejestrze zachowam maskę, która będzie zawierała 1 na bicie znaku gdy dodawanie odpowiednich liczb dało nam
 nadmiar oraz wynik dodawania jest dodatni.
 
 Oba dodatkowe rejestry przydadzą się do poprawy wyniku w dalszych krokach.
 
 6. 
 
 */

addsb:
        mov     %rdi, %rdx
        mov     %rdi, %r8
        mov     %rsi, %rax
        mov     %rsi, %r9
        mov     $0xFF00FF00FF00FF00, %r10
        and     %r10, %rdx
        and     %r10, %rax
        mov     $0xFF00FF00FF00FF, %r11
        and     %r11, %rdi
        and     %r11, %rsi
        add     %rdi, %rsi
        add     %rdx, %rax
        and     %r11, %rsi
        and     %r10, %rax
        orq     %rsi, %rax
        # ------------------>%rax ma wynik zwykłego dodawania #1
        xor     %rax, %r8
        xor     %rax, %r9
        and     %r9, %r8
        mov     $0x8080808080808080, %r10
        and     %r10, %r8
        # ------------------> w r_8 mamy wystąpienia overflow #2
        mov     %rax, %rdi
        and     %r10, %rdi
        # ------------------> w rdi znaki #3
        mov     %rdi, %rsi
        and     %r8, %rsi
        # ------------------> w rsi maska (nadmiar (TAK), wynik (-)) #4
        mov     %rdi, %rdx
        not     %rdx
        mov     %r8, %r10
        and     %rdx, %r10
        # ------------------> w r10 maska (nadmiar (TAK), wynik (+)) #5
        mov     %r8, %r11
        shr     $7, %r11
        sub     %r11, %r8
        # ------------------> edycja r8 #
        orq     %r8, %rax
        xor     %rsi, %rax
        shr     $7, %r10
        add     %r10, %rax
        ret     

        .size   addsb, .-addsb
