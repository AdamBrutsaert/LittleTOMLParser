#pragma once

#include "type.h"

typedef struct toml_file_reader toml_file_reader_t;

toml_file_reader_t *toml_file_reader_create(char const *filename, size_t capacity);
void toml_file_reader_destroy(toml_file_reader_t *file_reader);

char const *toml_file_reader_get_filename(toml_file_reader_t *file_reader);
size_t toml_file_reader_get_line(toml_file_reader_t *file_reader);
size_t toml_file_reader_get_column(toml_file_reader_t *file_reader);

char toml_file_reader_next(toml_file_reader_t *file_reader);
char toml_file_reader_peek(toml_file_reader_t *file_reader, size_t n);
toml_boolean_t toml_file_reader_end(toml_file_reader_t *file_reader);
