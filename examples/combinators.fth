define-node γ first second -> value! end
define-node δ target! -> first second end
define-node ε target! -> end

define-rule γ γ
  ( top-first top-second )
  ( lower-first lower-second )
  top-first lower-second connect
  top-second lower-first connect
end

define-rule δ δ
  ( top-first top-second )
  ( lower-first lower-second )
  top-first lower-first connect
  top-second lower-second connect
end

define-rule ε ε end
