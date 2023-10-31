var Person = function(name, surname) {
    this.name = name;
    this.surname = surname;
}
Person.prototype.say = function() {
    return `${this.name} ${this.surname}`;
} 

var Worker = function(name, surname, age) {
    Person.call( this, name, surname );
    this.age = age;
}

//Worker.prototype = Object.create( Person.prototype );
//Worker.prototype = Person.prototype
Worker.prototype = new Person();

Worker.prototype.say = function() {
    // "wywołanie metody z klasy bazowej"
    var _ = Person.prototype.say.call( this );
    return `${_} ${this.age}`;
}

var w = new Worker('jan', 'kowalski', 48);
console.log( w.say() );

/*
Funkcja Object.create(a) tworzy nową instancję obiektu i ustawia a jako jego prototyp.
Zatem wykoannie
Worker.prototype = Object.create(Person.prototype) 
zdefinuje prototyp klasy Worker - będzie to obiekt Person.prototype. Zatem wszystkie pola
i metody zdefiniowane w prototypie obiektu Person będą dostępne dla obiektów typu Worker
poprzez obecność w jej prototypie. Co ważne, zostanie utworzony nowy obiekt - po wywołaniu
Object.create() prototypy obu klas będą obiektami o takich samych polach i metodach, ale
modyfikacja prototypu klasy Worker nie będzie widoczna w prototypie klasy Person
*/
/*
Jaka jest wada rozwiązania postaci:
Worker.prototype = Person.prototype
Zarówno Worker.prototype jak i Person.prototype wskazują teraz na jedną i tą samą instancję obiektu.
Zatem zmiana wprowadzona w Worker.prototype będzie również widoczna w Person.prototype, co w naszym
przypadku doprowadzi do błędu. Chcąc nadpisać funkcję say() dla klasy Worker wywołujemy najpierw funkcję
say() dla klasy Person. W zamyśle funkcje say() powinny być róże w obu prototypach. Ponieważ jednak prototypami
obu klas jest jeden obiekt, próba nadpisania wartości funkcji say() w Worker.prototype doprowadzi do zastąpenia
starej wersji funkcji say() przez nową również w Person.prototype. Doprowadzi to do zapętlenia - funkcja say()
będzie w nieskończoność wywoływała samą siebie.
*/
/*
Jaka jest wada rozwiązania postaci:
Worker.prototype = new Person();
Rozwiązanie to działa w przeciwieństwie do poprzedniej próby. Główną jego wadą jest jednak niepotrzebne tworzenie
całego obiektu Person() - celem naszego rozwiązania jest aby Worker.prototype miał dostep do metod i parametrów
zdefiniowanych w Person.prototype. Wykonanie new Person() utworzy nową klasę Person, a więc rzeczywiście uzyskamy
dostep do Person.prototype, ale utworzenie nowego obiektu Person utworzy również wszystkie parametry tej klasy.
Jeśli więc obiekt miałby bardzo dużo parametrów to tworzenie utworzenie klasy Person zajmie znacznie więcej
pamięci niż utworzenie jedynie klasy Person.prototype.
*/
