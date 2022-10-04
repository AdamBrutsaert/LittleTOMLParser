#include <stdio.h>
#include <stdlib.h>

#include "toml/toml.h"
#include "toml/parser.h"
#include "toml/string.h"

int main()
{
    toml_map_t *map = toml_parse_file("res/config.toml");
    toml_map_t *general_hey = toml_map_get_map(toml_map_get_map(map, "General"), "Hey");
    toml_map_t *general_hey_my_dotted = toml_map_get_map(toml_map_get_map(general_hey, "my"), "dotted");

    printf("my_string = >>>%s<<<\n", toml_map_get_string(general_hey, "my_string"));
    printf("my_integer = >>>%lld<<<\n", toml_map_get_integer(general_hey, "my_integer"));
    printf("my_float = >>>%f<<<\n", toml_map_get_float(general_hey, "my_float"));
    printf("my_boolean = >>>%s<<<\n", toml_map_get_boolean(general_hey, "my_boolean") ? "true" : "false");
    printf("my.dotted.key = >>>%s<<<\n", toml_map_get_string(general_hey_my_dotted, "key"));

    toml_map_destroy(map);

    return 0;
}
