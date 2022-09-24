#include <stdio.h>

#include "toml/parser.h"

int main()
{
    toml_map_t map = toml_parse("res/config.toml");
    toml_map_destroy(map);

    return 0;
}
