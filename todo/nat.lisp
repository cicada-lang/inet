(define-node zero value!)
(define-node add1 prev value!)
(define-node add target! addend result)

(define-rule (add (zero) addend result)
  (connect addend result))

(define-rule (add (add1 prev) addend result)
  (add1 (add prev addend) result))

(define-rule* ((add target! addend result)
               (zero value!))
  (connect addend result))

(define-rule* ((add target! addend result)
               (add1 prev value!))
  (add1 (add prev addend) result))

;; test

(wire-print-net
 (run
  (wire-print-net
   (add (add1 (add1 zero))
        (add1 (add1 zero))))))
