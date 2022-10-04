#include "toml/string.h"

#include <stdlib.h>

char *toml_strdup(char const *string)
{
    char *str = malloc((toml_strlen(string) + 1) * sizeof(char));
    toml_strcpy(str, string);
    return str;
}
