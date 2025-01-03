define-node nil -- value! end
define-node cons tail head -- value! end
define-node append target! rest -- result end

define-rule nil append
  ( rest result )
  rest result connect
end

define-rule cons append
  ( rest result ) ( tail head )
  tail rest append
  head cons result connect
end

define-node sole -- value! end

nil sole cons sole cons sole cons
nil sole cons sole cons sole cons
append

wire-print-net
run
wire-print-net
