(node zero value!)
(node add1 prev value!)
(node add target! addend result)

(rule (add (zero) addend result)
  (connect addend result))

(rule (add (add1 prev) addend result)
  (add1 (add prev addend) result))

;; test

(wire-print-net
 (interact
  (wire-print-net
   (add (add1 (add1 zero))
        (add1 (add1 zero))))))
