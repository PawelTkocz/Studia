#lang racket

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join
         )

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

; Wstawianie
(define (same-type? x y)
  (if (or (and (equal? y 'number) (number? x))
          (and (equal? y 'string) (string? x))
          (and (equal? y 'symbol) (symbol? x))
          (and (equal? y 'boolean) (boolean? x)))
      #t
      #f))

(define (row-ok-typed? row schema)
  (if (null? row)
      #t
      (and (same-type? (car row) (column-info-type (car schema)))(row-ok-typed? (cdr row) (cdr schema)))))

(define (table-insert row tab)
  (if (row-ok-typed? row (table-schema tab))
      (table
       (table-schema tab)
       (cons row (table-rows tab)))
      (error 'failed))
  )

; Projekcja
(define (append-element xs elem)
  (foldr cons (cons elem null) xs))

(define (indexes-of-chosen-columns schema cols)
  (define (it schm res ind)
    (if (null? schm)
        res
        (if (member (column-info-name (car schm)) cols)
            (it (cdr schm) (append-element res ind) (+ 1 ind))
            (it (cdr schm) res (+ 1 ind)))))
  (it schema null 0))

(define (make-row column-indexes row)
  (define (it indxs res)
    (if (null? indxs)
        res
        (it (cdr indxs) (append-element res (list-ref row (car indxs))))))
  (it column-indexes null))

(define (schema-with-chosen-columns indexes schema)
  (define (it indx res)
    (if (null? indx)
        res
        (it (cdr indx) (append-element res (list-ref schema (car indx))))))
  (it indexes null))

(define (rows-with-chosen-columns table-rows indexes)
  (define (it rows res)
    (if (null? rows)
        res
        (it (cdr rows) (append-element res (make-row indexes (car rows))))))
  (it table-rows null))

(define (table-project cols tab)
  (let ([ind (indexes-of-chosen-columns (table-schema tab) cols)])
    (table
     (schema-with-chosen-columns ind (table-schema tab))
     (rows-with-chosen-columns (table-rows tab) ind))))

; Sortowanie
(define (lex-boolean<? bool1 bool2)
  (if (and (equal? #f bool1) (equal? #t bool2))
      #t
      #f))

(define (lex<? row1 row2 cols schema-col-names)
     (if (null? cols)
         #f
         (let ([ind (index-of schema-col-names (car cols))])
           (let ([elem1 (list-ref row1 ind)]
                 [elem2 (list-ref row2 ind)])
             (if (equal? elem1 elem2)
                 (lex<? row1 row2 (cdr cols) schema-col-names)
                 ((cond [(number? elem1) <]
                   [(string? elem1) string<?]
                   [(symbol? elem1) symbol<?]
                   [(boolean? elem1) lex-boolean<?]) elem1 elem2))))))

(define (insert row rows cols schema-col-names)
  (if (null? rows)
      (list row)
      (if (lex<? row (car rows) cols schema-col-names)
          (cons row rows)
          (cons (car rows) (insert row (cdr rows) cols schema-col-names)))))

(define (insertion-sort rows cols schema-col-names)
  (define (it xs res)
    (if (null? xs)
        res
        (it (cdr xs) (insert (car xs) res cols schema-col-names))))
  (it rows null))

(define (column-names tab)
  (map (λ (x) (column-info-name x))(table-schema tab)))

(define (table-sort cols tab)
  (table
   (table-schema tab)
   (insertion-sort (table-rows tab) cols (column-names tab))))


 ;Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (column-value column-name schema-col-names row)
  (if (equal? (column-info-name (car schema-col-names)) column-name)
      (car row)
      (column-value column-name (cdr schema-col-names) (cdr row))))

(define (table-select form tab)
  
  (define (row-fullfills-form? row formula)
    (cond [(and-f? formula) (and (row-fullfills-form? row (and-f-l formula))(row-fullfills-form? row (and-f-r formula)))]
          [(or-f? formula)(or (row-fullfills-form? row (or-f-l formula))(row-fullfills-form? row (or-f-r formula)))]
          [(not-f? formula)(not (row-fullfills-form? row (not-f-e formula)))]
          [(eq-f? formula)(equal? (eq-f-val formula) (column-value (eq-f-name formula) (table-schema tab) row))]
          [(eq2-f? formula)(equal? (column-value (eq2-f-name formula) (table-schema tab) row) (column-value (eq2-f-name2 formula) (table-schema tab) row))]
          [(lt-f? formula)(< (column-value (lt-f-name formula) (table-schema tab) row) (lt-f-val formula))]))
  (define (selected-rows rows res)
    (if (null? rows)
        res
        (if (row-fullfills-form? (car rows) form)
            (selected-rows (cdr rows) (append-element res (car rows)))
            (selected-rows (cdr rows) res))))
   (table
    (table-schema tab)
    (selected-rows (table-rows tab) null)))

; Zmiana nazwy

(define (table-rename col ncol tab)
  (define (renamed-schema schema res)
    (if (null? schema)
        res
        (if (equal? (column-info-name (car schema)) col)
            (renamed-schema (cdr schema) (append-element res (column-info ncol (column-info-type (car schema)))))
            (renamed-schema (cdr schema) (append-element res (car schema))))))
  (table
   (renamed-schema (table-schema tab) null)
   (table-rows tab)))

; Złączenie kartezjańskie

(define (cross-join-rows rows1 rows2)
  (define (it1 rows res)
    (define (it2 row21 rows22 res2)
      (if (null? rows22)
          res2
          (it2 row21 (cdr rows22) (cons (append row21 (car rows22)) res2))))
    (if (null? rows)
        res
        (it1 (cdr rows) (it2 (car rows) rows2 res))))
  (it1 rows1 null))

(define (table-cross-join tab1 tab2)
  (table
   (append (table-schema tab1)(table-schema tab2))
   (cross-join-rows (table-rows tab1) (table-rows tab2))))

; Złączenie

(define (final-columns-names tab1 tab2 repeats)
  (define (it tab2 res)
    (if (null? tab2)
        res
        (if (member (car tab2) repeats)
            (it (cdr tab2) res)
            (it (cdr tab2) (cons (car tab2) res)))))
  (it (column-names tab2) (column-names tab1)))

(define (make-formula repeats)
  (if (= 1 (length repeats))
      (eq2-f (car repeats) (repeating-name (car repeats)))
      (and-f (eq2-f (car repeats) (repeating-name (car repeats))) (make-formula (cdr repeats)))))

(define (names-of-repeating-columns schema1-col-names schema2-col-names)
  (define (it schm2 res)
    (if (null? schm2)
        res
        (if (member (car schm2) schema1-col-names)
            (it (cdr schm2) (cons (car schm2) res))
            (it (cdr schm2) res))))
  (it schema2-col-names null))

(define (repeating-name name)
  (string->symbol (string-append (symbol->string name) "repeat")))


(define (rename-repeating-columns tab repeating-columns)
  (if (null? repeating-columns)
      tab
      (rename-repeating-columns (table-rename (car repeating-columns) (repeating-name (car repeating-columns)) tab) (cdr repeating-columns))))

(define (table-natural-join tab1 tab2)
  (let ([repeats (names-of-repeating-columns (column-names tab1) (column-names tab2))])
    (table-project (final-columns-names tab1 tab2 repeats) (table-select (make-formula repeats) (table-cross-join tab1 (rename-repeating-columns tab2 repeats))))))