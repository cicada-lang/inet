define my-drop
  ( x )
end

1 2 my-drop 1 eq ok

define my-swap
  ( x y )
  y x
end

1 2 swap
1 eq ok
2 eq ok
