function get_digits(a){
    const digits = [];
    while(a > 0){
        digits.push(a%10);
        a = Math.floor(a/10);
    }
    return digits;
}

function sum_of_digits(digits){
    let sum = 0;
    for(let i=0; i<digits.length; i++){
        sum += digits[i];
    }
    return sum;
}

function is_ok(a){
    const digits = get_digits(a);
    if(a%sum_of_digits(digits) != 0){
        return false;
    }
    for(let i=0; i<digits.length; i++){
        if(digits[i] == 0 || a%digits[i] != 0){
            return false;
        }
    }
    return true;
}

function zad2(){
    const res = [];
    for(let i=1; i<=100000; i++){
        if(is_ok(i)){
            res.push(i);
        }
    }   
    return res;
}

const res = zad2();
for(let i=0; i<res.length; i++){
    console.log(res[i]);
}