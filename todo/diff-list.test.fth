import diff diff-append "diff-list.fth"
import nil cons "list.fth"
import sole "trivial.fth"

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
