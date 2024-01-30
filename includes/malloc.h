#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

#define TINY_HEAP 4 * getpagesize()
#define TINY_BLOCK TINY_HEAP / 128
#define SMALL_HEAP 32 * getpagesize()
#define SMALL_BLOCK 1024

#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

enum e_heap_type {
	TINY,
	SMALL,
	LARGE
};

typedef struct t_heap {
	struct t_heap *next;
	struct t_heap *prev;
	struct t_block *block;
	enum e_heap_type type;
	size_t total_size;
	size_t free_size;
	size_t used_size;
	size_t nb_block;
} t_heap;

typedef struct t_block {
	struct t_block *next;
	struct t_block *prev;
	size_t size;
	int free;
} t_block;

extern t_heap *g_heap_list;
extern pthread_mutex_t g_mutex;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

void dump_hex_block();

void	*create_or_append_heap(size_t size, enum e_heap_type type);
size_t	get_heap_size(size_t size);
enum e_heap_type get_type(size_t size);
t_block	*find_free_block(enum e_heap_type type, size_t size);
void block_init(t_heap *heap, size_t size);

#endif
