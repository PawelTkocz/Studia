var n = 1;
// liczba ma prototyp?
console.log( typeof Object.getPrototypeOf( n ) );
// można jej dopisać pole/funkcję?
n.foo = "foo";
console.log( n.foo );

/*
Wartości typów prostych nie mają prototypów.
Kiedy próbujemy odwoływać się w programie do typów prostych tak jakby były
obiektami, JavaScript tworzy tymczasowy Obiekt, który reprezentuje ten typ prosty.
Wykonuje zleconą operację, a po jej wykonaniu usuwa utworzony tymczasowo obiekt.
Stąd
Object.getPrototypeOf(n) zwróci object
n.foo = "foo" nie zwróci błędu (zostanie utworzone nowe pole, ale obiekt zostanie od razu po tym zwolniony)
console.log(n.foo) zwróci undefined (po utowrzeniu tymczasowego obiektu z liczby 1, wartość pola "foo" nie jest
dla niego zdefiniowana)
*/