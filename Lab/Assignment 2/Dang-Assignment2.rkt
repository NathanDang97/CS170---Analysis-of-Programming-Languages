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

; listleaves, defined so that (listleaves bt) lists the leaves in the binary tree bt,
; using the representation discussed in class and the text. For example,
; (listleaves '(a (b (c () ()) (d () (f () ()))) (e () ())))
; returns,
; (c f e)
(define (listleaves bt)
  ; if the 2th and 3th element of the list it null, then the 1st one is a leaf,
  ; thus, construct a list containing this one leaf
  (cond ((and (null? (nth bt 3)) (null? (nth bt 2))) (cons (car bt) '()))
        ; if the 3th element is null (i.e. right subtree is empty), traverse the left subtree
        ((null? (nth bt 3)) (listleaves (nth bt 2)))
        ; if the 2th element is null (i.e. left subtree is empty), traverse the right subtree
        ((null? (nth bt 2)) (listleaves (nth bt 3)))
        ; if none of the subtrees is null, traverse both and append their lists of leaves
        (#t (append (listleaves (nth bt 2)) (listleaves (nth bt 3))))))

; bsearch, so that (bsearch item bst) returns #t if item is found in the binary search tree bst.
; Assume that item is an integer and that the elements of the tree bst are integers.
; Use the binary search algorithm (not contains!). Thus, for example,
; (bsearch 3 '(5 (2 (1 () ()) (3 () (4 () ()))) (7 () ()))) returns #t, and
; (bsearch 6 '(5 (2 (1 () ()) (3 () (4 () ()))) (7 () ()))) returns #f.
(define (bsearch item bst)
  ; if reach null (i.e. the item cannot be found), return false
  (cond ((null? bst) #f)
        ; if the the current node is greater than the item, move to the left subtree
        ((> (car bst) item) (bsearch item (nth bst 2)))
        ; if the current node is less than the item, move to the right subtree
        ((< (car bst) item) (bsearch item (nth bst 3)))
        ; if it's a hit, return true
        ((equal? (car bst) item) #t)
        ; defaut case, for my own convention
        (#t #f)))