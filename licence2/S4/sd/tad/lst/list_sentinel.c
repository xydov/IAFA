#include "list_sent.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct s_item {
    int value;
    struct s_item *next;    
    struct s_item *previous;

} *Item;

typedef Item (*SuccessorCreator)(Item);

struct s_list{
    Item sentinel;
    unsigned int size;
};

struct s_list_iterator{
    Item indexed;
    Item sentinel;
    SuccessorCreator S;
};


List map(List l, FuncCreator f){
    for(Item i = l->sentinel->next; i!=l->sentinel; i=i->next){
        i->value=f(i->value);
    }
    return l;
}

List reduce(List l, ReducFunctor f, void* userData){
    for(Item i=l->sentinel->next; i!=l->sentinel; i=i->next){
        f(i->value, userData);
    }
    return l;
}

void afficherListe(List l){
    printf("Affichage de la liste de taille %d \n", l->size);
    Item iter = l->sentinel->next;
    printf("%d ", iter->value);

    for(int i=1;i<l->size;i++){
        iter=iter->next;
        printf(", %d ", iter->value);
    }

    printf(" | \n");
}

int isEmpty(List l){
    return l->size==0;
}

List create_list(void){
    List l = malloc(sizeof(struct s_list));
    l->sentinel=malloc(sizeof(struct s_item));
    l->sentinel->next=l->sentinel;
    l->sentinel->previous=l->sentinel;
    l->size=0;

    return l;
}

List push_front(List l, int e){
    Item i = malloc(sizeof(struct s_item));
    Item sent = l->sentinel;
    
    i->value=e;
    i->next=sent->next;
    i->previous=sent;
    sent->next->previous=i;
    sent->next=i;
    l->size++;

    return l;
}

List push_back(List l, int e){
    Item i = malloc(sizeof(struct s_item));
    Item sent = l->sentinel;

    i->value=e;
    i->next=sent;
    i->previous=sent->previous;
    sent->previous->next=i;
    sent->previous=i;
    l->size++;

    return l; 
}



List insert_at(List l, int i, int e){
    assert(i>=0 && i<=l->size);
    Item new = malloc(sizeof(struct s_item));
    new->value=e;
    Item recherche = l->sentinel;
    
    // on passe recherche à l'elem actuel i-1
    for(int j=0;j<i;j++){
        recherche=recherche->next;
    } 

    new->previous=recherche; // le prédecesseur du nouvel élement est l'elem actuel à i-1
    new->next=recherche->next; // le sucesseur du nouvel est l'elem actuel à i

    recherche->next=new;// le sucesseur de l'elem actuel à i-1 est le nouvel élement
    recherche=new->next;// on passe recherche à l'elem actuel i
    recherche->previous=new;// le predecesseur de l'elem actuel à i est le nouvel element


    l->size++;

    return l;
}

List remove_at(List l, int i){
    assert(i>=0 && i<l->size);
    
    Item element = l->sentinel->next;
    // on passe recherche à l'elem actuel i
    for(int j=0;j<i;j++){
        element=element->next;
    }

    Item previous = element->previous;
    Item next = element->next;

    previous->next=next; // le sucesseur du predecesseur de i devient le sucesseur de i
    next->previous=previous; // et inversement
    

    free(element);
    l->size--;

    return l;
} 

List pop_front(List l){
    assert(!isEmpty(l));
    Item sent = l->sentinel;
    Item oldFront = sent->next;
    sent->next=oldFront->next;
    sent->next->previous=sent;
    free(oldFront);
    l->size--;

    return l; 
}

List pop_back(List l){
    assert(!isEmpty(l));
    Item sent = l->sentinel;
    Item oldBack = sent->previous;
    sent->previous=oldBack->previous;
    sent->previous->next=sent;

    free(oldBack);
    l->size--;

    return l; 
}

int front(List l){
    assert(l->size>0);
    return l->sentinel->next->value;
}

int back(List l){
    assert(l->size>0);
    return l->sentinel->previous->value;
}

int ith(List l, int i){
    assert(i>=0 && i<l->size);
    Item recherche = l->sentinel->next;
    for(int j=0;j<i;j++){
        recherche = recherche->next;
    }

    return recherche->value;
}

/* fction utilisateur */

int printer(int a){
    printf("%d ", a);
    return a;
}

void paritySplitter(int e, void* userData){
    List *lists = (List*)userData;
    if(e%2==0){
        lists[0]=push_back(lists[0],e);
    }
    else{
        lists[1]=push_back(lists[1],e);        
    }
}

// Fonction iterator

Item successor(Item i){
    return i->next;
}

Item predecessor(Item i){
    return i->previous;
}

ListIterator list_iterator_create(List l, int d){
    ListIterator iter = malloc(sizeof(struct s_list_iterator));
    iter->sentinel = l->sentinel;
    if(d){
        iter->indexed = l->sentinel->previous;
        iter->S = predecessor;
    }
    else{
        iter->indexed=l->sentinel->next;
        iter->S = successor;
    }

    return iter;
}

ListIterator list_begin(ListIterator i){
    i->indexed=(i->S)(i->sentinel);
    return i;
}

int list_end(ListIterator i){
    return (i->indexed)==(i->sentinel);
}

ListIterator list_next(ListIterator i){
    i->indexed=(i->S)(i->indexed);
    return i;
}

int list_value(ListIterator i){
    return i->indexed->value;
}

void _iterator_delete(ListIterator *i){
    free(*i);
    *i=NULL;
    free(i);
}

int main(int argc, char* argv[]){
    List l = create_list();
    l = push_front(l, 3);
    l = push_front(l, 9);
    l = push_front(l, 7);
    l = push_front(l, 1000);
    l = push_front(l, 15);
    l = push_front(l, 25);
    l = push_front(l, 5);
    l = push_front(l, 7);
    l = push_front(l, 2);
    l = push_front(l, 26);

    List *L = malloc(2*sizeof(struct s_list));
    L[0]=create_list();
    L[1]=create_list();
    reduce(l, paritySplitter, L);

    afficherListe(l);
    afficherListe(L[0]);
    afficherListe(L[1]);

    ListIterator ItOnList = list_iterator_create(l, 1);

    for(ItOnList=list_begin(ItOnList);!list_end(ItOnList);ItOnList=list_next(ItOnList)){
        printf("%d ", list_value(ItOnList));

    }

}