#include "../includes/malloc.h"

void merge_block(t_block *block)
{
	t_block *next;
	t_block *prev;

	next = block->next;
	prev = block->prev;
	if (next != NULL && next->free == 1)
	{
		block->size += next->size;
		block->next = next->next;
		if (next->next != NULL)
			next->next->prev = block;
	}
	if (prev != NULL && prev->free == 1)
	{
		prev->size += block->size;
		prev->next = block->next;
		if (block->next != NULL)
			block->next->prev = prev;
	}
}

void free_memory(void *ptr)
{
	t_block *block;
	size_t size;

	block = ptr - sizeof(t_block); // ptr is the address of the memory the memory has been given just after the block structure so we need to shift the pointer to the left to get the adress of the block
	if (block == NULL || block->free == 1)
		return ;
	block->free = 1;
	size = block->size;
	if (block->next == NULL && block->prev == NULL)
	{
		munmap(block, size);
		munmap(g_heap_list, sizeof(t_heap));
		g_heap_list = NULL;
		return ;
	}
	merge_block(block);
}

void free(void *ptr)
{
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_mutex);
	free_memory(ptr);
	pthread_mutex_unlock(&g_mutex);
}
