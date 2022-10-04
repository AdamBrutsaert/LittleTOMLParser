#include "toml/parser.h"

void toml_parser_parse_key_value(toml_parser_t *parser)
{
    // store the current
    toml_map_t *current = parser->current;

    // go to the correct map and retrieve key
    char *key = toml_parser_parse_key(parser);

    // equal token expected
    toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

    // for now, we expect an integer
    toml_variant_t variant = toml_parser_parse_value(parser);

    // set in the map
    toml_map_set(parser->current, key, variant);

    // return to the previous map
    parser->current = current;

    // delete token until next line or end of the file
    while (!toml_tokenizer_end(parser->tokenizer)) {
        toml_token_type_t type = toml_tokenizer_peek(parser->tokenizer, 0).type; 
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

        if (type == TOML_TOKEN_TYPE_NEWLINE)
            break;
    }
}
