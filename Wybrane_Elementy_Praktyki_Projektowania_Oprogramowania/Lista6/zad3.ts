function forEach<T, R>(a: T[], f: (t: T) => R){
    for(let i=0; i<a.length; i++){
        f(a[i]);
    }
}

function map<T, R>(a: T[], f: (t: T) => R): R[]{
    let res: R[] = [];
    for(let i=0; i<a.length; i++){
        res.push(f(a[i]));
    }
    return res;
}

function filter<T>(a: T[], f: (t: T) => boolean): T[]{
    let res: T[] = [];
    for(let i=0; i<a.length; i++){
        if(f(a[i])){
            res.push(a[i]);
        }
    }
    return res;
}

let a = [1, 2, 3, 4];

forEach(a, _ => {console.log(_);})

let filter_res = filter(a, function(x){return x < 3});
console.log(filter_res);

let map_res = map(a, _ => _ * 2);
console.log(map_res);