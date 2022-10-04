#include "toml/parser.h"

#include <stdio.h>

static void parse_header(toml_parser_t *parser)
{
    
}

toml_map_t *toml_parser_parse_file(char const *filename)
{
    toml_file_reader_t *file_reader = toml_file_reader_create(filename, 256);

    toml_parser_t parser;
    parser.tokenizer = toml_tokenizer_create(file_reader, 16);
    parser.root = toml_map_create();
    parser.current = parser.root;
    
    while (!toml_tokenizer_end(parser.tokenizer)) {
        toml_token_t token = toml_tokenizer_next(parser.tokenizer);
        toml_token_print(token);
        toml_token_destroy(token);
    }
    
    toml_tokenizer_destroy(parser.tokenizer);
    toml_file_reader_destroy(file_reader);

    return parser.root;
}
