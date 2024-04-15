import {f} from "./a";

console.log(f(4, 5));

//różnice między eksportem domyślnym (export default Foo) a nazwanym (export Foo)
//jak w obu przypadkach wygląda eksport i import

/*
export default function g(x){
    ...
}

Tylko jedna defincicja default per plik. Wówczas import wygląda tak:
import g from "./plik"
albo tak
import f from "./plik"
Nazwa nie ma znaczenia

export function f1(x){
    ...
}
export function f2(x){
    ...
}

import {f1, f2} from "./plik"
można nadać im aliasy:
import {f1 as f, f2 as g} from "./plik"
albo zaimportować wszystko
import * as mod from "./plik"
mod.f1
mod.f2
*/