(define-type nat)

(define-node zero () ((! value nat)))
(define-node add1 ((prev nat)) ((! value nat)))

(define-node add
  ((! target nat)
   (addend nat))
  ((result nat)))

(let ((z (add (two) (two)))
      ((y z) (add (two)))
      ((x y z) (add)))
  (add (two) (two) result)
  (connect (add (two) (two)) result))

(define-rule
    (add (! target) addend result)
    (zero (! value))
  (connect addend result))

(define-rule
    (add (! target) addend result)
    (add1 prev (! value))
  (add1 (add prev addend) result))
