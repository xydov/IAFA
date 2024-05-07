><
# Méthodes Numériques

## 1. Chapitre 1 
## Recherche de racines d'une fonctions
**Objectif:** 

Soit $f$ continue sur $[a; b]$

On cherche : $R \in [a; b], f(R)=0$

* théoreme de valeurs intermédiaires:

soit $f$ continue sur $[A; B]$ si $\begin{Bmatrix}
    f(a)<0 \\
    f(b)>0
\end{Bmatrix}$ il existe $R\in ]a; b[$

Si $\begin{Bmatrix}
    f(a)>0 \\
    f(b)<0 
\end{Bmatrix}$ il existe $R \in [a; b] / f(R)$
* Unicité d'une racine:

Si $x\in \Reals$, et $f$ est strictement monotone alors la racine $R$ est unique

> * Si $f'\geqslant 0$ sur un intervalle alors croissant 
> * Si $f'\leqslant 0$ sur un intervalle alors décroissante

## 1.1. Localisation de la racine par Dichotomie

on suppose que $f$ possede une unique racine dans $[a; b]$ et que $f(a)f(b)<0$

1. On pose alors $m=\dfrac{a+b}{2}$ et on calc $f(m)$
2. si $f(m)=0$ alors $R$ a été trouvé
3. Si $f(m)=\not0$, on évalue $f(a)f(m)$
   * si $f(a)f(m)<0$ alors d'aprés le TVI, racine se trouve dans $[a;m]$ et on reprend avec $[a; b]=[a;m]$.
   * sinon (on a $f(m)f(b)<0$), alors toujours d'aprés le TVI la racine se trouve dans $]m;b[$ et on reprend avec $[a; b]=[m;b]$.

### Théoreme 2:
Soit $f$ une fonction continue de $[a,b]$ dans $R$. On suppose que $f(a)f(b)<0$ et l'équation $f(x)=0$ admet une unique solution $R$ sur $[a,b]$ . Si l'algo de dichoto parvient j'usqu'a l'étape n alors on a l'estimation : 
$$|r-c_n|\leqslant\frac{b-a}{2^{n+1}}$$

* Remarque
le critère d'arret peut-etre du type $\dfrac{b_n-a_n}{2}<\Large\varepsilon$

### Strictement:
> * Si $f'_1(x)>0$ alors $f_1$ strictement croissante sur $\R$, on peut en déduire unicité de la racine.
> * Si $f'_1(x)<0$ alors $f_1$ strictement décroissante sur $\R$, ... unicité de la racine.
> * Si $f_1$ est un poly, alors $f_1$ continue sur $\R$

## 1.2. Méthode de Newton
### Tangente en $x_0$
$$T_0(x)=f(x_0)+f'(x_0)(x-x_0)$$
L'équation $T_0(x)=0$ admet alors pour racine
$$x_1=x_0-\frac{f(x_0)}{f'(x_0)}$$
on espere que $x_1\approx r$

Itération n°2:
$$T_1(x)=f(x_1)+f'(x_1)(x-x_1)$$
### Suite de Newton
$$X_{n+1}=X_n-\frac{f(X_n)}{f'(X_n)}$$
* IL FAUT QUE LES $X_n \in [a;b]$
* $\forall n \in \N ,f'(X_n) =\not 0$.
* Le choix du point dedépart est important pour que chaque itérée $x_n$ soit dans $[a;b]$.

Une suite converge quadraiquement vers $r$ si on a
$$\lim\limits_{x\rArr}$$

## 2. Chapitre 2
## Interpolation polynomiale

on cherche a reconstruire une fonction $f$ par des polynomes

$p \in P^1 \implies (m+1)$ coéfficients à trouver
## 2.1 Forme de Lagrange
on definit $(n+1)$ polynomes

$$\forall j= 0,1,...,n$$
$$l_j,n(x) = \displaystyle\prod_{k=0;k=\not{j}}^n\frac{x-a_k}{a_j-a_k}$$
$$P_f(x) = \displaystyle\sum_{k=0}^nf_kl_k,n(x)$$
* n est le degré de $l_j,n(x)$
* $l_j,n(x)$ sont les polynomes de lagrange.

**vocab:**
* $a_0,a_1,a_n$ sont les points d'interpolations
* $f_0,f_1,f_n$ sont les valeurs interpolées
* $f$ est la fonction interpolées
* $P_f$ est le poly d'interpolation de $f$

### Majoration/calcul d'erreur
$$||E||_{\infin}\leqslant\frac{||f^{n+1}||}{(n+1)!}||\Pi_a||_\infin[a;b]$$