#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_list *List;

List list_create();
List push_front(List l, int v);
List pop_front(List l);
List push_back(List l, int v);
List pop_back(List l);
List insert_at(List l, int i, int v);
List remove_at(List l, int i);
int list_front(List l);
int list_back(List l);
int list_ith(List l, int i);

bool list_empty(List l);

#endif