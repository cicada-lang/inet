define-node γ car cdr -> value! end
define-node δ target! -> first second end
define-node ε target! -> end

define-rule γ γ
  ( top-car top-cdr )
  ( lower-car lower-cdr )
  top-car lower-cdr connect
  top-cdr lower-car connect
end

define-rule δ δ
  ( top-first top-second )
  ( lower-first lower-second )
  top-first lower-first connect
  top-second lower-second connect
end

define-rule ε ε end

define-rule ε γ
  ( car cdr )
  car ε cdr ε
end

define-rule ε δ
  ( first second )
  first ε second ε
end

define-rule γ δ
  ( first second )
  ( car cdr )
  car δ ( car-first car-second )
  cdr δ ( cdr-first cdr-second )
  car-first cdr-first γ first connect
  car-second cdr-second γ second connect
end

define forever
  wire-pair ( x0 x1 )
  wire-pair ε x0 γ
  δ ( first second )
  x1 first connect
  second dup ε
end

forever debug
