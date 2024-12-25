Require ast.
Require wrtonce.
Require useless.

Definition transfo (p: ast.prog): ast.prog :=
  useless.clean_p (wrtonce.elim_w2 p).
