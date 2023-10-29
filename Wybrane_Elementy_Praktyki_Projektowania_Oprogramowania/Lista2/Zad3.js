console.log( (![]+[]) [+[]] + (![]+[]) [+!+[]] + ([![]]+[][[]]) [+!+[]+[+[]]] + (![]+[]) [!+[]+!+[]] );

/*
(![]+[]) [+[]]
![] - Negacja oznacza, że argument musi być typu bool. Pusta tablica jest obiektem, a obiekty podczas
      konwersji na typ bool przyjmują wartość true. Stąd ![] będzie false
![]+[] - operator + działa albo na napisach albo na liczbach. Program określa najpierw primitive values
         obu argumentów. Dla false jest łatwo - primitive value to też false. Dla obiektu (pustej tablicy)
         program zwraca domyślną wartość obiektu wywołując wewnętrzną funkcję DefaultValue - jeśli obiekt
         ma zdefiniowaną metodę toString() to defaultValue tego obiektu jest równa object.toString().
         Dla pustej tablicy wynikiem jest pusty napis. Operator + konwertuje więc wartość false na napis,
         a wynikiem dodawania konkatenacja "false" i "" czyli "false"
+[] - unarny + powoduje, że argument jest konwertowany na liczbę. Jeśli argument jest typu Object, najpierw
      wywoływana jest funkcja ToPrimitive, która z kolei korzysta z funkcji DefaultValue. Dla pustej tablicy
      funkcja ta zwraca 0.

(![]+[]) [+[]] <=> "false"[0] <=> 'f'
*/
/*
(![]+[]) [+!+[]]
![]+[] - "false" (jak wcześniej)
+[] - 0 (jak wcześniej)
!+[] <=> !0 - Negacja oznacza, że argument musi być typu bool. 0 przekonwertowane na typ bool przyjmie wartość false.
              Zatem !0 przyjmie wartość true
+!+[] <=> +true - unarny + powoduje, że argument jest konwertowany na liczbę. Wartość true po konwersji na liczbę
                  przyjmuje wartośc 1.

(![]+[]) [+!+[]] <=> "false"[1] <=> 'a'                  
*/
/*
([![]]+[][[]]) [+!+[]+[+[]]]
![] - false (jak wcześniej)
[![]] <=> [false]
[][[]] - odwoładnie się do składowej obiektu (pustej tablicy) wykorzystując operator []. Składowa, do której próbujemy
         się odwołać to []. Nazwy składowych tablicy są typu string (o ile nie są liczbami) - na taki typ zostanie przekonwertowany
         każdy zadany argument podczas odwoływania się do składowych obiektu. W tym przypadku przed próbą odwołania się
         do składowej obiektu zostanie wywołana funkcja [].toString() której wynikiem jest pusty napis "". Wyrażenie 
         ma więc postać [][""] - próbujemy się odwołać do składowej "" obiektu []. Ponieważ obiekt pustej tablicy nie ma
         zdefiniowanej właściwości o nazwie "" zostanie zwrócona wartośc undefined 
[![]]+[][[]] <=> [false]+undefined - tak jak w pierwszym przypadku, program najpierw ustala primitive values obu argumentów.
                 [false] jest obiektem, zatem zwrócona zostanie domyślna wartość tego obiektu. Ponieważ tablica ma określoną
                 funkcję toString(), to domyślną wartością tego obiektu będzie [false].toString() czyli napis "false".
                 Skoro jeden z argumentów dodawania jest typu string, to program przekonwertuje również drugi argument do
                 tego typu i wykona konkatenację tych napisów. Dla argumentu undefined wartość wywołania funkcji toString()
                 będzie równa "undefined". Stąd po konkatencji obu tych napisów otrzymamy "falseundefined"
+[] - 0 (jak wcześniej)
[+[]] <=> [0]
+!+[] - 1 (jak wcześniej)
+!+[] + [+[]] <=> 1 + [0] - ponownie program ustala najpierw primitive values obu argumentów. Dla 1 jest to liczba 1, dla
                            [0] jest to wartość [0].toString() czyli "0". Ponieważ jeden z argumentów + jest typu string
                            to drugi zostaje przekonwertowany do tego typu - z 1 otrzymujemy "1". Na koniec następuje 
                            konkatenacja obu napisów: "1" + "0" = "10"

([![]]+[][[]]) [+!+[]+[+[]]] <=> "falseundefinded"["10"] <=> "falseundefined"[10] <=> 'i'                            
*/
/*
(![]+[]) [!+[]+!+[]]
![]+[] - "false" (jak wcześniej)
!+[] - true (jak wcześniej)
!+[]+!+[] <=> true + true - Operator + określa najpiewr Primitive Values obu argumentów. Obie te wartości są jasno
                            określone dla typów boolowskich (w przeciwnieństwie do np pustej tablicy, gdzie trzeba
                            wywoływać funkcję DefaultValue). Jeśli argumenty operatora + są Primitive Values to 
                            następuje konwersja tych argumentów do liczb. True zostaje przekonwertowane do 1. Stąd
                            true + true <=> 1+1 = 2

(![]+[]) [!+[]+!+[]] <=> "false"[2] <=> 'l'        
*/