function fib() {
    let a = 0;
    let b = 1;
    return {
        next : function() {
            let fib_val = a;
            [a, b] = [b, a + b];
            return {
                value : fib_val,
                done  : false
            }
        }
    }
}

function* fib2() {
    let a = 0;
    let b = 1;
    while (true) {
        yield a;
        [a, b] = [b, a + b]
    }
}

function* take(it, top) {
    for (let i = 0; i < top; i++) {
        let next = it.next();
        if (next.done) {
            return;
        } else {
            yield next.value
        }
    }
}

// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take(fib(), 10)){
    console.log(num);
}

for (let num of take(fib2(), 10)){
    console.log(num);
}