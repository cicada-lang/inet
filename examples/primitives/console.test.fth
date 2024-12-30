null print drop newline
true print drop newline
false print drop newline

1 2 add print drop newline
-1 -2 add print drop newline

0.0 0.0 fadd print drop newline
0.1 0.2 fadd print drop newline
1.0 2.0 fadd print drop newline
1.1 2.2 fadd print drop newline

1. print drop newline
2. print drop newline

1 2 3 print-value-stack

define hi
  1 2 3
  print-return-stack
  4 5 6
end

hi
