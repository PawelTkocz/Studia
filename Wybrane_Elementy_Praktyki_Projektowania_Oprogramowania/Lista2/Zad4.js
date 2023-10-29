/*
Operator typeof zwraca napis wskazujacy na typ wartości operanda
*/
console.log(typeof 42)
console.log(typeof 'dog')
console.log(typeof true)
console.log(typeof undeclaredVariable)

/*
Operator instanceof
Każdy obiekt w JavaScript ma wbudowaną właściwość prototype. Prototype sam jest obiektem,
więc również będzie miał właściwośc prototype - tworzy się w ten sposób prototype chain.
Kończy się na prototype którego właściwość prototype ma wartość null.
Kiedy próbujemy odwołać się do właściowści obiektu, jeśli właściwość ta nie zostanie
odnaleziona w obiekcie, program przeszukuje prototype chain. Dopiero kiedy właściowści tej
nie ma w całym łańcuchu, program zwraca undefined. Aby dowiedzieć się co jest prototype obiektu
można wywołać funkcję Object.getPrototypeOf(myObject)
object instanceof constructor
Operator instanceof sprawdza, czy właściwość prototype konstruktora pojawia się w prototype chain
obiektu. Zwracana jest wartość true albo false. 
*/

function Car(make, model, year) {
   this.make = make;
   this.model = model;
   this.year = year;
}
const auto = new Car('Honda', 'Accord', 1998);
  
console.log(auto instanceof Car);
// true, bo: Object.getPrototypeOf(auto) === Car.prototype
console.log(auto instanceof Object);

/*
Użycie typeof jest najlepszym rozwiązaniem w przypadku typów nie będących obiektami, tzn jeśli
chcemy sprawdzić czy zmienna jest liczbą, napisem, boolem.
W przypadku argumentu będącego obiektem zwróci wartość 'object'. Nie jest w stanie sprecyzować
jaki jest to obiekt. 
Użycie instanceof jest najlepszym rozwiązaiem w przypadku obiektów, tzn jeśli checmy sprawdzić
czy obiekt jest instancją konkretnego obiektu albo jest z nim 'spokrewniony'
*/

