#pragma once

#include <stddef.h>

void *toml_memmove(void *dest, void const *src, size_t n);
void *toml_memset(void *s, int c, size_t n);
