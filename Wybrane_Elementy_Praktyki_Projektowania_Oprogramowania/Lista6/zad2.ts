function fibonacci_recursive(n: number) : number{
    if(n <= 1){
        return n;
    }
    return fibonacci_recursive(n-1)+fibonacci_recursive(n-2);
}

function fibonacci_memoize(){
    var cache : {[id: number] : number} = {};

    return function(n: number) : number{
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

console.log(fibonacci_recursive(10));

let fibonacci_memo = fibonacci_memoize();
console.log(fibonacci_memo(10));