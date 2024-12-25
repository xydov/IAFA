/** Dynamic implementation of the TAD List
 */

#include "list.h"
#include <assert.h>


typedef struct s_internalElement
{
    int value;
    struct s_internalElement *previous;
    struct s_internalElement *next;
} InternalElement;


typedef struct s_list
{
    InternalElement *head;
    InternalElement *tail;
    unsigned int size;
};

/** Constructor : create a double chained list
 * List_create : -> List
 */
List list_create()
{
    List l = malloc(sizeof(struct s_list));
    l->head = l->tail = NULL;
    l->size = 0;
    return l;
}

/** Operator : push element at the front of the list
 * push_front : List x int -> List
 */
List push_front(List l, int v)
{
    InternalElement **e = (l->size ? &(l->head->previous) : &(l->tail));
    *e = malloc(sizeof(InternalElement));
    (*e)->value = v;
    (*e)->previous = NULL;
    (*e)->next = l->head;
    l->head = *e;
    ++(l->size);
    return l;
}

/** Operator : remove element from the front of the list
 * pop_front : List -> List
 * @pre !list_empty(l)
 */
List pop_front(List l)
{
    assert(l->size > 0);
    InternalElement *e;
    e = l->head;
    l->head = e->next;
    if (l->head)
    {
        l->head->previous = NULL;
    }
    else
    {
        l->tail = l->head;
    }
    --(l->size);
    free(e); 
    return l;
}

/** Operator : insert element at the end of the list
 * push_back : List x int -> List
 */
List push_back(List l, int v)
{
    InternalElement **e = (l->size ? &(l->tail->next) : &(l->head));
    *e = malloc(sizeof(InternalElement));
    (*e)->value = v;
    (*e)->previous = l->tail;
    (*e)->next = NULL;
    l->tail = *e;
    ++(l->size);
    return l;
}

/** Operator : remove element at the end of the List
 * pop_back : List -> List
 * @pre !list_empty(l)
 */
List pop_back(List l)
{
    assert(l->size > 0);
    InternalElement *e;
    e = l->tail;
    l->tail = e->previous;
    if (l->tail)
    {
        l->tail->next = NULL;
    }
    else
    {
        l->head = l->tail;
    }
    --(l->size);
    free(e);
    return l;
}

List insert_at(List l, int i, int v)
{
    assert((l->size > i));
    InternalElement *insert_at = l->head;
    InternalElement *new_element;
    new_element = malloc(sizeof(InternalElement));

    while (i--)
    {
        insert_at = insert_at->next;
    }
    new_element->value = v;
    new_element->next = insert_at;
    new_element->previous = insert_at->previous;
    insert_at->previous->next = new_element;
    insert_at->previous = new_element;
    //new_element->next = insert_at;    
    ++(l->size);
    return l;
}

List remove_at(List l, int i);



/** Operator : acces the first element of the list
 * list_front : List -> int
 * @pre !list_empty(l);
 */
int list_front(List l)
{
    assert(l->size > 0);
    return l->head->value;
}

/** Operator : acces the last element of the list
 * list_back : List -> int
 * @pre !list_empty(l);
 */
int list_back(List l)
{
    assert(l->size > 0);
    return l->tail->value;
}

/** Operator : acces the ith element of the list
 * list_back : List x int -> int
 * @pre !list_empty(l) && i >= 0 && i < l->size;
 */
int list_ith(List l, int i)
{
    assert((l->size > 0) && (0 <= i) && (i < l->size));
    InternalElement *e = l->head;
    while (i--)
    {
        e = e->next;
    }
    return e->value;    
}





/** Operator : is the list empty?
 * list_empty : List -> boolean
 */
bool list_empty(List l)
{
    return l->size == 0;
}