function enumerate_object(o){
    for (let name of Object.getOwnPropertyNames(o)) {
        console.log(name);
    }
}

function enumerate_object_chain(o){
    let object = o;
    do {
        enumerate_object(object);
        object = Object.getPrototypeOf(object);
    } while (object);
}

function zad2(o, name){
    return o.hasOwnProperty(name);
}

const object1 = {
    firstName: "Tom",
    lastName: "Smith",
    age: 10,
    greet: function() { console.log('hello') }
}

const object2 = new Date();

var p = {
    name: 'jan'
}
var q = {
    surname: 'kowalski'
}

/*
Object.setPrototypeOf( p, q );
console.log( p.name );
console.log( p.surname );
*/

//enumerate_object(object1);
//enumerate_object_chain(object2);


console.log(zad2(object1, "toString"));
console.log(zad2(Object.getPrototypeOf(object1), "toString"));