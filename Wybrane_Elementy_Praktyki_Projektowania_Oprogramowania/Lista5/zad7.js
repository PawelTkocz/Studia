var fs = require('fs');
const util = require('util') 

//wersja 0
fs.readFile('file.txt', 'utf-8', function(err, data){
    if(err){
        console.log("Nastąpił błąd\n");
    }
    else{
        console.log(data);
    }
})

//wersja 1
function readFilePromise(path, enc) {
    return new Promise((res, rej) => {
        fs.readFile(path, enc, (err, data) => {
            if (err) {
                console.log(err);
                rej(err);
            }
            res(data);
        })
    })
};

readFilePromise('file.txt', 'utf-8')
    .then(data => {
        console.log(`data: ${data}`);
    })
    .catch(err => {
        console.log(`err: ${err}`);
    })

//wersja 2
const readFileAsync = util.promisify(fs.readFile);

readFileAsync('file.txt', 'utf-8')
    .then(data => {
        console.log(`data: ${data}`);
    })
    .catch(err => {
        console.log(`err: ${err}`);
    })

//wersja 3
fs.promises.readFile('file.txt', 'utf-8');
/*
.then(data => {
    console.log(`data: ${data}`);
})
.catch(err => {
    console.log(`err: ${err}`);
})    
*/

/*
wywałanie po staremu:
readFilePromise('file.txt', 'utf-8')
    .then(data => {
        console.log(`data: ${data}`);
    })
    .catch(err => {
        console.log(`err: ${err}`);
    })

wywołanie po nowemu:
*/

(async function () {
    let data = await fs.promises.readFile('file.txt', 'utf-8');  
    console.log(`data: ${data}`);
})();
