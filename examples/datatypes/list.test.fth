* null -> value! end
* cons tail head -> value! end
* append target! rest -> result end

! (null)-(append)
  (append)-rest result-(append)
end

! (cons)-(append)
  (cons)-tail (append)-rest append
  (cons)-head cons result-(append)
end

(- test -)

* sole -> value! end

. null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append

  wire-print-net
  run
  wire-print-net
end
