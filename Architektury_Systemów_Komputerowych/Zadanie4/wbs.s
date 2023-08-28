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
        .globl  wbs
        .type wbs, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
Ważoną sumę bitów będę obliczał krokami, najperw w parach, potem w czwórkach, potem w 8, 16, 32 i na koniec dla 64 bitów.
Aby ułatwić sobie obliczenia wagi bitów będę traktował jako o 1 większe niż założone w zadaniu (ostatni bit ma wagę 1 a nie 0)
Na koniec, aby uzyskac poprawny wynik, odejmę od uzyskanego wyniku liczbę równą popcnt(x), gdzie x jest argumentem fukcji wbs()
Zauważmy, że przy moim założeniu o wagach bitów, suma wag w parach jest od razu obliczona.
Dla każdego kroku (pary, czwórki, 8, 16, ...) wykonam dwa, analogiczne kroki, które opiszę na przykładzie par bitów:
Weźmy dwie kolejne pary postaci abcd, gdzie ab-wbs(pierwszej pary), cd-wbs(drugiej pary). Zauważmy, że aby obliczyć wbs całej czwórki
wystarczy wykonać ab+cd+2*y, gdzie y to liczba zapalonych bitów w x na pozycjach zajmowanych przez parę ab.
W rejestrze %r8 będę stopniowo wykonywał operację popcount(x), najperw obliczę liczbe zapalonych bitów w kolejnych parach, potem
(po przejściu do następnego kroku) w kolejnych czwórkach, itd.
Właśnie z tego rejestru będę korzystał, by wyznaczyć wartość y
W rejestrze %r9 będę stopniowo obliczał wbs(x), najpierw dla par, potem dla czwórek, itd.
 */

wbs:
        movq	   $0x5555555555555555, %r8
        movq   	   %rdi, %r10
        shr        $1, %r10
        and        %r8, %r10
        and        %rdi, %r8
        add        %r10, %r8                   /*%r8 - liczba zapalonych bitów w każdej parze x, (suma wazona w parach gotowa od poczatku)*/
        movq       $0x3333333333333333, %r9    /*Obliczanie wbs dla czwórek*/
        movq       %rdi, %r10
        shr        $2, %r10
        and        %r9, %r10
        and        %rdi, %r9
        add        %r10, %r9
        movq       $0xCCCCCCCCCCCCCCCC, %r11
        and        %r8, %r11
        shr        $1, %r11
        add        %r11, %r9                  /*Koniec obliczania wbs dla czwórek*/
        movq       $0x0F0F0F0F0F0F0F0F, %r11  /*Obliczanie wbs dla ósemek*/
        movq       %r9, %r10
        shr        $4, %r10
        and        %r11, %r10
        and        %r11, %r9
        add        %r10, %r9                  /*wykonano dodawanie, teraz trzeba bedzie zaaktualizowac wartość w %r8, by wyznaczyc y*/
        movq       %r8, %rcx                  /*aktualizacja %r8, tak by wskazywał liczbę zapalonych bitow w x w każdej kolejnej czwórce bitów*/
        movq       $0x3333333333333333, %rdx
        shr        $2, %rcx
        and        %rdx, %rcx
        and        %rdx, %r8
        add        %rcx, %r8                  /*koniec aktualizacji %r8*/
        movq       $0xF0F0F0F0F0F0F0F0, %r11
        and        %r8, %r11
        shr        $2, %r11
        add        %r11, %r9                  /*Koniec obliczania wbs dla ósemek*/
        movq       $0x00FF00FF00FF00FF, %r11  /*Obliczanie wbs dla szesnastek*/
        movq       %r9, %r10
        shr        $8, %r10
        and        %r11, %r10
        and        %r11, %r9
        add        %r10, %r9                  /*wykonano dodawanie, teraz będzie aktualizacja %r8, by wyznaczyć y*/
        movq       %r8, %rcx                  /*aktualizacja %r8*/
        movq       $0x0F0F0F0F0F0F0F0F, %rdx
        shr        $4, %rcx
        and        %rdx, %rcx
        and        %rdx, %r8
        add        %rcx, %r8                  /*koniec aktualizacji %r8*/
        movq       $0xFF00FF00FF00FF00, %r11
        and        %r8, %r11
        shr        $5, %r11
        add        %r11, %r9                  /*Koniec obliczania wbs dla szesnastek*/
        movq       $0x0000FFFF0000FFFF, %r11  /*Obliczanie wbs dla 32*/
        movq       %r9, %r10
        shr        $16, %r10
        and        %r11, %r10
        and        %r11, %r9
        add        %r10, %r9                  /*wykonano dodawanie, teraz aktualizacja %r8*/
        movq       %r8, %rcx                  /*aktualizacja %r8*/
        movq       $0x00FF00FF00FF00FF, %rdx
        shr        $8, %rcx
        and        %rdx, %rcx
        and        %rdx, %r8
        add        %rcx, %r8                  /*koniec aktualizacji %r8*/
        movq       $0xFFFF0000FFFF0000, %r11
        and        %r8, %r11
        shr        $12, %r11
        add        %r11, %r9                  /*Koniec obliczania wbs dla 32*/
        movq       %r9, %r10                  /*Obliczanie wbs dla 64 bitów*/
        shr        $32, %r10
        add        %r9d, %r10d                /*wykonano dodawanie, teraz aktualizacja %r8 (od teraz zamiast w %r9 wynik jest przechowywany w %r10)*/
        movq       %r8, %rcx                  /*aktualizacja %r8*/
        movq       $0x0000FFFF0000FFFF, %rdx
        shr        $16, %rcx
        and        %rdx, %rcx
        and        %rdx, %r8
        add        %rcx, %r8                  /*koniec aktualizacji %r8*/
        movq       $0xFFFFFFFF00000000, %r11
        and        %r8, %r11
        shr        $27, %r11
        add        %r11, %r10                 /*Koniec obliczania wbs dla 64 bitów (dla zmienionego przeze mnie systemu wag)*/
        movq       %r8, %rdx                  /*Aktualizacja %r8 tak, by przechowywała wartośc =popcnt(x)*/
        shr        $32, %rdx
        add        %r8d, %edx                 /*Koniec aktualizacji %r8*/
        sub        %rdx, %r10                 /*Na koniec odejmuję od uzyskanego wyniku wbs wartośc przechowywaną w %r8*/
        movq       %r10, %rax
        ret
        .size wbs, .-wbs
