define-node zero -> value! end
define-node add1 prev -> value! end
define-node add target! addend -> result end

-- define-rule zero add
--   (add)-addend result-(add)
-- end

-- define-rule add1 add
--   (add1)-prev (add)-addend add
--   add1 result-(add)
-- end

define-rule zero add
  ( addend result )
  addend result connect
end

define-rule add1 add
  ( addend result ) ( prev )
  prev addend add
  add1 result connect
end

-- zero add1 add1
-- zero add1 add1
-- add

-- wire-print-net
-- run
-- wire-print-net
