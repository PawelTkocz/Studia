#lang racket
(require data/heap)
(require rackunit)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))


(struct sim ([curTime #:mutable] [eventHeap #:mutable]))
(struct wire ([value #:mutable] [actions #:mutable] sim))

(struct eventToDo (act time))

(define (eventToDo<=? x y)
  (<= (eventToDo-time x) (eventToDo-time y)))

(define (empty-heap)
  (make-heap eventToDo<=?))

(define (make-sim)
  (sim 0 (empty-heap)))

(define (call-events sim)
  (let ([eventHeap (sim-eventHeap sim)]
        [curTime (sim-curTime sim)])
    (if (= 0 (heap-count eventHeap))
          (void)
          (let* ([event (heap-min eventHeap)]
                 [eventTime (eventToDo-time event)])
            (if (<= eventTime curTime)
                (begin
                  (set-sim-curTime! sim eventTime)
                  ((eventToDo-act event))
                  (heap-remove-min! eventHeap)
                  (set-sim-curTime! sim curTime)
                  (call-events sim))
                (void))))))

(define (sim-wait! sim t)
  (begin
    (set-sim-curTime! sim (+ (sim-curTime sim) t))
    (call-events sim)))

(define (sim-time sim)
  (sim-curTime sim))

(define (sim-add-action! sim t act)
  (let* ([actTime (+ t (sim-curTime sim))]
         [eventToInsert (eventToDo act actTime)])
    (heap-add! (sim-eventHeap sim) eventToInsert)))

(define (make-wire sim)
  (wire #f null sim))

(define (wire-on-change! w act)
  (begin
    (set-wire-actions! w (cons act (wire-actions w)))
    (act)))

(define (call-wire-actions w)
  (define (it xs)
    (if (null? xs)
        (void)
        (begin
          ((car xs))
          (it (cdr xs)))))
  (it (wire-actions w)))

(define (wire-set! w v)
  (if (equal? (wire-value w) v)
      (void)
      (begin
        (set-wire-value! w v)
        (call-wire-actions w))))

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (valid-2-wires-connection a b)
  (equal? (wire-sim a) (wire-sim b)))

(define (valid-3-wires-connection a b c)
  (and (valid-2-wires-connection a b) (valid-2-wires-connection b c)))

(define (gate-not b a)
  (define (not-res)
    (wire-set! b (not (wire-value a))))
  (define (not-action)
    (sim-add-action! (wire-sim b) 1 not-res))
  (if (valid-2-wires-connection a b)
      (wire-on-change! a not-action)
      (error 'gate-not "connectig wires from different simulations")))

(define (gate-and c a b)
  (define (and-res)
    (wire-set! c (and (wire-value a) (wire-value b))))
  (define (and-action)
    (sim-add-action! (wire-sim c) 1 and-res))
  (if (valid-3-wires-connection a b c)
      (begin
        (wire-on-change! a and-action)
        (wire-on-change! b and-action))
      (error 'gate-and "connectig wires from different simulations")))

(define (gate-nand c a b)
  (define (nand-res)
    (wire-set! c (nand (wire-value a) (wire-value b))))
  (define (nand-action)
    (sim-add-action! (wire-sim c) 1 nand-res))
  (if (valid-3-wires-connection a b c)
      (begin
        (wire-on-change! a nand-action)
        (wire-on-change! b nand-action))
      (error 'gate-nand "connecting wires from different simulations")))

(define (gate-or c a b)
  (define (or-res)
    (wire-set! c (or (wire-value a) (wire-value b))))
  (define (or-action)
    (sim-add-action! (wire-sim c) 1 or-res))
  (if (valid-3-wires-connection a b c)
      (begin
          (wire-on-change! a or-action)
          (wire-on-change! b or-action))
      (error 'gate-or "connecting wires from different simulations")))

(define (gate-nor c a b)
  (define (nor-res)
    (wire-set! c (nor (wire-value a) (wire-value b))))
  (define (nor-action)
    (sim-add-action! (wire-sim c) 1 nor-res))
  (if (valid-3-wires-connection a b c)
      (begin
        (wire-on-change! a nor-action)
        (wire-on-change! b nor-action))
      (error 'gate-nor "connecting wires from different simulations")))

(define (gate-xor c a b)
  (define (xor-res)
    (wire-set! c (xor (wire-value a) (wire-value b))))
  (define (xor-action)
    (sim-add-action! (wire-sim c) 2 xor-res))
  (if (valid-3-wires-connection a b c)
      (begin
        (wire-on-change! a xor-action)
        (wire-on-change! b xor-action))
      (error 'gate-xor "connecting wires from different simulations")))

(define (wire-not a)
  (let ([c (make-wire (wire-sim a))])
    (begin
      (gate-not c a)
      c)))

(define (wire-and a b)
  (if (valid-2-wires-connection a b)
        (let ([c (make-wire (wire-sim a))])
          (begin
            (gate-and c a b)
            c))
        (error 'wire-and "connecting wires from different simulations")))

(define (wire-nand a b)
  (if (valid-2-wires-connection a b)
        (let ([c (make-wire (wire-sim a))])
          (begin
            (gate-nand c a b)
            c))
        (error 'wire-nand "connecting wires from different simulations")))

(define (wire-or a b)
  (if (valid-2-wires-connection a b)
        (let ([c (make-wire (wire-sim a))])
          (begin
            (gate-or c a b)
            c))
        (error 'wire-or "connecting wires from different simulations")))

(define (wire-nor a b)
  (if (valid-2-wires-connection a b)
        (let ([c (make-wire (wire-sim a))])
          (begin
            (gate-nor c a b)
            c))
        (error 'wire-nor "connecting wires from different simulations")))

(define (wire-xor a b)
  (if (valid-2-wires-connection a b)
        (let ([c (make-wire (wire-sim a))])
          (begin
            (gate-xor c a b)
            c))
        (error 'wire-xor "connecting wires from different simulations")))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

#|
;---------------------------------------------------------------------------------------------
;testy
(define test-sim (make-sim))
(define test-wire (make-wire test-sim))
(define test-val 0)
(define (pom-fun) (set! test-val (+ test-val 1)))

;funkcja sim?
(check-true (sim? test-sim))

;funckja wire?
(check-true (wire? test-wire))

;funkcja sim-time
(check-equal? 5 (sim-time (sim 5 (empty-heap))))

;funkcja sim-add-action!
(sim-add-action! test-sim 16 pom-fun)
(sim-add-action! test-sim 7 pom-fun)
(check-equal? 7 (eventToDo-time (heap-min (sim-eventHeap test-sim))))
((eventToDo-act (heap-min (sim-eventHeap test-sim))))
(check-equal? 1 test-val)

;funckja wire-set!
(wire-set! test-wire #t)
(check-true (wire-value test-wire))
(wire-set! test-wire #f)
(check-false (wire-value test-wire))

;funkcja wire-on-change!
(set! test-val 0)
(wire-on-change! test-wire pom-fun)
(wire-on-change! test-wire pom-fun)
(wire-on-change! test-wire pom-fun)
(check-equal? 3 test-val)
(set! test-val 0)
(wire-set! test-wire #t)
(check-equal? 3 test-val)

;funcja sim-wait!, sim-add-action!
(define test-sim2 (make-sim))
(set! test-val 0)
(sim-add-action! test-sim2 1 pom-fun)
(sim-add-action! test-sim2 3 pom-fun)
(sim-add-action! test-sim2 5 pom-fun)
(sim-add-action! test-sim2 7 pom-fun)
(sim-wait! test-sim2 3)
(check-equal? 2 test-val)
(check-equal? 2 (heap-count (sim-eventHeap test-sim2)))
(set! test-val 0)
(check-equal? 3 (sim-time test-sim2))
(sim-wait! test-sim2 4)
(check-equal? 2 test-val)
(check-equal? 7 (sim-time test-sim2))
(check-equal? 0 (heap-count (sim-eventHeap test-sim2)))
(define (pom-fun2)
  (set! test-val (+ test-val (sim-curTime test-sim2)))
  (sim-add-action! test-sim2 2 pom-fun2))
(set! test-val 0)
(sim-add-action! test-sim2 1 pom-fun2)
(sim-wait! test-sim2 10)
(check-equal? 17 (sim-time test-sim2))
(check-equal? 60 test-val)
(check-equal? 1 (heap-count (sim-eventHeap test-sim2)))

;funckja gate-not
(define a (make-wire test-sim))
(define b (make-wire test-sim))
(gate-not b a)
(sim-wait! test-sim 1)
(check-true (wire-value b))

;funckja gate-and
(define a2 (make-wire test-sim))
(define b2 (make-wire test-sim))
(define c2 (make-wire test-sim))
(gate-and c2 a2 b2)
(wire-set! a2 #t)
(sim-wait! test-sim 1)
(check-false (wire-value c2))
(wire-set! b2 #t)
(sim-wait! test-sim 1)
(check-true (wire-value c2))

;funckja gate-nand
(define a3 (make-wire test-sim))
(define b3 (make-wire test-sim))
(define c3 (make-wire test-sim))
(gate-nand c3 a3 b3)
(sim-wait! test-sim 1)
(check-true (wire-value c3))
(wire-set! a3 #t)
(sim-wait! test-sim 1)
(check-true (wire-value c3))
(wire-set! b3 #t)
(sim-wait! test-sim 1)
(check-false (wire-value c3))

;funckja gate-or
(define a4 (make-wire test-sim))
(define b4 (make-wire test-sim))
(define c4 (make-wire test-sim))
(gate-or c4 a4 b4)
(sim-wait! test-sim 1)
(check-false (wire-value c4))
(wire-set! a4 #t)
(sim-wait! test-sim 1)
(check-true (wire-value c4))
(wire-set! b4 #t)
(sim-wait! test-sim 1)
(check-true (wire-value c4))

;funckja gate-nor
(define a5 (make-wire test-sim))
(define b5 (make-wire test-sim))
(define c5 (make-wire test-sim))
(gate-nor c5 a5 b5)
(sim-wait! test-sim 1)
(check-true (wire-value c5))
(wire-set! a5 #t)
(sim-wait! test-sim 1)
(check-false (wire-value c5))
(wire-set! b5 #t)
(sim-wait! test-sim 1)
(check-false (wire-value c5))

;funckja gate-xor
(define a6 (make-wire test-sim))
(define b6 (make-wire test-sim))
(define c6 (make-wire test-sim))
(gate-xor c6 a6 b6)
(sim-wait! test-sim 2)
(check-false (wire-value c6))
(wire-set! a6 #t)
(sim-wait! test-sim 1)
(check-false (wire-value c6))
(sim-wait! test-sim 1)
(check-true (wire-value c6))
(wire-set! b6 #t)
(sim-wait! test-sim 2)
(check-false (wire-value c6))

;funkcje gate-xor i gate-nand - test opoznienia
(define d (make-wire test-sim))
(define e (make-wire test-sim))
(define f (make-wire test-sim))
(define g (make-wire test-sim))
(define h (make-wire test-sim))
(gate-xor f d e)
(gate-nand h g f)
(wire-set! d #t)
(sim-wait! test-sim 1)
(check-false (wire-value f))
(sim-wait! test-sim 1)
(check-true (wire-value f))
(wire-set! g #t)
(wire-set! e #t)
(sim-wait! test-sim 1)
(check-false (wire-value h))
(check-true (wire-value f))
(sim-wait! test-sim 1)
(check-false (wire-value h))

;funkcja wire-not
(define k (make-wire test-sim))
(define l (wire-not k))
(check-true (wire? l))
(sim-wait! test-sim 1)
(check-true (wire-value l))

;funkcja wire-and
(define k2 (make-wire test-sim))
(define m2 (make-wire test-sim))
(define l2 (wire-and k2 m2))
(check-true (wire? l2))
(wire-set! k2 #t)
(wire-set! m2 #t)
(sim-wait! test-sim 1)
(check-true (wire-value l2))

;funkcja wire-nand
(define k3 (make-wire test-sim))
(define m3 (make-wire test-sim))
(define l3 (wire-nand k3 m3))
(check-true (wire? l3))
(sim-wait! test-sim 1)
(check-true (wire-value l3))
(wire-set! k3 #t)
(wire-set! m3 #t)
(sim-wait! test-sim 1)
(check-false (wire-value l3))

;funkcja wire-or
(define k4 (make-wire test-sim))
(define m4 (make-wire test-sim))
(define l4 (wire-or k4 m4))
(check-true (wire? l4))
(wire-set! k4 #t)
(sim-wait! test-sim 1)
(check-true (wire-value l4))

;funkcja wire-nor
(define k5 (make-wire test-sim))
(define m5 (make-wire test-sim))
(define l5 (wire-nor k5 m5))
(check-true (wire? l3))
(sim-wait! test-sim 1)
(check-true (wire-value l5))
(wire-set! k5 #t)
(sim-wait! test-sim 1)
(check-false (wire-value l5))

;funkcja wire-xor
(define k6 (make-wire test-sim))
(define m6 (make-wire test-sim))
(define l6 (wire-xor k6 m6))
(check-true (wire? l6))
(wire-set! k6 #t)
(sim-wait! test-sim 2)
(check-true (wire-value l6))
(wire-set! m6 #t)
(sim-wait! test-sim 1)
(check-true (wire-value l6))
(sim-wait! test-sim 1)
(check-false (wire-value l6))

;ostatni test polegający na sprawdzeniu
;poprawności działania funkcji counter
(define test-sim3 (make-sim))

(define (make-counter n clk en)
  (if (= n 0)
      '()
      (let [(out (make-wire test-sim3))]
        (flip-flop out clk (wire-xor en out))
        (cons out (make-counter (- n 1) clk (wire-and en out))))))

(define clk (make-wire test-sim3))
(define en  (make-wire test-sim3))
(define counter (make-counter 4 clk en))

(wire-set! en #t)

(define (tick)
  (wire-set! clk #t)
  (sim-wait! test-sim3 20)
  (wire-set! clk #f)
  (sim-wait! test-sim3 20)
  (bus-value counter))

(define v (tick))
(check-equal? (modulo (+ 1 v) 16) (tick))
(check-equal? (modulo (+ 2 v) 16) (tick))
(check-equal? (modulo (+ 3 v) 16) (tick))
(check-equal? (modulo (+ 4 v) 16) (tick))
(check-equal? (modulo (+ 5 v) 16) (tick))
(check-equal? (modulo (+ 6 v) 16) (tick))
(check-equal? (modulo (+ 7 v) 16) (tick))
(check-equal? (modulo (+ 8 v) 16) (tick))
(check-equal? (modulo (+ 9 v) 16) (tick))
(check-equal? (modulo (+ 10 v) 16) (tick))
(check-equal? (modulo (+ 11 v) 16) (tick))
(check-equal? (modulo (+ 12 v) 16) (tick))
(check-equal? (modulo (+ 13 v) 16) (tick))
(check-equal? (modulo (+ 14 v) 16) (tick))
(check-equal? (modulo (+ 15 v) 16) (tick))
(check-equal? (modulo (+ 16 v) 16) (tick))

|#
