; The function fib, so that (fib n) returns the n-th Fibonacci number.
; Translate the efficient, tail-recursive C version discussed in lecture to Scheme.
; fib(n) should work starting at n=0, with fib(0) = 0, fib(1) = 1,
; and the recurrence relation taking care of fib(n) for n >= 2.
(define (goodfib n prev2 prev1) ; prev1 = fib of (n-1)th, prev2 = fib of (n-2)th
  (cond ((= n 0) prev2)
        ((= n 1) prev1)
        (#t (goodfib (- n 1) prev1 (+ prev1 prev2)))))
(define (fib n)
  (goodfib n 0 1))

; nth, defined such that (nth alist n) returns the n-th element in alist.
; Start the indexing at 1, so (for example),
; (nth '(a b c d) 1) returns a,
; (nth '(a b c d) 2) returns b, etc.
; If the list has less than n entries, have it return the empty list.
(define (nth list n)
  (cond ((null? list) '())
        ((< (length list) n) '())
        ((= n 1) (car list))
        (#t (nth (cdr list) (- n 1)))))

; contains, defined such that (contains alist item) returns #t
; if item can be found in any level of alist, and #f otherwise.
; For example,(contains '(a (b c) d) 'c) returns #t,
; and (contains '(a (b c) d) 'e) returns #f.
(define (contains list item)
  (cond ((null? list) #f)
        ((equal? (car list) item) #t)
        ; if we have something like '(a (b c) d e f), assuming not looking for 'a'
        ; we will want to check for the next level, i.e (b c)- the "inside list"
        ; and the rest of the list, i.e. d e f
        ; if either of the check is true, the function should return true
        ((list? (car list)) (or (contains (car list) item) (contains (cdr list) item)))
        (#t (contains (cdr list) item))))