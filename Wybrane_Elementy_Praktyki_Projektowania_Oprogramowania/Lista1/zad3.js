function is_prime(a){
    for(let i=2; i<a; i++){
        if(a%i == 0){
            return false;
        }
    }
    return true;
}

function zad3(){
    const res = [];
    for(let i=2; i<100000; i++){
        if(is_prime(i)){
            res.push(i);
        }
    }
    return res;
}

res = zad3();
for(let i=0; i<res.length; i++){
    console.log(res[i]);
}