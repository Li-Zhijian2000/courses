;; Scheme ;;


(define lst
  (list (list 1) 2 (list 3 4) 5)
)

(define (composed f g)
  (lambda (x) (f (g x)))
)

(define (remove item lst)
  (filter-lst (lambda (x) (not (= item x))) lst)
)


;;; Tests
(remove 3 nil)
; expect ()
(remove 3 '(1 3 5))
; expect (1 5)
(remove 5 '(5 3 5 5 1 4 5 4))
; expect (3 1 4 4)

(define (no-repeats s)
  (if (null? s)
    nil
    (cons (car s) (remove (car s) (no-repeats (cdr s)))))
)

(define (substitute s old new)
  (if (null? s)
    nil
    (cons (cond
            ((pair? (car s)) (substitute (car s) old new))
            ((equal? (car s) old) new)
            (else (car s)))
          (substitute (cdr s) old new)))
)


(define (sub-all s olds news)
  (if (null? olds)
    s
    (substitute (sub-all s (cdr olds) (cdr news)) (car olds) (car news)))
)
