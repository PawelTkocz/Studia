const person = {
    name: 'John',
    age: 10,
    'zip-code': '12-345',
    '2nd name': 'Leo',
    1234: 23,
    '[object Object]': 'object conversion'
}

console.log(person.name)
console.log(person["2nd name"])
//person."2nd name" nie zadziala
console.log(person["zip-code"])
//person.zip-code nie zadziała
let prop = 'age'
console.log(person[prop])
//person.prop nie zadziała
console.log(person['age'])
console.log(person['1234'])
//person.1234 nie zadziała


/*
Odwoływanie się do składowych obiektu operatorem . jest możliwe
jeśli znamy nazwę tej składowej. Wykonanie operacji postaci
let n = 'name'
person.n
jest niepoprawne
Dodatkowo nazwa składowej musi być poprawnym identifier - może zawierać
jedynie unicodowe litery, $, _, i cyfry 0-9, ale nie może zaczynać się liczbą.
Wyrażenia
person."zip-code"
person."2nd name"
są niepoprawne. W takich przypadkach trzeba użyć odwołania poprzez []
*/

console.log(person[123])
console.log(person[1234])

const car = {type:"Fiat", model:"500", color:"white"};
const dog = {breed:"Beagle", age:"3", eyes:"brown"};
console.log(car.toString())
console.log(dog.toString())
console.log(person[car])
console.log(person[dog])

/*
Jesli dla operatora [] użyjemy argumentu typu innego niż string, to argument ten zostanie
zrzutowany na stringa. Jeśli argument jest typu int, konwersja jest prosta. Jeśli argument
jest innym obiektem, konwersja polega na wykonaniu na zadanym obiekcie funkcji toString(), 
w wyniku której argument ma postać '[object Object]'. Oznacza to, że niezależnie od tego,
jaki obiekt zostanie podany jako argument, zawsze nastąpi odwołanie do tego samego parametru.
Zatem w przypadku argumentu liczbowego programista ma wpływ na wybór klucza - różne liczby
będą oznaczały różne klucze. Natomiast w przypadku argumentu obiektowego programista nie ma
wpływu na klucz pod jaki zostanie zapisana wartość - zawszes będzie to klucz '[object Object]'
*/

console.log("Część 3")

const array = [1, 2, 3]
console.log(array['length'])
console.log(typeof(array))
console.log(Object.keys(array))
console.log(array['dog'])
console.log(array['1'])
console.log(array[car])

array['3'] = 4;
console.log(array)
console.log(array.length)

array['7'] = 8;
console.log(array)
console.log(array.length)
console.log(array[5])

array['dog'] = 314
console.log(array['dog'])
console.log(array.dog)
console.log(array)
console.log(array.length)

array.length = 3
console.log(array.length)
console.log(array)
array.length = 8
console.log(array)

/*
Tablice są w rzeczywistości obiektami. Tak jak w przypadku składowej obiektu, wszystkie
argumenty operatora [] niebędące intem zostają przekonwertowane do stringa. Jeśli argumentem operatora jest 
napis, to o ile reprezentuje on liczbę nieujemną, mniejszą niż długość tablicy to zostanie
zwrócona wartość w tablicy spod indeksu reprezentowanego przez ten napis. Wpp zostanie zwrócone
undefined. Jeśli argumentem operatora jest obiekt, to zostanie przekonwertowany na napis metodą
toString(), a ponieważ napis '[object Object]' będący wynikiem tej konwersji nie reprezentuje
liczby nieujemnej, to odwołanie zwróci wartość undefined. 
Jeśli klucz po przekonwertowaniu na napis reprezentuje całkowitą nieujemną liczbę, to tablica zwiększy
swój rozmiar. Jesli klucz będzie równy długości dotychczasowej tablicy, to na jej koniec zostanie
zapisany nowy element. Jeśli klucz ten bedzie większy, elementy pomiędzy ostatnim w dotychczasowej
tablicy a właśnie wstawionym zostaną niezdefiniowane.
Jeśli natomiast klucz po przekonwertowaniu na napis nie będzie całkowitą nieujemną liczbą, to tablica
nie zwiększy swojej długości. Mimo to do zyska nową składową o nazwie tego klucza, do której można
się odwoływać tak jak do parametru length.
Wartosć składowej length obiektu tablicy można zmodyfikować w standardowy sposób. 
Jeśli długość tablicy zostanie zmniejszona, elementy wykraczające poza skróconą tablicę zostaną zapomniane.
Nawet w przypadku ponownego zwiększenia rozmiaru tablicy nie trafią do niej ponownie.
W przypadku zwiększenia wartości atrybutu lenght, elementy które trafiły na koniec tablicy są niezdefiniowane.
*/


