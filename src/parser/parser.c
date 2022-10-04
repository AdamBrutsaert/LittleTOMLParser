#include "toml/parser.h"

#include <stdio.h>

toml_map_t *toml_parser_parse_file(char const *filename)
{
    toml_file_reader_t *file_reader = toml_file_reader_create(filename, 256);

    toml_parser_t parser;
    parser.tokenizer = toml_tokenizer_create(file_reader, 16);
    parser.root = toml_map_create();
    parser.current = parser.root;
    
    while (!toml_tokenizer_end(parser.tokenizer)) {
        toml_token_t token = toml_tokenizer_peek(parser.tokenizer, 0);
        
        if (token.type == TOML_TOKEN_TYPE_LBRACKET)
            toml_parser_parse_header(&parser);
        else if (token.type == TOML_TOKEN_TYPE_STRING)
            toml_parser_parse_key_value(&parser);
        else
            // if we are here it means it is an unexpected token
            while (!toml_tokenizer_end(parser.tokenizer)) {
                toml_token_type_t type = toml_tokenizer_peek(parser.tokenizer, 0).type; 
                toml_token_destroy(toml_tokenizer_next(parser.tokenizer));

                if (type == TOML_TOKEN_TYPE_NEWLINE)
                    break;
            }
    }
    
    toml_tokenizer_destroy(parser.tokenizer);
    toml_file_reader_destroy(file_reader);

    return parser.root;
}
