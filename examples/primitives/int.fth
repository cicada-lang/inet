1 1 eq ok
1 2 eq not ok
1 -1 eq not ok
-1 -1 eq ok

1 1 add 2 eq ok
2 2 add 4 eq ok
1 -1 add 0 eq ok

1 1 mul 1 eq ok
2 2 mul 4 eq ok
2 -1 mul -2 eq ok

1 1 div 1 eq ok
5 2 div 2 eq ok
5 2 mod 1 eq ok

1 int-to-float 1.0 eq ok
