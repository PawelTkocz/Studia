function fib() {
    let a = 0;
    let b = 1;
    return {
        next : function() {
            let fib_val = a;
            [a, b] = [b, a + b];
            return {
                value : fib_val,
                done  : false //fib_val > 100 jeśli chcemy skończony
            }
        }
    }
}


var _it = fib();
for(var _result; _result = _it.next(), !_result.done; ){
    console.log(_result.value)
}

/*
wykonanie 
for (var i of fib()){
    console.log(i);
}
jest niepoprawne. Należałoby najpierw utworzyć iterator:

var fibIterator = {
    [Symbol.iterator]: fib
};

for (var f of fibIterator) 
    console.log(f)
*/

function* fib2() {
    let a = 0;
    let b = 1;
    //while(a < 100) jeśli chcemy skończony
    while (true) {
        yield a;
        [a, b] = [b, a + b]
    }
}

var _it = fib2();
for(var _result; _result = _it.next(), !_result.done; ){
    console.log(_result.value)
}

//w przypadku generatora działa również wypisanie elementów w taki sposób:
for( var i of fib2()){
    console.log(i);
}

