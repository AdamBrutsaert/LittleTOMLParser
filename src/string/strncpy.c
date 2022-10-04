#include "toml/string.h"

char *toml_strncpy(char *dest, char const *src, size_t n)
{
    size_t i = 0;

    for (; src[i] && i < n; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
