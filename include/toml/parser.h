#pragma once

#include "toml/tokenizer.h"
#include "map.h"

typedef struct toml_parser {
    toml_tokenizer_t *tokenizer;
    toml_map_t *root;
    toml_map_t *current;
} toml_parser_t;

toml_map_t *toml_parser_parse_file(char const *filename);

toml_integer_t toml_parser_parse_integer(toml_token_t token);
toml_float_t toml_parser_parse_float(toml_token_t token);
toml_string_t toml_parser_parse_string(toml_token_t token);