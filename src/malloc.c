#include "../includes/malloc.h"

int check_memory_limit(size_t size)
{
	struct rlimit limit;

	if (getrlimit(RLIMIT_DATA, &limit) == -1)
		return (0);
	if (size > limit.rlim_cur)
		return (0);
	return (1);
}

void *malloc_memory(size_t size)
{
	t_block *free_block;
	size_t heap_size;
	enum e_heap_type type;

	if (size <= 0)
		return (NULL);
	heap_size = get_heap_size(size);
	type = get_type(size);
	if (!check_memory_limit(heap_size))
		return (NULL);
	if (g_heap_list == NULL)
	{
		if (create_or_append_heap(heap_size, type) == NULL)
			return (NULL);
	}
	free_block = find_free_block(type, size);
	if (free_block == NULL)
	{
		create_or_append_heap(heap_size, type);
		free_block = find_free_block(type, size);
	}
	if (free_block == NULL)
		return (NULL);
	return (BLOCK_SHIFT(free_block));
}

void *malloc(size_t size)
{
	pthread_mutex_lock(&g_mutex);
	void *ptr = malloc_memory(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
