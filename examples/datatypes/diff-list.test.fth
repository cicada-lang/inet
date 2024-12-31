define-node diff front -> back value! end
define-node diff-append target! rest -> result end
define-node diff-open new-back target! -> old-back end

-- plug the front of the `target` to the back of `rest`.

define-rule diff diff-append
  ( rest result ) ( front back )
  front diff result connect
  rest diff-open back connect
end

define-rule diff diff-open
  ( new-back old-back ) ( front back )
  back new-back connect
  front old-back connect
end

-- import nil cons append "list.fth"

define-node nil -> value! end
define-node cons tail head -> value! end
define-node append target! rest -> result end

define-rule nil append
  ( rest result )
  rest result connect
end

define-rule cons append
  ( rest result ) ( tail head )
  tail rest append
  head cons result connect
end

-- test

define-node sole -> value! end

define sole-diff-list
  wire-pair -- wire wire
  diff -- wire back value
  swap -- wire value back
  sole cons sole cons -- wire value list
  rot -- value list wire
  connect -- value
end

sole-diff-list sole-diff-list diff-append

wire-print-net
run
wire-print-net
