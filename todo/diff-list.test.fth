import diff diff-append "diff-list.fth"
import nil cons "list.fth"
import sole "trivial.fth"

define sole-diff-list
  wire-pair ( front front-op )
  front diff ( back value )
  back sole cons sole cons
  front-op connect
  value
end

sole-diff-list
sole-diff-list
diff-append

wire-print-net
run
wire-print-net
