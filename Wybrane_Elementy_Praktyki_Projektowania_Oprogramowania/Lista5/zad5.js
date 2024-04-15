var http = require('http');

function promisedGet(url) {
    return new Promise(function (resolve, reject) {
        var client = http.get(url, function (res) {
            var buffer = '';
            res
                .on('data', function (data) {
                    buffer += data.toString();
                })
                .on('end', function () {
                    resolve(buffer);
                });
        });
    });
}

(async function () {
    var result = await promisedGet('http://www.google.pl');
    console.log(result);
})();
