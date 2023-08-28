/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: Paweł Tkocz, 332168
 */

        .text
        .globl  mod17
        .type   mod17, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
Załóżmy, że liczba ma postać x = b15, b14, b13, ..., b1, b0, gdzie bi to i-ta cyfra x od prawej w zapisie szesnastkowym
Chcę policzyć różnicę R=(b0 + b2 + ... + b14)-(b1 + b3 + ... + b15) = (b0-b1)+(b2-b3)+...+(b14-b15)
Aby uniknąć liczb ujemnych policzę sumę R+120=R+(15*8)=(15+b0-b1)+(15+b2-b3)+...(15+b14-b15)
Dzięki temu każdy ze składnków sumy będzie nieujemny. Te operacje oznaczę w kodzie jako krok 1
W następnym kroku policzę sumę tych składników uzyskując ostatecznie R+120 w rejestrze %eax (w kodzie operacje te oznaczam jako krok 2)
W tym momencie w %eax mam liczbę y z przedziału [0, 240] (a więc zapisaną na 2 bajtach). Policzę jej wynik operacji %17 (y%17)
Znów, aby uniknąć liczb ujemnych, policzę (y+15)%17, korzystając z tej samej metody (krok 3)
Otrzymam liczbę z z zakresu [0, 30] i również chcę policzyć z%17, a tak naprawdę, ponieważ wcześniej zamiast (x%17) i (y%17) liczyłem
(x+120)%17=(x+7*17+1)%17=(x+1)%17 i (y+15)%17 to do ostatecznego wyniku chcę policzyć (z-16)%17=(z+1)%17. Zrobię to w ostatnim, 4 kroku
W rejestrze %rax znajduje sie liczba z przediału [0, 16], która jest wynikiem operacji x%17
 */

mod17:
	movq    $0xF0F0F0F0F0F0F0F0, %r8                   /*Początek kroku 1*/
        movq    $0x0F0F0F0F0F0F0F0F, %r10
        and     %rdi, %r8
        and     %r10, %rdi
        shr     $4, %r8
        sub     %r8, %r10
        add     %rdi, %r10                                 /*koniec kroku 1*/
        movq    $0xFF00FF00FF00FF00, %r8                   /*Początek kroku 2*/
        movq    $0x00FF00FF00FF00FF, %r9
        and     %r10, %r8
        and     %r9, %r10
        shr     $8, %r8
        add     %r8, %r10
        movq    $0xFFFF0000FFFF0000, %r8
        movq    $0x0000FFFF0000FFFF, %r9
        and     %r10, %r8
        and     %r9, %r10
        shr     $16, %r8
        add     %r8, %r10
        movq    %r10, %r8
        shr     $32, %r8
        add     %r8, %r10
        mov     %r10d, %eax                                /*koniec kroku 2*/
        and     $15, %al                                   /*Początek kroku 3*/
        shr     $4, %r10b
        and     $15, %r10b
        add     $15, %al
        sub     %r10b, %al                                 /*koniec kroku 3*/
        mov     %al, %r10b                                 /*Początek kroku 4*/
        shr     $4, %r10b
        and     $1, %r10b                                  /*korzystam tu z faktu, że ponieważ z<31 to druga od prawej cyfra szesnastkowa to 0 lub 1*/
        and     $15, %al
        add     $1, %al
        sub     %r10b, %al				   /*koniec kroku 4*/
        ret
        .size   mod17, .-mod17
