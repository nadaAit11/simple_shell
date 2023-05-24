#include "shell.h"

/**
 * _Memcpy - Copies information between void pointers
 * @newptr: destination pointer
 * @ptr: source pointer
 * @size: size of the new pointer
 * Return: no return
 */
void _Memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}
/**
 * _Realloc - Reallocates a memory block with a diffrent size.
 * @ptr: Pointer to the memory block  previously allocated.
 * @old_size: The size, in bytes, of the allocated space of the memory block
 * pointed to by @ptr.
 *
 * @new_size: The new size, in bytes, of the reallocated memory block.
 * Return: ptr
 * if @new_size is equal to the original size (@old_size), the function return
 * the pointer (@ptr) without making any changes.
 * if malloc fails, returns NULL
 */
void *_Realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_Memcpy(newptr, ptr, new_size);
	else
		_Memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}

/**
 * _Reallocdp - reallocates a memory block  pointed to by a double pointer.
 * @ptr: Double pointer to the memory block previously allocated.
 * @old_size: The size, in bytes, of the allocated space for the memory block
 * pointed to by @ptr.
 *
 * @new_size: The new size, in bytes, of the reallocated memory block.
 * Return: ptr
 * if @new_size is equal to the original size (@old_size), the function
 * returns the pointer (@ptr) without making any changes.
 * if malloc fails, returns NULL
 */
char **_Reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];
	free(ptr);
	return (newptr);
}
