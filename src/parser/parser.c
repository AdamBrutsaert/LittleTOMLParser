#include "toml/parser.h"

#include <stdio.h>

static void parse_header(toml_parser_t *parser)
{
    // TODO check whenever I do next if we reached end or if it is the expected token
    toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

    toml_token_t token = toml_tokenizer_next(parser->tokenizer);
    toml_string_t string = toml_parser_parse_string(token);
    toml_token_destroy(token);

    if (!(toml_map_exists(parser->current, string) && toml_map_get_type(parser->current, string) == TOML_TYPE_MAP))
        toml_map_set_map(parser->current, string, toml_map_create());

    parser->current = toml_map_get_map(parser->current, string);

    while (toml_tokenizer_peek(parser->tokenizer, 0).type == TOML_TOKEN_TYPE_DOT) {
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

        token = toml_tokenizer_next(parser->tokenizer);
        string = toml_parser_parse_string(token);
        toml_token_destroy(token);

        if (!(toml_map_exists(parser->current, string) && toml_map_get_type(parser->current, string) == TOML_TYPE_MAP))
            toml_map_set_map(parser->current, string, toml_map_create());

        parser->current = toml_map_get_map(parser->current, string);
    }

    while (!toml_tokenizer_end(parser->tokenizer)) {
        toml_token_type_t type = toml_tokenizer_peek(parser->tokenizer, 0).type; 
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

        if (type == TOML_TOKEN_TYPE_NEWLINE)
            break;
    }
}

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
            parse_header(&parser);
        else
            toml_token_destroy(toml_tokenizer_next(parser.tokenizer));
    }
    
    toml_tokenizer_destroy(parser.tokenizer);
    toml_file_reader_destroy(file_reader);

    return parser.root;
}
