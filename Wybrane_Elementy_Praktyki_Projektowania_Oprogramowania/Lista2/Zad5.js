const person = {
    first_name : "",
    last_name : "",
    get name() {
        return this.first_name + " " + this.last_name;
    },
    set name(str) {
        let tab = str.split(" ");
        this.first_name = tab[0];
        this.last_name = tab[1];
    },
    name_length: function(){
        return this.first_name.length + this.last_name.length;
    }
}

person.name = "John Smith";
console.log(person.first_name);
console.log(person.last_name);
person.first_name = "Tedd";
console.log(person.name)
console.log(person.name_length())

//dodawanie pola do obiektu na dwa możliwe sposoby
person.year_of_birth = 2010;
Object.defineProperty(person, 'country', {value: 'Poland', writable: true});
console.log(person.year_of_birth);
console.log(person.country);

//dodawanie metody do obiektu na dwa możliwe sposoby
person.introduce = function(name){
    return "Hi " + name + "! I'm " + this.first_name;
}
console.log(person.introduce("Bob"));
Object.defineProperty(person, 'say_goodbye', {
    value: (name) => "Bye " + name + "! I have to go."
});
console.log(person.say_goodbye('Bob'));

//dodawanie nowej właściwości z akcesorami get i set
Object.defineProperty(person, 'age', {
    get(){
        let year = new Date().getFullYear();
        return year - this.year_of_birth;
    },
    set(value){
        let year = new Date().getFullYear();
        this.year_of_birth = year-value;
    }
})
console.log(person.age);
person.age = 17;
console.log(person.age);
console.log(person.year_of_birth);

