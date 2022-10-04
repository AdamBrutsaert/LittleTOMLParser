#pragma once

#include <stddef.h>

size_t toml_strhash(char const *string);
size_t toml_strlen(char const *string);

int toml_strcmp(char const *s1, char const *s2);

char *toml_strcpy(char *dest, char const *src);
char *toml_strncpy(char *dest, char const *src, size_t n);

char *toml_strdup(char const *string);
