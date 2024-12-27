define-node diff front -> back value! end
define-node diff-append target! rest -> result end
define-node diff-open new-back target! -> old-back end

(- plug the front of the `target` to the back of `rest` -)

define-rule diff diff-append
  (diff)-front diff result-(diff-append)
  (diff-append)-rest diff-open back-(diff)
end

define-rule diff diff-open
  (diff)-back new-back-(diff-open)
  (diff)-front old-back-(diff-open)
end

(- list.inet -)

define-node null -> value! end
define-node cons tail head -> value! end
define-node append target! rest -> result end

define-rule null append
  (append)-rest result-(append)
end

define-rule cons append
  (cons)-tail (append)-rest append
  (cons)-head cons result-(append)
end

(- test -)

define-node sole -> value! end

define sole-diff-list
  wire-pair
  (- wire wire -) diff
  (- wire back value -) swap
  (- wire value back -) sole cons sole cons
  (- wire value list -) rot
  (- value list wire -) connect
  (- value -)
end

begin sole-diff-list sole-diff-list diff-append

  wire-print-net
  run
  wire-print-net
end
