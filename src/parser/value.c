#include "toml/parser.h"

#include "toml/string.h"

static toml_type_t detect_type(toml_token_t token)
{
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

toml_variant_t toml_parser_parse_value(toml_parser_t *parser)
{
    toml_token_t token = toml_tokenizer_next(parser->tokenizer);
    toml_variant_t variant;

    switch(detect_type(token)) {
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