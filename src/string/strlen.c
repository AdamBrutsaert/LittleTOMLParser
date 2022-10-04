#include "toml/string.h"

size_t toml_strlen(char const *string)
{
    size_t length = 0;

    while (string[length])
        length++;
    return length;
}
