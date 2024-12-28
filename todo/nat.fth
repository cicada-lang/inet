define-node zero -> value! end
define-node add1 prev -> value! end
define-node add target! addend -> result end

define-rule add zero
  ( addend result )
  addend result connect
end

define-rule add add1
  ( addend result ) ( prev )
  prev addend add add1
  result connect
end

define two zero add1 add1 end

two two add

wire-print-net run
wire-print-net
