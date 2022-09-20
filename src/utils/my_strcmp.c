#include "utils/my_lib.h"

static size_t min(size_t a, size_t b)
{
    return a < b ? a : b;
}

int my_strcmp(char const *s1, char const *s2)
{
    size_t length = min(my_strlen(s1), my_strlen(s2));

    for (size_t i = 0; i <= length; i++) {
        if (s1[i] == s2[i])
            continue;
        return s1[i] - s2[i];
    }
    return 0;
}
