function fibonacci_recursive(n){
    if(n <= 1){
        return n;
    }
    return fibonacci_recursive(n-1)+fibonacci_recursive(n-2);
}

function fibonacci_memoize(){
    var cache = {};

    return function(n){
        if(n in cache){
            return cache[n]
        } else{
            if (n-1 in cache && n-2 in cache){
                let result = cache[n-1] + cache[n-2];
                cache[n] = result;
                return result;
            }
            let result = fibonacci_recursive(n);
            cache[n] = result;
            return result;
        }
    }
}

let memo_fibonacci = fibonacci_memoize();

function measure_time(max_n){
    for(let n=10; n<=max_n; n++){
        let time_taken = n.toString();
        console.time(time_taken);
        memo_fibonacci(n);
        console.timeEnd(time_taken);
    }
}

measure_time(100000);
//dla n=100000 czas to 0.004ms wczesniej dla n=45 czas wynosił 17s