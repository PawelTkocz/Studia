#lang plait

(module+ test
  (print-only-errors #t))


;; abstract syntax -------------------------------

(define-type Op
  (add) (sub) (mul) (leq))

(define-type Prog
  (progDef [defs : (Listof Fun)] [e : Exp]))

(define-type Fun
  (funDef [name : Symbol] [args : (Listof Symbol)] [e : Exp]))

(define-type Exp
  (numE [n : Number])                                             
  (varE [x : Symbol])                                             
  (opE [op : Op] [l : Exp] [r : Exp])                             
  (ifE [b : Exp] [l : Exp] [r : Exp])                             
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])                       
  (appE [f : Symbol] [args : (Listof Exp)]))                      


;; parse ----------------------------------------

(define (parse-prog [s : S-Exp]) : Prog
  (if (s-exp-match? `{define {ANY ...} for ANY} s)
      (progDef
       (parse-fun-definitions (s-exp->list (second (s-exp->list s))))
       (parse-exp (fourth (s-exp->list s))))
      (error 'parse-prog "Invalid program input")))

(define (parse-fun-definitions [funs : (Listof S-Exp)]) : (Listof Fun)
  (local [(define (it xs funs-names)
            (type-case (Listof S-Exp) xs
              [empty
               empty]
              [(cons s rest)
               (if (s-exp-match? `{fun SYMBOL (ANY ...) = ANY} s)
                   (let ([f-name (s-exp->symbol (second (s-exp->list s)))])
                     (if (member f-name funs-names)
                         (error 'parse-fun-definitions "Two functions with the same name")
                         (cons
                          (funDef
                           f-name
                           (parse-fun-args-definition (s-exp->list (third (s-exp->list s))))
                           (parse-exp (list-ref (s-exp->list s) 4)))
                          (it rest (cons f-name funs-names)))))
                   (error 'parse-fun-definitions "Invalid function definition"))]))]
    (it funs empty)))

(define (parse-fun-args-definition [args : (Listof S-Exp)]) : (Listof Symbol)
  (local [(define (it xs used-symbols)
              (type-case (Listof S-Exp) xs
                [empty empty]
                [(cons s rest)
                 (if (s-exp-match? `SYMBOL s)
                     (let ([symb (s-exp->symbol s)])
                       (if (member symb used-symbols)
                           (error 'parse-fun-args-definition "Different function arguments with the same symbol")
                           (cons symb (it rest (cons symb used-symbols)))))
                     (error 'parse-fun-args "Function argument not a symbol"))]))]
    (it args empty)))

(define (parse-exp [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (opE (parse-op (s-exp->symbol (second (s-exp->list s))))
          (parse-exp (first (s-exp->list s)))
          (parse-exp (third (s-exp->list s))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifE (parse-exp (second (s-exp->list s)))
          (parse-exp (fourth (s-exp->list s)))
          (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse-exp (fourth (s-exp->list s)))
           (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `{SYMBOL {ANY ...}} s)
     (appE (s-exp->symbol (first (s-exp->list s)))
           (parse-fun-args-application (s-exp->list (second (s-exp->list s)))))]
    [else (error 'parse-exp "invalid input")]))

(define (parse-fun-args-application [args : (Listof S-Exp)]) : (Listof Exp)
  (type-case (Listof S-Exp) args
    [empty empty]
    [(cons s rest)
     (cons (parse-exp s) (parse-fun-args-application rest))]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse-exp `2)
        (numE 2))
  (test (parse-exp `{2 + 1})
        (opE (add) (numE 2) (numE 1)))
  (test (parse-exp `{3 * 4})
        (opE (mul) (numE 3) (numE 4)))
  (test (parse-exp `{{3 * 4} + 8})
        (opE (add)
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test (parse-exp `{ifz {0 <= 1} then {3 * 4} else 8})
        (ifE (opE (leq) (numE 0) (numE 1))
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test/exn (parse-exp `{{1 + 2}})
            "invalid input")
  (test/exn (parse-exp `{1 ^ 2})
            "unknown operator")
  (test/exn (parse-exp `{+ 1})
            "invalid input")
  (test/exn (parse-exp `{+ 2 1})
            "invalid input")
  (test (parse-exp `{let x be 1 in {x + 1}})
        (letE 'x (numE 1) (opE (add) (varE 'x) (numE 1))))
  (test (parse-exp `{let x be {let y be 2 in {y + y}} in {x * 2}})
        (letE 'x
              (letE 'y (numE 2) (opE (add) (varE 'y) (varE 'y)))
              (opE (mul) (varE 'x) (numE 2))))
  (test (parse-exp `{fun1 (9 1)})
        (appE 'fun1 (list (numE 9) (numE 1))))
  (test (parse-exp `{fun2 ()})
        (appE 'fun2 '()))
  (test/exn (parse-exp `{fun2 1})
        "invalid input")
  (test (parse-fun-definitions (s-exp->list `{[fun even (n) = {ifz n then 0 else {odd ({n - 1})}}]
                                              [fun odd (n) = {ifz n then 42 else {even ({n - 1})}}]}))
        (list (funDef 'even
                      (list 'n)
                      (ifE {varE 'n} (numE 0) (appE 'odd (list (opE (sub) (varE 'n) (numE 1))))))
              (funDef 'odd
                      (list 'n)
                      (ifE (varE 'n) (numE 42) (appE 'even (list (opE (sub) (varE 'n) (numE 1))))))))
  (test/exn (parse-fun-definitions (s-exp->list `{[fun even (n) = {ifz n then 0 else {even ({n - 1})}}]
                                                  [fun even (n) = {ifz n then 42 else {even ({n - 1})}}]}))
        "Two functions with the same name")
  (test/exn (parse-fun-definitions (s-exp->list `{[fun even n = {ifz n then 0 else {even ({n - 1})}}]
                                                  [fun even (n) = {ifz n then 42 else {even ({n - 1})}}]}))
        "Invalid function definition")
  (test/exn (parse-fun-definitions (s-exp->list `{[fun even (n n) = {ifz n then 0 else {even ({n - 1})}}]
                                                  [fun even (n) = {ifz n then 42 else {even ({n - 1})}}]}))
            "Different function arguments with the same symbol")
  (test/exn (parse-fun-definitions (s-exp->list `{[fun even (4) = {ifz n then 0 else {even ({n - 1})}}]
                                                  [fun even (n) = {ifz n then 42 else {even ({n - 1})}}]}))
        "Function argument not a symbol")
  (test (parse-prog `{define
                       {[fun fact (n) = {ifz n then 1 else {n * {fact ({n - 1})}}}]}
                       for
                       {fact (5)}})
        (progDef
         (list (funDef
                'fact
                (list 'n)
                (ifE (varE 'n)
                     (numE 1)
                     (opE (mul)
                          (varE 'n)
                          (appE 'fact (list (opE (sub) (varE 'n) (numE 1))))))))
         (appE 'fact (list (numE 5))))))

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) (λ (a b) (if (<= a b) 0 57))]))

;; eval --------------------------------------

(define-type-alias Value Number)

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

;; environments

(define-type-alias Env (Listof Binding))
(define-type-alias DefinedFunctions (Listof Fun))

(define (lookup-fun [f : Symbol] [funs : DefinedFunctions]) : Fun
  (type-case (Listof Fun) funs
    [empty (error 'lookup-fun "unbound function name")]
    [(cons fun rest)
     (cond
       [(eq? f (funDef-name fun))
        fun]
       [else (lookup-fun f rest)])]))

(define mt-env empty)

(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))

(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case (Listof Binding) env
    [empty (error 'lookup-env "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (bind-val b)]
                        [else (lookup-env n rst-env)])]))

(define (make-env [symbs : (Listof Symbol)] [vals : (Listof Value)]) : Env
  (type-case (Listof Symbol) symbs
    [empty
     (if (empty? vals)
         empty
         (error 'eval "too many arguments passed to function"))]
    [(cons s rest-sym)
     (type-case (Listof Value) vals
       [empty
        (error 'eval "too few arguments passed to function")]
       [(cons v rest-val)
        (cons (bind s v) (make-env rest-sym rest-val))])]))

;; evaluation function (eval/apply)

(define (eval [p : Prog]) : Value
  (eval-exp (progDef-e p) (progDef-defs p) mt-env))

(define (eval-exp [e : Exp] [funs : DefinedFunctions] [env : Env]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o l r) ((op->proc o) (eval-exp l funs env) (eval-exp r funs env))]
    [(ifE b l r)
     (let ([v (eval-exp b funs env)])
       (if (= 0 v)
           (eval-exp l funs env)
           (eval-exp r funs env)))]
    [(varE x)
     (lookup-env x env)]                                   
    [(letE x e1 e2)
     (let ([v1 (eval-exp e1 funs env)])
       (eval-exp e2 funs (extend-env env x v1)))]  
    [(appE f args)
     (apply (lookup-fun f funs) (eval-exp-list args funs env) funs)]))                         

(define (apply [f : Fun] [args : (Listof Value)] [funs : DefinedFunctions]) : Value
  (eval-exp (funDef-e f) funs (make-env (funDef-args f) args)))

(define (eval-exp-list [xs : (Listof Exp)] [funs : DefinedFunctions] [env : Env]) : (Listof Value)
  (type-case (Listof Exp) xs
    [empty empty]
    [(cons e rest)
     (cons
      (eval-exp e funs env)
      (eval-exp-list rest funs env))]))


(define (run [s : S-Exp]) : Value
  (eval (parse-prog s)))

(module+ test
  (test (run `{define {} for 2})
        2)
  (test (run `{define {} for {2 + 1}})
        3)
  (test (run `{define {} for {3 * 4}})
        12)
  (test (run `{define {} for {{3 * 4} + 8}})
        20)
  (test (run `{define {} for {ifz {0 <= 1} then {3 * 4} else 8}})
        12)
  (test (run `{define {} for {let x be 1 in {x + 1}}})
        2)
  (test (run `{define {} for {let x be {let y be 2 in {y + y}} in {x * 2}}})
        8)
  (test (run `{define
                {[fun fact (n) = {ifz n then 1 else {n * {fact ({n - 1})}}}]}
                for
                {fact (5)}})
        120)
  (test (run `{define
                {[fun even (n) = {ifz n then 0 else {odd ({n - 1})}}]
                 [fun odd (n) = {ifz n then 42 else {even ({n - 1})}}]}
                for
                {even (1024)}})
        0)
  (test (run `{define
                {[fun gcd (m n) = {ifz n
                                       then m
                                       else {ifz {m <= n}
                                                 then {gcd (m {n - m})}
                                                 else {gcd ({m - n} n)}}}]}
                for
                {gcd (81 63)}})
        9)
  (test/exn (run `{define
                    {[fun f (m n) = {m + n}]}
                    for
                    {f (1 2 3)}})
            "too many arguments passed to function")
  (test/exn (run `{define
                    {[fun f (m n) = {m + n}]}
                    for
                    {f (1)}})
            "too few arguments passed to function")
  (test/exn (run `{define
                    {[fun f (m n) = {m + x}]}
                    for
                    {let x be 4 in {f (1 2)}}})
            "unbound variable")
  (test (run `{define
                {[fun f () = {ifz 0 then 1 else 2}]}
                for
                {f ()}})
        1)
  (test (run `{define
                {[fun fib (a) = {ifz {a <= 1}
                                     then a
                                     else {{fib ({a - 1})} + {fib ({a - 2})}}}]}
                for
                {fib (9)}})
        34))