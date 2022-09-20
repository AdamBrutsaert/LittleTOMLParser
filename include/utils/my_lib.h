#pragma once

#include <stddef.h>

void *my_memmove(void *dest, void const *src, size_t n);
void *my_memset(void *s, int c, size_t n);

size_t my_strhash(char const *string);
size_t my_strlen(char const *string);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *string);
