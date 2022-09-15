#include "utils/my_lib.h"

int my_strcmp(char const *s1, char const *s2)
{
    size_t length = my_min_size(my_strlen(s1), my_strlen(s2));

    for (size_t i = 0; i <= length; i++) {
        if (s1[i] == s2[i])
            continue;
        return s1[i] - s2[i];
    }
    return 0;
}
