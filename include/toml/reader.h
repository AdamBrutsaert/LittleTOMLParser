#pragma once

#include "type.h"

typedef struct toml_reader *toml_reader_t;

toml_reader_t toml_reader_create(char const *filename);
void toml_reader_destroy(toml_reader_t reader);

char const *toml_reader_get_filename(toml_reader_t reader);
size_t toml_reader_get_line(toml_reader_t reader);
size_t toml_reader_get_column(toml_reader_t reader);
toml_boolean_t toml_reader_reached_end(toml_reader_t reader);

char toml_reader_next(toml_reader_t reader);
char toml_reader_peek(toml_reader_t reader, size_t offset);
