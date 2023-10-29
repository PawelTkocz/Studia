function getLastProto(o){
    var p = o;
    do {
        o = p;
        p = Object.getPrototypeOf(o);
    } while (p);
    return o;
}
   
const object1 = {
    firstName: "Tom",
    lastName: "Smith",
    age: 10,
    greet: function() { console.log('hello') }
}

let object2 = [1, 2, 3, 4]

let object3 = {
    color: "red",
    size: "L",
    brand: "Nike"
}

let object4 = new Date();

console.log(getLastProto(object1) === getLastProto(object2))
console.log(getLastProto(object1) === getLastProto(object3))
console.log(getLastProto(object1) === getLastProto(object4))
console.log(getLastProto(object2) === getLastProto(object3))
console.log(getLastProto(object2) === getLastProto(object4))
console.log(getLastProto(object3) === getLastProto(object4))
