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

. zero add1 add1
  zero add1 add1
  add

  wire-print-net
  run
  wire-print-net
end
