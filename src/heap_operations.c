#include "../includes/malloc.h"

void *create_or_append_heap(size_t size, enum e_heap_type type)
{
	t_heap *heap;
	t_heap *tmp;
	size += sizeof(t_block) + sizeof(t_heap);
	if ((heap = (t_heap *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	heap->total_size = size; // size of heap and block included
	heap->free_size = size - sizeof(t_heap);
	heap->used_size = 0;
	heap->next = NULL;
	heap->type = type;
	block_init(heap, heap->free_size); // sizeof the block will be changed in block_init
	if (g_heap_list != NULL)
	{
		tmp = g_heap_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = heap;
	}
	else
		g_heap_list = heap;
	return ((void *)heap);
}

size_t get_heap_size(size_t size)
{
	size_t heap_size;
	if (size <= (size_t)TINY_BLOCK)
		heap_size = TINY_HEAP;
	else if (size <= (size_t)SMALL_BLOCK)
		heap_size = SMALL_HEAP;
	else
		heap_size = size;
	return (heap_size);
}

enum e_heap_type get_type(size_t size)
{
	if (size <= (size_t)TINY_BLOCK)
		return(TINY);
	if (size <= (size_t)SMALL_BLOCK)
		return(SMALL);
	return(LARGE);
}
