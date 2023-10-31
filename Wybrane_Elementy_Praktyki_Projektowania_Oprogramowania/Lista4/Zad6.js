function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

/*
Tree.prototype[Symbol.iterator] = function* () {
    yield this.val;
    if (this.left) yield* this.left;
    if (this.right) yield* this.right;
}
*/

var root = new Tree(1, new Tree(2, new Tree(3)), new Tree(4));

Tree.prototype[Symbol.iterator] = function* () {
    let queue = [this];

    while (queue.length > 0) {
        let node = queue[0];
        queue.splice(0, 1);
        if (node.right) {
            queue.splice(queue.length, 0, node.right);
            //queue.splice(0, 0, node.right);
        } 
        if (node.left){
            queue.splice(queue.length, 0, node.left);
            //queue.splice(0, 0, node.left);
        } 
        yield node.val;
    }
};

for (var e of root) {
    console.log(e);
}

