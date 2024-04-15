const fs = require("fs");
const readline = require("readline");

var rl = readline.createInterface({
    input: fs.createReadStream("file.txt")
});

let frequency = {};

rl.on("line", function (line) {
    let ip = line.split(' ')[1];
    if(frequency.hasOwnProperty(ip))
        frequency[ip]++;
    else
        frequency[ip] = 1;
});

rl.on("close", function () {
    let top3 = [["", 0], ["", 0], ["", 0]];

    delete frequency.undefined
    for(let ip in frequency){
        if(frequency[ip] > top3[2][1]){
            let tup = [ip, frequency[ip]];
            for(let i=0; i<3; i++){
                if(top3[i][1] < tup[1]){
                    let tmp = top3[i][1];
                    top3[i] = tup;
                    tup = tmp;
                }
            }
        }
    }
    console.log(top3[0][0], top3[0][1]);    
    console.log(top3[1][0], top3[1][1]);
    console.log(top3[2][0], top3[2][1]);
});