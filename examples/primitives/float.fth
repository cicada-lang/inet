0.1 0.1 eq ok
0.1 0.2 eq not ok
0.1 -0.1 eq not ok
-0.1 -0.1 eq ok

0.1 0.1 fadd 0.2 eq ok
0.2 0.2 fadd 0.4 eq ok
0.1 -0.1 fadd 0.0 eq ok

0.1 0.1 fdiv 1.0 eq ok
0.5 0.2 fdiv 2.5 eq ok
5.0 2.0 fdiv 2.5 eq ok

1.0 float-to-int 1 eq ok
