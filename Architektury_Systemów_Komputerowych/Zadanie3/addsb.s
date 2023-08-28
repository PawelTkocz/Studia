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
        .globl  addsb
        .type   addsb, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
Stosuje sposób analogiczny do tego opisanego w książce ,,Uczta programistów" w rodziale 2.17.
Na początku obliczam sumę i znajduję te int8, których sumowanie spowodowało nadmiar lub niedomiar
poprzez sprawdzenie, czy dwa najbardziej znaczące bity argumentów były takie same, a najbardziej znaczący bit
wyniku był od nich różny (wtedy jest nadmiar lub niedomiar)
Potem przygotowuję maski: jeśli nastąpił niedomiar przygotowuję maskę 10000000, a jeśli nadmiar to maskę 01111111
Na koniec składam wynik: tam, gdzie nie nastąpił nadmiar ani niedomiar pozostawiam wynik taki jaki był obliczony
Tam gdzie wystąpił nadmiar wpisuję maskę 01111111, a tam, gdzie niedomiar, maskę 10000000
 */

addsb:
	mov     $0x8080808080808080, %r8            /*  r8 maska 100000000100000000... */
    	mov     %rdi, %r9
    	add     %rsi, %r9                           /*  r9 suma argumentow */
    	mov     $0x7F7F7F7F7F7F7F7F, %rdx           /* rdx maska 01111111011111111... */
    	mov     %rdx, %r11
    	and     %rsi, %rdx
    	and     %rdi, %r11
    	add     %rdx, %r11                          /* r11 suma s, przy pominieciu najbardziej znaczacych bitow kazdego int8, by uniknąc przeniesienia */
    	mov     %rsi, %rax
    	xor     %rdi, %rax
    	and     %r8, %rax
    	xor     %rax, %r11                          /* r11 suma kazdej pary int8, przy zaniedbaniu przeniesienia i nadmiaru oraz niedomiaru */
    	mov     %r11, %r10
    	and     %r8, %r10                           /*  r10 najbardziej znaczace bity sumy */
    	xor     %r10, %rdi
    	xor     %r10, %rsi
    	and     %rsi, %rdi
    	and     %r8, %rdi                           /* rdi  info o overflow kazdego bajta, 1 w najbardziej znaczącym bicie jesli nastpilo nadmiar lub niedomiar */
    	mov     %rdi, %rcx
    	shr     $1, %rcx
    	or      %rcx, %rdi
    	mov     %rdi, %rcx
    	shr     $2, %rcx
    	or      %rcx, %rdi
    	mov     %rdi, %rcx
    	shr     $4, %rcx
    	or      %rcx, %rdi                          /* rdi maska 1111111100000000.... 1 gdy overflow */
    	mov     %r10, %rax
    	mov     %r10, %rcx
    	shr     $1, %rcx
    	or      %rcx, %r10
    	mov     %r10, %rcx
    	shr     $2, %rcx
    	or      %rcx, %r10
    	mov     %r10, %rcx
    	shr     $4, %rcx
    	or      %rcx, %r10
    	mov     %r10, %r9
    	sub     %rax, %r10
    	not     %r9
    	and     %r9, %r8
    	add     %r8, %r10
    	and     %rdi, %r10
    	not     %rdi
    	and     %rdi, %r11
    	or      %r11, %r10
    	mov     %r10, %rax
        ret
        .size   addsb, .-addsb
