const readln = require('readline');
var cl = readln.createInterface( process.stdin, process.stdout );

var question = function(q) {
    return new Promise( (res, rej) => {
        cl.question( q, answer => {
            res(answer);
        })
    });
};


(async function main() {
    let number = Math.floor(Math.random() * 100);
    var answer;
    let end = false;
    while (end == false) {
        answer = await question('Zgadnij liczbe: ');
        if(answer == number){
            console.log("To jest właśnie ta liczba");
            end = true;
        }
        else if(answer < number){
            console.log("Moja liczba jest większa");
        }
        else{
            console.log("Moja liczba jest mniejsza");
        }
    }
    cl.close();
})();