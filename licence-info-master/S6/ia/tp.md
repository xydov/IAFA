# TP IA

## TP 1
```ocaml
largeur [initG1] estButG1 etatsSuivantsG1;;
```

* Pour le bon fonctionnement (et un algorithme correct), implémenter une liste de noeud déjà visité pour le parcours en profondeur

```ocaml
creerLesFils initG1C 0 opPossG1C hEtatG1C;;
creerLesFils "B" 4 opPossG1C hEtatG1C;;
```

[(0, 0, 1); (0, 4, 5); (0, 3, 3); (0, 2, 3); (0, 0, 0)]

insertion (0, 1, 4) [(0, 0, 1); (0, 4, 5); (0, 3, 3); (0, 2, 3); (0, 0, 0)]