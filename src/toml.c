#include "toml/toml.h"

#include "toml/parser.h"

toml_map_t *toml_parse_file(char const *filename)
{
    return toml_parser_parse_file(filename);
}
