define-node zero -> value! end
define-node add1 prev -> value! end
define-node add target! addend -> result end

define-rule zero add
  (add)-addend result-(add)
end

define-rule add1 add
  (add1)-prev (add)-addend add
  add1 result-(add)
end

(- test -)

define one zero add1 end
define two one one add end
define three two one add end
define four two two add end

two two add
two two add
add

wire-print-net
run
wire-print-net

(- to define `mul`, we first need `nat-erase` and `nat-dup` -)

define-node nat-erase target! -> end

define-rule zero nat-erase
end

define-rule add1 nat-erase
  (add1)-prev nat-erase
end

define-node nat-dup target! -> first second end

define-rule zero nat-dup
  zero first-(nat-dup)
  zero second-(nat-dup)
end

define-rule add1 nat-dup
  (add1)-prev nat-dup
  (- first second -) add1 second-(nat-dup)
  (- first -) add1 first-(nat-dup)
end

define-node mul target! mulend -> result end

define-rule zero mul
  (mul)-mulend nat-erase
  zero result-(mul)
end

define-rule add1 mul
  (mul)-mulend nat-dup
  (- first second -) (add1)-prev swap mul
  (- first almost -) add result-(mul)
end

two two mul

wire-print-net
run
wire-print-net


(- to define `max`, we need `max-aux` -)

define-node max first! second -> result end
define-node max-aux first second! -> result end

define-rule zero max
  (max)-second result-(max)
end

define-rule add1 max
  (add1)-prev (max)-second max-aux
  result-(max)
end

define-rule zero max-aux
  (max-aux)-first add1
  result-(max-aux)
end

define-rule add1 max-aux
  (max-aux)-first (add1)-prev max
  add1 result-(max-aux)
end

one two max

wire-print-net
run
wire-print-net
