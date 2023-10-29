function createFs(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( var i=0; i<n; i++ ) {
        //zmiana na let i=0 sprawia, że otrzymujemy oczekiwane wyniki
        fs[i] =
            function() {
                return i;
            };
    };
    return fs;
}
var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10 // ale wszystkie zwracają 10!?

//1. wyjasnic zmiane na let

/*
Zmienne let mają zasięg bloku w którym sa zadeklarowane
Zmienne var mają zasięg całej domykającej funkcji
Przykład:
function varTest() {
  var x = 1;
  {
    var x = 2; // same variable!
    console.log(x); // 2
  }
  console.log(x); // 2
}

function letTest() {
  let x = 1;
  {
    let x = 2; // different variable
    console.log(x); // 2
  }
  console.log(x); // 1
}

Zatem w pętli for z var i tworzona jest tylko jedna zmienna, do której referencję mają wszystkie 
utworzone funkcje. Wartość tej zmiennej jest na koniec równa 10.
W przypadku for z let i za każdym razem tworzona jest nowa zmienna i

*/

//2. przedstawic sposob z dodatkowym zagniezdzeniem funkcji w funkcj,
//który dla każdej iteracji pętli for utworzy nowy kontekst wiązania domknięcia
//zmienić w fs[i] = ...

function createFs2(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( var i=0; i<n; i++ ) {
        //zmiana na let i=0 sprawia, że otrzymujemy oczekiwane wyniki
        fs[i] = (function() {
            var j=i;
            return function(){ return j; };
        })();
    };
    return fs;
}
var myfs2 = createFs2(10);
console.log( myfs2[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs2[2]() ); // druga miała zwrócić 2
console.log( myfs2[7]() );