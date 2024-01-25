#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;
	t_block *block;
	size_t old_size;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	block = ptr - sizeof(t_block);
	old_size = block->size;
	if (size <= old_size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
