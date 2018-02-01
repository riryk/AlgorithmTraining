#ifndef Vector_h
#define Vector_h 1

typedef int (*VectorCompareFunction)(const void *elementAddress1, const void *elementAddress2);

typedef void (*VectorMapFunction)(void *elementAddress, void *auxiliaryData);

typedef void (*VectorFreeFunction)(void *elementAddress);

typedef struct {
	void *elements;
	int elementSize;
	int length;
	int totalLength;
	VectorFreeFunction freeFunc;
} vector;

void VectorNew(vector *v, int elementSize, VectorFreeFunction freeFunc, int initialAllocation);

void VectorDispose(vector *v);

int VectorLength(const vector *v);

void *VectorNth(const vector *v, int position);

void VectorReplace(vector *v, const void *elementAddress, int position);

void VectorInsert(vector *v, const void *elementAddress, int position);

void VectorAppend(vector *v, const void *elementAddress);

int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFunc, int startIndex);

#endif
