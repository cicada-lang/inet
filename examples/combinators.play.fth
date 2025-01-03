// C: construct
// D: duplicate
// E: erase

define-node C car cdr -- value! end
define-node D target! -- first second end
define-node E target! -- end

define-rule C C
  ( top-car top-cdr )
  ( lower-car lower-cdr )
  top-car lower-cdr connect
  top-cdr lower-car connect
end

define-rule D D
  ( top-first top-second )
  ( lower-first lower-second )
  top-first lower-first connect
  top-second lower-second connect
end

define-rule E E end

define-rule E C
  ( car cdr )
  car E cdr E
end

define-rule E D
  ( first second )
  first E second E
end

define-rule C D
  ( first second )
  ( car cdr )
  car D ( car-first car-second )
  cdr D ( cdr-first cdr-second )
  car-first cdr-first C first connect
  car-second cdr-second C second connect
end

define E-value wire-pair E end

define forever
  wire-pair ( car car-op )
  car E-value C
  D ( first second )
  first E
  car-op second connect
end

forever debug
