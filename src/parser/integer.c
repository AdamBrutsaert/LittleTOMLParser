#include "toml/parser.h"

toml_integer_t toml_parser_parse_integer(toml_token_t token)
{
    char *str = token.buffer;
    char sign = 1;
    toml_integer_t number = 0;

    for (; *str == '+' || *str == '-'; str++) {
        if (*str == '-')
            sign *= -1;
    }
    for (; *str >= '0' && *str <= '9'; str++) {
        number = number * 10 + sign * (*str - '0');
        if ((sign > 0 && number < 0) || (sign < 0 && number > 0))
            return 0;
    }
    return number;
}
