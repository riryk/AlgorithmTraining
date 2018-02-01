#include "stdafx.h"
#include "hashtable.h"
#include <cstring>
#include <cstdlib>
#include <math.h>

static const unsigned int primes[] = {
  53, 97, 193, 389, 
  769, 1543, 3079, 6151, 
  12289, 24593, 49157, 98317,
  196613, 393241, 786433, 1572869,
  3145739, 6291469, 12582917, 25165843,
  50331653, 100663319, 201326611, 402653189,
  805306457, 1610612741
};

const unsigned int prime_table_length = sizeof(primes) / sizeof(primes[0]);
const float max_load_factor = 0.65;

struct hashtable* create_hashtable(
	unsigned int minsize,
    unsigned int (*hashfn) (void*),
    int (*equalfn) (void*,void*))
{
    struct hashtable *h;
    unsigned int pindex, size = primes[0];
    
    if (minsize > (1u << 30)) 
		return NULL;

    for (pindex = 0; pindex < prime_table_length; pindex++) {
        if (primes[pindex] > minsize) { 
			size = primes[pindex]; 
			break; 
		}
    }

    h = (struct hashtable *)malloc(sizeof(struct hashtable));
    if (h == NULL) 
		return NULL;

    h->table = (struct hashtable_entry **)malloc(sizeof(struct hashtable_entry*) * size);
	if (h->table == NULL) { 
		free(h); 
		return NULL; 
	}

    memset(h->table, 0, size * sizeof(struct hashtable_entry *));
    h->tablelength = size;
    h->primeindex = pindex;
    h->entrycount = 0;
    h->hashfn = hashfn;
    h->equalfn = equalfn;
    h->loadlimit = (unsigned int)ceil(size * max_load_factor);
    return h;
}

unsigned int hash(struct hashtable *h, void *key)
{
    unsigned int i = h->hashfn(key);
    i += ~(i << 9);
    i ^= ((i >> 14) | (i << 18));
    i += (i << 4);
    i ^= ((i >> 10) | (i << 22));
    return i;
}

int hashtable_insert(struct hashtable *h, void *key, void *value)
{
    unsigned int index;
    struct hashtable_entry *entry;

	if (++(h->entrycount) > h->loadlimit) {
        hashtable_expand(h);
	}   

	return 0;
}

static int hashtable_expand(struct hashtable *h)
{
    struct hashtable_entry **newtable;
    struct hashtable_entry *entry;
	struct hashtable_entry *nextentry;
    unsigned int newsize, i, index;
    
    if (h->primeindex == (prime_table_length - 1)) 
		return 0;

    newsize = primes[++(h->primeindex)];
	newtable = (struct hashtable_entry **)malloc(sizeof(struct hashtable_entry*) * newsize);
    if (newtable != NULL)
    {
        memset(newtable, 0, newsize * sizeof(struct hashtable_entry *));   
		for (i = 0; i < h->tablelength; i++) {
            while ((entry = h->table[i]) != NULL) {
                h->table[i] = entry->next;
				index = entry->hash % newsize;
                entry->next = newtable[index];
                newtable[index] = entry;
			}
		}
		free(h->table);
        h->table = newtable;
	}
	else 
	{
	    newtable = (struct hashtable_entry **)realloc(h->table, newsize * sizeof(struct hashtable_entry *));
        if (newtable == NULL) { 
			(h->primeindex)--; 
			return 0; 
		}
		h->table = newtable;
        memset(newtable[h->tablelength], 0, newsize - h->tablelength);
        for (i = 0; i < h->tablelength; i++) {
            entry = newtable[i];
			while (entry != NULL) {
				index = entry->hash % newsize;
				nextentry = entry->next;
				if (index != i) {
                    entry->next = newtable[index];
                    newtable[index] = entry;
				}
				entry = nextentry;
			}
		}
	}
	h->tablelength = newsize;
    h->loadlimit = (unsigned int) ceil(newsize * max_load_factor);
    return -1;
}


