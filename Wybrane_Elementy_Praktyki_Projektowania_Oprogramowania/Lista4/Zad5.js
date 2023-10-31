function Foo() {
    let cnt = 1;
    Foo.prototype.Bar = function() {
        let Qux = function () {
            console.log(cnt++);
        };
        Qux();
    }
}

let foo = new Foo();
foo.Bar();
foo.Bar();
foo.Bar();
console.log(foo.cnt); //undefined
//foo.Qux() zwróciłoby błąd