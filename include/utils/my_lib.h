#pragma once

#include <stddef.h>

size_t my_min_size(size_t s1, size_t s2);

void *my_memmove(void *dest, void const *src, size_t n);

size_t my_strhash(char const *string);
size_t my_strlen(char const *string);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
