#include "toml/parser.h"

#include <stdlib.h>

#include "toml/string.h"

toml_string_t toml_parser_parse_string(toml_token_t token)
{
    size_t length = toml_strlen(token.buffer);
    size_t new_length = 0;
    toml_boolean_t double_quote = token.buffer[0] == '"';
    toml_boolean_t single_quote = token.buffer[0] == '\'';

    for (size_t i = double_quote || single_quote; i < length; i++) {
        if (double_quote && token.buffer[i] == '"')
            break;
        if (single_quote && token.buffer[i] == '\'')
            break;
        new_length++;
    }

    char *string = malloc((new_length + 1) * sizeof(char));
    toml_strncpy(string, token.buffer + (double_quote || single_quote), new_length);
    string[new_length] = '\0';

    return string;
}
