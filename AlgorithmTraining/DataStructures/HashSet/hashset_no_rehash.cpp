#include "stdafx.h"
#include <cstdlib>
#include "hashset_no_rehash.h"
#include "../Vector/vector.h"

void hashSetCreateNew(hashset *set, int elementSize, int numberOfBuckets, 
		HashSetHashFunction hashFunc, HashSetCompareFunction compareFunc, HashSetFreeFunction freeFunc)
{
	set->elementSize = elementSize;
	set->numberOfBuckets = numberOfBuckets;
	set->numberOfElements = 0;

	set->buckets = malloc(sizeof(vector*) * numberOfBuckets);
	for (int i = 0; i < numberOfBuckets; i++)
	{
		void* v = (char*)set->buckets + i * sizeof(vector*);
		*(vector**)v = (vector*)malloc(sizeof(vector));
		VectorNew(*(vector**)v, elementSize, freeFunc, 1);
	}

	set->hashFunc = hashFunc;
	set->compareFunc = compareFunc;
	set->freeFunc = freeFunc;
}

void hashSetDispose(hashset *set)
{
	if (set->freeFunc != NULL)
		set->freeFunc(set);

	for (int i = 0; i < set->numberOfBuckets; i++)
	{
		vector* bucket = *(vector**)((char*)set->buckets + i * sizeof(vector*));
		VectorDispose(bucket);
	}

	free(set->buckets);	
}

void hashSetEnter(hashset *set, const void *elementAddress)
{
	int hashCode = set->hashFunc(elementAddress, set->numberOfBuckets);
	void* bucket = (char*)set->buckets + hashCode * sizeof(vector*);

    for (int i = 0; i < VectorLength(*(vector**)bucket); i++)
	{
        int compare = set->compareFunc(elementAddress, VectorNth(*(vector**)bucket, i));
        if (compare == 0)
		{
            VectorReplace(*(vector**)bucket, elementAddress, i);
			return; 
		}
		else if (compare < 0) 
		{
            VectorInsert(*(vector**)bucket, elementAddress, i);
			set->numberOfElements++;
			return;
		}
	}

	VectorAppend(*(vector**)bucket, elementAddress);
	set->numberOfElements++;
}

void *hashSetLookup(const hashset *set, const void *elementAddress)
{
	int hashCode = set->hashFunc(elementAddress, set->numberOfBuckets);

	void* bucket = (char*)set->buckets + hashCode * sizeof(vector*);
	int foundIndex = VectorSearch(*(vector**)bucket, elementAddress, set->compareFunc, 0);
	if (foundIndex == -1) 
		return NULL;

	return VectorNth(*(vector**)bucket, foundIndex);
}
