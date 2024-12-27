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

begin null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append debug
end
