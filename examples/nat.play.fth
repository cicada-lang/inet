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

define two zero add1 add1 end

begin two two add
  two two add
  add debug
end
