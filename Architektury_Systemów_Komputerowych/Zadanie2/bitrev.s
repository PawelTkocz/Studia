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
        .globl  bitrev
        .type bitrev, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
Na początku zamieniam parami sąsiadujące ze sobą bity: 0 z 1, 2 z 3 ... 62 z 63
Następnie zamieniam pary bitów w kolejnych czwórkach: bity na pozycji 0, 1 z bitami na pozycji 2, 3 itd
Następnie zamieniam czwórki bitów w kolejnych ósemkach: bity na pozycji 1, 2, 3, 4 z bitami na pozycji 5, 6, 7, 8 itd
Zamian tych dokonuje w analogiczny sposób, poprzez skopiowanie x do nowego rejestru, przesunięcie go o odpowiednio 1, 2, 4 bity w lewo,
a następnie nałożenie odpowiedniej maski na x i przesunietego x. Po przesunieciu odpowiedniej maski i wykonaniu na nich operacji or,
uzyskujemy odpowiedni wynik.
Po wykonaniu tych operacji można zapisać, że x=abcdefgh, gdzie a, b, ..., h to ósemki bitów z początkowej wartości x, tylko że w odwróconej kolejności
Wystarczy doprowadzić do tego, że x=hgfedcba, wtedy wszystkie 64 bity będą się znajdowały w odwróconej kolejności. Aby to osiągnąć najpierw przenoszę 
część efgh do %ecx, a część abcd do %eax, a następnie za pomocą trzech operacji ror dokonuję zamiany kolejności obu części
Na koniec wystarczy przesunąc pierwszą część (hgfe) o 32 bity w lewo i wykonać or z drugą, odwróconą częścią (dcba)
 */

bitrev:
	leaq    (,%rdi, 2), %r8            /*zamiana w parach sąsiadujących bitów*/
    	movq    $0xAAAAAAAAAAAAAAAA, %r9
    	and     %r9, %rdi
    	and     %r9, %r8
    	shr     $1, %rdi
    	or      %r8, %rdi                  /*koniec zamiany w parach*/
    	leaq    (,%rdi, 4), %r8            /*zamiana w czwórkach sąsiadujących par bitów*/
    	movq    $0xCCCCCCCCCCCCCCCC, %r9
    	and     %r9, %rdi
    	and     %r9, %r8
    	shr     $2, %rdi
    	or      %r8, %rdi                  /*koniec zamiany w czwórkach*/
    	movq    %rdi, %r8                  /*zamiana w ósemkach sąsiadujących czwórek bitów*/
    	shl     $4, %r8
    	movq    $0xF0F0F0F0F0F0F0F0, %r9
    	and     %r9, %rdi
    	and     %r9, %r8
    	shr     $4, %rdi
    	or      %r8, %rdi                  /*koniec zamiany w ósemkach*/
    	mov     %edi, %ecx                 /*przeniesienie cześci efhg do %ecx*/
    	mov     %rdi, %rax
    	shr     $32, %rax                  /*przeniesienie części abcd do %eax*/
    	ror     $8, %cx
    	ror     $16, %ecx
    	ror     $8, %cx                    /*w %ecx znajduje się już ghfe*/
    	ror     $8, %ax
    	ror     $16, %eax
    	ror     $8, %ax                    /*w %eax znajduje się już dcba*/
    	shl     $32, %rcx                  /*przesunięcie %rcx o 32 bity w lewo, aby usyzkać ghfe0000*/
    	or      %rcx, %rax                 /*wykonanie or by uzyskać ghfedcba*/
        ret
        .size bitrev, .-bitrev
