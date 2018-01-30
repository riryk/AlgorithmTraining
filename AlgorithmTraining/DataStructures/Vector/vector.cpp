#include "stdafx.h"
#include "vector.h"
#include <cstdlib>
#include <cstring>

void expandVector(vector *v);

void VectorNew(vector *v, int elementSize, VectorFreeFunction freeFunc, int initialAllocation)
{
	v->elementSize = elementSize;
	v->totalLength = initialAllocation;
	v->length = 0; 
	v->freeFunc = freeFunc;
	v->elements = malloc(initialAllocation * elementSize);
}

void VectorDispose(vector *v)
{
	if (v->freeFunc != NULL)
	{
		for (int i = 0; i < v->length; i++)
		{
			v->freeFunc((char*)(v->elements) + i * v->elementSize);
		}
	}
	free(v->elements);
}

int VectorLength(const vector *v)
{ 
	return v->length; 
}

void *VectorNth(const vector *v, int position)
{
	return ((char*)(v->elements) + position * v->elementSize);
}

void VectorReplace(vector *v, const void *elementAddress, int position)
{
	char* existingElement = ((char*)(v->elements) + position * v->elementSize);
	if (v->freeFunc != NULL)
		v->freeFunc(existingElement);
	memcpy(existingElement, elementAddress, v->elementSize);
}

void VectorInsert(vector *v, const void *elementAddress, int position)
{
	if (v->length == v->totalLength)
		expandVector(v);	

	char* elementPosition = (char*)v->elements + position * v->elementSize;
	int bufferSize = v->length - position;
	char* buffer = (char*)malloc(bufferSize * v->elementSize);

	memcpy(buffer, elementPosition, bufferSize * v->elementSize);
	memcpy(elementPosition, elementAddress, v->elementSize);
	memcpy(elementPosition + v->elementSize, buffer, bufferSize * v->elementSize);

	v->length++;
	free(buffer);
}

void expandVector(vector *v)
{
	if (v->totalLength == 0)
		v->totalLength = 1;

	v->totalLength = v->totalLength * 2;
	v->elements = realloc(v->elements, v->totalLength * v->elementSize);
}