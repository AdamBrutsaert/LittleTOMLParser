#include "utils/my_lib.h"

// djb2 hash
size_t my_strhash(char const *string)
{
    size_t hash = 5381;

    for (; *string; string++)
        hash = ((hash << 5) + hash) + *string;
    return hash;
}
