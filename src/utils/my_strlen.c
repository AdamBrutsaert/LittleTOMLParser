#include "utils/my_lib.h"

size_t my_strlen(char const *string)
{
    size_t length = 0;

    while (string[length])
        length++;
    return length;
}
