define-node nzero -> value! end
define-node nadd1 prev -> value! end
define-node nadd target! addend -> result end

define-rule nzero nadd
  ( addend result )
  addend result connect
end

define-rule nadd1 nadd
  ( addend result ) ( prev )
  prev addend nadd
  nadd1 result connect
end

define two
  nzero nadd1 nadd1
end

two two nadd

wire-print-net
run
wire-print-net
