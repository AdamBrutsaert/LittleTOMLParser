#include "utils/my_lib.h"

#include <stdlib.h>

char *my_strdup(char const *string)
{
    char *str = malloc((my_strlen(string) + 1) * sizeof(char));
    my_strcpy(str, string);
    return str;
}
