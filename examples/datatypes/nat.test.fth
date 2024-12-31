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

define one nzero nadd1 end
define two one one nadd end
define three two one nadd end
define four two two nadd end

two two nadd
two two nadd
nadd

wire-print-net
run
wire-print-net

-- to define `nmul`, we first need `nat-erase` and `nat-dup`

define-node nat-erase target! -> end

define-rule nzero nat-erase
end

define-rule nadd1 nat-erase
  ( prev )
  prev nat-erase
end

define-node nat-dup target! -> first second end

define-rule nzero nat-dup
  ( first second )
  nzero first connect
  nzero second connect
end

define-rule nadd1 nat-dup
  ( first second ) ( prev )
  prev nat-dup
  ( prev-first prev-second )
  prev-second nadd1 second connect
  prev-first nadd1 first connect
end

define-node nmul target! mulend -> result end

define-rule nzero nmul
  ( mulend result )
  mulend nat-erase
  nzero result connect
end

define-rule nadd1 nmul
  ( mulend result ) ( prev )
  mulend nat-dup
  ( mulend-first mulend-second )
  prev mulend-second swap nmul
  mulend-first nadd result connect
end

two two nmul

wire-print-net
run
wire-print-net

-- to define `nat-max`, we need `nat-max-aux`

define-node nat-max first! second -> result end
define-node nat-max-aux first second! -> result end

define-rule nzero nat-max
  ( second result )
  second result connect
end

define-rule nadd1 nat-max
  ( second result ) ( prev )
  prev second nat-max-aux result connect
end

define-rule nzero nat-max-aux
  ( first result )
  first nadd1 result connect
end

define-rule nadd1 nat-max-aux
  ( first result ) ( prev )
  first prev nat-max
  nadd1 result connect
end

one two nat-max

wire-print-net
run
wire-print-net
