#include "toml/parser.h"

static toml_float_t toml_pow(toml_float_t nb, toml_float_t p)
{
    toml_float_t power = 1;
    toml_float_t temp;

    if (p < 0 || (!nb && p))
        return 0;
    for (; p; p--) {
        temp = power * nb;
        if (power != temp / nb)
            return 0;
        power = temp;
    }
    return power;
}

toml_float_t toml_parser_parse_float(toml_token_t token)
{
    // TODO check overflow
    char *str = token.buffer;
    char sign = 1;
    toml_float_t number = 0;

    for (; *str == '+' || *str == '-'; str++) {
        if (*str == '-')
            sign *= -1;
    }
    for (; *str >= '0' && *str <= '9'; str++)
        number = number * 10 + sign * (*str - '0');
    if (*str == '.') {
        size_t i = 1;
        for (str++; *str >= '0' && *str <= '9'; str++) {
            number += sign * (*str - '0') / toml_pow(10, i); 
            i++;
        }
    }
    return number;
}
