#include "stdafx.h"
#include "hashtable.h"
#include <cstring>
#include <cstdlib>
#include <math.h>
#include "hashtable_test.h"

static const int ItemCount = 40;

typedef unsigned int uint32;
typedef unsigned short uint16;

struct key
{
    uint32 one_ip; 
	uint32 two_ip; 
};

struct value
{
    char *id;
};

static unsigned int hashfromkey(void *ky)
{
	long long key_value = *(long long*)ky;
    struct key *k = (struct key *)ky;

    unsigned int hash_first_part = ((k->one_ip << 17) | (k->one_ip >> 15)) ^ k->two_ip;
	unsigned int hash_second_part = (k->one_ip * 17) + (k->two_ip * 13 * 29);

    return hash_first_part + hash_second_part;
}

static int equalkeys(void *k1, void *k2)
{
	long long key_value1 = *(long long*)k1;
    long long key_value2 = *(long long*)k2;

    struct key *key1 = (struct key *)k1;
    struct key *key2 = (struct key *)k2;

    return 0 == memcmp(k1, k2, sizeof(struct key));
}

static struct hashtable *hashtable_create()
{
	struct hashtable *h;

    h = create_hashtable(4, hashfromkey, equalkeys);

	return h;
}

static void hashtable_insert_test(struct hashtable *h, long long* keys[])
{
	int i;

    for (i = 0; i < ItemCount; i++)
    {
	    hashtable_insert(h, keys[i], "value");
	}
}

static void hashtable_remove_test(struct hashtable *h, void *key)
{
    hashtable_remove(h, key);
}

void hashtable_test()
{
    struct hashtable *table = hashtable_create();
	long long* keys[ItemCount];
    int i;
    for (i = 0; i < ItemCount; i++)
    {
		keys[i] = (long long*)malloc(sizeof(long long));
        *keys[i] = (long long)(1000 + i);
	}

	long long keys_to_remove[] = { 1008, 1034, 1037, 1039, 1000, 1001, 1002 };

    hashtable_insert_test(table, keys);
	hashtable_remove_test(table, &keys_to_remove[0]);
	hashtable_remove_test(table, &keys_to_remove[1]);
	hashtable_remove_test(table, &keys_to_remove[2]);
	hashtable_remove_test(table, &keys_to_remove[3]);
	hashtable_remove_test(table, &keys_to_remove[4]);
	hashtable_remove_test(table, &keys_to_remove[5]);
    hashtable_remove_test(table, &keys_to_remove[6]);

	free(keys);
}