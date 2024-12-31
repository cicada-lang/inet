define-rule nzero nadd
  ( addend result )
  addend result connect
end

define-rule nadd1 nadd
  ( addend result ) ( prev )
  prev addend nadd
  nadd1 result connect
end
