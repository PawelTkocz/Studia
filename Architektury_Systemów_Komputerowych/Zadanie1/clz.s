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
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki:
Najpierw obliczę jaka jest pozycja pierwszej z lewej 1 (w zapisie 64 bitowym liczby x, podanej jako argument funkcji)
Gdzie bity numeruję jako 64, 63, 62, ..., 2, 1, a wartość 0 oznacza, że wszystkie 64 bity to 0
Indeks ten będzie stopniowo obliczany w rejestrze %r9
Na koniec, jako wynik funkcji zwrócę wartość 64 pomniejszoną o ten indeks, czyli 64-%r9
Aby sprawdzić, czy ten indeks jest wiekszy niż 32, porównuję liczbę x z 0xFFFFFFFF, czyli liczbą postaci 32 razy 0 a potem 32 razy 1
Jeśli jest to do %r9 wpisuję 32 i wykonuje x=x>>32 aby w następnych krokach znalezc indeks pierwszej z lewej 1, która sie tam znajduje
Jeśli nie jest, to %r9 dalej przechowuje wartość 0 a wartość x pozostaje niezmieniona (w dalszych krokach wystarczy analizować prawe 32 bity)
Następne kroki są analogiczne, tylko przeprowadzam je dla liczb 32, 16, 8, 4, 2, 1 bitowych, korzystając z odpowiednio zmienionych masek
Sprawdzam, czy w lewej połowie analizowanych bitów znajduje się jakaś 1 (poprzez porównanie x z odpowiednią maską postaci ,,y razy 0 y razy 1")
Jeśli jest to zwiększam wartość w %r9 i w następnym kroku analizuję lewą połowę bitów
Jeśli nie, to nie robię nic, i w następnym kroku analizuję prawą połowę bitów
 */

clz:
	xor     %r9, %r9          /*zeruje wartość w r9*/
    	mov     $0xFFFFFFFF, %r8
    	cmpq    %rdi, %r8         /*sprawdzam, czy x jest ma jedynke w pierwszych 32 bitach*/
    	adc     $0, %r9
    	shl     $5, %r9		  /*jeśli tak, to w r9 jest 32, jeśli nie to 0*/
    	movq    %r9, %rcx
    	shr     %cl, %rdi         /*przesuwam x bitowo w prawo o taką wartość, jaka jest w r9*/
    	xor     %rcx, %rcx
    	mov     $0xFFFF, %r8
    	cmpq    %rdi, %r8         /*sprawdzam, czy x ma jedynke w pierwszych 16, z analizowanych 32 bitów*/
    	adc     $0, %rcx
    	shl     $4, %rcx          /*jeśli tak, to w rcx jest 16, jeśli nie to 0*/
    	shr     %cl, %rdi         /*przesuwam x bitowo w prawo o wartość przechowywaną w rcx*/
    	or      %rcx, %r9         /*i dodaję wartość z rcx do r9*/
    	xor     %rcx, %rcx
    	mov     $0xFF, %r8
    	cmpq    %rdi, %r8         /*sprawdzam, czy x ma jedynke w pierwszych 8 z analizowanych 16 bitów*/
    	adc     $0, %rcx
    	shl     $3, %rcx          /*jeśli tak, to w rcx jest 8, jeśli nie to 0*/
    	shr     %cl, %rdi         /*przesuwam x bitowo w prawo o wartość przechowywaną w rcx*/
    	or      %rcx, %r9         /*i dodaję wartość z rcx do r9*/
    	xor     %rcx, %rcx
    	mov     $0xF, %r8         /*analogicznie dla liczby 8 bitowej*/
    	cmpq    %rdi, %r8
    	adc     $0, %rcx
    	shl     $2, %rcx
    	shr     %cl, %rdi
    	or      %rcx, %r9
    	xor     %rcx, %rcx
    	mov     $3, %r8           /*analogicznie dla liczby 4 bitowej*/
    	cmpq    %rdi, %r8
    	adc     $0, %rcx
    	shl     $1, %rcx
    	shr     %cl, %rdi
    	or      %rcx, %r9
    	xor     %rcx, %rcx
    	mov     $1, %r8           /*analogicznie dla liczby 2 bitowej*/
    	cmpq    %rdi, %r8
    	adc     $0, %rcx
    	shr     %cl, %rdi
    	or      %rcx, %r9
    	add     %rdi, %r9         /*dla jednobitowej liczby x=0 lub x=1, wystarczy do r9 dodać wartość x*/
    	mov     $64, %eax
    	sub     %r9d, %eax         /*w eax przechowuje wynik działania 64-%r9*/
    	ret

        .size   clz, .-clz
