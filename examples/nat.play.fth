* (zero) -> value! end
* (add1) prev -> value! end
* (add) target! addend -> result end

! (zero)-(add)
  (add)-addend result-(add)
end

! (add1)-(add)
  (add1)-prev (add)-addend add
  add1 result-(add)
end

(- test -)

= two zero add1 add1 end

. two two add
  two two add
  add debug
end
