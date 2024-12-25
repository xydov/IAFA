Inductive exp :=
| Const (c: nat)
| Call (op: nat->nat->nat) (e1 e2: exp)
| Test (op: nat->nat->bool) (e1 e2: exp)
| Ite (c e1 e2: exp)
| Error
| Try (e1 e2: exp).

