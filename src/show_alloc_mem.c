#include "../includes/malloc.h"

void print_hex(size_t n)
{
	char *hex = "0123456789ABCDEF";
	if (n >= 16)
		print_hex(n / 16);
	ft_putchar_fd(hex[n % 16], 1);
}

void dump_hex_block()
{
	pthread_mutex_lock(&g_mutex);
	t_heap *heap = g_heap_list;
	t_block *block;
	while (heap != NULL)
	{
		block = heap->block;
		while (block != NULL)
		{
			if (block->free == 0)
			{
				size_t size = block->size;
				size_t i = 0;
				void *ptr = BLOCK_SHIFT(block);
				ft_putstr_fd("Block content: ", 1);
				while (i < size)
				{
					print_hex(*(unsigned char*)(ptr + i));
					ft_putstr_fd(" ", 1);
					i++;
				}
				ft_putstr_fd("\n", 1);
			}
			block = block->next;
		}
		heap = heap->next;
	}
	pthread_mutex_unlock(&g_mutex);
}

void show_alloc_mem()
{
	size_t total = 0;
	pthread_mutex_lock(&g_mutex);
	t_heap *heap = g_heap_list;
	t_block *block;
	while (heap != NULL)
	{
		ft_putstr_fd(heap->type == TINY ? "TINY" : heap->type == SMALL ? "SMALL" : "LARGE", 1);
		ft_putstr_fd(" : 0x", 1);
		print_hex((size_t)heap);
		ft_putstr_fd("\n", 1);
		block = heap->block;
		while (block != NULL)
		{
			if (block->free == 0)
			{
				ft_putstr_fd("0x", 1);
				print_hex((size_t)BLOCK_SHIFT(block));
				ft_putstr_fd(" - ", 1);
				ft_putstr_fd("0x", 1);
				print_hex((size_t)BLOCK_SHIFT(block) + block->size);
				ft_putstr_fd(" : ", 1);
				ft_putnbr_fd(block->size, 1);
				ft_putstr_fd(" bytes\n", 1);
			}
			block = block->next;
		}
		total += heap->used_size;
		heap = heap->next;
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(total, 1);
	ft_putstr_fd(" bytes\n", 1);
	pthread_mutex_unlock(&g_mutex);
}
