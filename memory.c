#include "shell.h"

/**
 * _memcpy - Copies information between void pointers.
 * @newptr: The destination pointer where data will be copied.
 * @ptr: The source pointer from which data will be copied.
 * @size: The size, in bytes, of the data to be copied.
 *
 * Return: No return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	/*Treat 'ptr' as a char pointer*/
	char *char_ptr = (char *)ptr;

	/*Treat 'newptr' as a char pointer*/
	char *char_newptr = (char *)newptr;
	unsigned int i;

	/*Copy data from 'ptr' to 'newptr' byte by byte*/
	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - Reallocates memory for a memory block.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size, in bytes, of the allocated space of 'ptr'.
 * @new_size: The new size, in bytes, of the new memory block.
 *
 * Return: A pointer to the reallocated memory.
 * If 'new_size' is equal to 'old_size', it returns 'ptr' without changes.
 * If 'new_size' is 0, it frees 'ptr' and returns NULL.
 * If memory allocation (malloc) fails, it returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	/*If 'ptr' is NULL, allocate a new memory block of 'new_size'*/
	if (ptr == NULL)
		return (malloc(new_size));

	/*If 'new_size' is 0, free 'ptr' and return NULL*/
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	/*If 'new_size' is equal to 'old_size', return 'ptr' without changes*/
	if (new_size == old_size)
		return (ptr);

	/*Allocate a new memory block of 'new_size'*/
	newptr = malloc(new_size);

	/*If memory allocation with 'malloc' fails, return NULL*/
	if (newptr == NULL)
		return (NULL);

	/*Copy the content from the old 'ptr' to 'newptr'*/
	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	/* Free the old 'ptr'*/
	free(ptr);

	/*Return 'newptr' with reallocated memory*/
	return (newptr);
}


/**
 * _reallocdp - Reallocates memory for a double pointer.
 * @ptr: A double pointer to the memory previously allocated.
 * @old_size: The size, in bytes, of the allocated space of 'ptr'.
 * @new_size: The new size, in bytes, of the new memory block.
 *
 * Return: A pointer to the reallocated memory.
 * If 'new_size' is equal to 'old_size', it returns 'ptr' without changes.
 * If memory allocation (malloc) fails, it returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;


	/*If 'ptr' is NULL, allocate a new memory*/
	/*block for a double pointer of 'new_size'*/
	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	/*If 'new_size' is equal to 'old_size', return 'ptr' without changes*/
	if (new_size == old_size)
		return (ptr);

	/*Allocate a new memory block for a double pointer of 'new_size'*/
	newptr = malloc(sizeof(char *) * new_size);

	/*If memory allocation fails, return NULL*/
	if (newptr == NULL)
		return (NULL);

	/*Copy the content from the old 'ptr' to the new 'newptr'*/
	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	/*Free the old 'ptr'*/
	free(ptr);

	/*Return the 'newptr' with reallocated memory*/
	return (newptr);
}
