#include "../includes/malloc.h"

t_heap *g_heap_list = NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
