#include "toml/parser.h"

char *toml_parser_parse_key(toml_parser_t *parser)
{
    toml_token_t token = toml_tokenizer_next(parser->tokenizer);
    toml_string_t string = toml_parser_parse_string(token);
    toml_token_destroy(token);

    while (toml_tokenizer_peek(parser->tokenizer, 0).type == TOML_TOKEN_TYPE_DOT) {
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

        if (!(toml_map_exists(parser->current, string) && toml_map_get_type(parser->current, string) == TOML_TYPE_MAP))
            toml_map_set_map(parser->current, string, toml_map_create());
        parser->current = toml_map_get_map(parser->current, string);

        token = toml_tokenizer_next(parser->tokenizer);
        string = toml_parser_parse_string(token);
        toml_token_destroy(token);
    }

    return string;
}