var fs = require('fs');

function fspromise(path, enc) {
    return new Promise((res, rej) => {
        fs.readFile(path, enc, (err, data) => {
            if (err)
                rej(err);
            res(data);
        });
    });
}

fspromise('file.txt', 'utf-8')
    .then(data => {
        console.log(`data: ${data}`);
    })
    .catch(err => {
        console.log(`err: ${err}`);
    })