#include "stdafx.h"
#include "hashtable.h"
#include <cstring>
#include <cstdlib>
#include <math.h>
#include "hashtable_test.h"

static const int ItemCount = 4000;

typedef unsigned int uint32;
typedef unsigned short uint16;

struct key
{
    uint32 one_ip; 
	uint32 two_ip; 
	uint16 one_port; 
	uint16 two_port;
};

struct value
{
    char *id;
};

static unsigned int hashfromkey(void *ky)
{
    struct key *k = (struct key *)ky;
    return (((k->one_ip << 17) | (k->one_ip >> 15)) ^ k->two_ip) +
            (k->one_port * 17) + (k->two_port * 13 * 29);
}

static int equalkeys(void *k1, void *k2)
{
    return 0 == memcmp(k1, k2, sizeof(struct key));
}

static struct hashtable *hashtable_create()
{
	struct hashtable *h;

    h = create_hashtable(16, hashfromkey, equalkeys);

	return h;
}

static void hashtable_insert_test(struct hashtable *h)
{
	int i;
	int* keys = (int*)malloc(sizeof(int)*ItemCount);
    for (i = 0; i < ItemCount; i++)
    {
        keys[i] = 1000 + i;
	}

    for (i = 0; i < ItemCount; i++)
    {
	    hashtable_insert(h, keys + i, "value");
	}
}

void hashtable_test()
{
    struct hashtable *table = hashtable_create();

    hashtable_insert_test(table);
}