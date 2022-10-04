#include "toml/parser.h"

#include "toml/string.h"

toml_boolean_t toml_parser_parse_boolean(toml_token_t token)
{
    if (toml_strlen(token.buffer) == 4
        && token.buffer[0] == 't'
        && token.buffer[1] == 'r'
        && token.buffer[2] == 'u'
        && token.buffer[3] == 'e')
        return true;
    return false;
}