#include "toml/parser.h"

#include "toml/string.h"
#include "toml/array.h"
#include "toml/map.h"

static toml_type_t detect_type(toml_token_t token)
{
    if (token.type == TOML_TOKEN_TYPE_LBRACKET)
        return TOML_TYPE_ARRAY;

    if (token.type == TOML_TOKEN_TYPE_LBRACE)
        return TOML_TYPE_MAP;

    if (token.buffer[0] == '"' || token.buffer[0] == '\'')
        return TOML_TYPE_STRING;

    if (token.buffer[0] >= '0' && token.buffer[0] <= '9') {
        for (char *ptr = token.buffer; *ptr; ptr++)
            if (*ptr == '.')
                return TOML_TYPE_FLOAT;
        return TOML_TYPE_INTEGER;
    }

    return TOML_TYPE_BOOLEAN;
}

static toml_array_t *parse_array(toml_parser_t *parser)
{
    toml_array_t *array = toml_array_create();

    // next is a value
    toml_variant_t variant = toml_parser_parse_value(parser);
    toml_array_push_variant(array, variant);

    // next is either a comma followed by a value, or ] token
    while (toml_tokenizer_peek(parser->tokenizer, 0).type == TOML_TOKEN_TYPE_COMMA) {
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));
        toml_array_push_variant(array, toml_parser_parse_value(parser));
    }

    return array;
}

static toml_map_t *parse_map(toml_parser_t *parser)
{
    toml_map_t *current = parser->current;
    toml_map_t *map = toml_map_create();

    char *key = toml_parser_parse_key(parser);
    toml_token_destroy(toml_tokenizer_next(parser->tokenizer));
    toml_variant_t value = toml_parser_parse_value(parser);

    toml_map_set(map, key, value);
    parser->current = current;

    while (toml_tokenizer_peek(parser->tokenizer, 0).type == TOML_TOKEN_TYPE_COMMA) {
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));

        char *key = toml_parser_parse_key(parser);
        toml_token_destroy(toml_tokenizer_next(parser->tokenizer));
        toml_variant_t value = toml_parser_parse_value(parser);

        toml_map_set(map, key, value);
        parser->current = current;
    }

    return map;
}

toml_variant_t toml_parser_parse_value(toml_parser_t *parser)
{
    toml_token_t token = toml_tokenizer_next(parser->tokenizer);
    toml_variant_t variant;

    switch(detect_type(token)) {
        case TOML_TYPE_ARRAY:
            variant = toml_variant_create_array(parse_array(parser));
            break;
        case TOML_TYPE_MAP:
            variant = toml_variant_create_map(parse_map(parser));
            break;
        case TOML_TYPE_STRING:
            variant = toml_variant_create_string(toml_parser_parse_string(token));
            break;
        case TOML_TYPE_INTEGER:
            variant = toml_variant_create_integer(toml_parser_parse_integer(token));
            break;
        case TOML_TYPE_FLOAT:
            variant = toml_variant_create_float(toml_parser_parse_float(token));
            break;
        default:
            variant = toml_variant_create_boolean(toml_parser_parse_boolean(token));
            break;
    }

    toml_token_destroy(token);

    return variant;
}