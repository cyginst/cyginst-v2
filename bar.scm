;;; bar.scm

; The declaration marks this source file as the bar unit.  The names of the
; units and your files don't need to match.
(declare (unit bar))

(define (fac n)
  (if (zero? n)
      1
      (* n (fac (- n 1))) ) )
