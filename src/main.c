#include <stdio.h>
#include <stdlib.h>

#include "toml/toml.h"
#include "toml/parser.h"
#include "toml/string.h"

int main()
{
    /* toml_map_t *map = toml_parse_file("res/config.toml");
    toml_map_destroy(map); */

    /* toml_token_t token = toml_token_create_string(toml_strdup("true"), 0, 0);
    
    toml_boolean_t result = toml_parser_parse_boolean(token);
    printf("Result: >>>%s<<<\n", result ? "true" : "false");

    toml_token_destroy(token); */

    toml_map_t *map = toml_map_create();

    toml_map_set_float(map, toml_strdup("test"), 3204.5);

    printf("'test' exists : %d\n", toml_map_exists(map, "test"));
    printf("'key' exists : %d\n", toml_map_exists(map, "key"));

    toml_map_destroy(map);

    return 0;
}
