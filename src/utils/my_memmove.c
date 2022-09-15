#include "utils/my_lib.h"

void *my_memmove(void *dest, void const *src, size_t n)
{
    if (src >= dest) {
        for (size_t i = 0; i < n; i++)
            ((char *)dest)[i] = ((char const *)src)[i];
    } else if (n > 0) {
        for (size_t i = n - 1; i > 0; i--)
            ((char *)dest)[i] = ((char const *)src)[i];
        ((char *)dest)[0] = ((char const *)src)[0];
    }
    return dest;
}
