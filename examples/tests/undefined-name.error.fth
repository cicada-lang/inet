define-rule zero add
  (add)-addend result-(add)
end

define-rule add1 add
  (add1)-prev (add)-addend add
  add1 result-(add)
end
