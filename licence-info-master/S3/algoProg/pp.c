
int a

int sournois(int **x) {
    **x = **x + 1
    return a
}

int main() {
    int *pa;
    int **ppa;
    a = 5
    pa = &a
    ppa = &pa
    if(sournois(&pa) == sournois(ppa)) 
        printf(oui, a)
    else
    printf(non, a)
}