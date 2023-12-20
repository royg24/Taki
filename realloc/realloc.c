#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* arr_realloc(int* arr, int size, int new_size);

void main()
{
	int i;
	int* arr = (int*) malloc(6 * sizeof(int));
	if (arr == NULL)
	{
		printf("Error!\n");
		return;
	}
	for (i = 0; i < 6; i++)
	{
		*(arr + i) = 8;
	}
	int* temp_arr = (int*)arr_realloc(arr, 6, 5);
	if (temp_arr == NULL)
	{
		printf("Error!\n");
		return;
	}
	arr = temp_arr;
	for (i = 0; i < 5; i++)
	{
		*(arr + i) = i;
		printf("%d ", *(arr + i));
	}
	free(arr);
}

/*int* arr_realloc(int* arr, int size, int new_size)
{
	int i;
	int* new_arr = (int*) malloc(new_size * sizeof(int));
	if (new_arr == NULL)
	{
		return NULL;
	}
	if (new_size > size)
	{
		for (i = 0; i < size; i++)
		{
			*(new_arr + i) = *(arr + i);
		}
	}
	else
	{
		for (i = 0; i < new_size; i++)
		{
			*(new_arr + i) = *(arr + i);
		}
	}
	free(arr);
	return new_arr;
}*/

int* arr_realloc(int* arr, int size, int new_size)
{
	/*
	This function gets an array of integers, its size and a new one and
	changes the size to the new one
	*/
	int i;
	int* new_arr = (int*)malloc(new_size * sizeof(int));
	if (new_arr == NULL)
	{
		return NULL;
	}
	else
	{
		for (i = 0; i < size && i < new_size; i++)
		{
			*(new_arr + i) = *(arr + i);
		}
		free(arr);
	}
	return new_arr;
}