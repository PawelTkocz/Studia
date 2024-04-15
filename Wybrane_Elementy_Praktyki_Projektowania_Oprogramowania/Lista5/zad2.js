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
    var answer = null;
    while (answer == null) {
        answer = await question('Podaj swoje imie: ');
    }
    console.log("Witaj " + answer);
    cl.close();
})();