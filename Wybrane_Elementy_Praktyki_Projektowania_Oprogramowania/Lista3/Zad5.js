function createGenerator() {
    var _state = 0;
    return {
        next : function() {
            return {
                value : _state,
                done : _state++ >= 10
            }
        }
    }
}

var foo = {
    [Symbol.iterator] : createGenerator
};
    
for ( var f of foo )
    console.log(f);

//rozwiazanie
function createGeneratorParameter(n) {
    return function(){
        var _state = 0;
        return {
            next : function() {
                return {
                    value : _state,
                    done : _state++ >= n
                };
            }
        };
    };
}

var foo5 = {
    [Symbol.iterator] : createGeneratorParameter(5)
};
  
var foo15 = {
    [Symbol.iterator] : createGeneratorParameter(15)
};

for ( var f of foo5 )
    console.log(f);

for ( var f of foo15 )
    console.log(f);
    