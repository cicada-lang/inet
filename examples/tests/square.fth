define square
  dup mul
end

1 square 1 eq ok
2 square 4 eq ok
3 square 9 eq ok

define two 2 end

two square 4 eq ok
