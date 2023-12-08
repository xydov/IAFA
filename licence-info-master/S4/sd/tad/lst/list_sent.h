#ifndef LIST_H
#define LIST_H
#define FORWARD_ITERATOR 1
#define BACKWARD_ITERATOR 0

typedef struct s_list_iterator *ListIterator;
typedef struct s_list *List;


typedef int (*FuncCreator)(int);
List map(List l, FuncCreator f);

typedef void (*ReducFunctor)(int, void*);
List reduce(List l, ReducFunctor f, void* userData);

int isEmpty(List l);

List create_list(void);

List push_front(List l, int e);

List push_back(List l, int e);

List insert_at(List l, int i, int e);

List pop_front(List l);

List pop_back(List l);

List remove_at(List l, int i);

int front(List l);

int back(List l);

int ith(List l, int i);

// Fonctions Iterator
ListIterator list_iterator_create(List collection, int direction);
/* Implantation choice : pointer on an iterator */
void _iterator_delete(ListIterator *i);
ListIterator list_begin(ListIterator i);
int list_end(ListIterator i);
ListIterator list_next(ListIterator i);
int list_value(ListIterator i);



#endif