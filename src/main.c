#include <stdio.h>

#include "reader/toml_reader.h"

int main()
{
    toml_reader_t reader = toml_reader_create("res/config.toml");

    while (!toml_reader_reached_end(reader)) {
        char c = toml_reader_next(reader);
        size_t line = toml_reader_get_line(reader);
        size_t column = toml_reader_get_column(reader);
        printf("[%lu:%lu] %c\n", line, column, c);
    }

    toml_reader_destroy(reader);

    return 0;
}
