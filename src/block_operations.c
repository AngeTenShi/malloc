#include "../includes/malloc.h"

void block_init(t_heap *heap, size_t size)
{
	void *address = heap + sizeof(t_heap);
	t_block *block = (t_block *)address;
	if (heap->type == LARGE)
		size -= sizeof(t_block);
	block->size = size;
	block->free = 1;
	block->next = NULL;
	block->prev = NULL;
	heap->block = block;
	heap->free_size -= sizeof(t_block);
	heap->used_size += sizeof(t_block);
	heap->nb_block = 1;
}

void split_block(t_block *block, size_t size, t_heap *heap)
{
	if (block->size == size)
		return ;
	if (block->size - size - sizeof(t_block) < sizeof(t_block))
		return ;
	t_block	*new_block = BLOCK_SHIFT(block) + size;
	new_block->size = block->size - size - sizeof(t_block);
	new_block->free = 1;
	new_block->next = block->next;
	new_block->prev = block;
	block->next = new_block;
	block->size = size;
	heap->free_size -= sizeof(t_block);
	heap->used_size += sizeof(t_block);
	heap->nb_block += 1;
}

t_block *find_free_block(enum e_heap_type type, size_t size)
{
	t_heap *heap;
	t_block *block;

	if (g_heap_list == NULL)
		return (NULL);
	heap = g_heap_list;
	while (heap != NULL)
	{
		if (heap->type == type)
		{
			block = heap->block;
			while (block != NULL)
			{
				if (block->free == 1 && block->size >= size)
				{
					block->free = 0;
					heap->free_size -= size;
					heap->used_size += size;
					split_block(block, size, heap);
					return (block);
				}
				block = block->next;
			}
		}
		heap = heap->next;
	}
	return (NULL);
}
