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

zero add1 add1
zero add1 add1
add

wire-print-net
run
wire-print-net
