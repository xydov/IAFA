#include <stdlib.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"

typedef struct s_node
{
	int key;
	unsigned int level;
	struct s_node **next;
    struct s_node **previous;

} node;


struct s_SkipList 
{
	node *sentinel;
	// next = head
	// previous = tail, NIL
	unsigned int nb_level;
};



SkipList skiplist_create(int nblevels) {
	

	SkipList sl = malloc(sizeof(SkipList));
	node *sentinel = malloc(sizeof(struct s_node) * nblevels);
	sl->nb_level = nblevels;
	sl->sentinel = sentinel;

	sentinel->level = nblevels;

	sentinel->next = malloc(sizeof(struct s_node) * nblevels);
	sentinel->previous = malloc(sizeof(struct s_node));
	sentinel->previous[0] = sentinel;

	for (int i = 0; i < nblevels; i++)
	{
		sentinel->next[i] = sentinel;
		// sentinel->previous[i] = sentinel;
		// or previous[0]
	}
	
	sl->sentinel->key = 0;

	return sl;
}

void skiplist_delete(SkipList d) {
	(void)d;
}


unsigned int skiplist_size(SkipList d)
{
	return d->sentinel->key;
}


// need search method
SkipList skiplist_insert(SkipList d, int value) 
{
	node *search = d->sentinel;
	node *new = malloc(sizeof(struct s_node));
	
	// on avance dans la liste, en cherchant le 1er élement plus grand que value
	int i = 0;
	while (search->key < value && i < d->sentinel->key)
	{
		search = search->next[0];
		i++;
	}

	// how do i get the rng struct into this func? global variable(noooo)?
	RNG rng;

	new->key = value;
	new->level = rng_get_value(&rng, d->nb_level);
	
	
	// added 1 element
	++d->sentinel->key;
	return d;
}
