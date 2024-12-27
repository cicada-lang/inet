* zero -> value! end
* add1 prev -> value! end
* add target! addend -> result end

! (zero)-(add)
  (add)-addend result-(add)
end

! (add1)-(add)
  (add1)-prev (add)-addend add
  add1 result-(add)
end

(- test -)

= one zero add1 end
= two one one add end
= three two one add end
= four two two add end

. two two add
  two two add
  add

  wire-print-net
  run
  wire-print-net
end

(- to define `mul`, we first need `nat-erase` and `nat-dup`. -)

* nat-erase target! -> end

! (zero)-(nat-erase)
end

! (add1)-(nat-erase)
  (add1)-prev nat-erase
end

* nat-dup target! -> first second end

! (zero)-(nat-dup)
  zero first-(nat-dup)
  zero second-(nat-dup)
end

! (add1)-(nat-dup)
  (add1)-prev nat-dup
  (- first second -) add1 second-(nat-dup)
  (- first -) add1 first-(nat-dup)
end

* mul target! mulend -> result end

! (zero)-(mul)
  (mul)-mulend nat-erase
  zero result-(mul)
end

! (add1)-(mul)
  (mul)-mulend nat-dup
  (- first second -) (add1)-prev swap mul
  (- first almost -) add result-(mul)
end

. two two mul

  wire-print-net
  run
  wire-print-net
end

(- to define `max`, we need `max-aux`. -)

* max first! second -> result end
* max-aux first second! -> result end

! (zero)-(max)
  (max)-second result-(max)
end

! (add1)-(max)
  (add1)-prev (max)-second max-aux
  result-(max)
end

! (zero)-(max-aux)
  (max-aux)-first add1
  result-(max-aux)
end

! (add1)-(max-aux)
  (max-aux)-first (add1)-prev max
  add1 result-(max-aux)
end

. one two max

  wire-print-net
  run
  wire-print-net
end
